#ifndef TILED_TILELAYER_HPP
#define TILED_TILELAYER_HPP
#include <vector>
#include <string>
#include "Layer.hpp"

namespace tiled
{
class Map;
class Tile;
class TileLayer : public Layer
{
public:
    enum class Encoding { LUA, BASE64, COUNT };
    enum class Compression { NONE, ZLIB, GZIB, COUNT };
    TileLayer();
    virtual ~TileLayer();

    void setEncoding(Encoding encoding);
    Encoding getEncoding() const;

    void setCompression(Compression compression);
    Compression getCompression() const;

    void setData(const std::string& data);
    std::string& getData();
    const std::string& getData() const;

    void setTileMap(const std::vector<int>& map_tile);
    std::vector<int>& getTileMap();
    const std::vector<int>& getTileMap() const;

    void parseData(const Map& map);


private:
    Encoding p_encoding;
    Compression p_compression;
    std::string p_data;
    std::vector<int> p_map_tile; //vector of tiles gid's
};
}
#endif
