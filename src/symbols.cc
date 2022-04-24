#include "symbols.hh"

SymbolTable *currentTable;

SymbolTable::SymbolTable(int level, SymbolTable *parent) : scope_level(level), parent(parent) { }

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

bool add_symbol(string &symbol, Entry entry)
{
    if(currentTable->entries.find(symbol) != currentTable->entries.end())
    {
        return false;
    }

    currentTable->entries[symbol] = entry;
    return true;
}

bool check_symbol(string &symbol, Entry &entry)
{
    SymbolTable *table = currentTable;
    while(table != NULL)
    {
        auto found = table->entries.find(symbol);
        if(found != table->entries.end())
        {
            entry = found->second;
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