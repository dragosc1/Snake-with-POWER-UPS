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

enum class Direction {
    NONE,
    Up,
    Down,
    Left,
    Right
};

// A cell on the screen
class Cell {
private:
    // cell data
    int x, y, cellSize;
public:
    // cell constructor
    explicit Cell(int _x = 0, int _y = 0, int _cS = 16) : x(_x), y(_y), cellSize(_cS) {}

    // cell copy constructor
    Cell(const Cell& other) : x(other.x), y(other.y), cellSize(other.cellSize) {}

    // cell operator=
    Cell& operator= (const Cell& other) {
        x = other.x;
        y = other.y;
        cellSize = other.cellSize;
        return *this;
    }

    // cell getters
    int getX() const { return x; }
    int getY() const { return y; }
    int getCellSize() { return cellSize; }

    // cell setter
    void set(const Cell &other) {
        x = other.x;
        y = other.y;
        cellSize = other.cellSize;
    }

    void setX(int _x) { x = _x; }
    void setY(int _y) { y = _y; }

    // cell destructor
    ~Cell() = default;

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
    sf::RenderWindow window;
    bool isdone, isFullscreen;
    sf::Vector2u windowSize;
    std::string windowTitle;
public:
    // window constructor
    GameWindow(int _width = 1920, int _height = 1080) {
        setup("Snake", sf::Vector2u(_width, _height));
        window.setFramerateLimit(60);
    }

    // window setup
    void setup(const std::string& title, const sf::Vector2u& size) {
        windowTitle = title;
        windowSize = size;
        isFullscreen = false;
        isdone = false;
        create();
    }

    // window create
    void create() {
        auto style = (isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        window.create({ windowSize.x, windowSize.y, 32 }, windowTitle, style);
    }

    // destroy window
    void destroy() {
        window.close();
    }

    // window operator<<
    friend std::ostream& operator<<(std::ostream& os, const GameWindow& _gameWindow) {
        os << "Window dimensions: " << _gameWindow.window.getSize().x << 'x' << _gameWindow.window.getSize().y << '\n';
        return os;
    }

    // window width setter
    void setWidth(int _width) {
        window.setSize(sf::Vector2u(_width, window.getSize().y));
    }

    // window height setter
    void setHeight(int _height) {
        window.setSize(sf::Vector2u(window.getSize().x, _height));
    }

    // window getter
    sf::RenderWindow* getWindow() {
        return &window;
    }

    // window begin draw
    void beginDraw() {
        window.clear(sf::Color::Black);
    }

    // window end draw
    void endDraw() {
        window.display();
    }

    // window draw
    void draw(sf::Drawable& drawable) {
        window.draw(drawable);
    }

    // window update
    void update() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isdone = true;
            }
            else if (event.type == sf::Event::KeyPressed &&
                     event.key.code == sf::Keyboard::F5) {
                toggleFullscreen();
            }
        }
    }

    bool isDone() {
        return isdone;
    }

    // window destructor
    ~GameWindow() {
        destroy();
    }

    // toggle fullscreen
    void toggleFullscreen() {
        isFullscreen = !isFullscreen;
        destroy();
        create();
    }

};

// The snake
class Snake {
private:
    // snake data
    std::vector<Cell> body;
    int speed, score;
    bool lost;
    Direction dir;
public:
    // snake constructors
    Snake() { reset(); }

    // reset snake
    void reset() {
        body.clear();
        body.push_back(Cell(5, 7));
        body.push_back(Cell(5, 6));
        body.push_back(Cell(5, 5));

        setDirection(Direction::NONE); // snake direction is still
        speed = 15;
        score = 0;
        lost = false;
    }

    // snake direciton setter
    void setDirection(Direction _dir) { dir = _dir; }

    // snake direction getter
    Direction getDirection() { return dir; }

    // snake get speed
    int getSpeed() { return speed; }

    // get snake score
    int getScore() { return score; }

    // snake lost
    bool hasLost() { return lost; }

    // increase score
    void increaseScore() { score++; }

    // snake has lost
    void lose() { lost = true; }

    // extend the snake
    void extend() {
        if (body.empty())
            return;
        const Cell& tailHead = body[body.size() - 1];
        if (body.size() > 1) {
            Cell& tailBone = body[body.size() - 2];
            if (tailHead.getX() == tailBone.getX()) {
                if (tailHead.getY() > tailBone.getY()) {
                    body.push_back(Cell(tailHead.getX(), tailHead.getY() + 1));
                }
                else {
                    body.push_back(Cell(tailHead.getX(), tailHead.getY() - 1));
                }
            }
            else if (tailHead.getY() == tailBone.getY()) {
                if (tailHead.getX() > tailBone.getX()) {
                    body.push_back(Cell(
                            tailHead.getX() + 1, tailHead.getY()));
                }
                else {
                    body.push_back(Cell(
                            tailHead.getX() - 1, tailHead.getY()));
                }
            }
        }
        else {
            if (dir == Direction::Up) {
                body.push_back(Cell(
                        tailHead.getX(), tailHead.getY() + 1));
            }
            else if (dir == Direction::Down) {
                body.push_back(Cell(
                        tailHead.getX(), tailHead.getY() - 1));
            }
            else if (dir == Direction::Left) {
                body.push_back(Cell(
                        tailHead.getX() + 1, tailHead.getY()));
            }
            else if (dir == Direction::Right) {
                body.push_back(Cell(
                        tailHead.getX() - 1, tailHead.getY()));
            }
        }
    }

    void move() {
        for (int i = body.size() - 1; i > 0; --i)
            body[i] = body[i - 1];
        if (dir == Direction::Left)
            body[0].setX(body[0].getX() - 1);
        else if (dir == Direction::Right)
            body[0].setX(body[0].getX() + 1);
        else if (dir == Direction::Up)
            body[0].setY(body[0].getY() - 1);
        else if (dir == Direction::Down)
            body[0].setY(body[0].getY() + 1);
    }

    Direction getPhysicalDirection() {
        if (body.size() <= 1) {
            return Direction::NONE;
        }
        const Cell& head = body[0];
        const Cell& neck = body[1];
        if (head.getX() == neck.getX()) {
            return (head.getY() > neck.getY()
                    ? Direction::Down : Direction::Up);
        }
        else if (head.getY() == neck.getY()) {
            return (head.getX() > neck.getX()
                    ? Direction::Right : Direction::Left);
        }
        return Direction::NONE;
    }

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
    sf::RectangleShape bounds[4];
    sf::CircleShape appleShape;
public:
    // world constructors
    World(const Snake &_snake, const Cell &_fruit, const std::vector<Cell> &pU) : snake(_snake), fruit(_fruit), powerUps(pU) {}
    World() {
        appleShape.setFillColor(sf::Color::Red);
        appleShape.setRadius(8);
    }
    // world operator<<
    friend std::ostream& operator<<(std::ostream& os, const World& world) {
        os << world.snake << '\n' << "Fruit: \n" << world.fruit << '\n';
        std::cout << "PowerUps available:\n\n";
        for (Cell cell : world.powerUps)
            std::cout << cell << '\n';
        return os;
    }

    void render(sf::RenderWindow* _window) {
        for (int i = 0; i < 4; ++i) {
            _window->draw(bounds[i]);
        }
        _window->draw(appleShape);
    }

    Snake getSnake() {
        return snake;
    }

    // world destructor
    ~World() {}
};

// The game
class Game {
private:
    // game data
    World world;
    GameWindow window;
    float timespent = 0, timestep = 750;
    sf::Clock clock;
    sf::Time elapsed;
public:
    // game constructors
    Game() = default;
    explicit Game(const World &_world) : world(_world) {}

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

    GameWindow* getWindow2() {
        return &window;
    }

    // render game
    void render() {
        window.beginDraw();
        world.render(window.getWindow());
        window.endDraw();
    }

    // handle the input
    void handleInput() {
        window.update();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            && world.getSnake().getPhysicalDirection() != Direction::Down) {
            world.getSnake().setDirection(Direction::Up);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
                 && world.getSnake().getPhysicalDirection() != Direction::Up) {
            world.getSnake().setDirection(Direction::Down);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                 && world.getSnake().getPhysicalDirection() != Direction::Right) {
            world.getSnake().setDirection(Direction::Left);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                 && world.getSnake().getPhysicalDirection() != Direction::Left) {
            world.getSnake().setDirection(Direction::Right);
        }
    }

    // game update
    void update() {
        window.update(); // Update window events.
        if (timespent >= timestep) {
            if (world.getSnake().hasLost()) {
                world.getSnake().reset();
            }
            timespent = 0;
        }
        else timespent++;
    }

    // game destructor
    ~Game() {}
};

int main() {
    #ifdef __linux__
    XInitThreads();
    #endif

    Game game;
    std::cout << game;
    while (!game.getWindow2()->isDone()) {
          game.handleInput();
          game.update();
          game.render();
    }
    return 0;
}
