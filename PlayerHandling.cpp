#include "Playerhandling.hpp"
#include "NetworkCommunication.hpp"
#include "Renderer.hpp"
#include "GlobalRecources.hpp"
#include "iostream" 
using namespace std;

PlayerHandling::PlayerHandling() {//basically 100% hardcorded stuff for players
	playerCount = 2;
	float vel = 50;//velocity on path if path is given
	int startX = 700;
	int rectSize = 100;
	int defaultMaxHp = 500;
	int defaultDmg = 10;


	players = shared_ptr<vector<shared_ptr<Player>>>(new vector<shared_ptr<Player>>(playerCount));
	for (int i = 0; i < playerCount; i++) {
		int startY = i * 1000 / playerCount + 200;//move players away from each other in y
		players->at(i) = shared_ptr<Player>(new Player(startX, startY, rectSize, rectSize, vel, defaultMaxHp, defaultDmg));//places players on map, x dist depends on playercount
	}
	GlobalRecources::players = players;
	GlobalRecources::playerCount = playerCount;
}

void PlayerHandling::draw() {
	for (int i = 0; i < playerCount; i++) {
		if (players->at(i)->getHp() > 0) {
			players->at(i)->draw();//if he has a path, he moves on this path
		}
	}
}

void PlayerHandling::sendPlayerData() {
	int otherPlayer = 0;
	if (myPlayerI == 0) {
		otherPlayer = 1;
	}

	const Player* me = players->at(myPlayerI).get();
	if (me->hasPath() == false) {
		NetworkCommunication::addToken(0);//bool if path should be interrupted
		NetworkCommunication::addToken(me->getY());
		NetworkCommunication::addToken(me->getX());
	}
	else if (me->hasNewPath == true) {
		players->at(myPlayerI)->hasNewPath = false;
		NetworkCommunication::addToken(1);//bool if new bath was found

		NetworkCommunication::addToken(me->pathLenght - me->cPathIndex);//only the path that hasnt been walked yet (lag/connection built up while walking)
		for (int i = me->cPathIndex; i < me->pathLenght; i++) {
			int x = me->pathXpositions[i];
			NetworkCommunication::addToken(me->pathXpositions[i]);
			NetworkCommunication::addToken(me->pathYpositions[i]);
		}
	}
	else {
		NetworkCommunication::addToken(2);
	}


	NetworkCommunication::addToken(players->at(otherPlayer)->getHp());
}

/** Has to pass pathfinding so that we can update pathfinding-graph if player positions changed
**/
int hpSyncDelay = 0;
void PlayerHandling::receivePlayerData() {
	int otherPlayer = 0;
	if (myPlayerI == 0) {
		otherPlayer = 1;
	}

	int actionIndex = NetworkCommunication::receiveNextToken();

	if (actionIndex == 0) {//interrupt path/no path is there
		if (players->at(otherPlayer)->hasPath() == true) {
			players->at(otherPlayer)->deletePath();
		}			
		int y = NetworkCommunication::receiveNextToken();
		int x = NetworkCommunication::receiveNextToken();
		players->at(otherPlayer)->setY(y);
		players->at(otherPlayer)->setX(x);
	}
	else if (actionIndex == 1) {//new path
		int pathLenght = NetworkCommunication::receiveNextToken();

		shared_ptr<int[]> pathX = shared_ptr<int[]>(new int[pathLenght]);
		shared_ptr<int[]> pathY = shared_ptr<int[]>(new int[pathLenght]);
		for (int i = 0; i < pathLenght; i++) {
			pathX[i] = NetworkCommunication::receiveNextToken();
			pathY[i] = NetworkCommunication::receiveNextToken();
		}
		players->at(otherPlayer)->givePath(move(pathX), move(pathY), pathLenght);
	}
	else if (actionIndex == 2) {//follow the path given to you
		//do nothing yet
	}
	int hp = NetworkCommunication::receiveNextToken();
	hpSyncDelay ++;
	if (hpSyncDelay > 10) {
		players->at(myPlayerI)->setHp(hp);
		hpSyncDelay = 0;
	}
}