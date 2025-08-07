#include "utils.hpp"
#include <any>
#include <bitset>
#include <boost/regex.hpp>
#include <map>
#include <string>

#ifdef __WIIU__
#include <coreinit/dynload.h>
#endif

extern "C" {

std::any Bitwise_isNumberBits(std::map<std::string, std::any> arguments) {
  static const boost::regex bin_regex{"^-?[01]+$"};
  return boost::regex_match(anyToString(arguments["CENTRAL"]), bin_regex);
}

std::any Bitwise_toNumberBits(std::map<std::string, std::any> arguments) {
  return removeLeadingZeros(std::bitset<64>(anyToInt(arguments["CENTRAL"])).to_string());
}

std::any Bitwise_ofNumberBits(std::map<std::string, std::any> arguments) {
  return std::stoi(anyToString(arguments["CENTRAL"]), nullptr, 2);
}

std::any Bitwise_bitwiseRightShift(std::map<std::string, std::any> arguments) {
  return anyToInt(arguments["LEFT"]) >> anyToInt(arguments["RIGHT"]);
}

std::any Bitwise_bitwiseLeftShift(std::map<std::string, std::any> arguments) {
  return anyToInt(arguments["LEFT"]) << anyToInt(arguments["RIGHT"]);
}

std::any Bitwise_bitwiseLogicalRightShift(std::map<std::string, std::any> arguments) {
  return anyToInt(arguments["LEFT"]) >> anyToInt(arguments["RIGHT"]);
}

std::any Bitwise_bitwiseLogicalLeftShift(std::map<std::string, std::any> arguments) {
  return anyToInt(arguments["LEFT"]) << anyToInt(arguments["RIGHT"]);
}

std::any Bitwise_bitwiseAnd(std::map<std::string, std::any> arguments) {
  return anyToInt(arguments["LEFT"]) & anyToInt(arguments["RIGHT"]);
}

std::any Bitwise_bitwiseOr(std::map<std::string, std::any> arguments) {
  return anyToInt(arguments["LEFT"]) | anyToInt(arguments["RIGHT"]);
}

std::any Bitwise_bitwiseXor(std::map<std::string, std::any> arguments) {
  return anyToInt(arguments["LEFT"]) ^ anyToInt(arguments["RIGHT"]);
}

std::any Bitwise_bitwiseNot(std::map<std::string, std::any> arguments) {
  return ~anyToInt(arguments["CENTRAL"]);
}
}

#ifdef __WIIU__
int rpl_entry(OSDynLoad_Module module,
              OSDynLoad_EntryReason reason) {
  if (reason == OS_DYNLOAD_LOADED) {
    // Do stuff on load
  } else if (reason == OS_DYNLOAD_UNLOADED) {
    // Do stuff on unload
  }

  return 0;
}
#endif
