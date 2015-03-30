// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GridWorld.h"
#include "Row.h"

const char* GRID_WORLD_FILE = "MyGridWorld.txt";

int _tmain(int argc, _TCHAR* argv[])
{
	GridWorld *myGridWorld = new GridWorld(GRID_WORLD_FILE);
	printf(myGridWorld->PrintGridWorld().c_str());
	return 0;
}

