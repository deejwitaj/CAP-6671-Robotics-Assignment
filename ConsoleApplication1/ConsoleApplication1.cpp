// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GridWorld.h"
#include "Robot.h"

const char* GRID_WORLD_FILE = "MyNewGridWorld.txt";

int _tmain(int argc, _TCHAR* argv[])
{
	GridWorld *myGridWorld = new GridWorld(GRID_WORLD_FILE);
	myGridWorld->Enter();
	myGridWorld->MoveRight();
	myGridWorld->MoveDown();
	myGridWorld->MoveDown();
	myGridWorld->MoveDown();
	myGridWorld->MoveRight();
	myGridWorld->MoveRight();
	myGridWorld->MoveRight();

	return 0;
}

