#include "TileLayer.hpp"

#include <string.h>
#include <algorithm>

#define MINIZ_HEADER_FILE_ONLY
#include "miniz/miniz.c"

#include <stdlib.h>
#include <stdio.h>

#include "Util.hpp"
#include "Map.hpp"

using namespace tiled;

TileLayer::TileLayer():
p_encoding(Encoding::LUA),
p_compression(Compression::NONE)
{
    p_type = Layer::LayerType::TILE_LAYER;
}

TileLayer::~TileLayer()
{}

void TileLayer::setEncoding(Encoding encoding)
{
    p_encoding = encoding;
}

TileLayer::Encoding TileLayer::getEncoding() const
{
    return p_encoding;
}

void TileLayer::setCompression(Compression compression)
{
    p_compression = compression;
}

TileLayer::Compression TileLayer::getCompression() const
{
    return p_compression;
}

void TileLayer::setData(const std::string& data)
{
    p_data = data;
}

std::string& TileLayer::getData()
{
    return p_data;
}

const std::string& TileLayer::getData() const
{
    return p_data;
}

void TileLayer::setTileMap(const std::vector<int>& map_tile)
{
    p_map_tile = map_tile;
}

std::vector<int>& TileLayer::getTileMap()
{
    return p_map_tile;
}

const std::vector<int>& TileLayer::getTileMap() const
{
    return p_map_tile;
}

void TileLayer::parseData(const Map& map)
{
    if (p_encoding == Encoding::BASE64)
    {
        Util::trim(p_data);

        const std::string& text = Util::decodeBase64(p_data);

        // Temporary array of gids to be converted to map tiles.
        unsigned *out = 0;

        if (p_compression == Compression::ZLIB)
        {
            // Use zlib to uncompress the tile layer into the temporary array of tiles.
            uLongf outlen = p_width * p_height * 4;
            out = (unsigned *)malloc(outlen);
            uncompress(
                (Bytef*)out, &outlen,
                (const Bytef*)text.c_str(), text.size());

        }

        else if (p_compression == Compression::GZIB)
        {
            // Use the utility class for decompressing (which uses zlib)
            out = (unsigned *)Util::decompressGZIP(
                text.c_str(), text.size(), p_width * p_height * 4);
        }
        else
        {
            out = (unsigned *)malloc(text.size());

            // Copy every gid into the temporary array since
            // the decoded string is an array of 32-bit integers.
            memcpy(out, text.c_str(), text.size());
        }

        // Convert the gids to map tiles.
        for (int x = 0; x < p_width; x++)
        {
            for (int y = 0; y < p_height; y++)
            {
                unsigned gid = out[y * p_width + x];

                // Find the tileset index.
                const int tilesetIndex = map.findTilesetIndex(gid);
                if (tilesetIndex != -1)
                {
                    // If valid, set up the map tile with the tileset.
                    p_map_tile[y * p_width + x] = gid;
                }
                else
                {
                    // Otherwise, make it null.
                    p_map_tile[y * p_width + x] = gid;
                }
            }
        }

        // Free the temporary array from memory.
        free(out);
    }
}
