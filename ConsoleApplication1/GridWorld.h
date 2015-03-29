#ifndef INC_3B8C6296F12F440F8120893B785D9C69
#define INC_3B8C6296F12F440F8120893B785D9C69

#include <iostream>
#include <fstream>
#include <vector>

#include "Row.h"
#include "Robot.h"

class GridWorld
{
public:
	typedef std::vector<Row>::const_iterator gridWorldIt;

	GridWorld();
	GridWorld(GridWorld &i_gridWorld);
	GridWorld(std::vector<Row> i_gridWorldRows);
	GridWorld(const char* i_gridWorldFile);
	
	gridWorldIt cbegin(){ return m_gridWorldRows.cbegin(); }
	gridWorldIt cend(){ return m_gridWorldRows.cend(); }

protected:
private:
	std::vector<Row> m_gridWorldRows;
	int m_width, m_height;
};

#endif