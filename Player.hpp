#pragma once
#include "SFML/Graphics.hpp"
class Player {
public:
	Player(int i_col, int i_row, int i_width, int i_height, float i_vel, float i_maxHp, int i_dmg);
    void givePath(int* pathX, int* pathY, int pathLenght);
    void deletePath();
    void move();
    void draw();
    void setTexture(int index);

    bool hasNewPath = false;
    int* pathXpositions;
    int* pathYpositions;
    int pathLenght;
    int cPathIndex;
private:

	int row;
	int col;
	float velocity;
    
    int width;
    int height;
    int cTextureI;
    sf::Texture* textures;

    void initTextures();
    //Getters and Setters (autogenerated)

    float hp;
    float maxHp;
    int dmg;


    bool findingPath;
    long long lastMoveTime;
    
public:
    //used in pathfinding threads => mutices are locked and unlocked----------
    void setFindingPath(bool i_findingPath);
    bool isFindingPath();

    //------------------------------------------------------------------------


    int pathsFound = 0;
    inline int getRow() { return row; }
    inline void setRow(int row) { this->row = row; }

    inline int getCol() { return col; }
    inline void setCol(int col) { this->col = col; }

    inline float getVelocity() { return velocity; }
    inline void setVelocity(float velocity) { this->velocity = velocity; }

    inline int getWidth() { return width; }
    inline void setwidth(int width) { this->width = width; }

    inline int getHeight() { return height; }
    inline void setheight(int height) { this->height = height; }

    inline float getHp() { return hp; }
    inline void setHp(float hp) { this->hp = hp; }

    inline float getMaxHp() { return maxHp; }
    inline void setMaxHp(float maxHp) { this->maxHp = maxHp; }

    inline int getDmg() { return dmg; }
    inline void setDmg(int dmg) { this->dmg = dmg; }

    inline bool hasPath() {
        if (pathLenght == -1) return false;
        return true;
    }


    inline int getPathGoalX() {
        return pathXpositions[pathLenght - 1];
    }

    inline int getPathGoalY() {
        return pathYpositions[pathLenght - 1];
    }

    inline int getTextureIndex() {
        return cTextureI;
    }
};
