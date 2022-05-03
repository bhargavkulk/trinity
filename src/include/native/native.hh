#ifndef NATIVE_NATIVE_HH
#define NATIVE_NATIVE_HH

#include "common.hh"
#include <vector>

#define def_native(name) u64 name(std::vector<u64> &argv)

#endif /* NATIVE_NATIVE_HH */