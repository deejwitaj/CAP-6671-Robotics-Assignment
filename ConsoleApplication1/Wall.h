class Wall
{
public:
	Wall(bool i_bHasExit = false){ m_bHasExit = i_bHasExit; }
	bool bHasExit(){ return m_bHasExit; }

private:
	bool m_bHasExit;
};