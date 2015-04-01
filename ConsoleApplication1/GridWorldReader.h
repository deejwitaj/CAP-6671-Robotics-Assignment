#ifndef INC_1367707BE01D4FA18E6AEB05B796D10B
#define INC_1367707BE01D4FA18E6AEB05B796D10B

#include <string>
#include <vector>

#include "Row.h"
#include "Cell.h"

class GridWorldReader
{
public:
	static bool CreateGridWorld(const char* i_gridWorldFile, std::vector<Row> &io_gridWorldRows);

protected:
private:
	static bool BeginRead(std::string::const_iterator &i_line);
	static bool ConvertStringToNumber(const std::string i_string, int &io_number);
	static bool ReadAndConvertStringToNumber(std::string::const_iterator &i_line, int &io_number);
	static bool ReadCell(std::string::const_iterator &i_line, Cell &io_cell);
	static bool ReadGridStats(std::string::const_iterator &i_line, int &io_gridWidth, int &io_gridHeight);
	static bool ReadRow(std::string const &i_gridWorldRow, Row &io_row, int const i_gridWidth);
	static bool ReadNumberToString(std::string::const_iterator &i_line, std::string &io_string);

	static bool bIsNumber(std::string const i_string);
};

#endif