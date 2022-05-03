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

/**** RECORDS ****/

unordered_map<string, RecordEntry> records;

void init_records()
{
    records = unordered_map<string, RecordEntry>();
}

bool add_record(string &record, RecordEntry entry)
{
    if(records.find(record) != records.end())
    {
        return false;
    }

    records[record] = entry;
    return true;
}

bool check_record(string &record, RecordEntry &entry)
{
    if(records.find(record) == records.end())
    {
        return false;
    }

    entry = records[record];
    return true;
}

bool add_record_field(string &record, string &field, RecordEntry::FieldEntry entry)
{
    auto rec = records.find(record);
    if(rec == records.end()) return false;
    auto &recEntry = rec->second;
    
    if(recEntry.fields.find(field) != recEntry.fields.end())
    {
        return false;
    }

    recEntry.fields[field] = entry;
    return true;
}

bool check_record_field(string &record, string &field, RecordEntry::FieldEntry &entry)
{
    auto rec = records.find(record);
    if(rec == records.end()) return false;
    auto &recEntry = rec->second;

    if(recEntry.fields.find(field) == recEntry.fields.end())
    {
        return false;
    }

    entry = recEntry.fields[field];
    return true;
}


static string current_record_name;
static u64 current_record_field_id;

void set_current_record_name(string record)
{
    current_record_name = record;
    current_record_field_id = 0;
}

string &get_current_record_name()
{
    return current_record_name;
}

u64 get_current_record_field_id()
{
    return current_record_field_id++;
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


/**** Native Functions ****/

// Defined in native/native.cc
extern void add_native_functions(std::unordered_map<string, FuncEntry> &natives);

unordered_map<string, FuncEntry> natives;

void init_natives()
{
    natives = unordered_map<string, FuncEntry>();
    add_native_functions(natives);
}

bool check_native(string &symbol, FuncEntry &entry)
{
    if(natives.find(symbol) == natives.end())
    {
        return false;
    }

    entry = natives[symbol];
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
