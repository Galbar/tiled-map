#include "WithProperties.hpp"

namespace tiled
{
namespace priv
{
WithProperties::WithProperties()
{}

WithProperties::~WithProperties()
{}

void WithProperties::setProperties(const Properties& properties)
{
    p_properties = properties;
}

Properties& WithProperties::getProperties()
{
    return p_properties;
}
const Properties& WithProperties::getProperties() const
{
    return p_properties;
}
}
}
