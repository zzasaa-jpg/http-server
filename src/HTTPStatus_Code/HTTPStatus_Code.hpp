#ifndef HTTP_STATUS_CODE
#define HTTP_STATUS_CODE

#include <string>
#include <unordered_map>

class HTTPStatus_Code
{
private:
    const std::unordered_map<std::string, std::string> status_code_map = {
        // 1xx informational response
        {"100", " Continue"},
        {"101", " Switching Protocols"},
        {"102", " Processing (WebDAV; RFC 2518)"},
        {"103", " Early Hints (RFC 8297)"},

        // 2xx success
        {"200", " OK"},
        {"201", " Created"},
        {"202", " Accepted"},
        {"203", " Non-Authoritative Information (since HTTP/1.1)"},
        {"204", " No Content"},
        {"205", " Reset Content"},
        {"206", " Partial Content"},
        {"207", " Multi-Status (WebDAV; RFC 4918)"},
        {"208", " Already Reported (WebDAV; RFC 5842)"},
        {"226", " IM Used (RFC 3229)"},

        // 3xx redirection
        {"300", " Multiple Choices"},
        {"301", " Moved Permanently"},
        {"302", " Found"},
        {"303", " See Other (since HTTP/1.1)"},
        {"304", " Not Modified"},
        {"305", " Use Proxy (since HTTP/1.1)"},
        {"306", " Switch Proxy"},
        {"307", " Temporary Redirect (since HTTP/1.1)"},
        {"308", " Permanent Redirect"},

        // 4xx client error
        {"400", " Bad Request"},
        {"401", " Unauthorized"},
        {"402", " Payment Required"},
        {"403", " Forbidden"},
        {"404", " Not Found"},
        {"405", " Method Not Allowed"},
        {"406", " Not Acceptable"},
        {"407", " Proxy Authentication Required"},
        {"408", " Request Timeout"},
        {"409", " Conflict"},
        {"410", " Gone"},
        {"411", " Length Required"},
        {"412", " Precondition Failed"},
        {"413", " Content Too Large"},
        {"414", " URI Too Long"},
        {"415", " Unsupported Media Type"},
        {"416", " Range Not Satisfiable"},
        {"417", " Expectation Failed"},
        {"418", " I'm a teapot (RFC 2324, RFC 7168)"},
        {"421", " Misdirected Request"},
        {"422", " Unprocessable Content"},
        {"423", " Locked (WebDAV; RFC 4918)"},
        {"424", " Failed Dependency (WebDAV; RFC 4918)"},
        {"425", " Too Early (RFC 8470)"},
        {"426", " Upgrade required"},
        {"428", " Precondition Required (RFC 6585"},
        {"429", " Too Many Requests (RFFC 6585)"},
        {"431", " Request Header Fields Too Large (RFC 6585)"},
        {"451", " Unavailable For Legal Reasons (RFC 7725)"},

        // 5xx server error
        {"500", " Internal Server Error"},
        {"501", " Not Implemented"},
        {"502", " Bad Gateway"},
        {"503", " Service Unavailable"},
        {"504", " Gateway Timeout"},
        {"505", " HTTP Version Not Supported"},
        {"506", " Variant Also Negotiates (RFC 2295)"},
        {"507", " Insufficient Storage (WebDAV; RFC 4918)"},
        {"508", " Loop Detected (WebDAV; RFC 5842)"},
        {"510", " Not Extended (RFC 2774)"},
        {"511", " Network Authentication Required (RFC 6585)"}};

public:
    std::string Get_HTTPStatus_Code(const std::string &status_code);
};

#endif // HTTP_STATUS_CODE