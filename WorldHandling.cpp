#include "WorldHandling.hpp"	

#include "Renderer.hpp"
#include "Terrain.hpp"

WorldHandling::WorldHandling() {
	viewSpaceLimits = new int[4];
	viewSpaceLimits[0] = 0;//left
	viewSpaceLimits[1] = 2000;//right
	viewSpaceLimits[2] = 0;//top
	viewSpaceLimits[3] = 2000;//bot
	cViewSpace = new int[2];
	cViewSpace[0] = 0;//row (top to bot)
	cViewSpace[1] = 0;//col (left to right)



	//hardcoded rows and cols
	frameRows = 1080;
	frameCols = 1920;
	worldRows = frameRows + viewSpaceLimits[3];
	worldCols = frameCols + viewSpaceLimits[1];


	Renderer::linkViewSpace(cViewSpace, viewSpaceLimits);
	terrain = new Terrain();
	hardCodeTerrain();
}

void WorldHandling::update() {
	Renderer::updateViewSpace();//move view space if mouse on edge of window
}

void WorldHandling::draw() {
	terrain->draw();
}

void WorldHandling::hardCodeTerrain() {
	terrain->addRect(0, 0, worldCols, 50);
	terrain->addRect(0, 0, 50, worldRows);
	terrain->addRect(0, worldCols - 50, 50, worldRows);
	terrain->addRect(worldRows - 70, 0, worldCols, 50);

	terrain->addRect(300, 0, 300, 100);
	terrain->addRect(300, 300, 100, 300);

	terrain->addRect(1000, 1000, 500, 500);
}
