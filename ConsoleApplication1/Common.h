#ifndef INC_61C61E4F91C94280AF5B24FCB22F20B5
#define INC_61C61E4F91C94280AF5B24FCB22F20B5

enum CellSide
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

struct Position
{
public:
	bool operator==(Position i_position) const
	{
		if ((x == i_position.GetXPosition()) && (y == i_position.GetYPosition()))
			return true;
		return false;
	}

	int GetXPosition() const { return x; }
	int GetYPosition() const { return y; }

	void SetXPosition(int i_x){ x = i_x; }
	void SetYPosition(int i_y){ y = i_y; }

private:
	int x = 0;
	int y = 0;
};

#endif