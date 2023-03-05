#include <iostream>
#include <vector>

// A cell on the screen
class Cell {
private:
    // cell data
    int x, y, cellSize;
public:
    // cell constructor
    Cell(int _x = 0, int _y = 0, int _cS = 10) : x(_x), y(_y), cellSize(_cS) {}

    // cell copy constructor
    Cell(const Cell& other) : x(other.x), y(other.y), cellSize(other.cellSize) {}

    // cell operator=
    Cell& operator= (const Cell& other) {
        x = other.x;
        y = other.y;
        cellSize = other.cellSize;
        return *this;
    }

    // cell destructor
    ~Cell() {}

    // cell operator<<
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell) {
        os << "Cell:\t" << "X=" << cell.x << "; Y=" << cell.y << "; Size=" << cell.cellSize << '\n';
        return os;
    }
};

// The window
class Window {
private:
    // window data
    int width;
    int height;
public:
    // window constructor
    Window(int _width = 1920, int _height = 1080) : width(_width), height(_height) {}

    // window operator<<
    friend std::ostream& operator<<(std::ostream& os, const Window& window) {
        os << "Window dimensions: " << window.width << 'x' << window.height << '\n';
        return os;
    }

    // window width setter
    void setWidth(int _width) {
        width = _width;
    }

    // window height setter
    void setHeight(int _height) {
        height = _height;
    }
};

// The snake
class Snake {
private:
    // snake data
    std::vector<Cell> body;
public:
    // snake constructors
    Snake() { body.resize(3); }
    explicit Snake(const std::vector<Cell>& _body) : body(_body) {}

    // snake operator<<
    friend std::ostream& operator<<(std::ostream& os, const Snake& snake) {
        os << "Snake cells:\n";
        for (Cell cell : snake.body) os << cell << '\n';
        return os;
    }
};

// The World
class World {
private:
    // world data
    Snake snake;
    Cell fruit;
    std::vector<Cell> powerUps;
public:
    // world constructors
    World() = default;
    World(const Snake &_snake, const Cell &_fruit, const std::vector<Cell> &pU) : snake(_snake), fruit(_fruit), powerUps(pU) {}

    // world operator<<
    friend std::ostream& operator<<(std::ostream& os, const World& world) {
        os << world.snake << '\n' << "Fruit: \n" << world.fruit << '\n';
        return os;
    }
};

// The game
class Game {
private:
    // game data
    World world;
    Window window;
public:
    // game constructors
    Game() = default;
    Game(const World &_world, const Window &_window) : world(_world), window(_window) {}

    // game operator<<
    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
        os << game.world << game.window << '\n';
        return os;
    }

    // window setter
    void setWindow(int _width = 1920, int _height = 1080) {
        window.setWidth(_width);
        window.setHeight(_height);
    }
};

int main() {
    // declare and display the default values of the game object
    Game game;
    std::cout << game;

    // set the window to 800x600 and then display the changes
    game.setWindow(800, 600);
    std::cout << game;
    return 0;
}