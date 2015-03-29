#ifndef INC_F7CA2A225B094E93926BD88DEA99675E
#define INC_F7CA2A225B094E93926BD88DEA99675E

class Wall
{
public:
	Wall(bool i_bHasExit = false){ m_bHasExit = i_bHasExit; }
	bool bHasExit(){ return m_bHasExit; }

private:
	bool m_bHasExit;
};

#endif