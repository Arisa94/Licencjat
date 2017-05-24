#include "stdafx.h"
#include "Ability.h"

CAbility::CAbility(){

//KUPA!
	speed = 15; //smaller the better!
	capacity = 3;
	attack = 15;
	defence = 15;
	manliness = 1;

}

bool CAbility::ifCapacityFull(){

	return(capacity > 0);

}

void CAbility::setSpeed(int passedSpeed){

	speed = passedSpeed;

}

void CAbility::setCapacity(int passedCapacity){

	capacity = passedCapacity;

}

void CAbility::setAttack(int passedAttack){

	attack = passedAttack;

}

void CAbility::setDefence(int passedDefence){

	defence = passedDefence;

}

void CAbility::setManliness(int passedManliness){

	manliness = passedManliness;

}

int CAbility::getSpeed(){
	
	return speed;

}

int CAbility::getCapacity(){

	return capacity;

}

int CAbility::getAttack(){
	
	return attack;

}

int CAbility::getDefence(){

	return defence;

}

int CAbility::getManliness(){

	return manliness;

}

CAbility::~CAbility(){

}
