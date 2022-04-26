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
    i64 dim_count; // For arrays
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
    i64 ret_dim_count;
    u32 pc;
    vector<DataType> paramTypes;
    vector<i64> param_dim_counts; // For arrays.
};

void init_funcs();
bool add_func(string &symbol, FuncEntry entry);
bool check_func(string &symbol, FuncEntry &entry);

extern DataType currFuncRetType;
extern i64 curr_func_ret_dim_count;


/**** Scope Start Symbols ****/

struct ScopeStartEntry
{
    string symbol;
    DataType type;
    i64 dim_count; // For arrays
};

extern vector<ScopeStartEntry> scope_starts;

/**** Arguments ****/

struct ArgvEntry
{
    DataType type;
    i64 dim_count;
};

extern vector<ArgvEntry> argv;


/**** Loop entries for cnt and brk****/
struct LoopEntry
{
    u64 loop_start;
    vector<u64> breaks;
};

extern vector<LoopEntry> loop_entries;

void init_buffers();

#endif /* SYMBOLS_HH */