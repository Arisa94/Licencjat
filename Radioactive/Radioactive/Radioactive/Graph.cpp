#include "Graph.h"

CGraph::CGraph(){

	//  800/25 = 32 WIDTH, 500/25 = 20 HEIGHT 32*20= number of nodes

	clearFloydWarshall();
	clearBFS();
	floydWarshall();

}

void CGraph::clearFloydWarshall(){

	for (int i = 0; i < 640; i++){

		for (int j = 0; j < 640; j++){

			incidenceMatrix[i][j] = 1000;
			predecessorMatrix[i][j] = i;

		}
		incidenceMatrix[i][i] = 0;

	}

	for (int i = 0; i < 640; i++){

		if (i - 32 > 0){

			incidenceMatrix[i][i - 32] = 1;
			incidenceMatrix[i - 32][i] = 1;

		}

		if (i + 32 < 640){

			incidenceMatrix[i][i + 32] = 1;
			incidenceMatrix[i + 32][i] = 1;

		}

		if (i % 32 != 0){

			incidenceMatrix[i][i - 1] = 1;
			incidenceMatrix[i - 1][i] = 1;

		}

		if (i % 32 != 31){

			incidenceMatrix[i][i + 1] = 1;
			incidenceMatrix[i + 1][i] = 1;

		}

	}

}

void CGraph::clearBFS(){

	for (int i = 0; i < 640; i++){

		for (int j = 0; j < 640; j++){

			incidenceBFSMatrix[i][j] = 0;

		}

	}

	for (int i = 0; i < 640; i++){

		if (i - 32 > 0){

			incidenceBFSMatrix[i][i - 32] = 1;
			incidenceBFSMatrix[i - 32][i] = 1;

		}

		if (i + 32 < 640){

			incidenceBFSMatrix[i][i + 32] = 1;
			incidenceBFSMatrix[i + 32][i] = 1;

		}

		if (i % 32 != 0){

			incidenceBFSMatrix[i][i - 1] = 1;
			incidenceBFSMatrix[i - 1][i] = 1;

		}

		if (i % 32 != 31){

			incidenceBFSMatrix[i][i + 1] = 1;
			incidenceBFSMatrix[i + 1][i] = 1;

		}

	}
}

void CGraph::BFS(int playerPosition){

	//std::cout << " ROBIE! " << std::endl;
	std::queue<int> queue;

	int tempPrev = playerPosition;
	bool V[640];

	for (int i = 0; i < 640; i++){

		V[i] = false;
		goTable[i] = -1;

	}

	goTable[playerPosition] = playerPosition;
	queue.push(playerPosition);
	V[playerPosition] = true;

	while (!queue.empty()){

		playerPosition = queue.front();

		queue.pop();

		for (int j = 0; j < 640; j++){

			if (incidenceBFSMatrix[j][playerPosition] == 1 && V[j] == false){

				goTable[j] = playerPosition;
				queue.push(j);
				V[j] = true;

			}

		}

	}

}

void CGraph::floydWarshall(){

	for (int i = 0; i < 640; i++){

		for (int j = 0; j < 640; j++){

			floydMatrix[i][j] = incidenceMatrix[i][j];

		}

	}

	for (int k = 0; k < 640; k++){

		for (int i = 0; i < 640; i++){

			for (int j = 0; j < 640; j++){

				if (floydMatrix[i][k] + floydMatrix[k][j] < floydMatrix[i][j]){

					floydMatrix[i][j] = floydMatrix[i][k] + floydMatrix[k][j];
					predecessorMatrix[i][j] = predecessorMatrix[k][j];

				}

			}

		}

	}
	//std::cout << "zrobione!" << std::endl;
}

void CGraph::makeIncidence(int x, int y){

	//std::cout << "X: " << x << " Y: " << y << std::endl;
	int index;
	x /= 25;
	y /= 25;

	index = 32 * y + x;

//	std::cout << "NOWA KOLIZJA!" << std::endl;
//	std::cout << "X: " << x << " Y: " << y << std::endl;

	if (x > 0){

		//std::cout << "x>1" << std::endl;
		removeIncidences(index, index - 1);

	}

	if (x < 31){

		//std::cout << "x<32" << std::endl;
		removeIncidences(index, index + 1);

	}

	if (y > 0){

		//std::cout << "y>1" << std::endl;
		removeIncidences(index, index - 32);

	}

	if (y < 19){

		//std::cout << "y<20" << std::endl;
		removeIncidences(index, index + 32);

	}

}

void CGraph::removeIncidences(int x, int y){

	//std::cout << "USUWAM POLACZENIE!" << std::endl;
	//std::cout << "X: " << x << " Y: " << y << std::endl;
	incidenceMatrix[x][y] = 100000;
	incidenceMatrix[y][x] = 100000;
	incidenceBFSMatrix[x][y] = 100000;
	incidenceBFSMatrix[y][x] = 100000;
	predecessorMatrix[x][y] = 100000;
	predecessorMatrix[y][x] = 100000;
}

void CGraph::restoreIncidences(int x, int y){

	incidenceMatrix[x][y] = 1;
	incidenceMatrix[y][x] = 1;

}

int CGraph::getPredecessor(int from, int to){

	return predecessorMatrix[to][from];

}

int CGraph::getBFSPredecessor(int from){

	return goTable[from];

}

int CGraph::getDistance(int from, int to){

	return floydMatrix[from][to];

}

CGraph::~CGraph(){


}
