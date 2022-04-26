#include "symbols.hh"

SymbolTable *currentTable;

SymbolTable::SymbolTable(int level, SymbolTable *parent) : scope_level(level), parent(parent) { }

DataType currFuncRetType;
i64 curr_func_ret_dim_count;

void init_symbols()
{
    currentTable = new SymbolTable(0, NULL);
}

void open_scope()
{
    currentTable = new SymbolTable(currentTable->scope_level + 1, currentTable);
}

void close_scope()
{
    SymbolTable *parent = currentTable->parent;
    delete currentTable;
    currentTable = parent;
}

bool is_currently_global()
{
    return currentTable->parent == NULL;
}

bool add_symbol(string &symbol, SymbolEntry entry)
{
    if(currentTable->entries.find(symbol) != currentTable->entries.end())
    {
        return false;
    }

    currentTable->entries[symbol] = entry;
    return true;
}

bool check_symbol(string &symbol, SymbolEntry &entry, bool &is_global)
{
    SymbolTable *table = currentTable;
    while(table != NULL)
    {
        auto found = table->entries.find(symbol);
        if(found != table->entries.end())
        {
            entry = found->second;
            is_global = (table->parent == NULL);
            return true;
        }
        table = table->parent;
    }
    return false;
}

usize get_scope_var_count()
{
    return currentTable->entries.size();
}


/***** Functions *****/

unordered_map<string, FuncEntry> funcs;

void init_funcs()
{
    funcs = unordered_map<string, FuncEntry>();
}

bool add_func(string &symbol, FuncEntry entry)
{
    if(funcs.find(symbol) != funcs.end())
    {
        return false;
    }

    funcs[symbol] = entry;
    return true;
}

bool check_func(string &symbol, FuncEntry &entry)
{
    if(funcs.find(symbol) == funcs.end())
    {
        return false;
    }

    entry = funcs[symbol];
    return true;
}


/**** Scope Start Symbols ****/

vector<ScopeStartEntry> scope_starts;
vector<ArgvEntry> argv;

/**** Loop entries ****/
vector<LoopEntry> loop_entries;

void init_buffers()
{
    scope_starts = vector<ScopeStartEntry>();
    argv = vector<ArgvEntry>();
    loop_entries = vector<LoopEntry>();
}
