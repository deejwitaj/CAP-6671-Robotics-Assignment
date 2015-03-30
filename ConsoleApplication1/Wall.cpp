#include "stdafx.h"

#include "Wall.h"

std::string Wall::PrintVertically()
{
	return ToString();
}

std::string Wall::PrintHorizontally()
{
	if (bHasExit())
		return " ";
	return "_";
}

std::string Wall::ToString()
{
	if (bHasExit())
		return " ";
	return "|";
}