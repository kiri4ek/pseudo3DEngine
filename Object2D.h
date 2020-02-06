//
// Created by ivan- on 18.01.2020.
//

#ifndef PSEUDO3DENGINE_OBJECT2D_H
#define PSEUDO3DENGINE_OBJECT2D_H

#include <utility>
#include <vector>
#include <cmath>
#include "Idrawable.h"
#include "settings.h"

struct Point2D {
    double x = 0;
    double y = 0;

    Point2D& operator+=(const Point2D& point2D) { this->x += point2D.x; this->y += point2D.y; }
    Point2D& operator=(const Point2D& point2D) { this->x = point2D.x; this->y = point2D.y; return *this; }
    Point2D& operator*(double number) { this->x *= number; this->y *= number; }
    Point2D operator-(const Point2D& point2D) const { return {this->x - point2D.x, this->y - point2D.y}; }
    Point2D operator+(const Point2D& point2D) const { return {this->x + point2D.x, this->y + point2D.y}; }

    Point2D normalize() { return Point2D{this->x/abs(), this->y/abs()};}
    double abs() {return sqrt(x*x + y*y); }
};

class Object2D : virtual public Idrawable {
private:
    std::vector<Point2D> v_points2D;

    Point2D p_position;
    Point2D p_velocity;

    std::string s_name;

    sf::Texture T_texture;
    std::string s_texture;
    bool texture_loaded = false;
public:
    Object2D(Point2D position = {0, 0}, std::vector<Point2D> points = {}, std::string texture = WALL_TEXTURE, Point2D velocity = {0, 0})
    : p_position(position), v_points2D(points), p_velocity(velocity),  s_texture(std::move(texture)) {}

    const double x() { return p_position.x; }
    const double y() { return p_position.y; }

    void setPosition(Point2D position) { p_position = position; };

    void shift(Point2D vector) { p_position += vector; }

    std::vector<Point2D>& nodes() { return v_points2D; }

    static bool segments_crossing(std::pair<Point2D, Point2D> segment1, std::pair<Point2D, Point2D> segment2, Point2D& point);

    void setName(std::string name) {s_name = name;}
    std::string getName() { return s_name; }

    const Point2D position() { return p_position; }

    void draw(sf::RenderWindow& window) override;

    sf::Texture& loadTexture() {
        if(texture_loaded) return T_texture;
        texture_loaded = true;
        if (!T_texture.loadFromFile(s_texture)) {
            texture_loaded = false;
        }
        T_texture.setRepeated(true);
        return T_texture;
    }
};


#endif //PSEUDO3DENGINE_OBJECT2D_H