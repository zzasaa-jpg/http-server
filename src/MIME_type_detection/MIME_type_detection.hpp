#ifndef MIME_TYPE_DETECTION_HPP
#define MIME_TYPE_DETECTION_HPP

#include <string>
#include <unordered_map>

class MIME_TYPE_DETECTION_CLASS
{
public:
    static std::string get_MIME_Type(const std::string &extension)
    {
        auto it = mime_types.find(extension);

        if (it != mime_types.end())
        {
            return it->second;
        }

        return "application/octet-stream";
    }

private:
    static const std::unordered_map<std::string, std::string> mime_types;
};

const std::unordered_map<std::string, std::string>
    MIME_TYPE_DETECTION_CLASS::mime_types = {
        // Text
        {"html", "text/html"},
        {"htm", "text/html"},
        {"css", "text/css"},
        {"js", "text/javascript"},
        {"json", "application/json"},
        {"txt", "text/plain"},

        // Images
        {"png", "image/png"},
        {"jpg", "image/jpeg"},
        {"jpeg", "image/jpeg"},
        {"gif", "image/gif"},
        {"ico", "image/x-icon"},
        {"svg", "image/svg+xml"},
        {"webp", "image/webp"},

        // Audio
        {"mp3", "audio/mpeg"},
        {"wav", "audio/wav"},
        {"ogg", "audio/ogg"},
        {"aac", "audio/aac"},
        {"m4a", "audip/mp4"},

        // Video
        {"mp4", "video/mp4"},
        {"m4v", "video/mp4"},
        {"webm", "video/webm"},
        {"avi", "video/x-msvideo"},
        {"mov", "video/quicktime"},
        {"mkv", "video/x-matroska"},

        // Documents
        {"pdf", "application/pdf"},
        {"xml", "application/xml"},
        {"zip", "application/zip"}};

#endif // MIME_TYPE_DETECTION_HPP