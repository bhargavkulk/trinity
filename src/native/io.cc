#include "native/io.hh"
#include <cstdio>
#include <cstdlib>

def_native(nat_prints)
{
    printf("%s", reinterpret_cast<const char *>(argv.at(0)));
    return 0;
}

def_native(nat_printi)
{
    printf("%lu", static_cast<i64>(argv.at(0)));
    return 0;
}

def_native(nat_cls)
{
    system("clear");
}