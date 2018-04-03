#pragma once

#include <cstdint>
#include <string>

// http://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml

namespace panda {
namespace http {

class Status {
 public:
  static constexpr uint16_t Continue = 100;            // RFC 7231, 6.2.1
  static constexpr uint16_t SwitchingProtocols = 101;  // RFC 7231, 6.2.2
  static constexpr uint16_t Processing = 102;          // RFC 2518, 10.1

  static constexpr uint16_t OK = 200;                    // RFC 7231, 6.3.1
  static constexpr uint16_t Created = 201;               // RFC 7231, 6.3.2
  static constexpr uint16_t Accepted = 202;              // RFC 7231, 6.3.3
  static constexpr uint16_t NonAuthoritativeInfo = 203;  // RFC 7231, 6.3.4
  static constexpr uint16_t NoContent = 204;             // RFC 7231, 6.3.5
  static constexpr uint16_t ResetContent = 205;          // RFC 7231, 6.3.6
  static constexpr uint16_t PartialContent = 206;        // RFC 7233, 4.1
  static constexpr uint16_t MultiStatus = 207;           // RFC 4918, 11.1
  static constexpr uint16_t AlreadyReported = 208;       // RFC 5842, 7.1
  static constexpr uint16_t IMUsed = 226;                // RFC 3229, 10.4.1

  static constexpr uint16_t MultipleChoices = 300;    // RFC 7231, 6.4.1
  static constexpr uint16_t MovedPermanently = 301;   // RFC 7231, 6.4.2
  static constexpr uint16_t Found = 302;              // RFC 7231, 6.4.3
  static constexpr uint16_t SeeOther = 303;           // RFC 7231, 6.4.4
  static constexpr uint16_t NotModified = 304;        // RFC 7232, 4.1
  static constexpr uint16_t UseProxy = 305;           // RFC 7231, 6.4.5
  static constexpr uint16_t TemporaryRedirect = 307;  // RFC 7231, 6.4.7
  static constexpr uint16_t PermanentRedirect = 308;  // RFC 7538, 3

  static constexpr uint16_t BadRequest = 400;             // RFC 7231, 6.5.1
  static constexpr uint16_t Unauthorized = 401;           // RFC 7235, 3.1
  static constexpr uint16_t PaymentRequired = 402;        // RFC 7231, 6.5.2
  static constexpr uint16_t Forbidden = 403;              // RFC 7231, 6.5.3
  static constexpr uint16_t NotFound = 404;               // RFC 7231, 6.5.4
  static constexpr uint16_t MethodNotAllowed = 405;       // RFC 7231, 6.5.5
  static constexpr uint16_t NotAcceptable = 406;          // RFC 7231, 6.5.6
  static constexpr uint16_t ProxyAuthRequired = 407;      // RFC 7235, 3.2
  static constexpr uint16_t RequestTimeout = 408;         // RFC 7231, 6.5.7
  static constexpr uint16_t Conflict = 409;               // RFC 7231, 6.5.8
  static constexpr uint16_t Gone = 410;                   // RFC 7231, 6.5.9
  static constexpr uint16_t LengthRequired = 411;         // RFC 7231, 6.5.10
  static constexpr uint16_t PreconditionFailed = 412;     // RFC 7232, 4.2
  static constexpr uint16_t RequestEntityTooLarge = 413;  // RFC 7231, 6.5.11
  static constexpr uint16_t RequestURITooLong = 414;      // RFC 7231, 6.5.12
  static constexpr uint16_t UnsupportedMediaType = 415;   // RFC 7231, 6.5.13
  static constexpr uint16_t RequestedRangeNotSatisfiable =
      416;                                               // RFC 7233, 4.4
  static constexpr uint16_t ExpectationFailed = 417;     // RFC 7231, 6.5.14
  static constexpr uint16_t Teapot = 418;                // RFC 7168, 2.3.3
  static constexpr uint16_t UnprocessableEntity = 422;   // RFC 4918, 11.2
  static constexpr uint16_t Locked = 423;                // RFC 4918, 11.3
  static constexpr uint16_t FailedDependency = 424;      // RFC 4918, 11.4
  static constexpr uint16_t UpgradeRequired = 426;       // RFC 7231, 6.5.15
  static constexpr uint16_t PreconditionRequired = 428;  // RFC 6585, 3
  static constexpr uint16_t TooManyRequests = 429;       // RFC 6585, 4
  static constexpr uint16_t RequestHeaderFieldsTooLarge = 431;  // RFC 6585, 5
  static constexpr uint16_t UnavailableForLegalReasons = 451;   // RFC 7725, 3

  static constexpr uint16_t InternalServerError = 500;      // RFC 7231, 6.6.1
  static constexpr uint16_t NotImplemented = 501;           // RFC 7231, 6.6.2
  static constexpr uint16_t BadGateway = 502;               // RFC 7231, 6.6.3
  static constexpr uint16_t ServiceUnavailable = 503;       // RFC 7231, 6.6.4
  static constexpr uint16_t GatewayTimeout = 504;           // RFC 7231, 6.6.5
  static constexpr uint16_t HTTPVersionNotSupported = 505;  // RFC 7231, 6.6.6
  static constexpr uint16_t VariantAlsoNegotiates = 506;    // RFC 2295, 8.1
  static constexpr uint16_t InsufficientStorage = 507;      // RFC 4918, 11.5
  static constexpr uint16_t LoopDetected = 508;             // RFC 5842, 7.2
  static constexpr uint16_t NotExtended = 510;              // RFC 2774, 7
  static constexpr uint16_t NetworkAuthenticationRequired = 511;  // RFC 6585, 6

  static std::string text(uint16_t code);
};

}  // namespace http
}  // namespace panda