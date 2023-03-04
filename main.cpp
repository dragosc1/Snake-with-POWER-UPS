#include <iostream>
#include <vector>

// A cell on the screen
class Cell {
private:
    int x, y;
public:
    // constructor
    Cell(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    // getters si setters
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int _x) { x = _x; }
    void setY(int _y) { y = _y; }
};

// The window in which the game is played
class Window {
private:
    int width;
    int height;
public:
    Window(int _width = 1920, int _height = 1080) : width(_width), height(_height) {}
    int getHeight() const { return height; }
    int getWidth() const { return width; }
    void setHeight(int _height) { height = _height; }
    void setWidth(int _width) { width = _width; }
};

class Snake {
private:
    std::vector<Cell> body;
public:
    Snake() {

    }
    Snake(const std::vector<Cell>& _body) : body(_body) {}
};

class World {
private:
    Snake snake;
    Cell fruit;
public:

};

class Game {
private:
    World world;
    Window window;
    int cellSize;
public:
    Game() {
    }
};

int main() {
    Game game;

    return 0;
}