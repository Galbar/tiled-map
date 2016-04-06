#include "extensions/lua.hpp"
#include <iostream>
#include <cstdlib>
#include <unordered_map>

using namespace tiled;

Value getValue(lua_State* L, int position)
{
    Value result;
    if (lua_isnumber(L, position))
    {
        float n = lua_tonumber(L, position);
        result = Value(n);
    }
    else if (lua_isboolean(L, position))
    {
        bool b = lua_toboolean(L, position);
        result = Value(b);
    }
    else if (lua_isstring(L, position))
    {
        std::string s(lua_tostring(L, position));
        result = Value(s);
    }
    return result;
}

Value getValue(lua_State* L, const char* key)
{
    lua_pushstring(L, key);
    lua_gettable(L, -2);  /* get table[key] */
    Value result = getValue(L, -1);
    lua_pop(L, 1);
    return result;
}

Color getColor(const std::string& s_color)
{
    Color c_color;
    c_color.a = std::strtoul(s_color.substr(1, 2).c_str(), 0, 16);
    c_color.r = std::strtoul(s_color.substr(3, 2).c_str(), 0, 16);
    c_color.g = std::strtoul(s_color.substr(5, 2).c_str(), 0, 16);
    c_color.b = std::strtoul(s_color.substr(7, 2).c_str(), 0, 16);
    return c_color;
}


void getProperties(lua_State* L, Properties& properties)
{
    lua_pushstring(L, "properties");
    lua_gettable(L, -2);
    if(lua_istable(L, -1))
    {
        lua_pushnil(L);
        while(lua_next(L, -2) != 0)
        {
            properties.set(getValue(L, -2).getString(), getValue(L, -1));
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}


Image* getImage(lua_State* L)
{
    Image* image = new Image();
    Value value;

    value = getValue(L, "imagewidth");
    if (value.getType() == Value::Type::FLOAT)
    {
        image->setWidth(value.getFloat());
    }

    value = getValue(L, "imageheight");
    if (value.getType() == Value::Type::FLOAT)
    {
        image->setHeight(value.getFloat());
    }

    value = getValue(L, "trans");
    if (value.getType() == Value::Type::STRING)
    {
        Color transparent_color = getColor(value.getString());
        image->setTransparentColor(transparent_color);
    }

    value = getValue(L, "image");
    if (value.getType() == Value::Type::STRING)
    {
        image->setSource(value.getString());
    }

    return image;
}


Object* getObject(lua_State* L)
{
    Object* object = new Object();
    Value value;

    value = getValue(L, "x");
    if (value.getType() == Value::Type::FLOAT)
    {
        object->setX(value.getFloat());
    }

    value = getValue(L, "y");
    if (value.getType() == Value::Type::FLOAT)
    {
        object->setY(value.getFloat());
    }

    value = getValue(L, "id");
    if (value.getType() == Value::Type::FLOAT)
    {
        object->setGId(value.getFloat());
    }

    value = getValue(L, "width");
    if (value.getType() == Value::Type::FLOAT)
    {
        object->setWidth(value.getFloat());
    }

    value = getValue(L, "height");
    if (value.getType() == Value::Type::FLOAT)
    {
        object->setHeight(value.getFloat());
    }

    value = getValue(L, "visible");
    if (value.getType() == Value::Type::BOOL)
    {
        object->setVisibility(value.getBool());
    }

    value = getValue(L, "rotation");
    if (value.getType() == Value::Type::FLOAT)
    {
        object->setRotation(value.getFloat());
    }

    value = getValue(L, "name");
    if (value.getType() == Value::Type::STRING)
    {
        object->setName(value.getString());
    }

    value = getValue(L, "shape");
    if (value.getType() == Value::Type::STRING)
    {
        if (value.getString() == "rectangle")
        {
            object->setShape(Object::Shape::RECTANGLE);
        }
        else if (value.getString() == "ellipse")
        {
            object->setShape(Object::Shape::ELLIPSE);
        }
        else if (value.getString() == "polygon")
        {
            object->setShape(Object::Shape::POLYGON);
        }
        else if (value.getString() == "polyline")
        {
            object->setShape(Object::Shape::POLYLINE);
        }
    }

    lua_pushstring(L, value.getString().c_str());
    lua_gettable(L, -2);
    if (lua_istable(L, -1))
    {
        lua_pushnil(L);
        while (lua_next(L, -2) != 0)
        {
            float x = getValue(L, "x").getFloat();
            float y = getValue(L, "y").getFloat();
            if (value.getType() == Value::Type::STRING)
            {
                object->getPoints().push_back(Point{x, y});
            }

            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);

    value = getValue(L, "type");
    if (value.getType() == Value::Type::STRING)
    {
        object->setType(value.getString());
    }

    getProperties(L, object->getProperties());

    return object;
}

void getObjects(lua_State* L, std::vector<Object*>& objects)
{
    lua_pushstring(L, "objects");
    lua_gettable(L, -2);
    if(lua_istable(L, -1))
    {
        lua_pushnil(L);
        while(lua_next(L, -2) != 0)
        {
            if(lua_istable(L, -1))
            {
                Object* object = getObject(L);
                objects.push_back(object);
            }
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}


void getLayer(lua_State* L, Layer* layer)
{
    Value value;
    value = getValue(L, "width");
    if (value.getType() == Value::Type::FLOAT)
    {
        layer->setWidth(value.getFloat());
    }

    value = getValue(L, "height");
    if (value.getType() == Value::Type::FLOAT)
    {
        layer->setHeight(value.getFloat());
    }

    value = getValue(L, "x");
    if (value.getType() == Value::Type::FLOAT)
    {
        layer->setX(value.getFloat());
    }

    value = getValue(L, "y");
    if (value.getType() == Value::Type::FLOAT)
    {
        layer->setY(value.getFloat());
    }

    value = getValue(L, "offsetx");
    if (value.getType() == Value::Type::FLOAT)
    {
        layer->setOffsetX(value.getFloat());
    }

    value = getValue(L, "offsety");
    if (value.getType() == Value::Type::FLOAT)
    {
        layer->setOffsetY(value.getFloat());
    }

    value = getValue(L, "visible");
    if (value.getType() == Value::Type::BOOL)
    {
        layer->setVisibility(value.getBool());
    }

    value = getValue(L, "opacity");
    if (value.getType() == Value::Type::FLOAT)
    {
        layer->setOpacity(value.getFloat());
    }

    value = getValue(L, "name");
    if (value.getType() == Value::Type::STRING)
    {
        layer->setName(value.getString());
    }

    getProperties(L, layer->getProperties());
}

TileLayer* getTileLayer(lua_State* L)
{
    TileLayer* layer = new TileLayer();

    getLayer(L, layer);

    Value value;
    value = getValue(L, "encoding");
    if (value.getType() == Value::Type::STRING)
    {
        TileLayer::Encoding encoding = TileLayer::Encoding::LUA;
        if(value.getString() == "base64")
        {
            encoding = TileLayer::Encoding::BASE64;
        }
        layer->setEncoding(encoding);
    }

    value = getValue(L, "compression");
    if (value.getType() == Value::Type::STRING)
    {
        TileLayer::Compression compression = TileLayer::Compression::NONE;
        if(value.getString() == "zlib")
        {
            compression = TileLayer::Compression::ZLIB;
        }
        else if (value.getString() == "gzib")
        {
            compression = TileLayer::Compression::GZIB;
        }
        layer->setCompression(compression);
    }

    lua_pushstring(L, "data");
    lua_gettable(L, -2);
    if(lua_istable(L, -1))
    {
        std::vector<int> tile_map;
        lua_pushnil(L);
        while(lua_next(L, -2) != 0)
        {
            tile_map.push_back(lua_tonumber(L, -1));
            lua_pop(L, 1);
        }
        layer->setTileMap(tile_map);
    }
    else if(lua_isstring(L, -1))
    {
        std::string s(lua_tostring(L, -1));
        layer->setData(s);
    }
    lua_pop(L, 1);

    return layer;
}


ImageLayer* getImageLayer(lua_State* L)
{
    ImageLayer* layer = new ImageLayer();

    getLayer(L, layer);

    Image* image = getImage(L);
    layer->setImage(image);

    return layer;
}


ObjectLayer* getObjectLayer(lua_State* L)
{
    ObjectLayer* layer = new ObjectLayer();

    getLayer(L, layer);

    Value value;
    value = getValue(L, "draworder");
    if (value.getType() == Value::Type::STRING)
    {
        ObjectLayer::DrawOrder dwo = ObjectLayer::DrawOrder::INDEX;
        if (value.getString() == "topdown")
        {
            dwo = ObjectLayer::DrawOrder::TOPDOWN;
        }
        layer->setDrawOrder(dwo);
    }

    value = getValue(L, "color");
    if (value.getType() == Value::Type::STRING)
    {
        Color color = getColor(value.getString());
        layer->setColor(color);
    }

    getObjects(L, layer->getObjects());

    return layer;
}


void getLayers(lua_State* L, Map& map)
{
    lua_pushstring(L, "layers");
    lua_gettable(L, -2);
    if(lua_istable(L, -1))
    {
        lua_pushnil(L);
        while(lua_next(L, -2) != 0)
        {
            if(lua_istable(L, -1))
            {
                Value value = getValue(L, "type");
                if (value.getType() == Value::Type::STRING)
                {
                    if (value.getString() == "tilelayer")
                    {
                        TileLayer* layer = getTileLayer(L);
                        map.getLayers().push_back(layer);
                        map.getTileLayers().push_back(layer);
                    }
                    //else if (value.getString() == "imagelayer")
                    //{
                    //    ImageLayer* layer = getImageLayer(L);
                    //    map.getLayers().push_back(layer);
                    //    map.getImageLayers().push_back(layer);
                    //}
                    //else if (value.getString() == "objectgroup")
                    //{
                    //    ObjectLayer* layer = getObjectLayer(L);
                    //    map.getLayers().push_back(layer);
                    //    map.getObjectLayers().push_back(layer);
                    //}
                }
            }
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}


Terrain* getTerrain(lua_State* L)
{
    Terrain* terrain = new Terrain();
    Value value;

    value = getValue(L, "name");
    if (value.getType() == Value::Type::STRING)
    {
        terrain->setName(value.getString());
    }

    value = getValue(L, "tile");
    if (value.getType() == Value::Type::FLOAT)
    {
        terrain->setTile(value.getFloat());
    }

    getProperties(L, terrain->getProperties());

    return terrain;
}


void getTerrains(lua_State* L, std::vector<Terrain*>& terrains)
{
    lua_pushstring(L, "terrains");
    lua_gettable(L, -2);
    if(lua_istable(L, -1))
    {
        lua_pushnil(L);
        while(lua_next(L, -2) != 0)
        {
            if(lua_istable(L, -1))
            {
                Terrain* terrain = getTerrain(L);
                terrains.push_back(terrain);
            }
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}


void getAnimation(lua_State* L, std::vector<Frame>& animation)
{
    lua_pushstring(L, "animation");
    lua_gettable(L, -2);
    if(lua_istable(L, -1))
    {
        lua_pushnil(L);
        while (lua_next(L, -2) != 0)
        {
            Frame frame;
            frame.tile_id = getValue(L, "tileid").getFloat();
            frame.duration = getValue(L, "duration").getFloat();
            animation.push_back(frame);
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}


Tile* getTile(lua_State* L, Tileset* parent)
{
    Tile* tile = new Tile();
    tile->setParent(parent);
    Value value;

    value = getValue(L, "id");
    if (value.getType() == Value::Type::FLOAT)
    {
        tile->setId(value.getFloat());
    }

    value = getValue(L, "probability");
    if (value.getType() == Value::Type::FLOAT)
    {
        tile->setProbability(value.getFloat());
    }

    lua_pushstring(L, "terrain");
    lua_gettable(L, -2);
    if(lua_istable(L, -1))
    {
        lua_pushnil(L);
        int cont = 1;
        TerrainCoords tcoords;
        while(lua_next(L, -2) != 0)
        {
            if(lua_isnumber(L, -1))
            {
                if (cont == 1)
                {
                    tcoords.top_left = lua_tonumber(L, -1);
                }
                else if (cont == 2)
                {
                    tcoords.top_right = lua_tonumber(L, -1);
                }
                else if (cont == 3)
                {
                    tcoords.bottom_left = lua_tonumber(L, -1);
                }
                else if (cont == 4)
                {
                    tcoords.bottom_right = lua_tonumber(L, -1);
                }
            }
            ++cont;
            lua_pop(L, 1);
        }
        tile->setTerrain(tcoords);
    }
    lua_pop(L, 1);

    getObjects(L, tile->getObjects());

    getAnimation(L, tile->getAnimation());

    getProperties(L, tile->getProperties());

    return tile;
}


void getTiles(lua_State* L, std::vector<Tile*>& tiles, Tileset* parent)
{
    lua_pushstring(L, "tiles");
    lua_gettable(L, -2);
    if(lua_istable(L, -1))
    {
        lua_pushnil(L);
        while(lua_next(L, -2) != 0)
        {
            if(lua_istable(L, -1))
            {
                Tile* tile = getTile(L, parent);
                tiles.push_back(tile);
            }
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}


Tileset* getTileset(lua_State* L)
{
    Tileset* tileset = new Tileset();
    Value value;

    value = getValue(L, "firstgid");
    if (value.getType() == Value::Type::FLOAT)
    {
        tileset->setGId(value.getFloat());
    }

    value = getValue(L, "tilewidth");
    if (value.getType() == Value::Type::FLOAT)
    {
        tileset->setTileWidth(value.getFloat());
    }

    value = getValue(L, "tileheight");
    if (value.getType() == Value::Type::FLOAT)
    {
        tileset->setTileHeight(value.getFloat());
    }

    value = getValue(L, "spacing");
    if (value.getType() == Value::Type::FLOAT)
    {
        tileset->setSpacing(value.getFloat());
    }

    value = getValue(L, "margin");
    if (value.getType() == Value::Type::FLOAT)
    {
        tileset->setMargin(value.getFloat());
    }

    value = getValue(L, "tilecount");
    if (value.getType() == Value::Type::FLOAT)
    {
        tileset->setTileCount(value.getFloat());
    }

    value = getValue(L, "columns");
    if (value.getType() == Value::Type::FLOAT)
    {
        tileset->setColumns(value.getFloat());
    }

    value = getValue(L, "name");
    if (value.getType() == Value::Type::STRING)
    {
        tileset->setName(value.getString());
    }

    value = getValue(L, "filename");
    if (value.getType() == Value::Type::STRING)
    {
        tileset->setFileName(value.getString());
    }

    lua_pushstring(L, "tileoffset");
    lua_gettable(L, -2);

        value = getValue(L, "x");
        if (value.getType() == Value::Type::FLOAT)
        {
            tileset->setTileOffsetX(value.getFloat());
        }

        value = getValue(L, "y");
        if (value.getType() == Value::Type::FLOAT)
        {
            tileset->setTileOffsetY(value.getFloat());
        }

    lua_pop(L, 1);

    Image* image = getImage(L);
    tileset->setImage(image);

    getTiles(L, tileset->getTiles(), tileset);

    getTerrains(L, tileset->getTerrains());

    getProperties(L, tileset->getProperties());

    return tileset;
}


void getTilesets(lua_State* L, std::vector<Tileset*>& tilesets)
{
    lua_pushstring(L, "tilesets");
    lua_gettable(L, -2);
    if(lua_istable(L, -1))
    {
        lua_pushnil(L);
        while(lua_next(L, -2) != 0)
        {
            if(lua_istable(L, -1))
            {
                Tileset* tileset = getTileset(L);
                tilesets.push_back(tileset);
            }
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}


namespace tiled
{
namespace lua
{
void load(Map& map, lua_State* L)
{
    Value value;
    value = getValue(L, "version");
    if (value.getType() == Value::Type::FLOAT)
    {
        map.setVersion(std::to_string(value.getFloat()));
    }


    value = getValue(L, "tiledversion");
    if (value.getType() == Value::Type::STRING)
    {
        map.setTiledVersion(value.getString());
    }


    value = getValue(L, "orientation");
    if (value.getType() == Value::Type::STRING)
    {
        Map::Orientation orientation;
        if (value.getString() == "orthogonal")
        {
            orientation = Map::Orientation::ORTHOGONAL;
        }
        else if (value.getString() == "isometric")
        {
            orientation = Map::Orientation::ISOMETRIC;
        }
        else if (value.getString() == "staggered")
        {
            orientation = Map::Orientation::STAGGERED;
        }
        else
        {
            orientation = Map::Orientation::HEXAGONAL;
        }
        map.setOrientation(orientation);
    }


    value = getValue(L, "renderorder");
    if (value.getType() == Value::Type::STRING)
    {
        Map::RenderOrder render_order;
        if (value.getString() == "right-down")
        {
            render_order = Map::RenderOrder::RIGHT_DOWN;
        }
        else if (value.getString() == "right-up")
        {
            render_order = Map::RenderOrder::RIGHT_UP;
        }
        else if (value.getString() == "left-down")
        {
            render_order = Map::RenderOrder::LEFT_DOWN;
        }
        else
        {
            render_order = Map::RenderOrder::LEFT_UP;
        }
        map.setRenderOrder(render_order);
    }


    value = getValue(L, "width");
    if (value.getType() == Value::Type::FLOAT)
    {
        map.setWidth(value.getFloat());
    }


    value = getValue(L, "height");
    if (value.getType() == Value::Type::FLOAT)
    {
        map.setHeight(value.getFloat());
    }


    value = getValue(L, "tilewidth");
    if (value.getType() == Value::Type::FLOAT)
    {
        map.setTileWidth(value.getFloat());
    }


    value = getValue(L, "tileheight");
    if (value.getType() == Value::Type::FLOAT)
    {
        map.setTileHeight(value.getFloat());
    }


    value = getValue(L, "hexsidelength");
    if (value.getType() == Value::Type::FLOAT)
    {
        map.setHexSideLength(value.getFloat());
    }


    value = getValue(L, "staggeraxis");
    if (value.getType() == Value::Type::STRING)
    {
        Map::StaggerAxis stagger_axis = Map::StaggerAxis::X;
        if (value.getString() == "y")
        {
            stagger_axis = Map::StaggerAxis::Y;
        }
        map.setStaggerAxis(stagger_axis);
    }


    value = getValue(L, "staggerindex");
    if (value.getType() == Value::Type::STRING)
    {
        Map::StaggerIndex stagger_index = Map::StaggerIndex::ODD;
        if (value.getString() == "even")
        {
            stagger_index = Map::StaggerIndex::EVEN;
        }
        map.setStaggerIndex(stagger_index);
    }


    value = getValue(L, "backgroundcolor");
    if (value.getType() == Value::Type::STRING)
    {
        Color background_color = getColor(value.getString());
        map.setBackgroundColor(background_color);
    }


    value = getValue(L, "nextobjectid");
    if (value.getType() != Value::Type::NONE)
    {
        map.setNextObjectId(value.getFloat());
    }

    getLayers(L, map);

    //getTilesets(L, map.getTilesets());

    //getProperties(L, map.getProperties());
}
}
}
