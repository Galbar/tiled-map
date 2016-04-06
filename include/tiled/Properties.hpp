#ifndef TILED_PROPERTIES_HPP
#define TILED_PROPERTIES_HPP
#include <set>
#include <unordered_map>
#include <string>
#include "Value.hpp"

namespace tiled
{
class Properties
{
public:
    Properties();
    virtual ~Properties();
    void set(const std::string& name, bool value);
    void set(const std::string& name, int value);
    void set(const std::string& name, float value);
    void set(const std::string& name, const std::string& value);
    void set(const std::string& name, const char* value);
    void set(const std::string& name, const Value& value);
    const Value& get(const std::string& name) const;
    const std::set<std::string>& keys() const;
    void clear();

private:
    static Value s_p_none;
    std::set<std::string> p_keys;
    std::unordered_map<std::string, Value> p_bag;
};
} /* tiled */
#endif /* ifndef TILED_PROPERTIES_HPP */
