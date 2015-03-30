// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GridWorld.h"
#include "Row.h"

const char* GRID_WORLD_FILE = "C:/Users/Didier/Documents/Visual Studio 2013/Projects/CAP 6671 Robotics Assignment/ConsoleApplication1/MyGridWorld.txt";

int _tmain(int argc, _TCHAR* argv[])
{
	GridWorld *myGridWorld = new GridWorld(GRID_WORLD_FILE);
	return 0;
}

