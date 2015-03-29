#include <list>
#include "Cell.h"

//The Row is a single row of cells that, when put together with multiple other cells, can make up
//a grid world. It does not assist with ensuring that a valid path exists. That is up to the creator
//of the passed in grid world file
class Row
{
public:
	Row(bool i_bIsOpen = true, int i_width = 1);
	Row(Cell i_cell, int i_width = 1, int i_startingColumn = 0);
	Row(std::list<Cell> i_row, int i_width, int i_startingColumn = 0);

protected:
private:
	std::list<Cell> m_row;

	void AddCell();
	void AddCell(Cell i_cell, int i_column = 0);
	void AddRow(int i_startingColumn, int i_endingColumn);
	void AddRow(std::list<Cell> i_row, int i_startingColumn = 0);
};