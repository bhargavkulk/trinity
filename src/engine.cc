#include <pthread.h>
#include <unistd.h>

#include <cstdint>
#include <cstdio>

#include "common.hpp"
#include "vm.hh"

// Block *grid[10][10] = {};
uint32_t game_grid[10][20] = {};

extern void draw_block(int x, int y, uint32_t colour);
extern void flush_requests();

// void refresh_gui() {
//     for (int i = 0; i < 10; i++) {
//         for (int j = 0; j < 10; j++) {
//             if (grid[i][j] && grid[i][j]->shouldDraw) {
//                 draw_block(i * 50, j * 50, grid[i][j]->colour);
//             } else {
//                 draw_block(i * 50, j * 50, 0);
//             }
//         }
//     }
//     flush_requests();
// }

void refresh_gui_() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            draw_block(i * 50, j * 50, game_grid[i][j]);
        }
    }
    flush_requests();
}

extern VM vm;

void time_handler() {
    refresh_gui_();
    vm.set_pc_to_update_pc();
}

bool upPressed = false, leftPressed = false, rightPressed = false,
     downPressed = false;

void key_handler(Key key) {
    switch (key) {
        case Key::UP_PRESS:
            upPressed = true;
            printf("UP press\n");
            break;
        case Key::UP_RELEASE:
            upPressed = false;
            printf("UP release\n");
            break;
        case Key::LEFT_PRESS:
            leftPressed = true;
            printf("LEFT press\n");
            break;
        case Key::LEFT_RELEASE:
            leftPressed = false;
            printf("LEFT release\n");
            break;
        case Key::RIGHT_PRESS:
            rightPressed = true;
            printf("RIGHT press\n");
            break;
        case Key::RIGHT_RELEASE:
            rightPressed = false;
            printf("RIGHT release\n");
            break;
        case Key::DOWN_PRESS:
            downPressed = true;
            printf("DOWN press\n");
            break;
        case Key::DOWN_RELEASE:
            downPressed = false;
            printf("DOWN release\n");
            break;
        default:
            break;
    }
}

extern void *tick(void *args);
extern void *io(void *args);

extern bool isWindowActive;
extern void stop_timer();

void engine_main() {
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_t time_thread;
    pthread_create(&time_thread, &attr, tick, (void *)32);

    pthread_t io_thread;
    pthread_create(&io_thread, &attr, io, NULL);

    vm.run();

    while (isWindowActive)
        ;

    stop_timer();

    pthread_join(io_thread, NULL);
    pthread_join(time_thread, NULL);
}