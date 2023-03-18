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
    int x, y;
public:
    // cell constructor
    explicit Cell(int _x = 0, int _y = 0) : x(_x), y(_y) {}

    // cell copy constructor
    Cell(const Cell& other) : x(other.x), y(other.y) {}

    // cell operator=
    Cell& operator= (const Cell& other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    std::pair<int, int> position() {
        return {x, y};
    }

    // cell getters
    int getX() const { return x; }
    int getY() const { return y; }

    void setX(int _x) { x = _x; }
    void setY(int _y) { y = _y; }

    // cell destructor
    ~Cell() = default;

    // cell operator<<
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell) {
        os << "Cell:\t" << "X=" << cell.x << "; Y=" << cell.y << '\n';
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
    GameWindow(int _width = 800, int _height = 600) {
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
    sf::Vector2u windowSize;
    int cellSize;
public:
    // snake constructors
    Snake(const int& _cellSize) : cellSize(_cellSize) {
        reset();
    }
    // reset snake
    void reset() {
        body.clear();
        body.push_back(Cell(5, 7));
        body.push_back(Cell(5, 6));
        body.push_back(Cell(5, 5));

        setDirection(Direction::NONE); // snake direction is still
        score = 0;
        lost = false;
    }

    // snake direciton setter
    void setDirection(Direction _dir) { dir = _dir; }

    // snake lost
    bool hasLost() { return lost; }

    // snake direction getter
    Direction getDirection() { return dir; }

    // snake get speed
    int getSpeed() { return speed; }

   // get snake score
   int getScore() { return score; }

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
        for (const Cell& cell : snake.body) os << cell << '\n';
        return os;
    }

    // snake tick
    void tick() {
        if (body.empty()) { return; }
        if (dir == Direction::NONE) { return; }
        move();
        checkCollision();
    }

    // snake check collision
    void checkCollision() {
        if (body.size() < 5) { return; }
        Cell& head = body.front();
        for (auto itr = body.begin() + 1; itr != body.end(); ++itr)
            if (itr->position() == head.position()) {
                int segments = body.end() - itr;
                reset();
                break;
            }
    }

    // snake render
    void render(sf::RenderWindow* _window) {
        if (body.empty()) { return; }
        auto head = body.begin();
        sf::RectangleShape bodyRect;
        bodyRect.setFillColor(sf::Color::Green);
        bodyRect.setPosition(head->getX() * cellSize,head->getY() * cellSize);
        bodyRect.setSize(sf::Vector2f(cellSize, cellSize));
        _window->draw(bodyRect);
        bodyRect.setFillColor(sf::Color::Green);
        for (auto itr = body.begin() + 1; itr != body.end(); ++itr) {
            bodyRect.setPosition(itr->getX() * cellSize,itr->getY() * cellSize);
            _window->draw(bodyRect);

        }
    }
};

// The World
class World {
private:
    // world data
    Snake snake;
    std::vector<Cell> powerUps;
    sf::RectangleShape bounds[4];
    sf::CircleShape fruitShape;
    sf::Vector2u windowSize;
    int cellSize;
public:
    // world constructors
    World() = default;
    World(const sf::Vector2u& _windowSize) : windowSize(_windowSize), snake(cellSize = 16) {
        fruitShape.setFillColor(sf::Color::Red);
        fruitShape.setRadius(8);
        cellSize = 16;
        setRandomFruitPosition();
    }
    // apple random position
    void setRandomFruitPosition() {
        int maxX = windowSize.x - 2;
        int maxY = windowSize.y - 2;
        int x = 1LL * rand() * rand() % (maxX / cellSize) * cellSize;
        int y = 1LL * rand() * rand() % (maxY / cellSize) * cellSize;
        fruitShape.setPosition(sf::Vector2f(x, y));
    }
    // world operator<<
    friend std::ostream& operator<<(std::ostream& os, const World& world) {
        os << world.snake << '\n' << "Fruit:\t" << "X=" << world.fruitShape.getPosition().x << "; Y=" << world.fruitShape.getPosition().y << '\n';
        std::cout << "PowerUps available:\n\n";
        for (Cell cell : world.powerUps)
            std::cout << cell << '\n';
        return os;
    }

    void render(sf::RenderWindow* _window) {
        for (int i = 0; i < 4; ++i) {
            _window->draw(bounds[i]);
        }
        _window->draw(fruitShape);
    }

    Snake& getSnake() {
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
    Game() : world(sf::Vector2u(800, 600)), window() {}

    // game operator<<
    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
        os << game.world << game.window;
        return os;
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
        world.getSnake().render(window.getWindow());
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
    srand(time(0));
    #ifdef __linux__
    XInitThreads();
    #endif

    Game game;
    while (!game.getWindow2()->isDone()) {
        game.handleInput();
        game.update();
        game.render();
    }
    return 0;
}
