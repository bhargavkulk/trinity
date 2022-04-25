#ifndef STRUCTURES_HH
#define STRUCTURES_HH

#include <vector>
#include "common.hh"

using std::vector;

struct Array
{
	vector<i64> dims;
	vector<u64> arr;
};

#endif /* STRUCTURES_HH */