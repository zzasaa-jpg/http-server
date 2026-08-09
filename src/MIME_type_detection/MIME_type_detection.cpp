#include "./MIME_type_detection.hpp"

std::string MIME_TYPE_DETECTION_CLASS::get_MIME_Type(const std::string &extension)
{
    auto it = mime_types.find(extension);

    if (it != mime_types.end())
    {
        return it->second;
    }

    return "application/octet-stream";
}
