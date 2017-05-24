#pragma once
class CAbility{

public:

	CAbility();

	bool ifCapacityFull();

	void setSpeed(int passedSpeed);
	void setCapacity(int passedCapacity);
	void setAttack(int passedAttack);
	void setDefence(int passedDefence);
	void setManliness(int passedManliness);

	int getSpeed();
	int getCapacity();
	int getAttack();
	int getDefence();
	int getManliness();




	~CAbility();


private:

	int speed;
	int capacity;
	int attack;
	int defence;
	int manliness;

};

