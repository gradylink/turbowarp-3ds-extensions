#include <scratch-3ds.h>
#include <stdlib.h>
#include <string.h>

#ifdef __WIIU__
#include <coreinit/dynload.h>
#endif

bool Bitwise_isNumberBits(struct ExtensionData data, const char *central) {
  for (unsigned int i = 0; i < strlen(central); i++)
    if (central[i] != '0' && central[i] != '1') return false;
  return true;
}

const char *Bitwise_toNumberBits(struct ExtensionData data, const double central) {
  unsigned int n = (unsigned int)central; // TODO: support negative numbers
  static char buf[33];

  if (n == 0) return "0";

  unsigned int i = 0;
  while (n != 0) {
    buf[i++] = (n & 1) ? '1' : '0';
    n >>= 1;
  }

  // reverse
  for (unsigned int j = 0; j < i / 2; j++) {
    const char t = buf[j];
    buf[j] = buf[i - 1 - j];
    buf[i - 1 - j] = t;
  }

  return buf;
}

double Bitwise_ofNumberBits(struct ExtensionData data, const char *central) {
  unsigned int ret = 0;
  for (unsigned int i = 0; central[i] != '\0'; i++) ret = (ret << 1) + (central[i] - '0');
  return ret;
}

double Bitwise_bitwiseRightShift(struct ExtensionData data, const double left, const double right) {
  return (int)left >> (int)right;
}

double Bitwise_bitwiseLeftShift(struct ExtensionData data, const double left, const double right) {
  return (int)left << (int)right;
}

double Bitwise_bitwiseLogicalRightShift(struct ExtensionData data, const double left, const double right) {
  return (unsigned int)left >> (unsigned int)right;
}

double Bitwise_bitwiseLogicalLeftShift(struct ExtensionData data, const double left, const double right) {
  return (unsigned int)left << (unsigned int)right;
}

double Bitwise_bitwiseAnd(struct ExtensionData data, const double left, const double right) {
  return (unsigned int)left & (unsigned int)right; // TODO: support negative numbers
}

double Bitwise_bitwiseOr(struct ExtensionData data, const double left, const double right) {
  return (unsigned int)left | (unsigned int)right; // TODO: support negative numbers
}

double Bitwise_bitwiseXor(struct ExtensionData data, const double left, const double right) {
  return (unsigned int)left ^ (unsigned int)right; // TODO: support negative numbers
}

double Bitwise_bitwiseNot(struct ExtensionData data, const double central) {
  return ~(unsigned int)central; // TODO: support negative numbers
}

#ifdef __WIIU__
int rpl_entry(OSDynLoad_Module module, OSDynLoad_EntryReason reason) {
  return 0;
}
#endif
