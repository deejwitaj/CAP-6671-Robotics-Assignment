#include "stdafx.h"

#include "Robot.h"

Robot::Robot(PathPlanner i_planner) :
	m_pathPlanner(i_planner)
{
}

void Robot::FinishLearning()
{
  m_pathPlanner.FinishLearning();
}

Action Robot::GetNextMove(Position i_current, std::list<Action> i_validMoves)
{
	return m_pathPlanner.GetNextMove(i_current, i_validMoves);
}

void Robot::ProcessMove(Position i_from, Position i_to, double i_reward, std::list<Action> i_validMoves, Action i_toAction)
{
	m_pathPlanner.DidMove(i_from, i_to, i_toAction, i_reward, i_validMoves);
}

void Robot::PrintQMap()
{
	m_pathPlanner.PrintQMap();
}