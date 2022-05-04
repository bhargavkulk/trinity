#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xcb/xcb.h>

#include "common.hpp"

extern void key_handler(Key key);
bool isWindowActive = true;

xcb_connection_t *c;
xcb_window_t win;

void draw_block(int x, int y, uint32_t colour) {
    xcb_gcontext_t f = xcb_generate_id(c);
    uint32_t mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    uint32_t value[] = {colour, 0};
    xcb_create_gc(c, f, win, mask, value);

    xcb_rectangle_t rec = {(short)x, (short)y, 50, 50};
    xcb_poly_fill_rectangle(c, win, f, 1, &rec);
}

void flush_requests() { xcb_flush(c); }

void *io(void *args) {
    /* Open the connection to the X server. Use the DISPLAY environment
     * variable */
    c = xcb_connect(NULL, NULL);
    if (xcb_connection_has_error(c)) {
        fprintf(stderr, "xcb_connect() failed\n");
        return (void *)-1;
    }

    xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(c)).data;

    win = xcb_generate_id(c);
    uint32_t win_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t win_value[] = {screen->black_pixel,
                            XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS |
                                XCB_EVENT_MASK_KEY_RELEASE};
    xcb_create_window(c, screen->root_depth, win, screen->root, 100, 100, 500,
                      1000, 10, XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual, win_mask, win_value);

    xcb_change_property(c, XCB_PROP_MODE_REPLACE, win, XCB_ATOM_WM_NAME,
                        XCB_ATOM_STRING, 8, 7, "Tetris");
    // xcb_change_property(c, XCB_PROP_MODE_REPLACE, win, XCB_ATOM_WM_ICON_NAME,
    // XCB_ATOM_STRING, 8, 4, "ICON");

    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(c, 1, 12, "WM_PROTOCOLS");
    xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(c, cookie, 0);

    xcb_intern_atom_cookie_t cookie2 =
        xcb_intern_atom(c, 0, 16, "WM_DELETE_WINDOW");
    xcb_intern_atom_reply_t *reply2 = xcb_intern_atom_reply(c, cookie2, 0);

    xcb_change_property(c, XCB_PROP_MODE_REPLACE, win, reply->atom, 4, 32, 1,
                        &reply2->atom);

    xcb_map_window(c, win);
    xcb_flush(c);

    xcb_gcontext_t f1 = xcb_generate_id(c);
    uint32_t f1_mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    uint32_t f1_value[] = {screen->white_pixel, 0};
    xcb_create_gc(c, f1, win, f1_mask, f1_value);

    xcb_gcontext_t f2 = xcb_generate_id(c);
    uint32_t f2_mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    uint32_t f2_value[] = {0x00FF0000, 0};
    xcb_create_gc(c, f2, win, f2_mask, f2_value);
    xcb_flush(c);

    /*xcb_rectangle_t rec = {(short)0, (short)500, 500, 5};
    xcb_poly_fill_rectangle(c, win, f1, 1, &rec);


    xcb_font_t font = xcb_generate_id(c);
    const char *font_str = "6x13";
    xcb_open_font(c, font, strlen(font_str), font_str);

    xcb_gcontext_t txtf = xcb_generate_id(c);
    uint32_t txtf_mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
    uint32_t txtf_value[] = {screen->white_pixel, screen->black_pixel, font};
    xcb_create_gc(c, txtf, win, txtf_mask, txtf_value);
    xcb_close_font(c, font);

    const char *str = "Hello text";
    xcb_image_text_8(c, strlen(str), win, txtf, 0, 0, str);*/

    xcb_generic_event_t *e;
    while (isWindowActive && (e = xcb_wait_for_event(c))) {
        switch (e->response_type & ~0x80) {
            case XCB_EXPOSE: {
                break;
            }

            case XCB_KEY_PRESS: {
                xcb_key_press_event_t *ev = (xcb_key_press_event_t *)e;
                Key key;
                switch (ev->detail) {
                    case 111:
                        key = Key::UP_PRESS;
                        break;
                    case 113:
                        key = Key::LEFT_PRESS;
                        break;
                    case 114:
                        key = Key::RIGHT_PRESS;
                        break;
                    case 116:
                        key = Key::DOWN_PRESS;
                        break;
                    default:
                        key = Key::NONE;
                        break;
                }
                if (key != Key::NONE) {
                    key_handler(key);
                }
                break;
            }

            case XCB_KEY_RELEASE: {
                xcb_key_release_event_t *ev = (xcb_key_release_event_t *)e;
                Key key;
                switch (ev->detail) {
                    case 111:
                        key = Key::UP_RELEASE;
                        break;
                    case 113:
                        key = Key::LEFT_RELEASE;
                        break;
                    case 114:
                        key = Key::RIGHT_RELEASE;
                        break;
                    case 116:
                        key = Key::DOWN_RELEASE;
                        break;
                    default:
                        key = Key::NONE;
                        break;
                }
                if (key != Key::NONE) {
                    key_handler(key);
                }
                break;
            }

            case XCB_CLIENT_MESSAGE: {
                if (((xcb_client_message_event_t *)e)->data.data32[0] ==
                    reply2->atom) {
                    isWindowActive = false;
                }
                break;
            }

            default:
                break;
        }
        free(e);
    }

    xcb_disconnect(c);

    pthread_exit((void *)0);
}