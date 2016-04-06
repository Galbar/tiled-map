#include "Properties.hpp"

namespace tiled
{
Value Properties::s_p_none = Value();

Properties::Properties()
{}

Properties::~Properties()
{}

void Properties::set(const std::string& name, bool value)
{
    set(name, Value(value));
}

void Properties::set(const std::string& name, int value)
{
    set(name, Value(value));
}

void Properties::set(const std::string& name, float value)
{
    set(name, Value(value));
}

void Properties::set(const std::string& name, const std::string& value)
{
    set(name, Value(value));
}

void Properties::set(const std::string& name, const char* value)
{
    set(name, Value(std::string(value)));
}

void Properties::set(const std::string& name, const Value& value)
{
    p_keys.insert(name);
    p_bag[name] = value;
}

const Value& Properties::get(const std::string& name) const
{
    auto it = p_bag.find(name);
    if (it == p_bag.end())
    {
        return s_p_none;
    }
    return it->second;
}

const std::set<std::string>& Properties::keys() const
{
    return p_keys;
}

void Properties::clear()
{
    p_bag.clear();
    p_keys.clear();
}
} /* tiled */
