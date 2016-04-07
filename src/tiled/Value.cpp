#include <iostream>
#include "Value.hpp"

namespace tiled
{
Value::Value():
p_type(Type::NONE)
{}

Value::Value(bool value):
p_type(Type::BOOL),
p_bool_value(value)
{}

Value::Value(int value):
p_type(Type::INT),
p_int_value(value)
{}

Value::Value(float value):
p_type(Type::FLOAT),
p_float_value(value)
{}

Value::Value(const std::string& value):
p_type(Type::STRING),
p_string_value(value)
{}

Value::Value(const Value& other):
p_type(other.p_type),
p_bool_value(other.p_bool_value),
p_int_value(other.p_int_value),
p_float_value(other.p_float_value),
p_string_value(other.p_string_value)
{}

const char* Value::typeToString(Value::Type type)
{
    if (type == Type::NONE)
    {
        return "None";
    }
    else if (type == Type::BOOL)
    {
        return "Bool";
    }
    else if (type == Type::INT)
    {
        return "Int";
    }
    else if (type == Type::FLOAT)
    {
        return "Float";
    }
    else
    {
        return "String";
    }
}

Value::~Value()
{}

Value::Type Value::getType() const
{
    return p_type;
}

bool Value::getBool() const
{
    if (p_type == Type::BOOL)
    {
        return p_bool_value;
    }
    std::cerr << "Type is " << typeToString(p_type) << std::endl;
    throw WrongValueType();
}

int Value::getInt() const
{
    if (p_type == Type::INT)
    {
        return p_int_value;
    }
    std::cerr << "Type is " << typeToString(p_type) << std::endl;
    throw WrongValueType();
}

float Value::getFloat() const
{
    if (p_type == Type::FLOAT)
    {
        return p_float_value;
    }
    std::cerr << "Type is " << typeToString(p_type) << std::endl;
    throw WrongValueType();
}

const std::string& Value::getString() const
{
    if (p_type == Type::STRING)
    {
        return p_string_value;
    }
    std::cerr << "Type is " << typeToString(p_type) << std::endl;
    throw WrongValueType();
}
}
