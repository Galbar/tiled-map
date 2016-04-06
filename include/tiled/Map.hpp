#ifndef TILED_MAP_HPP
#define TILED_MAP_HPP
#include <string>
#include <vector>
#include <unordered_map>
#include "Color.hpp"
#include "WithProperties.hpp"

namespace tiled
{
class Layer;
class TileLayer;
class ImageLayer;
class ObjectLayer;
class Tileset;
class Map : public priv::WithProperties
{
public:
    enum class Orientation { ORTHOGONAL, ISOMETRIC, STAGGERED, HEXAGONAL, COUNT };
    enum class RenderOrder { RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP, COUNT };
    enum class StaggerAxis { NONE, X, Y, COUNT };
    enum class StaggerIndex { NONE, ODD, EVEN, COUNT };
    Map();
    virtual ~Map();

    int findTilesetIndex(int gid) const;

    void setVersion(const std::string& version);
    const std::string& getVersion() const;

    void setTiledVersion(const std::string& version);
    const std::string& getTiledVersion() const;

    void setOrientation(Orientation orientation);
    Orientation getOrientation() const;

    void setRenderOrder(RenderOrder render_order);
    RenderOrder getRenderOrder() const;

    void setWidth(int width);
    int getWidth() const;

    void setHeight(int height);
    int getHeight() const;

    void setTileWidth(int tile_width);
    int getTileWidth() const;

    void setTileHeight(int tile_height);
    int getTileHeight() const;

    void setHexSideLength(int hex_side_length);
    int getHexSideLength() const;

    void setStaggerAxis(StaggerAxis stagger_axis);
    StaggerAxis getStaggerAxis() const;

    void setStaggerIndex(StaggerIndex stagger_index);
    StaggerIndex getStaggerIndex() const;

    void setBackgroundColor(const Color& background_color);
    const Color& getBackgroundColor() const;

    void setNextObjectId(int next_object_id);
    int getNextObjectId() const;

    void setLayers(const std::vector<Layer*>& layers);
    std::vector<Layer*>& getLayers();
    const std::vector<Layer*>& getLayers() const;

    void setTileLayers(const std::vector<TileLayer*>& tilelayers);
    std::vector<TileLayer*>& getTileLayers();
    const std::vector<TileLayer*>& getTileLayers() const;

    void setImageLayers(const std::vector<ImageLayer*>& tmagelayers);
    std::vector<ImageLayer*>& getImageLayers();
    const std::vector<ImageLayer*>& getImageLayers() const;

    void setObjectLayers(const std::vector<ObjectLayer*>& objectlayers);
    std::vector<ObjectLayer*>& getObjectLayers();
    const std::vector<ObjectLayer*>& getObjectLayers() const;

    void setTilesets(const std::vector<Tileset*>& tileset);
    std::vector<Tileset*>& getTilesets();
    const std::vector<Tileset*>& getTilesets() const;

private:
    int p_width,
        p_height,
        p_tile_width,
        p_tile_height,
        p_next_object_id,
        p_hex_side_length;
    Orientation p_orientation;
    RenderOrder p_render_order;
    StaggerAxis p_stagger_axis;
    StaggerIndex p_stagger_index;
    Color p_background_color;
    std::string p_version, p_tiled_version;
    std::vector<Layer*> p_layers;
    std::vector<TileLayer*> p_tile_layers;
    std::vector<ImageLayer*> p_image_layers;
    std::vector<ObjectLayer*> p_object_layers;
    std::vector<Tileset*> p_tileset;
};
} /* tiled */

#endif /* ifndef TILED_MAP_HPP */
