#include <iostream>
#include <fstream>

#include "Robot.h"

class GridWorld
{
public:
	GridWorld(const char* i_gridWorldFile);
	
protected:
private:
	int m_width, m_height;
	Robot m_robot;
};