#include "stdafx.h"

#include <string>

#include "Interface.h"
#include "GridWorld.h"
#include "Robot.h"
#include "Common.h"
#include "QMap.h"

const char* GRID_WORLD_FILE = "MyNewGridWorld.txt";

int _tmain(int argc, _TCHAR* argv[])
{
	GridWorld *myGridWorld = new GridWorld(GRID_WORLD_FILE);
	QMap myQMap;
	
	return 0;
}

