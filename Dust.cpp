#include "Dust.hpp"
#include "Painter.hpp"
#include <random>

const Color Dust::COLOR{1.0, 0.8, 0.2};

/**
 * Обновляет состояние частицы
 * @param timePerTick - время одного тика симуляции
 */
void Dust::update(double timePerTick) {
    center_ = center_ + velocity_.vector() * timePerTick;
    lifetime_ -= timePerTick;
}

/**
 * Отрисовывает частицу
 * @param painter - контекст отрисовки
 */
void Dust::draw(Painter& painter) const {
    double alpha = std::min(1.0, lifetime_ * 5.0);
    Color fadeColor(COLOR.red() * alpha, COLOR.green() * alpha, COLOR.blue() * alpha);
    painter.draw(center_, SIZE, fadeColor);
}

/**
 * Проверяет жива ли еще частица
 * @return true если время жихни > 0
 */
bool Dust::isAlive() const { return lifetime_ > 0; }