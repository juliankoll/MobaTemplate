#pragma once

#include <SFML/Graphics.hpp>
class Renderer {
public:
    static sf::RenderWindow* currentWindow;

    static void init(sf::RenderWindow* window);
    static void initGrid( int rows,  int cols);

    static void drawRect(int row, int col, int width, int height, sf::Color c);
    static void drawRectOutline(int row, int col, int width, int height, sf::Color c, int thickness);
    static void drawCircle(int row, int col, int radius, sf::Color c, bool fill);
    static void drawLine(int row1, int col1, int row2, int col2, sf::Color c);
  
    static void getMousePos(int* o_x, int* o_y);
    static void updateViewSpace(int* viewSpace, int* viewspaceLimits, int windowRows, int windowCols);
};