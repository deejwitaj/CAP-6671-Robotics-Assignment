#ifndef INC_90120DF4FB544967B71CFB471ECDDCA9
#define INC_90120DF4FB544967B71CFB471ECDDCA9

#include <vector>
#include "Cell.h"

//The Row is a single row of cells that, when put together with multiple other cells, can make up
//a grid world. It does not assist with ensuring that a valid path exists. That is up to the creator
//of the passed in grid world file
class Row
{
public:
	typedef std::vector<Cell>::const_iterator rowIt;

	Row(bool const i_bIsOpen = true, int const i_width = 1);
	Row(Cell const i_cell, int const i_width = 1, int const i_startingColumn = 0);
	Row(std::vector<Cell> i_row, int const i_Width, int const i_startingColumn = 0);

	int GetWidth() const{ return m_row.size(); }
	bool GetCell(int const i_cellPosition, Cell &io_cell) const;

	std::string const PrintTopWalls();
	std::string const PrintSideWalls();
	std::string const PrintBottomWalls();
	std::string const PrintSideAndBottomWalls();
	std::string const PrintRow();

	rowIt cbegin() const{ return m_row.cbegin(); }
	rowIt cend() const{ return m_row.cend(); }

protected:
private:
	std::vector<Cell> m_row;

	void AddCell(Cell i_cell);
	void AddRow(int const i_numOfCells, Cell i_cell);
	void AddRow(std::vector<Cell> i_row);
};

#endif