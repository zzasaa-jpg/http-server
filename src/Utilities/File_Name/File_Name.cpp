#include "./File_Name.hpp"

#include <iostream>

int scan_file_name(int num, const std::string &file_path)
{
    int prev = num;
    while (num < file_path.length())
    {
        if (file_path[num] == '/')
            prev = num + 1;
        if (file_path[num] == '.')
            return prev;
        else
            num++;
    }
    return -1;
}

std::string get_file_name(const std::string &file_path)
{
    std::string file_name = "";
    int i = scan_file_name(0, file_path);
    if (i == -1)
    {
        std::cout << "-- Given file path inside does not have file name[FILE_NAME_UTILITY].\n";
        return "";
    }
    while (i < file_path.length())
    {
        file_name += file_path[i];
        i++;
    }
    return file_name;
}

// Time: O(n) | Space: O(1)