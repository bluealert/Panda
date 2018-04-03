#pragma once

#include <string>

namespace panda {
namespace http {

class MIMETypes {
 public:
  static constexpr char application_json[] = "application/json";
  static constexpr char text_json[] = "text/json";
};

constexpr char MIMETypes::application_json[];
constexpr char MIMETypes::text_json[];

}  // namespace http
}  // namespace panda