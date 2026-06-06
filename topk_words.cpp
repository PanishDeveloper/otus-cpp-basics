// Read files and prints top k word by frequency

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <unordered_map>
//#include <map>
#include <thread>
#include <vector>
#include <chrono>
#include <future>

constexpr size_t TOPK = 10;

// Realization for unordered_map
using Counter = std::unordered_map<std::string, std::size_t>;

// // Realization for map
// using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string &str);

// Proccess a list of files and return a local counter
Counter count_files (const std::vector<std::string>& filenames);

// Merges several local counres into one global counter
Counter merge_counters (const std::vector<Counter>& counters);

void count_words(std::istream& stream, Counter&);

// Rewritten
void print_topk(std::ostream& stream, const Counter&, size_t k);

// function that performs all the multithreading processing
Counter run_parallel_count(const std::vector<std::string>& files);



int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    std::vector<std::string> files(argv +1, argv + argc);
    auto start = std::chrono::high_resolution_clock::now();

    Counter global;
    try
    {
        global = run_parallel_count(files);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    print_topk(std::cout, global, TOPK);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time (multithreaded) is " << elapsed_ms.count() << " us\n";
}



std::string tolower(const std::string &str) {
    std::string lower_str;
    lower_str.reserve(str.size());
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });    
}

Counter count_files (const std::vector<std::string>& filenames)
{
    Counter local_counter;

    for (const auto& fname : filenames)
    {
        std::ifstream input{fname};

        if (!input.is_open())
            throw std::runtime_error("Failed to open file " + fname + "\n");

        count_words(input, local_counter);
    }

    return local_counter;
}

// Realization for unordered_map
Counter merge_counters (const std::vector<Counter>& counters)
{
    Counter global;

    for (const auto& local : counters)
    {
        for (const auto& [word, cnt] : local)
            global[word] += cnt;
    }

    return global;
}

// // Realization for map
// Counter merge_counters (const std::vector<Counter>& counters)
// {
//     if (counters.empty()) return counters[0];
//     if (counters.size() == 1) return counters[0];
//
//     std::vector<Counter::const_iterator> iters;
//     std::vector<Counter::const_iterator> ends;
//     for (const auto& c : counters)
//     {
//         iters.emplace_back(c.begin());
//         ends.emplace_back(c.end());
//     }
//
//     Counter result;
//     while (true)
//     {
//         Counter::const_iterator* min_it = nullptr;
//         std::string min_key;
//         for (size_t i = 0; i < iters.size(); ++i)
//         {
//             if (iters[i] == ends[i]) continue;
//             if (!min_it || iters[i]->first < min_key)
//             {
//                 min_it = &iters[i];
//                 min_key = iters[i]->first;
//             }
//         }
//         if (!min_it) break;
//
//         std::size_t total = 0;
//         for (size_t i = 0; i < iters.size(); ++i)
//         {
//             if (iters[i] != ends[i] && iters[i]->first == min_key)
//             {
//                 total += iters[i]->second;
//                 ++iters[i];
//             }
//         }
//
//         result.insert(result.end(), {min_key, total});
//     }
//
//     return result;
// }

void print_topk(std::ostream& stream, const Counter& counter, size_t k) {
    std::vector<std::pair<std::string, std::size_t>> words(counter.begin(), counter.end());

    std::partial_sort(
        words.begin(), words.begin() + std::min(k, words.size()), words.end(),
        [] (const auto& a, const auto& b) { return a.second > b.second; });

    for (size_t i = 0; i < std::min(k, words.size()); ++i)
        stream << std::setw(4) << words[i].second << ' ' << words[i].first << '\n';
}

Counter run_parallel_count(const std::vector<std::string>& files)
{
    // Determine number of hardware threads
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0)  num_threads = 2;
    if (files.size() < num_threads) num_threads = static_cast<unsigned int>(files.size());
    if (num_threads == 0)  num_threads = 1;

    // Split files into blocks - each block will be proccessed by one thread
    std::vector<std::vector<std::string>> file_blocks(num_threads);
    for (size_t i = 0; i < files.size(); ++i)
        file_blocks[i % num_threads].emplace_back(files[i]);

    // Launch threads using std::async
    std::vector<std::future<Counter>> futures;
    for (const auto& block : file_blocks)
    {
        if (block.empty()) continue;

        futures.emplace_back(std::async(std::launch::async,count_files, block));
    }

    std::vector<Counter> local_counters;

    local_counters.reserve(futures.size());
    for (auto& fut : futures)
        local_counters.emplace_back(fut.get());

    return merge_counters(local_counters);
}