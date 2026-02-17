#pragma once
#include "Ball.hpp"
#include "Dust.hpp"
#include <vector>

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, std::vector<Dust>& dusts, size_t ticks) const;

  private:
    // Добавлен параметр dusts во все методы, сязанные с коллизиями
    void collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dusts) const;
    void collideWithBox(std::vector<Ball>& balls) const;
    void move(std::vector<Ball>& balls) const;
    void processCollision(Ball& a, Ball& b, std::vector<Dust>& dusts,
                          double distanceBetweenCenters2) const;
    static Velocity randomVelocity(double baseSpeed);

  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
};
