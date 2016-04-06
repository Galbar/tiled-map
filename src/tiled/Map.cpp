#include "Map.hpp"
#include "Layer.hpp"
#include "TileLayer.hpp"
#include "ImageLayer.hpp"
#include "ObjectLayer.hpp"
#include "Tileset.hpp"
#include "Properties.hpp"

using namespace tiled;

Map::Map():
p_hex_side_length(-1),
p_render_order(RenderOrder::RIGHT_DOWN),
p_stagger_axis(StaggerAxis::NONE),
p_stagger_index(StaggerIndex::NONE),
p_background_color(Color{128, 128, 128, 255})
{}

Map::~Map()
{
    for(Layer* layer : p_layers)
    {
        delete layer;
    }
    for(Tileset* tileset : p_tileset)
    {
        delete tileset;
    }
}

int Map::findTilesetIndex(int gid) const
{
    for (int i = p_tileset.size() - 1; i >= 0; --i)
    {
        if (gid >= p_tileset[i]->getGId())
        {
            return i;
        }
    }
    return -1;
}

void Map::setVersion(const std::string& version)
{
    p_version = version;
}

const std::string& Map::Map::getVersion() const
{
    return p_version;
}

void Map::setTiledVersion(const std::string& version)
{
    p_tiled_version = version;
}

const std::string& Map::getTiledVersion() const
{
    return p_tiled_version;
}


void Map::setOrientation(Map::Orientation orientation)
{
    p_orientation = orientation;
}

Map::Orientation Map::getOrientation() const
{
    return p_orientation;
}

void Map::setRenderOrder(Map::RenderOrder render_order)
{
    p_render_order = render_order;
}

Map::RenderOrder Map::getRenderOrder() const
{
    return p_render_order;
}

void Map::setWidth(int width)
{
    p_width = width;
}

int Map::getWidth() const
{
    return p_width;
}

void Map::setHeight(int height)
{
    p_height = height;
}

int Map::getHeight() const
{
    return p_height;
}

void Map::setTileWidth(int tile_width)
{
    p_tile_width = tile_width;
}

int Map::getTileWidth() const
{
    return p_tile_width;
}

void Map::setTileHeight(int tile_height)
{
    p_tile_height = tile_height;
}

int Map::getTileHeight() const
{
    return p_tile_height;
}

void Map::setHexSideLength(int hex_side_length)
{
    p_hex_side_length = hex_side_length;
}

int Map::getHexSideLength() const
{
    return p_hex_side_length;
}

void Map::setStaggerAxis(Map::StaggerAxis stagger_axis)
{
    p_stagger_axis = stagger_axis;
}

Map::StaggerAxis Map::getStaggerAxis() const
{
    return p_stagger_axis;
}

void Map::setStaggerIndex(Map::StaggerIndex stagger_index)
{
    p_stagger_index = stagger_index;
}

Map::StaggerIndex Map::getStaggerIndex() const
{
    return p_stagger_index;
}

void Map::setBackgroundColor(const Color& background_color)
{
    p_background_color = background_color;
}

const Color& Map::getBackgroundColor() const
{
    return p_background_color;
}

void Map::setNextObjectId(int next_object_id)
{
    p_next_object_id = next_object_id;
}

int Map::getNextObjectId() const
{
    return p_next_object_id;
}

void Map::setLayers(const std::vector<Layer*>& layers)
{
    p_layers = layers;
}

std::vector<Layer*>& Map::getLayers()
{
    return p_layers;
}

const std::vector<Layer*>& Map::getLayers() const
{
    return p_layers;
}

void Map::setTileLayers(const std::vector<TileLayer*>& tilelayers)
{
    p_tile_layers = tilelayers;
}

std::vector<TileLayer*>& Map::getTileLayers()
{
    return p_tile_layers;
}

const std::vector<TileLayer*>& Map::getTileLayers() const
{
    return p_tile_layers;
}

void Map::setImageLayers(const std::vector<ImageLayer*>& imagelayers)
{
    p_image_layers = imagelayers;
}

std::vector<ImageLayer*>& Map::getImageLayers()
{
    return p_image_layers;
}

const std::vector<ImageLayer*>& Map::getImageLayers() const
{
    return p_image_layers;
}

void Map::setObjectLayers(const std::vector<ObjectLayer*>& objectlayers)
{
    p_object_layers = objectlayers;
}

std::vector<ObjectLayer*>& Map::getObjectLayers()
{
    return p_object_layers;
}

const std::vector<ObjectLayer*>& Map::getObjectLayers() const
{
    return p_object_layers;
}

void Map::setTilesets(const std::vector<Tileset*>& tilesets)
{
    p_tileset = tilesets;
}

std::vector<Tileset*>& Map::getTilesets()
{
    return p_tileset;
}

const std::vector<Tileset*>& Map::getTilesets() const
{
    return p_tileset;
}
