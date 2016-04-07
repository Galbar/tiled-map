#include "Tileset.hpp"
#include "Tile.hpp"
#include "Terrain.hpp"
#include "Image.hpp"
#include "Properties.hpp"

using namespace tiled;

Tileset::Tileset()
{

}

Tileset::~Tileset()
{
    delete p_image;
    for(auto it : p_tiles)
    {
        delete it.second;
    }
    for(Terrain* terrain : p_terrains)
    {
        delete terrain;
    }
}

void Tileset::setGId(int first_g_id)
{
    p_first_g_id = first_g_id;
}

int Tileset::getGId() const
{
    return p_first_g_id;
}

void Tileset::setTileWidth(int tile_width)
{
    p_tile_width = tile_width;
}

int Tileset::getTileWidth() const
{
    return p_tile_width;
}

void Tileset::setTileHeight(int tile_height)
{
    p_tile_height = tile_height;
}

int Tileset::getTileHeight() const
{
    return p_tile_height;
}

void Tileset::setSpacing(int spacing)
{
    p_spacing = spacing;
}

int Tileset::getSpacing() const
{
    return p_spacing;
}

void Tileset::setMargin(int margin)
{
    p_margin = margin;
}

int Tileset::getMargin() const
{
    return p_margin;
}

void Tileset::setTileCount(int tile_count)
{
    p_tile_count = tile_count;
}

int Tileset::getTileCount() const
{
    return p_tile_count;
}

void Tileset::setColumns(int columns)
{
    p_columns = columns;
}

int Tileset::getColumns() const
{
    return p_columns;
}

void Tileset::setTileOffsetX(int tile_offset_x)
{
    p_tile_offset_x = tile_offset_x;
}

int Tileset::getTileOffsetX() const
{
    return p_tile_offset_x;
}

void Tileset::setTileOffsetY(int tile_offset_y)
{
    p_tile_offset_y = tile_offset_y;
}

int Tileset::getTileOffsetY() const
{
    return p_tile_offset_y;
}

void Tileset::setName(const std::string& name)
{
    p_name = name;
}

const std::string& Tileset::getName() const
{
    return p_name;
}

void Tileset::setFileName(const std::string& file_name)
{
    p_file_name = file_name;
}

const std::string& Tileset::getFileName() const
{
    return p_file_name;
}

void Tileset::setImage(Image* image)
{
    p_image = image;
}

Image* Tileset::getImage()
{
    return p_image;
}

const Image* Tileset::getImage() const
{
    return p_image;
}

void Tileset::setTiles(const std::unordered_map<unsigned int, Tile*>& Tiles)
{
    p_tiles = Tiles;
}

std::unordered_map<unsigned int, Tile*>& Tileset::getTiles()
{
    return p_tiles;
}

const std::unordered_map<unsigned int, Tile*>& Tileset::getTiles() const
{
    return p_tiles;
}

void Tileset::setTerrains(const std::vector<Terrain*>& Terrains)
{
    p_terrains = Terrains;
}

std::vector<Terrain*>& Tileset::getTerrains()
{
    return p_terrains;
}

const std::vector<Terrain*>& Tileset::getTerrains() const
{
    return p_terrains;
}
