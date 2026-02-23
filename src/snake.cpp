#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <ctime>
#include "game.h"
#include "platform/controls.h"

using namespace std;

/*
 * 1. setup board
 * 2. randomly place head of snake
 * 3. randomly place bits
 * 3. poll for input
 * 4. move the parent and then the children
 */

int main()
{
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
        controls->clear_shell();
        controls->print("Score: %d\n", game->score);

        if (game->has_player_won())
        {
            controls->print("You have won! Press any key to quit\n");
            controls->refresh_shell();
            char c = controls->get_user_input();
            break;
        }

        controls->print(game->generate_board().c_str());

        controls->print("Press WASD or arrow keys to move, or escape to quit... ");

        char c = controls->get_user_input();

        switch (c)
        {
            case 3:   // arrow keys
            case 119: // Mac: W
            case 72: // Win: Up arrow
                game->move_snake(North);
                break;
            case 2:   // arrow keys
            case 115: // Mac: S
            case 80: // Win: Down arrow
                game->move_snake(South);
                break;
            case 4:  // arrow keys
            case 97: // A
            case 75: // Win: Right arrow
                game->move_snake(West);
                break;
            case 5:   // arrow keys
            case 100: // D
            case 77: // Win: Left arrow
                game->move_snake(East);
                break;
            case 27: // escape
                keep_playing = false;
                break;
            default:
                break;
            }
        controls->refresh_shell();
    }

    controls->teardown();

    return 0;
}
