#ifndef DATE_HPP
#define DATE_HPP

#include <ctime>
#include <string>

class Date_Class
{
public:
    static std::string get_Date()
    {
        std::time_t now = std::time(0);
        std::tm *localtime = std::localtime(&now);
        return std::to_string(localtime->tm_year + 1900) + "/" +
               std::to_string(localtime->tm_mon + 1) + "/" +
               std::to_string(localtime->tm_mday);
    }
};

#endif // DATE_HPP