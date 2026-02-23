#include <conio.h>
#include <stdlib.h>
#include "controls.h"

void Controls::setup() {
}

void Controls::clear_shell() {
    system("cls");
}

void Controls::refresh_shell() {
}

int Controls::print(const char *input, const char *var) {
    return _cprintf(input, var);
}

int Controls::print(const char *input, const int var) {
    return _cprintf(input, var);
}

int Controls::print(const char *input) {
    return _cprintf(input);
}

char Controls::get_user_input() {
    return _getch();
}

void Controls::teardown() {
}
