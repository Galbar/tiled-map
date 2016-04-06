#ifndef TILED_OBJECT_HPP
#define TILED_OBJECT_HPP
#include <string>
#include <unordered_map>
#include <vector>
#include "WithProperties.hpp"
#include "Point.hpp"


namespace tiled
{
class Object : public priv::WithProperties
{
public:
    enum class Shape { RECTANGLE, ELLIPSE, POLYGON, POLYLINE, COUNT };
    Object();
    virtual ~Object();

    void setX(int x);
    int getX() const;

    void setY(int y);
    int getY() const;

    void setGId(int g_id);
    int getGId() const;

    void setWidth(int width);
    int getWidth() const;

    void setHeight(int height);
    int getHeight() const;

    void setVisibility(bool visibility);
    const bool getVisibility() const;

    void setRotation(float rotation);
    float getRotation() const;

    void setShape(Shape shape);
    Shape getShape() const;

    void setName(const std::string& name);
    const std::string& getName() const;

    void setPoints(const std::vector<Point>& points);
    std::vector<Point>& getPoints();
    const std::vector<Point>& getPoints() const;

    void setType(const std::string& type);
    const std::string& getType() const;

private:
    int p_width,
        p_height,
        p_x,
        p_y,
        p_g_id;
    bool p_visibility;
    float p_rotation;
    Shape p_shape;
    std::vector<Point> p_points;
    std::string p_name, p_type;
};
} /* tiled */

#endif /* ifndef TILED_MAP_HPP */
