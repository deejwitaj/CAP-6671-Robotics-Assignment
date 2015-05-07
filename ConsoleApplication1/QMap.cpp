#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>

#include "QMap.h"

using namespace std;

QMap::QMap()
{
}

double QMap::GetQ(Position i_position, Action i_action) const
{
	return GetQ(R(i_position, i_action));
}

double QMap::GetQ(R i_r) const
{
	auto it = m_qMap.find(i_r);
	if (it != m_qMap.end())
		return it->second;

	return 0;
}

void QMap::SetQ(R i_r, double i_reward)
{
	m_qMap[i_r] = i_reward;
}

void QMap::Print()
{
  using namespace std;

  ofstream myfile("QMap.txt");
  if (myfile.is_open())
  {
	  for (auto it : m_qMap)
	  {
		  double x = it.first.state.GetXPosition();
		  double y = it.first.state.GetYPosition();
		  std::string action;
		  switch (it.first.action)
		  {
		  case MOVE_UP:
			  action = "MOVE UP";
			  break;
		  case MOVE_DOWN:
			  action = "MOVE DOWN";
			  break;
		  case MOVE_LEFT:
			  action = "MOVE LEFT";
			  break;
		  case MOVE_RIGHT:
			  action = "MOVE RIGHT";
			  break;
      case NO_MOVE:
        action = "NO_MOVE";
        break;
		  }

      myfile << "State: " << x << ", " << y << "Action: " << action.c_str() << ": " << it.second << "\n";
	  }
  }
}