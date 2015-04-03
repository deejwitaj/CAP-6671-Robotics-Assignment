#ifndef INC_61C61E4F91C94280AF5B24FCB22F20B5
#define INC_61C61E4F91C94280AF5B24FCB22F20B5

enum CellSide
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

enum Action
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
};

struct Position
{
public:
	Position(int const i_x = 0, int const i_y = 0):
			x(i_x)
		, y(i_y)
	{
	}

	bool operator==(Position i_position) const
	{
		if ((x == i_position.GetXPosition()) && (y == i_position.GetYPosition()))
			return true;
		return false;
	}

	bool operator< (const Position& i_right) const
	{
		if (*this == i_right)
			return false;

		if (GetXPosition() < i_right.GetXPosition())
		{
			if ((GetYPosition() < i_right.GetYPosition()) || (GetYPosition() == i_right.GetYPosition()))
				return true;
			return false;
		}
		else if (GetXPosition() > i_right.GetXPosition())
		{
			if ((GetYPosition() == i_right.GetYPosition()) || (GetYPosition() > i_right.GetYPosition()))
				return false;
			return true;
		}
		else
		{
			if (GetYPosition() > i_right.GetYPosition())
				return false;
			return true;
		}
	}

	int GetXPosition() const { return x; }
	int GetYPosition() const { return y; }

	void SetXPosition(int i_x){ x = i_x; }
	void SetYPosition(int i_y){ y = i_y; }

private:
	int x = 0;
	int y = 0;
};

struct R
{
	R(Position i_state, Action i_action)
	{
		state = i_state;
		action = i_action;
	}

	bool operator== (const R& i_right) const
	{
		if (state == i_right.state)
			return true;
		return false;
	}

	bool operator< (const R& i_right) const
	{
		if (state < i_right.state)
			return true;

		return false;
	}
	Position state;
	Action action;
};

#endif