#ifndef INC_93E1D27140414CBCBDC94F51395C287E
#define INC_93E1D27140414CBCBDC94F51395C287E

/*Represents a single cell in a grid world.*/
#include <string>
#include "Common.h"

/*Makes up the entire grid. Each cell is made up of four walls with each wall potentially having an exit.*/
class Cell
{
public:
	Cell(bool i_bIsOpen = true, bool i_bIsOccupied = false, bool i_bIsGoal = false);

	void Accept(){ m_bIsAccepted = true; }
	void Consider(){ m_bIsBeingConsidered = true; }
	void Decline(){ m_bIsAccepted = false; }
	bool Leave();
	bool Occupy();
	void Unconsider(){ m_bIsBeingConsidered = false; }

	bool bIsOpen() const { return m_bIsOpen; }
	bool bIsOccupied() const { return m_bIsOccupied; }
	bool bIsAccepted() const { return m_bIsAccepted; }
	bool bIsConsidered() const { return m_bIsBeingConsidered; }
	bool bIsGoal() const { return m_bIsGoal; }

	std::string PrintCell() const;

private:
	int m_reward;
	bool m_bIsOpen; //If true, can be entered. If false, is a wall
	bool m_bIsOccupied; //If true, an occupant is inhabiting the cell
	bool m_bIsBeingConsidered; //If true, cell is part of a considered path in A* planning
	bool m_bIsAccepted; //If true, cell is accepted as part of a final A* path
	bool m_bIsGoal; //If true, cell is goal cell in grid world
};

#endif