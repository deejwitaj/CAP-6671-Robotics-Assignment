// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GridWorldReader.h"
#include "Row.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GridWorldReader testReader;
	Row testRow;

	testReader.ReadRow("(3,5)(1,1,0,0)(1,1,0,0)(1,1,0,0)", testRow, 8);
	return 0;
}

