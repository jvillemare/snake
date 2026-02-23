#include <curses.h>
#include "controls.h"

void Controls::setup() {
    initscr();              // initialize the window
    cbreak();               // line buffering disabled
    noecho();               // don't echo input
    keypad(stdscr, TRUE);   // enable function keys and arrow keys
}

void Controls::clear_shell() {
    clear();
}

void Controls::refresh_shell() {
    refresh();
}

int Controls::print(const char *input, const char *var) {
    return printw(input, var);
}

int Controls::print(const char *input, const int var) {
    return printw(input, var);
}

int Controls::print(const char *input) {
    return printw(input);
}

char Controls::get_user_input() {
    return getch();
}

void Controls::teardown() {
    endwin();  // restore original terminal mode
}
