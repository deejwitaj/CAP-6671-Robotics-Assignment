// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GridWorld.h"
#include "Robot.h"

const char* GRID_WORLD_FILE = "MyNewGridWorld.txt";

int _tmain(int argc, _TCHAR* argv[])
{
	GridWorld *myGridWorld = new GridWorld(GRID_WORLD_FILE);
	std::string gridWorldString = myGridWorld->PrintGridWorld();
	printf(gridWorldString.c_str());
	return 0;
}

