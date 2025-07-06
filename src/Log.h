#pragma once
#include <string>

class Log
{
   public:
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

    static Log& getInstance();

    // Your logging functionality
    static void ErrorMessage(const std::string& message);
    static void InfoMessage(const std::string& message);

   private:
    Log() = default;

    ~Log() = default;
};

inline void LogError(const std::string& message)
{
    Log::ErrorMessage(message);
}

inline void LogInfo(const std::string& message)
{
    Log::InfoMessage(message);
}