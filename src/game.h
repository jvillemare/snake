#include <string>

using namespace std;

enum Direction { North, East, South, West };

class FoodNode {
  public:
    int x;
    int y;
};

class SnakeNode {
  public:
    int x;
    int y;
    Direction dir;
    bool is_head;
    SnakeNode* child;
};

// the different objects that can occupy a space in the board
class GameObject {
  public:
    SnakeNode *snake;
    FoodNode *food;
};

class Game {
  private:
    int rows;
    int cols;
  public:
    int score = 0;
    SnakeNode *head;
    GameObject ***board;

    Game(int given_rows, int given_cols);

    // move the snake an amount
    bool move_snake(int x, int y);

    // move the snake in a direction
    bool move_snake(Direction d);

    // detect if a player has met the win condition
    bool has_player_won();

    // place food randomly wherever the user is not
    void place_food();

    // make the current board
    string generate_board();

    ~Game();
};

