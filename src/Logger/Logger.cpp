#include "./Logger.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include "../Utilities/Date/Date.h"
#include "../Utilities/Time/Time.h"

const std::string LOG_FOLDER_PATH = "../../log";
const std::string LOG_FILE_PATH = "../../log/server.log.";

bool Logger_Class::init_log_file()
{
    bool init_file_or_folder_exists = std::filesystem::exists(LOG_FOLDER_PATH);
    if (init_file_or_folder_exists == false)
    {
        std::filesystem::create_directory(LOG_FOLDER_PATH);
        std::ofstream file(LOG_FILE_PATH);
        if (!file.is_open())
        {
            std::cerr << "Failed to create server.log file![Logger Module]\n";
            return false;
        }
        std::string init_table_headings =
            "Type Date Time Module_Name Content\n";

        file << init_table_headings;
        file.close();
        return true;
    }
    else
        return true;
}

bool Logger_Class::logger(const std::string type, const std::string module_name, const std::string content)
{
    Date_Class dt;
    Time_Class time__;
    if (init_log_file())
    {
        std::ofstream file(LOG_FILE_PATH, std::ios::app);

        if (!file.is_open())
        {
            std::cerr << "server.log file is not found![Logger Module]\n";
            return false;
        }

        std::string append_data = type + " " + dt.get_Date() + " " + time__.get_Time() + " " + module_name + " " + content + "\n";
        file << append_data;
        file.close();
        return true;
    }
    else
    {
        std::cerr << "Failed to initialization server.log file.[Logger Module]\n";
        return false;
    }
}
