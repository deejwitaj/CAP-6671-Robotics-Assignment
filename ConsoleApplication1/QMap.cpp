#include "stdafx.h"

#include "QMap.h"

QMap::QMap()
{
}

int QMap::GetQ(Position i_position, Action i_action) const
{
	return GetQ(R(i_position, i_action));
}

int QMap::GetQ(R i_r) const
{
	auto it = m_qMap.find(i_r);
	if (it != m_qMap.end())
		return it->second;

	return -1;
}

void QMap::SetQ(R i_r, int i_reward)
{
	m_qMap[i_r] = i_reward;
}