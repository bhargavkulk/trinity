#ifndef SYMBOLS_HH
#define SYMBOLS_HH

#include "types.hh"
#include <unordered_map>
#include <string>
using std::string;
using std::unordered_map;

struct Entry
{
    DataType type;
    usize id;
};

struct SymbolTable
{
    int scope_level;
    unordered_map<string, Entry> entries;
    SymbolTable *parent;

    SymbolTable(int level, SymbolTable *parent);
};

void init_symbols();
void open_scope();
void close_scope();

bool add_symbol(string &symbol, Entry entry);
bool check_symbol(string &symbol, Entry &entry);
usize get_scope_var_count();

#endif /* SYMBOLS_HH */