#ifndef SYMBOLS_HH
#define SYMBOLS_HH

#include "types.hh"
#include <unordered_map>
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::unordered_map;

struct SymbolEntry
{
    DataType type;
    usize id;
};

struct SymbolTable
{
    int scope_level;
    unordered_map<string, SymbolEntry> entries;
    SymbolTable *parent;

    SymbolTable(int level, SymbolTable *parent);
};


void init_symbols();
void open_scope();
void close_scope();
bool is_currently_global();

bool add_symbol(string &symbol, SymbolEntry entry);
bool check_symbol(string &symbol, SymbolEntry &entry, bool &is_global);
usize get_scope_var_count();


/**** FUNCTIONS ****/

struct FuncEntry
{
    DataType retType;
    u32 pc;
    vector<DataType> paramTypes;
};

void init_funcs();
bool add_func(string &symbol, FuncEntry entry);
bool check_func(string &symbol, FuncEntry &entry);

extern DataType currFuncRetType;


/**** Scope Start Symbols ****/

struct ScopeStartEntry
{
    string symbol;
    DataType type;
};


extern vector<ScopeStartEntry> scope_starts;
extern vector<DataType> argv;

/**** Loop entries for cnt and brk****/
struct LoopEntry
{
    u64 loop_start;
    vector<u64> breaks;
};

extern vector<LoopEntry> loop_entries;

void init_buffers();

#endif /* SYMBOLS_HH */