#pragma once
#include <queue>
#include "stdafx.h"

class CGraph{

public:

	void makeIncidence(int x, int y);
	void displayIncidences();
	void removeIncidences(int x, int y);
	void removeBFSIncidences(int x, int y);
	void restoreIncidences(int x, int y);
	void floydWarshall();
	void displayPath();
	void BFS(int playerPosition);
	void clearBFS();
	void display();
	void clearFloydWarshall();

	int getPredecessor(int from, int to);
	int getBFSPredecessor(int from);
	int getDistance(int from, int to);

	CGraph();
	~CGraph();

private:

	int incidenceBFSMatrix[640][640];
	int incidenceMatrix[640][640];
	int floydMatrix[640][640];
	int goTable[640];
	int predecessorMatrix[640][640];

};

