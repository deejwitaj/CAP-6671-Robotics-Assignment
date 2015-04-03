#include "stdafx.h"

#include "RewardsMap.h"
#include "Row.h"

RewardsMap::RewardsMap()
{
}

int RewardsMap::GetReward(Position i_position, Action i_action) const
{
	return -1;
}

int RewardsMap::GetReward(R i_r) const
{
	auto it = m_rewardsMap.find(i_r);
	if (it != m_rewardsMap.end())
		return it->second;

	return -1;
}

void RewardsMap::SetReward(R i_r, int i_reward)
{
	m_rewardsMap[i_r] = i_reward;
}