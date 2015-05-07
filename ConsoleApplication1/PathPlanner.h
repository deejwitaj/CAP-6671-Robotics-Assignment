#ifndef INC_E1BEE5A3F4C54D32B84B72E3A0AE69B3
#define INC_E1BEE5A3F4C54D32B84B72E3A0AE69B3

#include <list>

#include "Common.h"
#include "QMap.h"

/*This class handles forming a plan with a given map.*/
class PathPlanner
{
public:
	PathPlanner(bool i_bIsQLearning = false, double i_discountFactor = 0.0, double i_learningRate = 1.0);


	void DidMove(Position i_from, Position i_to, Action i_action, double i_reward, double i_oppositeReward, std::list<Action> i_validMoves);
	Action GetNextMove(Position i_from, std::list<Action> i_validMoves);
	Action GetGreediestMove(Position i_position, std::list<Action> i_validMoves) const;
	void PrintQMap();
  void PrintTimesCellVisited();
  void FinishLearning(){ m_bIsExploring = false; }
protected:
private:
	bool m_bIsQLearning; //If true, we are using the Q learning method to solve maze
	bool m_bIsExploring; //If true along with bIsQLearning, then we are still filling q map
	QMap m_qMap;
	double m_discountFactor;
	double m_learningRate;
  std::map<Position, int> m_timesCellVisited;

	double CalculateNextQ(double i_reward, Position i_from, Position i_to, Action i_action, std::list<Action> i_validMoves);
  double CalculateOppositeQ(double i_reward, Position i_from, Position i_to, Action i_action, std::list<Action> i_validMoves);
  void UpdateCellVisited(Position const i_visitedCell);

  Action GetMaxQAction(double &i_maxQ, Action i_curentAciton, Action i_potentialAction, Position i_position) const;
	double GetMaxQ(Position i_position, std::list<Action> i_validMoves) const;
	Action GetMinQAction(double i_maxQ, Action i_currentAction, Action i_potentialAction, Position i_position) const;
	Action GetMaxQMove(Position i_position, std::list<Action> i_validMoves) const;
};
#endif