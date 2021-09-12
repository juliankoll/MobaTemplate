#pragma once
#include "Renderer.hpp"
#include "Rect.hpp"
#include <iostream>
class Terrain {
public:
	Terrain();
	void addRect(int y, int x, int width, int height);
	void draw();
	void addCollidablesToGrid(bool** grid, float pathfindingAccuracy, int playerWidth, int playerHeight);
	std::vector<Rect*>* getCollidables();

private:
	std::vector<Rect*>* objectsY;
};