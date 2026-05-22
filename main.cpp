#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

#include "CRC32.hpp"
#include "IO.hpp"

/**
 * @brief Замеряет время перебора CRC32 в указанном числе потоков
 * @param prefixCrc Инвертированный CRC32 префикса файла
 * @param numHushes Количество пробных итераций
 * @param numThreads Число потоков для теста
 * @return Время выполнения в миллисекундах
 */
double measureTime(uint32_t prefixCrc, size_t numHushes, unsigned numThreads)
{
  auto worker = [&](size_t start, size_t end)
  {
    auto tailValue = static_cast<uint32_t>(start);

    for (size_t i = start; i < end; ++i)
    {
      tailValue = static_cast<uint32_t>(i);
      crc32(reinterpret_cast<const char *>(&tailValue), 4, prefixCrc);
    }
  };

  auto startTime = std::chrono::steady_clock::now();

  std::vector<std::thread> threads;
  size_t chunkSize = numHushes / numThreads;
  for (unsigned t = 0; t < numThreads; ++t)
  {
    size_t start = t * chunkSize;
    size_t end = (t == numThreads - 1) ? numHushes : start + chunkSize;
    threads.emplace_back(worker, start, end);
  }
  for (auto &th : threads) th.join();

  auto endTime = std::chrono::steady_clock::now();

  return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}

/**
 * @brief Подбирает оптимальное число потоков пробным прогоном
 * @details Последовательно тестирует 1, 2, 4... потоков на 500 000 итераций
 *          и выбирает вариант с наименьшим временем выполнения
 * @param prefixCrc Инвертированный CRC32 префикса файла
 * @return Оптимальное число потоков
 */
unsigned findOptimalThreadCount(uint32_t prefixCrc)
{
  const unsigned maxThreads = std::thread::hardware_concurrency();
  if (maxThreads <= 1) return 1;
  constexpr size_t testHashes = 1000000;

  std::cout << "=== Dynamic thread count calibration ===\n";

  double bestTime = std::numeric_limits<double>::max();
  unsigned bestCount = 1;

  for (unsigned count = 1; count <= maxThreads; count *= 2)
  {
    double time = measureTime(prefixCrc, testHashes, count);
    double speed = testHashes / time;
    std::cout << "  " << count << " thread(s): " << time << " ms (" << speed << " hashes/ms)\n";

    if (time < bestTime)
    {
      bestTime = time;
      bestCount = count;
    }
  }

  if (maxThreads != bestCount && (maxThreads & (maxThreads - 1)) != 0)
  {
    double time = measureTime(prefixCrc, testHashes, maxThreads);
    double speed = testHashes / time;
    std::cout << "  " << maxThreads << " thread(s): " << time << " ms (" << speed << " hashes/ms)\n";

    if (time < bestTime)
      bestCount = maxThreads;
  }

  std::cout << "Optimal thread count: " << bestCount << "\n";
  std::cout << "========================================\n";

  return bestCount;
}

/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального,
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального вектора совпадали
 * @param original Оригинальный вектор
 * @param injection Произвольная строка, которая будет добавлена после данных оригинального вектора
 * @return Новый вектор
 */

std::vector<char> hack(const std::vector<char> &original,
                       const std::string &injection) {
  const uint32_t originalCrc32 = crc32(original.data(), original.size());

  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);
  
  // Вычисляем CRC32 префикса (original + injection) один раз и инвертируем
  uint32_t prefixCrc = ~crc32(result.data(), original.size() + injection.size());

  // Вычисляем offset один раз
  const size_t offset = original.size() + injection.size();
  constexpr auto maxVal = static_cast<size_t>(std::numeric_limits<uint32_t>::max()) + 1;

  // Определяем оптимальное число потоков
  unsigned numThreads = findOptimalThreadCount(prefixCrc);

  std::atomic<bool> found{false};
  std::atomic<uint32_t> solution{0};
  std::mutex mtx;

  auto worker = [&](size_t start, size_t end)
  {
    auto tailValue = static_cast<uint32_t>(start);
    char tailBuffer[4];

    // Перебираем свой поддиапазон, выходим если другой поток нашёл
    for (size_t i = start; i < end && !found.load(); ++i)
    {
      tailValue = static_cast<uint32_t>(i);

      std::copy_n(reinterpret_cast<const char*>(&tailValue), 4, tailBuffer);

      // Считаем CRC32 только для последних 4 байт с учётом префикса
      auto currentCrc32 = crc32(tailBuffer, 4, prefixCrc);
      if (currentCrc32 == originalCrc32)
      {
        bool expected = false;
        // Атомарно записываем решение, только если еще не найдено
        if (found.compare_exchange_strong(expected, true))
        {
          solution.store(static_cast<uint32_t>(i));
        }
        return;
      }

      // Прогресс раз в 10 миллионов итераций
      if (i % 10000000 == 0) {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "progress: " << static_cast<double>(i) / static_cast<double>(maxVal) << std::endl;
      }
     }
  };

  // Запускаем потоки каждый со своим поддиапазоном
  std::vector<std::thread> threads;
  size_t chunkSize = maxVal / numThreads;

  auto overallStart = std::chrono::steady_clock::now();

  for (unsigned t = 0; t < numThreads; ++t)
  {
    size_t start = t * chunkSize;
    size_t end = (t == numThreads - 1) ? maxVal : start + chunkSize;

    threads.emplace_back(worker, start, end);
  }

  // Ждем завершения всех потоков
  for (auto &th : threads)
    if (th.joinable()) th.join();

  auto overallEnd = std::chrono::steady_clock::now();
  auto elapsed = std::chrono::duration<double>(overallEnd - overallStart).count();

  // Проверяем нашли ли ответ
  if (found.load())
  {
    std::cout << "Success in " << elapsed << " seconds.\n";
    uint32_t sol = solution.load();
    std::copy_n(reinterpret_cast<const char*>(&sol), 4, result.data() + offset);
    return result;
  }

  // Если не нашли - ошибка
  throw std::logic_error("Can't hack");
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Call with two args: " << argv[0]
              << " <input file> <output file>\n";
    return 1;
  }

  try {
    const std::vector<char> data = readFromFile(argv[1]);
    const std::vector<char> badData = hack(data, "He-he-he");
    writeToFile(argv[2], badData);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << '\n';
    return 2;
  }
  return 0;
}
