#include "stdafx.h"

#include <string>
#include <list>
#include <iostream>
#include <ctime>

#include "Interface.h"
#include "Common.h"
#include "GridWorld.h"
#include "Robot.h"
#include "PathPlanner.h"

const char* GRID_WORLD_FILE = "MyNewGridWorld.txt";

void ContinueLearning(GridWorld *i_gridWorld, Robot *i_robot, int i_episodeLength)
{
	while (i_episodeLength > 0)
	{
		Position currentPosition, futurePosition;
		std::list<Action> validToMoves, validFutureMoves;
		Action toAction;

		validToMoves = i_gridWorld->GetValidMoves();
		currentPosition = i_gridWorld->GetCurrentPosition();
		toAction = i_robot->GetNextMove(currentPosition, validToMoves);

    Action actualToAction;
    double reward = i_gridWorld->Move(toAction, actualToAction);
    futurePosition = i_gridWorld->GetCurrentPosition();
    validFutureMoves = i_gridWorld->GetValidMoves();

		i_robot->ProcessMove(currentPosition, futurePosition, reward, validFutureMoves, actualToAction);

		if (i_gridWorld->bIsGoal(i_gridWorld->GetCurrentPosition()))
			i_episodeLength = 0;
		else
			--i_episodeLength;
	}
}

bool SolveMazeWithQMap()
{
  using namespace std;

  int choice;
  printf("Would you like to solve the maze with your q map?\nType '1' for yes and '0' for no.\n");
  cin >> choice;
  if (choice == 1)
    return true;
  return false;
}

void StartDeterministicMap()
{
	
}

void StartStochiasticMap(int i_numOfEpisodes, int i_episodeLength)
{
	GridWorld *m_gridWorld = new GridWorld(GRID_WORLD_FILE, true);
	Robot *m_robot = new Robot(PathPlanner(true, 1, 0.1));

	if (m_gridWorld->Enter())
	{
		for (int i = 0; i < i_numOfEpisodes; i++)
		{
			ContinueLearning(m_gridWorld, m_robot, i_episodeLength);
			m_gridWorld->Leave();
			m_gridWorld->Enter();
		}
		m_robot->PrintQMap();
	}

  bool bSolveMaze = SolveMazeWithQMap();
  while (bSolveMaze)
  {
    m_robot->FinishLearning();
    m_gridWorld->SetStochasticity(false);
    m_gridWorld->Enter();
    while (!(m_gridWorld->bIsGoal(m_gridWorld->GetCurrentPosition())))
    {
      Action action;
      Position position;
      position = m_gridWorld->GetCurrentPosition();
      action = m_robot->GetNextMove(position, m_gridWorld->GetValidMoves());
      Action actualToAction;
      m_gridWorld->Move(action, actualToAction);
      system("pause");
    }
    m_gridWorld->Leave();
     bool bSolveMaze = SolveMazeWithQMap();
  }

	delete m_gridWorld;
	delete m_robot;
}

void StartAStarMap()
{

}

bool AskForMapType()
{
	using namespace std;

	int mapType;
	printf("What type of map would you like?\n Type '1' for deterministic and '2' for stochastic.\n");
	cin >> mapType;
	if (mapType == 1)
	{
    StartDeterministicMap();
		return true;
	}
	if (mapType == 2)
	{
		int numOfEpisodes, episodeLength;
		printf("How many episodes?\n");
		cin >> numOfEpisodes;
		printf("How long is an episode?\n");
		cin >> episodeLength;
    StartStochiasticMap(numOfEpisodes, episodeLength);
		return true;
	}
	printf("Please input a proper map type\n");
	return false;
}

bool AskForRobotType()
{
	using namespace std;
	int robotType;
	printf("What type of robot would you like?\n Type '1' for an A* robot and '2' for a q learning robot.\n");
	cin >> robotType;
	if (robotType == 1)
	{
		StartAStarMap();
		return true;
	}
	if (robotType == 2)
	{
		while (!AskForMapType())
			continue;
		return true;
	}
	printf("Please input a valid robot type\n");
	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned)time(NULL));

	while (!AskForRobotType())
		continue;
	return 0;
}

