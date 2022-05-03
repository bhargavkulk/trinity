#include "common.hh"
#include "native/native.hh"
#include "native/array.hh"
#include "crash.hh"

def_native(Array_1D_Len)
{
    Array *array = deref_dptr(argv.at(0), Array *);
    CRASH_IF_NIL(array);
    return array->dims.at(0);
}