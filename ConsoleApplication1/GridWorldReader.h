#ifndef INC_1367707BE01D4FA18E6AEB05B796D10B
#define INC_1367707BE01D4FA18E6AEB05B796D10B

#include <iostream>
#include <fstream>
#include <string>

#include "Row.h"
#include "Cell.h"
#include "Wall.h"

class GridWorldReader
{
public:
	GridWorldReader(const char* i_gridWorldFile);


protected:
private:
	bool BeginRead(std::string::const_iterator &i_line);
	bool ConvertStringToNumber(const std::string i_string, int &io_number);
	bool ReadAndConvertStringToNumber(std::string::const_iterator &i_line, int &io_number);
	bool ReadCellStats(std::string::const_iterator &i_line, Cell &io_cell);
	bool ReadRow(std::string const &i_gridWorldRow, Row &io_row, int const i_gridWidth);
	bool ReadRowStats(std::string::const_iterator &i_line, int &io_width, int &io_startingColumn);
	bool ReadNumberToString(std::string::const_iterator &i_line, std::string &io_string);
	bool ReadWall(std::string::const_iterator &i_line, Wall &io_wall);

	bool bIsNumber(std::string const i_string);
};

#endif