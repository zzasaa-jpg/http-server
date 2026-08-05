#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

class Logger_Class
{
public:
    bool logger(const std::string type, const std::string module_name, const std::string content);
    bool init_log_file();
};

#endif // LOGGER_HPP