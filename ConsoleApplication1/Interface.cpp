#include "stdafx.h"

#include <string>
#include <list>

#include "Interface.h"
#include "Common.h"
#include "GridWorld.h"
#include "Robot.h"
#include "PathPlanner.h"

const char* GRID_WORLD_FILE = "MyNewGridWorld.txt";

void ContinueLearning(GridWorld *i_gridWorld, Robot *i_robot)
{
	int episodeLength = 150;
	while (episodeLength > 0)
	{
		Position currentPosition, futurePosition;
		std::list<Action> validToMoves, validFutureMoves;
		Action toAction;

		validToMoves = i_gridWorld->GetValidMoves();
		currentPosition = i_gridWorld->GetCurrentPosition();
		toAction = i_robot->GetNextMove(currentPosition, validToMoves);
		if (currentPosition == Position(1, 8))
			int x = 1;

		switch (toAction)
		{
		case MOVE_UP:
			futurePosition = Position(currentPosition.GetXPosition(), currentPosition.GetYPosition() - 1);
		case MOVE_DOWN:
			futurePosition = Position(currentPosition.GetXPosition(), currentPosition.GetYPosition() + 1);
		case MOVE_LEFT:
			futurePosition = Position(currentPosition.GetXPosition() - 1, currentPosition.GetYPosition());
		case MOVE_RIGHT:
			futurePosition = Position(currentPosition.GetXPosition() + 1, currentPosition.GetYPosition());
		}

		validFutureMoves = i_gridWorld->GetValidMoves(futurePosition);
		double reward = i_gridWorld->Move(toAction);

		i_robot->ProcessMove(currentPosition, futurePosition, reward, validFutureMoves);
		--episodeLength;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	GridWorld *m_gridWorld = new GridWorld(GRID_WORLD_FILE);
	Robot *m_robot = new Robot(PathPlanner(true, 0.5, 1.0));

	if (m_gridWorld->Enter())
	{
		for (int i = 0; i < 100; i++)
			ContinueLearning(m_gridWorld, m_robot);
	}

	return 0;
}

