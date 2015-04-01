#include "stdafx.h"

#include <iostream>
#include <fstream>

#include "GridWorldReader.h"

//Creates a grid world and passes the vector representing the rows in a grid world back into vector
bool GridWorldReader::CreateGridWorld(const char* i_gridWorldFile, std::vector<Row> &io_gridWorldRows)
{
	using namespace std;

	ifstream gridWorldFile(i_gridWorldFile);
	if (gridWorldFile.is_open())
	{
		string nextLine;
		if (getline(gridWorldFile, nextLine))
		{
			int gridWidth, gridHeight;
			auto it = nextLine.cbegin();

			if (ReadGridStats(it, gridWidth, gridHeight))
			{
				int numOfRowsToRead = gridHeight;
				Row newRow;

				while (getline(gridWorldFile, nextLine) && numOfRowsToRead > 0)
				{
					--numOfRowsToRead;
					if (ReadRow(nextLine, newRow, gridWidth))
						io_gridWorldRows.push_back(newRow);
				}
				return true;
			}

			//There was an error with reading in stats on grid world width and height
			else
				return false;
		}
	}

	return false;
}

//Moves past the intial opening parenthesis of a group in the line
/*Returns false if the line does not begin with an open parenthesis*/
bool GridWorldReader::BeginRead(std::string::const_iterator &i_line)
{
	if (*i_line != '(' && *i_line != ',')
		return false;

	++i_line;
	return true;
}

//Attempts to convert char to int while also determining if character is actually an int
bool GridWorldReader::ConvertStringToNumber(const std::string i_string, int &io_number)
{
	io_number = atoi(i_string.c_str());
	return bIsNumber(i_string);

}

//Both reads in a string using an iterator and converts it to a number from a grouping
bool GridWorldReader::ReadAndConvertStringToNumber(std::string::const_iterator &i_line, int &io_number)
{
	if (BeginRead(i_line))
	{
		std::string string;
		if (ReadNumberToString(i_line, string))
			return ConvertStringToNumber(string, io_number);
	}

	return false;
}

//Reads in the information of a single cell
bool GridWorldReader::ReadCell(std::string::const_iterator &i_line, Cell &io_cell)
{
	std::string cellString = "";
	bool bIsOpen;

	if (*i_line == 'X')
		bIsOpen = false;
	else if (*i_line == 'O')
		bIsOpen = true;
	else
		return false;

	Cell newCell(bIsOpen);
	io_cell = newCell;
	return true;
}

//Reads in the information on the entire grid
/*The expected format is (m,n)
  'm' represents the grid width
	'n' represents the grid height*/
bool GridWorldReader::ReadGridStats(std::string::const_iterator &i_line, int &io_gridWidth, int &io_gridHeight)
{
	if (ReadAndConvertStringToNumber(i_line, io_gridWidth) && ReadAndConvertStringToNumber(i_line, io_gridHeight))
		return true;

	return false;
}

//Converts an entire passed in line to a new row for a grid
bool GridWorldReader::ReadRow(std::string const &i_gridWorldRow, Row &io_row, int const i_gridWidth)
{
	std::vector<Cell> i_readCells;
	auto it = i_gridWorldRow.cbegin();

	//No cells were specified in file, so an empty row is created
	if (it == i_gridWorldRow.end())
	{
		io_row = Row(true, i_gridWidth);
		return true;
	}

	Cell cell;
	for (int i = 0; i < i_gridWidth; i++)
	{
		//If if statement is true, then there were not enough cells to match the stated partial row width
		if (it == i_gridWorldRow.end())
			return false;

		//Read in cell
		if (ReadCell(it, cell))
		{
			i_readCells.emplace_back(cell);
			++it;
		}

		//Currently read in cell was not valid
		else
			return false;
	}

	io_row = Row(i_readCells, i_gridWidth);
	return true;
}

//Passes values pointed to by iterator into a string until comma  or closing parentheses is reached.
/*If the value pointed to by the iterator is not a number, the function returns false*/
bool GridWorldReader::ReadNumberToString(std::string::const_iterator &i_line, std::string &io_string)
{
	if (!isdigit(*i_line))
		return false;

	io_string = "";
	while (*i_line != ',' && *i_line != ')')
	{
		if (isdigit(*i_line))
			io_string += *i_line++;
		else
			return false;
	}

	return true;
}

//Determine if the string is a number
bool GridWorldReader::bIsNumber(std::string const i_string)
{
	auto it = i_string.begin();
	while (it != i_string.end() && isdigit(*it))
		++it;

	return !i_string.empty() && it == i_string.end();
}