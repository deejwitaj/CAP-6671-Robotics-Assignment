#ifndef INC_E1BEE5A3F4C54D32B84B72E3A0AE69B3
#define INC_E1BEE5A3F4C54D32B84B72E3A0AE69B3

#include <vector>

#include "Common.h"
#include "QMap.h"

/*This class handles forming a plan with a given map.*/
class PathPlanner
{
public:
	PathPlanner(QMap i_qMap, bool i_bIsQLearning = false, double i_discountFactor = 0.0, double i_learningRate = 1.0);


	Action GetNextMove(Position i_position, double i_reward);
protected:
private:
	bool m_bIsQLearning; //If true, we are using the Q learning method to solve maze
	bool m_bIsExploring; //If true along with bIsQLearning, then we are still filling q map
	QMap m_qMap;
	double m_discountFactor;
	double m_learningRate;

	double CalculateNextQ(double i_reward, Position i_currentPosition, Action i_action);

	double GetMaxQ(Position i_position) const;
	Action GetMaxQMove(Position i_position) const;
	Action GetGreediestMove(Position i_position) const;
};
#endif