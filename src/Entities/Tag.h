#pragma once
#include <iostream>
#include <string>
#include <variant>

enum class TagType
{
    INT,
    FLOAT,
    TEXT,
    BOOL,
    CAPPED_INT,
    CAPPED_FLOAT
};

template <typename T>
class CappedValue
{
   private:
    T value;
    T maxValue;

   public:
    CappedValue(T val, T maxVal) : value(std::min(val, maxVal)), maxValue(maxVal) {}

    void set(T val)
    {
        value = std::min(val, maxValue);
    }

    void setMax(T maxVal)
    {
        maxValue = maxVal;
    }

    T get() const
    {
        return value;
    }
    T getMax() const
    {
        return maxValue;
    }
};

class TagValue
{
   public:
    TagType type;
    bool displayable = false;
    std::variant<int, float, bool, std::string, CappedValue<int>, CappedValue<float>> value;

    // Constructors for different types
    TagValue() : type(TagType::INT), value(0) {}
    TagValue(int v) : type(TagType::INT), value(v) {}
    TagValue(float v) : type(TagType::FLOAT), value(v) {}
    TagValue(bool v) : type(TagType::BOOL), value(v) {}
    TagValue(const std::string& v) : type(TagType::TEXT), value(v) {}
    TagValue(const char* v)
        : type(TagType::TEXT), value(std::string(v)) {}  // Allow C-string assignment
    TagValue(CappedValue<int> v) : type(TagType::CAPPED_INT), value(v) {}
    TagValue(CappedValue<float> v) : type(TagType::CAPPED_FLOAT), value(v) {}
    void makeDisplayable()
    {
        displayable = true;
    }
    // Get type as string (for debugging)
    std::string getTypeName() const
    {
        switch (type)
        {
            case TagType::INT:
                return "int";
            case TagType::FLOAT:
                return "float";
            case TagType::BOOL:
                return "bool";
            case TagType::TEXT:
                return "text";
            case TagType::CAPPED_INT:
                return "capped int";
            case TagType::CAPPED_FLOAT:
                return "capped float";
            default:
                return "unknown";
        }
    }

    // Safe getter functions
    template <typename T>
    T get() const
    {
        if (std::holds_alternative<T>(value))
        {
            return std::get<T>(value);
        }
        throw std::runtime_error("Incorrect type access: expected " + getTypeName());
    }

    // Safe setter functions
    template <typename T>
    void set(T val)
    {
        if (std::holds_alternative<T>(value))
        {
            std::get<T>(value) = val;
        }
        else
        {
            throw std::runtime_error("Incorrect type assignment: expected " + getTypeName());
        }
    }
};
