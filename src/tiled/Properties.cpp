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
    p_bag[name] = Value(value);
}

void Properties::set(const std::string& name, int value)
{
    p_bag[name] = Value(value);
}

void Properties::set(const std::string& name, float value)
{
    p_bag[name] = Value(value);
}

void Properties::set(const std::string& name, const std::string& value)
{
    p_bag[name] = Value(value);
}

void Properties::set(const std::string& name, const char* value)
{
    p_bag[name] = Value(std::string(value));
}

void Properties::set(const std::string& name, const Value& value)
{
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

void Properties::clear()
{
    p_bag.clear();
}
} /* tiled */
