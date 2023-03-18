#include <SFML/Graphics.hpp>
#include <iostream>

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

    // cell operator==
    bool operator== (const Cell& other) const { return (x == other.x && y == other.y); }

    std::pair<int, int> position() {
        return {x, y};
    }

    // cell getters
    int getX() const { return x; }
    int getY() const { return y; }

    // cell setters
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
        os << "Window title: " << _gameWindow.windowTitle << '\n';
        os << "Window fullScreen: " << (_gameWindow.isFullscreen ? "Yes\n" : "No\n");
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
    void draw(const sf::Drawable& drawable) {
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
    float speed;
    int score, speedTime;
    bool lost;
    Direction dir;
    int cellSize;
public:
    // snake constructors
    explicit Snake(const int& _cellSize) : cellSize(_cellSize) {
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
        speed = 1;
        speedTime = 1e9;
        lost = false;
    }

    // snake direciton setter
    void setDirection(const Direction &_dir) { dir = _dir; }

    // snake lost
    bool hasLost() { return lost; }

    // snake get speed
    float getSpeed() { return speed; }

    // snake get position
    Cell getPosition() { return body[0]; }

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
               if (tailHead.getY() > tailBone.getY())
                   body.push_back(Cell(tailHead.getX(), tailHead.getY() + 1));
               else
                   body.push_back(Cell(tailHead.getX(), tailHead.getY() - 1));
           }
           else if (tailHead.getY() == tailBone.getY()) {
               if (tailHead.getX() > tailBone.getX()) {
                   body.push_back(Cell(tailHead.getX() + 1, tailHead.getY()));
               }
               else {
                   body.push_back(Cell(tailHead.getX() - 1, tailHead.getY()));
               }
           }
       }
       else {
           if (dir == Direction::Up) {
               body.push_back(Cell(tailHead.getX(), tailHead.getY() + 1));
           }
           else if (dir == Direction::Down) {
               body.push_back(Cell(tailHead.getX(), tailHead.getY() - 1));
           }
           else if (dir == Direction::Left) {
               body.push_back(Cell(tailHead.getX() + 1, tailHead.getY()));
           }
           else if (dir == Direction::Right) {
               body.push_back(Cell(tailHead.getX() - 1, tailHead.getY()));
           }
       }
   }

   // snake move
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

   // get physicial direction
    Direction getPhysicalDirection() {
        const Cell& head = body[0];
        const Cell& neck = body[1];
        if (head.getX() == neck.getX()) { return (head.getY() > neck.getY() ? Direction::Down : Direction::Up); }
        else if (head.getY() == neck.getY()) { return (head.getX() > neck.getX() ? Direction::Right : Direction::Left); }
        return Direction::NONE;
    }

    // snake operator<<
    friend std::ostream& operator<<(std::ostream& os, const Snake& snake) {
        os << "Snake cells:\n";
        for (const Cell& cell : snake.body) os << cell << '\n';
        os << "Snake speed: " << snake.speed << '\n';
        os << "Snake score: " << snake.score << "\n\n";
        return os;
    }

    // snake tick
    void tick() {
        if (body.empty()) { return; }
        if (dir == Direction::NONE) { return; }
        speedTime--;
        if (speedTime == 0)
            speed = 1;
        move();
        checkCollision();
    }

    // snake check collision
    void checkCollision() {
        if (body.size() < 5) { return; }
        Cell& head = body.front();
        for (auto itr = body.begin() + 1; itr != body.end(); ++itr)
            if (itr->position() == head.position()) {
                lose();
                break;
            }
    }

    // slow time
    void slowTime() {
        speed = speed * 1.0 / 2;
        speedTime = 30;
    }

    // snake render
    void render(sf::RenderWindow* _window) {
        if (body.empty()) { return; }
        auto head = body.begin();
        sf::RectangleShape bodyRect;
        bodyRect.setFillColor(sf::Color(0, 195, 50));
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
    sf::CircleShape slowTimeShape;
    Cell slowTime;
    sf::RectangleShape bounds[4];
    sf::CircleShape fruitShape;
    sf::Vector2u windowSize;
    int cellSize;
    Cell fruit;
public:
    // world constructors
    explicit World(const sf::Vector2u& _windowSize) : snake(cellSize = 16), windowSize(_windowSize) {
        fruitShape.setFillColor(sf::Color::Red);
        fruitShape.setRadius(8);
        setRandomFruitPosition();
        slowTimeShape.setFillColor(sf::Color::Blue);
        slowTimeShape.setRadius(8);
        setRandomSlowTimePosition();
        cellSize = 16;
        for (int i = 0; i < 4; ++i) {
            bounds[i].setFillColor(sf::Color(100, 100, 100));
            if (((i + 1) & 1) == 0) {
                bounds[i].setSize(sf::Vector2f(windowSize.x, cellSize));
            }
            else bounds[i].setSize(sf::Vector2f(cellSize, windowSize.y));
            if (i < 2) bounds[i].setPosition(0, 0);
            else {
                bounds[i].setOrigin(bounds[i].getSize());
                bounds[i].setPosition(sf::Vector2f(windowSize));
            }
        }
    }

    // fruit random position
    void setRandomFruitPosition() {
        int maxX = (windowSize.x / cellSize) - 2;
        int maxY = (windowSize.y / cellSize) - 2;
        int x = 1LL * rand() * rand() % maxX + 1;
        int y = 1LL * rand() * rand() % maxY + 1;
        fruit = Cell(x, y);
        fruitShape.setPosition(sf::Vector2f(x * cellSize, y * cellSize));
    }

    // fruit random position
    void setRandomSlowTimePosition() {
        int maxX = (windowSize.x / cellSize) - 2;
        int maxY = (windowSize.y / cellSize) - 2;
        int x = 1LL * rand() * rand() % maxX + 1;
        int y = 1LL * rand() * rand() % maxY + 1;
        slowTime = Cell(x, y);
        slowTimeShape.setPosition(sf::Vector2f(x * cellSize, y * cellSize));
    }

    // world operator<<
    friend std::ostream& operator<<(std::ostream& os, const World& world) {
        os << world.snake << "Fruit:\t" << "X=" << world.fruitShape.getPosition().x << "; Y=" << world.fruitShape.getPosition().y << '\n';
        os << "PowerUps available:\n";
        os << "Slow time:\t" << "X=" << world.slowTimeShape.getPosition().x << "; Y=" << world.slowTimeShape.getPosition().y << "\n\n";
        os << "Cell size: " << world.cellSize << '\n';
        return os;
    }

    // window render bounds
    void render(sf::RenderWindow* _window) {
        for (int i = 0; i < 4; ++i) {
            _window->draw(bounds[i]);
        }
        _window->draw(fruitShape);
        _window->draw(slowTimeShape);
    }

    // get snake
    Snake* getSnake() {
        return &snake;
    }

    // update snake
    void update(Snake* _snake) {
        if (_snake->getPosition() == slowTime) {
            _snake->slowTime();
            setRandomSlowTimePosition();
        }
        if (_snake->getPosition() == fruit) {
            _snake->extend();
            _snake->increaseScore();
            setRandomFruitPosition();
        }
        int gridSize_x = windowSize.x / cellSize;
        int gridSize_y = windowSize.y / cellSize;
        if (_snake->getPosition().getX() <= 0 ||
            _snake->getPosition().getY() <= 0 ||
            _snake->getPosition().getX() >= (gridSize_x - 1) ||
            _snake->getPosition().getY() >= (gridSize_y - 1))
            _snake->lose();
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
    float timespent = 0, timestep = 10;
    sf::Text score;
    sf::Font font;
public:
    // game constructors
    Game() : world(sf::Vector2u(800, 600)), window() {
        font.loadFromFile("arial.ttf");
        score.setFont(font);
        score.setString("Score: ");
        score.setPosition(sf::Vector2f(700, 16));
        score.setCharacterSize(20);
        score.setFillColor(sf::Color::White);
    }

    // game draw score
    void drawScore() {
        score.setString("Score: " + std::to_string(world.getSnake()->getScore()));
        window.getWindow()->draw(score);
    }

    // game operator<<
    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
        os << game.world << game.window << "Time spent: " << game.timespent << '\n' << "Time step: " << game.timestep << '\n';
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
        drawScore();
        world.render(window.getWindow());
        world.getSnake()->render(window.getWindow());
        window.endDraw();
    }

    // handle the input
    void handleInput() {
        window.update();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            && world.getSnake()->getPhysicalDirection() != Direction::Down) {
            world.getSnake()->setDirection(Direction::Up);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
                 && world.getSnake()->getPhysicalDirection() != Direction::Up) {
            world.getSnake()->setDirection(Direction::Down);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                 && world.getSnake()->getPhysicalDirection() != Direction::Right) {
            world.getSnake()->setDirection(Direction::Left);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                 && world.getSnake()->getPhysicalDirection() != Direction::Left) {
            world.getSnake()->setDirection(Direction::Right);
        }
    }

    // game update
    void update() {
        window.update(); // Update window events.
        if (timespent >= timestep) {
            world.getSnake()->tick();
            world.update(world.getSnake());
            if (world.getSnake()->hasLost()) {
                world.getSnake()->reset();
                world.setRandomFruitPosition();
            }
            timespent = 0.f;
        }
        else timespent += world.getSnake()->getSpeed();
    }

    // game destructor
    ~Game() {}
};

int main() {
    srand(time(NULL));

    Game game;
    std::cout << "GAME INFO:\n\n";
    std::cout << game;
    while (!game.getWindow2()->isDone()) {
        game.handleInput();
        game.update();
        game.render();
    }
    return 0;
}
