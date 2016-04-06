#ifndef TILED_TERRAIN_HPP
#define TILED_TERRAIN_HPP
#include <string>
#include <unordered_map>
#include "WithProperties.hpp"

namespace tiled
{
class Tile;
class Terrain : public priv::WithProperties
{
public:
    Terrain();
    virtual ~Terrain();

    void setTile(int tile);
    int getTile() const;

    void setName(const std::string& name);
    const std::string& getName() const;

private:
    int p_tile;
    std::string p_name;
};
} /* tiled */

#endif /* ifndef TILED_MAP_HPP */
