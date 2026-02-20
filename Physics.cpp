#include "Physics.hpp"

#include <iostream>
#include <random>

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

// Добавлена работа с частицами
void Physics::update(std::vector<Ball>& balls, std::vector<Dust>& dusts, const size_t ticks) const {
    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        collideWithBox(balls);
        collideBalls(balls, dusts); // Передаем dusts для создания частиц при ударах

        // Обновляем все существующие частицы
        for (auto& dust : dusts) {
            dust.update(timePerTick);
        }

        // Удаляем новые частицы
        dusts.erase(std::remove_if(dusts.begin(), dusts.end(),
            [](const Dust& d) { return !d.isAlive(); }), dusts.end());
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dusts) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        for (auto b = std::next(a); b != balls.end(); ++b) {
            if (!a->isCollidable() || !b->isCollidable()) {
                continue;
            }
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2) {
                processCollision(*a, *b, dusts, distanceBetweenCenters2);
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        if (!ball.isCollidable()) { continue; }
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        }
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b, std::vector<Dust>& dusts,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));

    // создаем частицы при столкновении
    const Point collissionPoint = (a.getCenter() + b.getCenter()) * 0.5;
    const double baseSpeed = std::sqrt(dot(aV, aV)) + std::sqrt(dot(bV, bV));

    // создаем 10-20 часиц
    const int dustCount = 10 + rand() % 10;
    for (int i = 0; i < dustCount; ++i) {
        Velocity dustVel = randomVelocity(baseSpeed * 0.5);
        double lifetime = 0.5 * (rand() % 10) * 0.2;

        dusts.emplace_back(collissionPoint, dustVel, lifetime);
    }
}

// Генератор случайных частиц
Velocity Physics::randomVelocity(double baseSpeed) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> angleDist(0, 2 * M_PI);
    static std::uniform_real_distribution<> speedDist(0, 1.5);

    double angle = angleDist(gen);
    double speed = baseSpeed * speedDist(gen);

    return Velocity(speed, angle);
}