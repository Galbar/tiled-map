#ifndef TILED_WITH_PROPERTIES_HPP
#define TILED_WITH_PROPERTIES_HPP
#include "Properties.hpp"

namespace tiled
{
namespace priv
{
class WithProperties
{
public:
    WithProperties();
    virtual ~WithProperties();
    void setProperties(const Properties& properties);
    Properties& getProperties();
    const Properties& getProperties() const;

private:
    Properties p_properties;
};
}
}
#endif /* ifndef TILED_WITH_PROPERTIES_HPP */
