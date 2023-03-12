#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

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
class GameWindow {
private:
    // window data
    sf::RenderWindow *window;
public:
    // window constructor
    GameWindow(int _width = 1920, int _height = 1080) {
        window = new sf::RenderWindow(sf::VideoMode(_width, _height), "Snake", sf::Style::Default);
    }

    // window operator<<
    friend std::ostream& operator<<(std::ostream& os, const GameWindow& _gameWindow) {
        os << "Window dimensions: " << _gameWindow.window->getSize().x << 'x' << _gameWindow.window->getSize().y << '\n';
        return os;
    }

    // window width setter
    void setWidth(int _width) {
        window->setSize(sf::Vector2u(_width, window->getSize().y));
    }

    // window height setter
    void setHeight(int _height) {
        window->setSize(sf::Vector2u(window->getSize().x, _height));
    }

    // window getter
    sf::RenderWindow* getWindow() {
        return window;
    }

    // window copy constructor
    GameWindow(const GameWindow &other) {
        window = other.window;
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
        std::cout << "PowerUps available:\n\n";
        for (Cell cell : world.powerUps)
            std::cout << cell << '\n';
        return os;
    }
};

// The game
class Game {
private:
    // game data
    World world;
    GameWindow window;
public:
    // game constructors
    Game() = default;
    Game(const World &_world, const GameWindow &_window) : world(_world), window(_window) {}

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

    // window getter
    sf::RenderWindow* getWindow() {
        return window.getWindow();
    }
};

int main() {
    #ifdef __linux__
    XInitThreads();
    #endif

    Game game;
    while (game.getWindow()->isOpen()) {
        // game.handleInput();
        // game.update();
        // game.render();
    }
    return 0;
}
