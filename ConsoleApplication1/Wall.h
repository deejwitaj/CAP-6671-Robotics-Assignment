#ifndef INC_F7CA2A225B094E93926BD88DEA99675E
#define INC_F7CA2A225B094E93926BD88DEA99675E

#include <string>

/*The wall makes up the side of a cell. It can have either an exit or be a solid wall*/
class Wall
{
public:
	Wall(bool i_bHasExit = false){ m_bHasExit = i_bHasExit; }
	bool bHasExit(){ return m_bHasExit; }

	std::string PrintVertically();
	std::string PrintHorizontally();
	std::string ToString();

private:
	bool m_bHasExit;
};

#endif