#pragma once

enum APP_PHASE	{ SPLASH,	MENU,	GAME,	ENDING,		QUIT};
enum GAME_PHASE { LOAD,		PLAY,	PAUSE,	UNLOAD,		LOAD_NEXT };


extern APP_PHASE	g_sAPP_STAT;
extern GAME_PHASE	g_sGAME_STAT;


#define BIT(x) (1<<(x))

enum Content_FilterGroups 
{
    COL_NOTHING = 0,	// Collide with Nothing
	COL_BASIC = BIT(1), // Collide with Basic Objects
    COL_WALLS = BIT(2), // Collide with Walls
	COL_BALLS = BIT(3), // Collide with Balls
};

//extern const int Content_Filter_WallsCollides = COL_BASIC | COL_BALLS;