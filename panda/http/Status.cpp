#include <panda/http/Status.h>
#include <unordered_map>

namespace panda {
namespace http {

constexpr uint16_t Status::Continue;            // RFC 7231, 6.2.1
constexpr uint16_t Status::SwitchingProtocols;  // RFC 7231, 6.2.2
constexpr uint16_t Status::Processing;          // RFC 2518, 10.1

constexpr uint16_t Status::OK;                    // RFC 7231, 6.3.1
constexpr uint16_t Status::Created;               // RFC 7231, 6.3.2
constexpr uint16_t Status::Accepted;              // RFC 7231, 6.3.3
constexpr uint16_t Status::NonAuthoritativeInfo;  // RFC 7231, 6.3.4
constexpr uint16_t Status::NoContent;             // RFC 7231, 6.3.5
constexpr uint16_t Status::ResetContent;          // RFC 7231, 6.3.6
constexpr uint16_t Status::PartialContent;        // RFC 7233, 4.1
constexpr uint16_t Status::MultiStatus;           // RFC 4918, 11.1
constexpr uint16_t Status::AlreadyReported;       // RFC 5842, 7.1
constexpr uint16_t Status::IMUsed;                // RFC 3229, 10.4.1

constexpr uint16_t Status::MultipleChoices;    // RFC 7231, 6.4.1
constexpr uint16_t Status::MovedPermanently;   // RFC 7231, 6.4.2
constexpr uint16_t Status::Found;              // RFC 7231, 6.4.3
constexpr uint16_t Status::SeeOther;           // RFC 7231, 6.4.4
constexpr uint16_t Status::NotModified;        // RFC 7232, 4.1
constexpr uint16_t Status::UseProxy;           // RFC 7231, 6.4.5
constexpr uint16_t Status::TemporaryRedirect;  // RFC 7231, 6.4.7
constexpr uint16_t Status::PermanentRedirect;  // RFC 7538, 3

constexpr uint16_t Status::BadRequest;                    // RFC 7231, 6.5.1
constexpr uint16_t Status::Unauthorized;                  // RFC 7235, 3.1
constexpr uint16_t Status::PaymentRequired;               // RFC 7231, 6.5.2
constexpr uint16_t Status::Forbidden;                     // RFC 7231, 6.5.3
constexpr uint16_t Status::NotFound;                      // RFC 7231, 6.5.4
constexpr uint16_t Status::MethodNotAllowed;              // RFC 7231, 6.5.5
constexpr uint16_t Status::NotAcceptable;                 // RFC 7231, 6.5.6
constexpr uint16_t Status::ProxyAuthRequired;             // RFC 7235, 3.2
constexpr uint16_t Status::RequestTimeout;                // RFC 7231, 6.5.7
constexpr uint16_t Status::Conflict;                      // RFC 7231, 6.5.8
constexpr uint16_t Status::Gone;                          // RFC 7231, 6.5.9
constexpr uint16_t Status::LengthRequired;                // RFC 7231, 6.5.10
constexpr uint16_t Status::PreconditionFailed;            // RFC 7232, 4.2
constexpr uint16_t Status::RequestEntityTooLarge;         // RFC 7231, 6.5.11
constexpr uint16_t Status::RequestURITooLong;             // RFC 7231, 6.5.12
constexpr uint16_t Status::UnsupportedMediaType;          // RFC 7231, 6.5.13
constexpr uint16_t Status::RequestedRangeNotSatisfiable;  // RFC 7233, 4.4
constexpr uint16_t Status::ExpectationFailed;             // RFC 7231, 6.5.14
constexpr uint16_t Status::Teapot;                        // RFC 7168, 2.3.3
constexpr uint16_t Status::UnprocessableEntity;           // RFC 4918, 11.2
constexpr uint16_t Status::Locked;                        // RFC 4918, 11.3
constexpr uint16_t Status::FailedDependency;              // RFC 4918, 11.4
constexpr uint16_t Status::UpgradeRequired;               // RFC 7231, 6.5.15
constexpr uint16_t Status::PreconditionRequired;          // RFC 6585, 3
constexpr uint16_t Status::TooManyRequests;               // RFC 6585, 4
constexpr uint16_t Status::RequestHeaderFieldsTooLarge;   // RFC 6585, 5
constexpr uint16_t Status::UnavailableForLegalReasons;    // RFC 7725, 3

constexpr uint16_t Status::InternalServerError;            // RFC 7231, 6.6.1
constexpr uint16_t Status::NotImplemented;                 // RFC 7231, 6.6.2
constexpr uint16_t Status::BadGateway;                     // RFC 7231, 6.6.3
constexpr uint16_t Status::ServiceUnavailable;             // RFC 7231, 6.6.4
constexpr uint16_t Status::GatewayTimeout;                 // RFC 7231, 6.6.5
constexpr uint16_t Status::HTTPVersionNotSupported;        // RFC 7231, 6.6.6
constexpr uint16_t Status::VariantAlsoNegotiates;          // RFC 2295, 8.1
constexpr uint16_t Status::InsufficientStorage;            // RFC 4918, 11.5
constexpr uint16_t Status::LoopDetected;                   // RFC 5842, 7.2
constexpr uint16_t Status::NotExtended;                    // RFC 2774, 7
constexpr uint16_t Status::NetworkAuthenticationRequired;  // RFC 6585, 6

static std::unordered_map<uint16_t, std::string> statusText = {
    {Status::Continue, "Continue"},
    {Status::SwitchingProtocols, "Switching Protocols"},
    {Status::Processing, "Processing"},

    {Status::OK, "OK"},
    {Status::Created, "Created"},
    {Status::Accepted, "Accepted"},
    {Status::NonAuthoritativeInfo, "Non-Authoritative Information"},
    {Status::NoContent, "No Content"},
    {Status::ResetContent, "Reset Content"},
    {Status::PartialContent, "Partial Content"},
    {Status::MultiStatus, "Multi-Status"},
    {Status::AlreadyReported, "Already Reported"},
    {Status::IMUsed, "IM Used"},

    {Status::MultipleChoices, "Multiple Choices"},
    {Status::MovedPermanently, "Moved Permanently"},
    {Status::Found, "Found"},
    {Status::SeeOther, "See Other"},
    {Status::NotModified, "Not Modified"},
    {Status::UseProxy, "Use Proxy"},
    {Status::TemporaryRedirect, "Temporary Redirect"},
    {Status::PermanentRedirect, "Permanent Redirect"},

    {Status::BadRequest, "Bad Request"},
    {Status::Unauthorized, "Unauthorized"},
    {Status::PaymentRequired, "Payment Required"},
    {Status::Forbidden, "Forbidden"},
    {Status::NotFound, "Not Found"},
    {Status::MethodNotAllowed, "Method Not Allowed"},
    {Status::NotAcceptable, "Not Acceptable"},
    {Status::ProxyAuthRequired, "Proxy Authentication Required"},
    {Status::RequestTimeout, "Request Timeout"},
    {Status::Conflict, "Conflict"},
    {Status::Gone, "Gone"},
    {Status::LengthRequired, "Length Required"},
    {Status::PreconditionFailed, "Precondition Failed"},
    {Status::RequestEntityTooLarge, "Request Entity Too Large"},
    {Status::RequestURITooLong, "Request URI Too Long"},
    {Status::UnsupportedMediaType, "Unsupported Media Type"},
    {Status::RequestedRangeNotSatisfiable, "Requested Range Not Satisfiable"},
    {Status::ExpectationFailed, "Expectation Failed"},
    {Status::Teapot, "I'm a teapot"},
    {Status::UnprocessableEntity, "Unprocessable Entity"},
    {Status::Locked, "Locked"},
    {Status::FailedDependency, "Failed Dependency"},
    {Status::UpgradeRequired, "Upgrade Required"},
    {Status::PreconditionRequired, "Precondition Required"},
    {Status::TooManyRequests, "Too Many Requests"},
    {Status::RequestHeaderFieldsTooLarge, "Request Header Fields Too Large"},
    {Status::UnavailableForLegalReasons, "Unavailable For Legal Reasons"},

    {Status::InternalServerError, "Internal Server Error"},
    {Status::NotImplemented, "Not Implemented"},
    {Status::BadGateway, "Bad Gateway"},
    {Status::ServiceUnavailable, "Service Unavailable"},
    {Status::GatewayTimeout, "Gateway Timeout"},
    {Status::HTTPVersionNotSupported, "HTTP Version Not Supported"},
    {Status::VariantAlsoNegotiates, "Variant Also Negotiates"},
    {Status::InsufficientStorage, "Insufficient Storage"},
    {Status::LoopDetected, "Loop Detected"},
    {Status::NotExtended, "Not Extended"},
    {Status::NetworkAuthenticationRequired, "Network Authentication Required"}};

std::string Status::text(uint16_t code) { return statusText[code]; }

}  // namespace http
}  // namespace panda