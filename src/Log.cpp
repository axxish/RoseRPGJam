#include "Log.h"
#include <iostream>

// The one and only way to get the Log instance.
// This is thread-safe and handles initialization and destruction automatically.
Log& Log::getInstance()
{
    static Log instance; // The "magic static"
    return instance;
}

void Log::ErrorMessage(const std::string& message)
{

    std::cout << "[ERROR]: " << message << std::endl;
}

void Log::InfoMessage(const std::string& message)
{
    std::cout << "[INFO]: " << message << std::endl;
}

