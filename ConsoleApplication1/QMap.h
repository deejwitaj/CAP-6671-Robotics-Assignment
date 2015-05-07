#ifndef INC_628F12B837D24ECCA844DDFE460E3D1A
#define INC_628F12B837D24ECCA844DDFE460E3D1A

#include <map>

#include "Common.h"

class QMap
{
public:
	QMap();

	double GetQ(Position i_position, Action i_action) const;
	double GetQ(R const i_r) const;
	void SetQ(R i_r, double i_reward);

	void Print();

protected:
private:

	std::map<R, double> m_qMap;
};
#endif