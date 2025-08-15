#include "cast.hpp"
#include <any>
#include <bitset>
#include <map>
#include <scratch-3ds.hpp>
#include <string>

#ifdef __WIIU__
#include <coreinit/dynload.h>
#endif

extern "C" {

bool Bitwise_isNumberBits(const std::map<std::string, std::any> &arguments, ExtensionData data) {
  for (const auto &c : cast::toString(arguments.find("CENTRAL")->second))
    if (c != '0' && c != '1') return false;
  return true;
}

void Bitwise_toNumberBits(const std::map<std::string, std::any> &arguments, std::string *ret, ExtensionData data) {
  *ret = std::bitset<64>(cast::toInt(arguments.find("CENTRAL")->second)).to_string();
  size_t first = (*ret).find_first_not_of('0');
  if (first == std::string::npos) {
    *ret = "0";
    return;
  }
  (*ret).erase(0, first);
}

int Bitwise_ofNumberBits(const std::map<std::string, std::any> &arguments, ExtensionData data) {
  return std::stoi(cast::toString(arguments.find("CENTRAL")->second), nullptr, 2);
}

int Bitwise_bitwiseRightShift(const std::map<std::string, std::any> &arguments, ExtensionData data) {
  return cast::toInt(arguments.find("LEFT")->second) >> cast::toInt(arguments.find("RIGHT")->second);
}

int Bitwise_bitwiseLeftShift(const std::map<std::string, std::any> &arguments, ExtensionData data) {
  return cast::toInt(arguments.find("LEFT")->second) << cast::toInt(arguments.find("RIGHT")->second);
}

int Bitwise_bitwiseLogicalRightShift(const std::map<std::string, std::any> &arguments, ExtensionData data) {
  return static_cast<unsigned int>(cast::toInt(arguments.find("LEFT")->second)) >> cast::toInt(arguments.find("RIGHT")->second);
}

int Bitwise_bitwiseLogicalLeftShift(const std::map<std::string, std::any> &arguments, ExtensionData data) {
  return static_cast<unsigned int>(cast::toInt(arguments.find("LEFT")->second)) << cast::toInt(arguments.find("RIGHT")->second);
}

int Bitwise_bitwiseAnd(const std::map<std::string, std::any> &arguments, ExtensionData data) {
  return cast::toInt(arguments.find("LEFT")->second) & cast::toInt(arguments.find("RIGHT")->second);
}

int Bitwise_bitwiseOr(const std::map<std::string, std::any> &arguments, ExtensionData data) {
  return cast::toInt(arguments.find("LEFT")->second) | cast::toInt(arguments.find("RIGHT")->second);
}

int Bitwise_bitwiseXor(const std::map<std::string, std::any> &arguments, ExtensionData data) {
  return cast::toInt(arguments.find("LEFT")->second) ^ cast::toInt(arguments.find("RIGHT")->second);
}

int Bitwise_bitwiseNot(const std::map<std::string, std::any> &arguments, ExtensionData data) {
  return ~cast::toInt(arguments.find("CENTRAL")->second);
}

#ifdef __WIIU__
int rpl_entry(OSDynLoad_Module module, OSDynLoad_EntryReason reason) {
  return 0;
}
#endif
}
