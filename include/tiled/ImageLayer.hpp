#ifndef TILED_IMAGE_LAYER_HPP
#define TILED_IMAGE_LAYER_HPP
#include "Layer.hpp"

namespace tiled
{
class Image;
class ImageLayer : public Layer
{
public:
    ImageLayer();
    virtual ~ImageLayer();

    void setImage(Image* image);
    Image* getImage();
    const Image* getImage() const;

private:
    Image* p_image;
};
}
#endif
