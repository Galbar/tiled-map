#ifndef TILED_LAYER_HPP
#define TILED_LAYER_HPP
#include <string>
#include <unordered_map>

namespace tiled
{
class Layer
{
public:
    enum class LayerType { TILE_LAYER, IMAGE_LAYER, OBJECT_LAYER, COUNT };

    void setWidth(int width);
    int getWidth() const;

    void setHeight(int height);
    int getHeight() const;

    void setX(int x);
    int getX() const;

    void setY(int y);
    int getY() const;

    void setOffsetX(int offset_x);
    int getOffsetX() const;

    void setOffsetY(int offset_y);
    int getOffsetY() const;

    void setVisibility(bool visibility);
    bool getVisibility() const;

    void setOpacity(float opacity);
    float getOpacity() const;

    void setType(LayerType type);
    LayerType getType() const;

    void setName(const std::string& name);
    const std::string& getName() const;

    void setProperties(const std::unordered_map<std::string, std::string>& properties);
    std::unordered_map<std::string, std::string>& getProperties();
    const std::unordered_map<std::string, std::string>& getProperties() const;


protected:
    LayerType p_type;

private:
    int p_x,
        p_y,
        p_width,
        p_height,
        p_offset_x,
        p_offset_y;
    bool p_visibility;
    float p_opacity;
    std::string p_name;
    std::unordered_map<std::string, std::string> p_properties;
};
} /* tiled */

#endif /* ifndef TILED_MAP_HPP */
