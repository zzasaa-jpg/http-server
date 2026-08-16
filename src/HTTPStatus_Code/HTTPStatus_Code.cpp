#include "./HTTPStatus_Code.hpp"

std::string HTTPStatus_Code::Get_HTTPStatus_Code(const std::string &status_code)
{
    auto it = status_code_map.find(status_code);
    std::string final_status_code = "";
    if (it != status_code_map.end())
    {
        final_status_code = it -> first + it -> second;
        return final_status_code;
    }
    return "Internal Server Error";
}