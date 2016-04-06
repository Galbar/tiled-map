#ifndef TILED_TILESET_HPP
#define TILED_TILESET_HPP
#include <string>
#include <vector>
#include <unordered_map>
#include "WithProperties.hpp"

namespace tiled
{
class Tile;
class Image;
class Terrain;
class Tileset : public priv::WithProperties
{
public:
    Tileset();
    virtual ~Tileset();

    void setGId(int first_g_id);
    int getGId() const;

    void setTileWidth(int tile_width);
    int getTileWidth() const;

    void setTileHeight(int tile_height);
    int getTileHeight() const;

    void setSpacing(int spacing);
    int getSpacing() const;

    void setMargin(int margin);
    int getMargin() const;

    void setTileCount(int tile_count);
    int getTileCount() const;

    void setColumns(int columns);
    int getColumns() const;

    void setTileOffsetX(int tile_offset_x);
    int getTileOffsetX() const;

    void setTileOffsetY(int tile_offset_y);
    int getTileOffsetY() const;

    void setName(const std::string& name);
    const std::string& getName() const;

    void setFileName(const std::string& file_name);
    const std::string& getFileName() const;

    void setImage(Image* image);
    Image* getImage();
    const Image* getImage() const;

    void setTiles(const std::vector<Tile*>& Tiles);
    std::vector<Tile*>& getTiles();
    const std::vector<Tile*>& getTiles() const;

    void setTerrains(const std::vector<Terrain*>& Terrains);
    std::vector<Terrain*>& getTerrains();
    const std::vector<Terrain*>& getTerrains() const;

private:
    int p_tile_width,
        p_tile_height,
        p_spacing,
        p_margin,
        p_tile_count,
        p_first_g_id,
        p_columns,
        p_tile_offset_x,
        p_tile_offset_y;
    std::string p_name, p_file_name;
    Image* p_image;
    std::vector<Tile*> p_tiles;
    std::vector<Terrain*> p_terrains;
};
} /* tiled */

#endif /* ifndef TILED_MAP_HPP */
