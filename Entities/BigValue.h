#pragma once
#include <string>
#include <variant>
#include <iostream>

enum class BigValueType{
    INT, FLOAT, TEXT
};

struct BigValue{
    std::variant<int, float, std::string> value;
    std::variant<int, float, std::string> maxValue;
    BigValueType type;
};

