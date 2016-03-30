#ifndef TILED_PROPERTIES_HPP
#define TILED_PROPERTIES_HPP
#include <unordered_map>
#include <string>
#include "Value.hpp"

namespace tiled
{
class Properties
{
public:
    virtual ~Properties();
    void set(const std::string& name, bool value);
    void set(const std::string& name, int value);
    void set(const std::string& name, float value);
    void set(const std::string& name, const std::string& value);
    void set(const std::string& name, const char* value);
    void set(const std::string& name, const Value& value);
    const Value& get(const std::string& name) const;
    void clear();

private:
    Value p_none;
    std::unordered_map<std::string, Value> p_bag;
};
} /* tiled */
#endif /* ifndef TILED_PROPERTIES_HPP */
