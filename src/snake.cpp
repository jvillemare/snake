#include <iostream>
#include <curses.h>
#include <string>
#include <thread>
#include <vector>
#include <ctime>
#include "game.h"
#include "platform/controls.h"

using namespace std;

void exit_handler(int s)
{
    printf("Caught signal %d\n", s);
    exit(1);
}

/*
 * 1. setup board
 * 2. randomly place head of snake
 * 3. randomly place bits
 * 3. poll for input
 * 4. move the parent and then the children
 */

int main()
{
    // register signal handler
    signal(SIGINT, exit_handler);
    // seed random with the current time
    srand(time({}));

    Game *game = new Game(5, 5);

    // put the food in a random place
    game->place_food();

    // get platform agnostics controls for the shell
    Controls *controls = new Controls();
    controls->setup();

    bool keep_playing = true;

    while (keep_playing)
    {
        // clear screen
        clear();
        controls->print("Score: %d\n", game->score);

        if (game->has_player_won())
        {
            controls->print("You have won! Press any key to quit\n");
            refresh();
            char c = controls->get_user_input();
            break;
        }

        controls->print(game->generate_board().c_str());

        controls->print("Press WASD or arrow keys to move, or escape to quit... ");

        char c = controls->get_user_input();

        switch (c)
        {
            case KEY_UP:
            case 3:   // arrow keys
            case 119: // W
                game->move_snake(North);
                break;
            case KEY_DOWN:
            case 2:   // arrow keys
            case 115: // S
                game->move_snake(South);
                break;
            case KEY_LEFT:
            case 4:  // arrow keys
            case 97: // A
                game->move_snake(West);
                break;
            case KEY_RIGHT:
            case 5:   // arrow keys
            case 100: // D
                game->move_snake(East);
                break;
            case 27: // escape
                keep_playing = false;
                break;
            default:
                break;
            }
        refresh();
    }

    controls->teardown();

    return 0;
}
