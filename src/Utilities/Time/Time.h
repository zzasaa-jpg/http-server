#ifndef TIME_HPP
#define TIME_HPP

#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

class Time_Class
{
public:
    static std::string get_Time()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm *local_time = std::localtime(&now_time_t);

        std::ostringstream oss;
        oss << std::put_time(local_time, "%H:%M:%S");
        return oss.str();
    }
};

#endif // TIME_HPP