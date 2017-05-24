#pragma once
#include "Building.h"
#include "Tree.h"
#include "Environment.h"

#include <vector>

class CSaver{

public:

	CSaver(CEnvironment* passedForestArea);
	~CSaver();

	void saveLevel(int currentLevel);
	void saveGame();
	void loadLevel(int levelNumber);

	int giveLevelPath();

	std::vector<CTree*>  getTrees();
	std::vector<CBuilding*> getBuildings();
	std::vector<CCrate*> getCrates();

private:

	CEnvironment* forestArea;

	std::vector<CTree*>  trees;
	std::vector<CBuilding*> buildings;
	std::vector<CCrate*> crates;

};

