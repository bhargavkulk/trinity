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


extern u32 game_grid[10][20];

def_native(nat_draw_at)
{
    int x = static_cast<int>(argv.at(0));
    int y = static_cast<int>(argv.at(1));
    u32 colour = static_cast<u32>(argv.at(2));

    game_grid[x][y] = colour;
}

def_native(nat_grid_at)
{
    int x = static_cast<int>(argv.at(0));
    int y = static_cast<int>(argv.at(1));

    return game_grid[x][y];
}