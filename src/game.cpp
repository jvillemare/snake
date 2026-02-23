#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <string>
#include "game.h"

using namespace std;

Game::Game(int given_rows, int given_cols)
{
    // setup the board
    rows = given_rows;
    cols = given_cols;
    board = (GameObject ***)malloc(rows * sizeof(GameObject **));
    for (int r = 0; r < rows; r++)
    {
        board[r] = (GameObject **)malloc(cols * sizeof(GameObject *));
        for (int c = 0; c < cols; c++)
        {
            board[r][c] = new GameObject();
        }
    }

    // put the snake in a random place
    const int random_x = rand() % cols;
    const int random_y = rand() % rows;

    head = new SnakeNode();
    head->x = random_x;
    head->y = random_y;
    head->is_head = true;
    board[random_y][random_x]->snake = head;
}

bool Game::move_snake(int x, int y)
{
    // prevent going out of bounds
    int future_x = this->head->x + x;
    int future_y = this->head->y + y;
    if (future_x < 0 || future_x >= this->rows || future_y < 0 || future_y >= this->cols)
    {
        return false;
    }

    // clear the board
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            board[r][c]->snake = NULL;
        }
    }

    // move head
    int prev_x = this->head->x;
    int prev_y = this->head->y;

    this->head->x += x;
    this->head->y += y;

    bool did_eat = false;
    if (this->board[this->head->y][this->head->x]->food != NULL)
    {
        // there is food here, eat it
        this->score += 1;
        this->board[this->head->y][this->head->x]->food = NULL;

        // add child
        SnakeNode *last = this->head;
        while (last->child) {
            last = last->child;
        }
        last->child = new SnakeNode();
        last->child->is_head = false;
        last->child->x = last->x;
        last->child->y = last->y;

        did_eat = true;
    }

    // move children
    SnakeNode *c = this->head->child;
    int i_x;
    int i_y;
    while (c)
    {
        i_x = c->x;
        i_y = c->y;
        c->x = prev_x;
        c->y = prev_y;
        prev_x = i_x;
        prev_y = i_y;
        c = c->child;
    }

    // refill the board
    c = this->head;
    while (c) {
        this->board[c->y][c->x]->snake = c;
        c = c->child;
    }

    if (did_eat) {
        for (int i = 0; i < this->score; i++) {
            this->place_food();
        }
    }

    return true;
}

bool Game::move_snake(Direction d)
{
    switch (d)
    {
    case North:
        return move_snake(0, -1);
    case East:
        return move_snake(1, 0);
    case South:
        return move_snake(0, 1);
    case West:
        return move_snake(-1, 0);
    default:
        return false;
    }
}

bool Game::has_player_won()
{
    // score threshold
    if (this->score > 5)
    {
        return true;
    }
    // player takes up the entire board
    for (int r = 0; r < this->rows; r++)
    {
        for (int c = 0; c < this->cols; c++)
        {
            if (this->board[r][c]->snake == NULL)
            {
                return false;
            }
        }
    }
    return true;
}

// place food in a random place
void Game::place_food()
{
    while (true)
    {
        const int food_random_x = rand() % this->cols;
        const int food_random_y = rand() % this->rows;

        if (this->board[food_random_y][food_random_x]->snake != NULL)
        {
            // there is a snake here, try again
            continue;
        }

        FoodNode food;
        food.x = food_random_x;
        food.y = food_random_y;

        this->board[food_random_y][food_random_x]->food = &food;
        break;
    }
}

string Game::generate_board()
{
    string base = "";
    for (int r = 0; r < this->rows; r++)
    {
        for (int c = 0; c < this->cols; c++)
        {
            if (this->board[r][c] == NULL)
            {
                base.append("0 ");
            }
            else
            {
                if (this->board[r][c]->snake != NULL)
                {
                    if (this->board[r][c]->snake->is_head) {
                        base.append("O ");
                    } else {
                        base.append("o ");
                    }
                }
                else if (this->board[r][c]->food != NULL)
                {
                    base.append("* ");
                }
                else
                {
                    base.append(". ");
                }
            }
        }
        base.append("\n");
    }
    return base;
}

Game::~Game()
{
    for (int i = 0; i < this->rows; ++i)
    {
        delete[] this->board[i];
    }
    delete[] this->board; // Delete the array of pointers
    this->board = nullptr;
    cout << "Memory deallocated" << endl;
}
