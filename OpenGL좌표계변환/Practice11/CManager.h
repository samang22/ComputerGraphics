#pragma once
#include <list>
#define DRAW_SIN '1'
#define DRAW_SPRING '2'
#define DRAW_RIBBON '3'
#define DRAW_RECTANGLE '4'

#define MOVE_X_SMALL 'x'
#define MOVE_X_LARGE 'X'
#define MOVE_Y_SMALL 'y'
#define MOVE_Y_LARGE 'Y'

#define EXPANSION_X_SMALL 's'
#define EXPANSION_X_LARGE 'S'

#define SHRINK_X_SMALL 'w'
#define SHRINK_X_LARGE 'W'


#define MOVE10_X_SMALL 'r'
#define MOVE10_X_LARGE 'R'

#define MOVE_ANIMATION_SMALL 'a'
#define MOVE_ANIMATION_LARGE 'A'
#define REVERSE_MOVE_ANIMATION_SMALL 'z'
#define REVERSE_MOVE_ANIMATION_LARGE 'Z'


#define STOP_ANIMATION_SMALL 't'
#define STOP_ANIMATION_LARGE 'T'

#define PROGRAM_QUIT_SMALL 'q'
#define PROGRAM_QUIT_LARGE 'Q'

#define RADIUS 100

class CManager
{
private:
	float Point[800][2];
	float LUX;
	float LUY;
	float RDX;
	float RDY;

	std::list<char> MoveList;

private:
	int Mode_Draw;
	int Mode_Move;
	bool Move_Switch;

public:
	void DrawLine();
	void Update();
	void Draw();
	bool Move();
	void InitCoordinate();

	void Delete();
public:
	void GetCommand(char _Key);
	int GetModeMove();
	bool GetMoveSwitch();
public:
	CManager();
	~CManager();
};

