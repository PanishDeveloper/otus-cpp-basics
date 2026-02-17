#pragma once
#include "Point.hpp"
#include "Velocity.hpp"
#include "Color.hpp"
#include "Painter.hpp"

class Dust {
public:
    Dust(const Point& center, const Velocity& velocity, double lifetime)
    : center_(center), velocity_(velocity), lifetime_(lifetime) {}

    void update(double timePerTick);
    void draw(Painter& painter) const;
    [[nodiscard]]bool isAlive() const;

private:
    Point center_;
    Velocity velocity_;
    double lifetime_;
    static constexpr double SIZE = 5.0;
    static const Color COLOR;
};
