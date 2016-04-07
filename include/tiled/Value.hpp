#ifndef TILED_VALUE_HPP
#define TILED_VALUE_HPP
#include <string>

namespace tiled
{
class WrongValueType : public std::exception
{};

class Value
{
public:
    enum class Type { NONE, BOOL, INT, FLOAT, STRING };

    Value();
    Value(bool value);
    Value(int value);
    Value(float value);
    Value(const std::string& value);
    Value(const Value& other);
    virtual ~Value();
    virtual Type getType() const;
    virtual bool getBool() const;
    virtual int getInt() const;
    virtual float getFloat() const;
    virtual const std::string& getString() const;

    static const char* typeToString(Type type);

private:
    Type p_type;
    bool p_bool_value;
    int p_int_value;
    float p_float_value;
    std::string p_string_value;
};
}

#endif
