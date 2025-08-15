#pragma once

#include <any>
#include <stdexcept>
#include <string>

namespace cast {
static std::string toString(const std::any &value) {
  if (!value.has_value()) return "null";

  if (value.type() == typeid(std::string)) return std::any_cast<const std::string &>(value);
  if (value.type() == typeid(double)) return std::to_string(std::any_cast<double>(value));
  if (value.type() == typeid(int)) return std::to_string(std::any_cast<int>(value));
  if (value.type() == typeid(float)) return std::to_string(std::any_cast<float>(value));
  if (value.type() == typeid(bool)) return std::any_cast<bool>(value) ? "true" : "false";

  throw std::runtime_error("Unsupported type in std::any");
}

static int toInt(const std::any &value) {
  if (value.type() == typeid(std::string)) return std::stod(std::any_cast<const std::string &>(value));
  if (value.type() == typeid(double)) return static_cast<int>(std::any_cast<double>(value));
  if (value.type() == typeid(int)) return std::any_cast<int>(value);
  if (value.type() == typeid(float)) return static_cast<int>(std::any_cast<float>(value));
  if (value.type() == typeid(bool)) return std::any_cast<bool>(value) ? 1 : 0;

  throw std::runtime_error("Unsupported type in std::any");
}
} // namespace cast
