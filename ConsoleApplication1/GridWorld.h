#ifndef INC_3B8C6296F12F440F8120893B785D9C69
#define INC_3B8C6296F12F440F8120893B785D9C69

#include <iostream>
#include <fstream>
#include <vector>

#include "Row.h"
#include "Robot.h"

/*The grid world is a vecotr of rows whose ordering represents a top to bottom placement*/
class GridWorld
{
public:
	typedef std::vector<Row>::const_iterator gridWorldIt;

	GridWorld(int const i_gridWidth = 8, int const i_gridHeight = 8);
	GridWorld(std::vector<Row> i_gridWorldRows);
	GridWorld(const char* i_gridWorldFile);
	
	gridWorldIt cbegin(){ return m_gridWorldRows.cbegin(); }
	gridWorldIt cend(){ return m_gridWorldRows.cend(); }

protected:
private:
	std::vector<Row> m_gridWorldRows;
	int m_width, m_height;

	bool AddRow(Row i_row);
};

#endif