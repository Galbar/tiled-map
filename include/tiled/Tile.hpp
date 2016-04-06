#ifndef TILED_TILE_HPP
#define TILED_TILE_HPP
#include <vector>
#include <unordered_map>
#include "TerrainCoords.hpp"
#include "WithProperties.hpp"
#include "Frame.hpp"

namespace tiled
{
class Tileset;
class Object;
class Tile : public priv::WithProperties
{
public:
    Tile();
    virtual ~Tile();

    void setId(int id);
    int getId() const;

    int getGId() const;

    void setProbability(float probability);
    float getProbability() const;

    void setTerrain(TerrainCoords& terrain);
    TerrainCoords& getTerrain();
    const TerrainCoords& getTerrain() const;

    void setParent(Tileset* parent);
    Tileset* getParent();
    const Tileset* getParent() const;

    void setObjects(const std::vector<Object*>& objects);
    std::vector<Object*>& getObjects();
    const std::vector<Object*>& getObjects() const;

    void setAnimation(const std::vector<Frame>& animation);
    std::vector<Frame>& getAnimation();
    const std::vector<Frame>& getAnimation() const;

private:
    int p_id;
    float p_probability;
    TerrainCoords p_terrain;
    Tileset* p_parent;
    std::vector<Object*> p_objects;
    std::vector<Frame> p_animation;
};
} /* tiled */

#endif /* ifndef TILED_MAP_HPP */
