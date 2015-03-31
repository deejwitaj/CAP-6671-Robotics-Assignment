// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GridWorld.h"
#include "Robot.h"

const char* GRID_WORLD_FILE = "MyGridWorld.txt";

int _tmain(int argc, _TCHAR* argv[])
{
	GridWorld *myGridWorld = new GridWorld(GRID_WORLD_FILE);
	std::string gridWorldString = myGridWorld->PrintGridWorld();
	printf(gridWorldString.c_str());
	myGridWorld->Enter();
	bool result = false;
	result = myGridWorld->MoveLeft();
	result = myGridWorld->MoveUp();
	result = myGridWorld->MoveRight();
	result = myGridWorld->MoveDown();
	result = myGridWorld->MoveDown();
	return 0;
}

