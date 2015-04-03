#ifndef INC_DB8DD6D0698E438496C6C4F764688D77
#define INC_DB8DD6D0698E438496C6C4F764688D77

#include<map>

#include "Common.h"

class RewardsMap
{
public:
	RewardsMap();

	int GetReward(Position i_position, Action i_action) const;
	void SetReward(R i_r, int i_reward);

protected:
private:
	int GetReward(R const i_r) const;

	std::map<R, int> m_rewardsMap;
};
#endif