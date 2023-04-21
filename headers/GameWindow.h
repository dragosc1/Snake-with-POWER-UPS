//
// Created by dragosc1 on 21.04.2023.
//

#ifndef OOP_GAMEWINDOW_H
#define OOP_GAMEWINDOW_H
#include "extern.h"
// The window
class GameWindow {
private:
    // window data
    sf::RenderWindow window;
    bool isclosed, isFullscreen;
    sf::Vector2u windowSize;
    std::string windowTitle;

    // window create
    void create();

    // destroy window
    void destroy();

    // window setup
    void setup(const std::string& , const sf::Vector2u& );
public:
    // window constructor
    GameWindow(int width_ = 800, int height_ = 600);

    // window operator<<
    friend std::ostream& operator<<(std::ostream&, const GameWindow&);

    // window getter
    sf::RenderWindow& getWindow();

    // window begin draw
    void beginDraw();

    // window end draw
    void endDraw();

    // window draw score
    void drawScore(const sf::Text&);

    // window draw
    void draw(const sf::Drawable&);

    // window update
    void update();

    // window is closed
    bool isClosed();

    // window destructor
    ~GameWindow();

    // toggle fullscreen
    void toggleFullscreen();

};

#endif //OOP_GAMEWINDOW_H
