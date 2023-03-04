#include <iostream>
#include <vector>

using namespace std;

class Cell {
private:
    int x, y;
public:
    // getters si setters
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void setX(int _x) {
        x = _x;
    }
    void setY(int _y) {
        y = _y;
    }
};

class Window {

};

class Snake {
    vector<Cell> body;

};

class World {

};

int main() {

    return 0;
}