#ifndef INC_628F12B837D24ECCA844DDFE460E3D1A
#define INC_628F12B837D24ECCA844DDFE460E3D1A

#include <map>

#include "Common.h"

class QMap
{
public:
	QMap();

	int GetQ(Position i_position, Action i_action) const;
	void SetQ(R i_r, int i_reward);

protected:
private:
	int GetQ(R const i_r) const;

	std::map<R, int> m_qMap;
};
#endif