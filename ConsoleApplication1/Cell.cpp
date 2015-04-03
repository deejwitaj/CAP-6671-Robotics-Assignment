#include "stdafx.h"
#include "Cell.h"

//If no walls are given, then the cell defaults to a barrier
Cell::Cell(bool i_bIsOpen, bool i_bIsOccupied, bool i_bIsGoal) :
		m_bIsOpen(i_bIsOpen)
	, m_bIsOccupied(i_bIsOccupied)
	, m_bIsGoal(i_bIsGoal)
	, m_bIsAccepted(false)
	, m_bIsBeingConsidered(false)
{
}

//Cell becomes unoccupied. Returns false if cell was not occupied before call
bool Cell::Leave()
{
	if (!m_bIsOccupied)
		return false;

	m_bIsOccupied = false;
	return true;
}

//Cell becomes occupied. Returns false if cell is already occupied or is not open
bool Cell::Occupy()
{
	if (m_bIsOccupied || !m_bIsOpen)
		return false;

	m_bIsOccupied = true;
	return true;
}

/*Prints out the cell according to its state. 
Closed cells print out an 'X'
Open cells print out an 'O'
Considered cells print out a '?'
Accepted cells print out a '!'*/
std::string Cell::PrintCell() const
{
	if (!m_bIsOpen)
		return "X";

	if (m_bIsOccupied)
		return "R";

	if (m_bIsAccepted)
		return "!";

	if (m_bIsBeingConsidered)
		return "?";

	if (m_bIsGoal)
		return "G";

	return "O";
}