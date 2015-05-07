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
#include "AStarPathPlanner.h"

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

    Action actualToAction, oppositeAction;

    switch (toAction)
    {
    case MOVE_UP:
      oppositeAction = MOVE_DOWN;
      break;
    case MOVE_DOWN:
      oppositeAction = MOVE_UP;
      break;
    case MOVE_LEFT:
      oppositeAction = MOVE_RIGHT;
      break;
    case MOVE_RIGHT:
      oppositeAction = MOVE_LEFT;
      break;
    case NO_MOVE:
      oppositeAction = NO_MOVE;
      break;
    default:
      printf("Uh oh");
      break;
    }

    double reward = i_gridWorld->Move(toAction, actualToAction);
    double oppositeReward = i_gridWorld->GetReward(oppositeAction);
    futurePosition = i_gridWorld->GetCurrentPosition();
    validFutureMoves = i_gridWorld->GetValidMoves();

		i_robot->ProcessMove(currentPosition, futurePosition, reward, oppositeReward, validFutureMoves, actualToAction);

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

bool AStarMap()
{
  using namespace std;

  int choice;
  printf("Would you like to solve the maze with A* again?\nType '1' for yes and '0' for no.\n");
  cin >> choice;
  if (choice == 1)
    return true;
  return false;
}

void StartDeterministicMap()
{
  GridWorld *m_gridWorld = new GridWorld(GRID_WORLD_FILE, false);
  bool bGoAgain = true;
  while (m_gridWorld->Enter() && bGoAgain)
  {
    AStarPathPlanner *m_aStarPlanner = new AStarPathPlanner(m_gridWorld);
    Node * path = m_aStarPlanner->FindPath();
    while (path)
    {
      m_gridWorld->AcceptCell(path->pos);
      path = path->from;
    }
    system("pause");
    m_gridWorld->Leave();
    bGoAgain = AStarMap();
    m_gridWorld->Reset();
  }
  
}

void StartStochiasticMap(int i_numOfEpisodes, int i_episodeLength)
{
	GridWorld *m_gridWorld = new GridWorld(GRID_WORLD_FILE, true);
	Robot *m_robot = new Robot(PathPlanner(true, .7, 0.6));

	if (m_gridWorld->Enter())
	{
		for (int i = 0; i < i_numOfEpisodes; i++)
		{
			ContinueLearning(m_gridWorld, m_robot, i_episodeLength);
			m_gridWorld->Leave();
			m_gridWorld->Enter();
		}

    m_robot->PrintTimesCellVisited();
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

bool AskForEpisodeData()
{
  using namespace std;
	int numOfEpisodes, episodeLength;
	printf("How many episodes?\n");
	cin >> numOfEpisodes;
	printf("How long is an episode?\n");
	cin >> episodeLength;
  StartStochiasticMap(numOfEpisodes, episodeLength);
	return true;
}

bool AskForRobotType()
{
	using namespace std;
	int robotType;
	printf("What type of robot would you like?\n Type '1' for an A* robot and '2' for a q learning robot.\n");
	cin >> robotType;
	if (robotType == 1)
	{
    StartDeterministicMap();
		return true;
	}
	if (robotType == 2)
	{
    AskForEpisodeData();
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

