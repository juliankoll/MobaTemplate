#pragma once
#include "SFML/Graphics.hpp"

class Player {
public:
	Player(int i_col, int i_row, int i_width, int i_height, float i_vel);
    void givePath(int* pathX, int* pathY, int pathLenght);
    void deletePath();
    void move();
    void draw();
    void setTexture(int index);

    int* pathXpositions;
    int* pathYpositions;
    int pathLenght;
private:

	int row;
	int col;
	float velocity;
    
    int width;
    int height;
    sf::Texture currentTexture;
    sf::Texture* textures;

    void initTextures();
    //Getters and Setters (autogenerated)

    int hp;
    int dmg;

    float cPathIndex;
    bool findingPath;
public:
    inline int getRow() { return row; }
    inline void setRow(int row) { this->row = row; }

    inline int getCol() { return col; }
    inline void setY(int col) { this->col = col; }

    inline float getVelocity() { return velocity; }
    inline void setVelocity(float velocity) { this->velocity = velocity; }

    inline int getWidth() { return width; }
    inline void setwidth(int width) { this->width = width; }

    inline int getHeight() { return height; }
    inline void setheight(int height) { this->height = height; }

    inline int getHp() { return hp; }
    inline void setHp(int hp) { this->hp = hp; }

    inline int getDmg() { return dmg; }
    inline void setDmg(int dmg) { this->dmg = dmg; }

    inline bool hasPath() {
        if (pathLenght == -1) return false;
        return true;
    }

    inline void setFindingPath(bool i_findingPath) {
        findingPath = i_findingPath;
    }

    inline bool isFindingPath() {
        return findingPath;
    }

    inline int getPathGoalX() {
        return pathXpositions[pathLenght - 1];
    }

    inline int getPathGoalY() {
        return pathYpositions[pathLenght - 1];
    }
};
