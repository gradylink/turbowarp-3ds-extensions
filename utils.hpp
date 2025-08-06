#pragma once

#include <any>
#include <stdexcept>
#include <string>

static std::string anyToString(const std::any &value) {
  if (!value.has_value()) return "null";

  if (value.type() == typeid(std::string)) return std::any_cast<const std::string &>(value);
  if (value.type() == typeid(double)) return std::to_string(std::any_cast<double>(value));
  if (value.type() == typeid(int)) return std::to_string(std::any_cast<int>(value));
  if (value.type() == typeid(float)) return std::to_string(std::any_cast<float>(value));
  if (value.type() == typeid(bool)) return std::any_cast<bool>(value) ? "true" : "false";

  throw std::runtime_error("Unsupported type in std::any");
}

static int anyToInt(const std::any &value) {
  if (value.type() == typeid(std::string)) return std::stod(std::any_cast<const std::string &>(value));
  if (value.type() == typeid(double)) return static_cast<int>(std::any_cast<double>(value));
  if (value.type() == typeid(int)) return std::any_cast<int>(value);
  if (value.type() == typeid(float)) return static_cast<int>(std::any_cast<float>(value));
  if (value.type() == typeid(bool)) return std::any_cast<bool>(value) ? 1 : 0;

  throw std::runtime_error("Unsupported type in std::any");
}

static std::string removeLeadingZeros(std::string str) {
  size_t first = str.find_first_not_of('0');
  if (first == std::string::npos) return "0";
  str.erase(0, first);
  return str;
}
