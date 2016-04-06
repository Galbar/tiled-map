#ifndef TILED_OBJECTLAYER_HPP
#define TILED_OBJECTLAYER_HPP
#include <vector>
#include "Layer.hpp"
#include "Color.hpp"

namespace tiled
{
class Object;
class ObjectLayer : public Layer
{
public:
    enum class DrawOrder { INDEX, TOPDOWN, COUNT };
    ObjectLayer();
    virtual ~ObjectLayer();

    void setDrawOrder(DrawOrder draw_order);
    DrawOrder getDrawOrder() const;

    void setColor(const Color& color);
    const Color& getColor() const;

    void setObjects(const std::vector<Object*>& Objects);
    std::vector<Object*>& getObjects();
    const std::vector<Object*>& getObjects() const;

private:
    DrawOrder p_draw_order;
    Color p_color;
    std::vector<Object*> p_objects;
};
}
#endif
