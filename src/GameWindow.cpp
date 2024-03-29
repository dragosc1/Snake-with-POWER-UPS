//
// Created by dragosc1 on 21.04.2023.
//
#include "../headers/GameWindow.h"

// window instance
GameWindow& GameWindow::getGameWindow() {
    static GameWindow gameWindowInstance;
    return gameWindowInstance;
}

// window create
void GameWindow::create() {
    auto style = sf::Style::Titlebar | sf::Style::Close;
    window.create({windowSize.x, windowSize.y, 32}, windowTitle, style);
}

// destroy window
void GameWindow::destroy() {
    window.close();
}

// window setup
void GameWindow::setup(const std::string &title, const sf::Vector2u &size) {
    windowTitle = title;
    windowSize = size;
    isclosed = false;
    create();
}

// window constructor
GameWindow::GameWindow(int width_, int height_) {
    setup("Snake", sf::Vector2u(width_, height_));
    window.setFramerateLimit(60);
}

// window operator<<
std::ostream &operator<<(std::ostream &os, const GameWindow &gameWindow) {
    os << "Window dimensions: " << gameWindow.window.getSize().x << 'x' << gameWindow.window.getSize().y << '\n';
    os << "Window title: " << gameWindow.windowTitle << '\n';
    return os;
}

// window getter
sf::RenderWindow& GameWindow::getWindow() {
    return window;
}

// window begin draw
void GameWindow::beginDraw() {
    window.clear(BLACK);
}

// window end draw
void GameWindow::endDraw() {
    window.display();
}

// window draw score
void GameWindow::drawScore(const sf::Text &score) {
    window.draw(score);
}

// window draw
void GameWindow::draw(const sf::Drawable &drawable) {
    window.draw(drawable);
}

// window update
void GameWindow::update() {
    sf::Event event;
    while (window.pollEvent(event))
        if (event.type == sf::Event::Closed)
            isclosed = true;
}

// window is closed
bool GameWindow::isClosed() {
    return isclosed;
}

// window destructor
GameWindow::~GameWindow() {
    destroy();
}