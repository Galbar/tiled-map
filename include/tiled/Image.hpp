#ifndef TILED_IMAGE_HPP
#define TILED_IMAGE_HPP
#include <string>
#include "Color.hpp"

namespace tiled
{
class Image
{
public:
    Image();
    virtual ~Image();

    void setWidth(int width);
    int getWidth() const;

    void setHeight(int height);
    int getHeight() const;

    void setTransparentColor(const Color& trans);
    const Color& getTransparentColor() const;

    void setSource(const std::string& source);
    const std::string& getSource() const;


private:
    int p_width, p_height;
    Color p_transparent_color;
    std::string p_source;
};
}

#endif
