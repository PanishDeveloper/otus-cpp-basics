#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include "Color.hpp"

class Ball {
public:
    Ball(const Point& center, const Velocity& velocity, double radius, const Color& color, bool isCollidable)
        : center_(center), velocity_(velocity), radius_(radius), color_(color), isCollidable_(isCollidable) {}

    void setVelocity(const Velocity& velocity);
    [[nodiscard]]Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    [[nodiscard]]Point getCenter() const;
    [[nodiscard]]double getRadius() const;
    [[nodiscard]]double getMass() const;

    [[nodiscard]]bool isCollidable() const { return isCollidable_; }
    void setCollidable(bool collidable) { isCollidable_ = collidable; }

private:
    Point center_;
    Velocity velocity_;
    double radius_ = 0.0;
    Color color_;
    bool isCollidable_ = true;
};
