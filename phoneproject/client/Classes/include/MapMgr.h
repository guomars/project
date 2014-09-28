#ifndef __G_MAP_MGR_H__
#define __G_MAP_MGR_H__

#include <stdio.h>
#include <memory.h>

#define MAX_ROW 128
#define MAX_COL 128

typedef unsigned char MAP_GRID_TYPE;

//如果这个宏打开的话寻路支持斜着穿格子
#define CAN_GO_LEAN

enum
{
	MAP_GRID_BASIC_DENY = 0x01,
	MAP_GRID_ALREADY_SEARCHED = 0x80,

	MAP_GRID_DENY_MASK_SET = MAP_GRID_BASIC_DENY,	//除了已经搜索的标志之外不允许通过的标志集合
	MAP_GRID_DENY_MASK_ALL = MAP_GRID_DENY_MASK_SET | MAP_GRID_ALREADY_SEARCHED,	//所有不许通过的标志集合
};

struct  aStar
{   
	int X;   
	int Y;   
	aStar* Pnext;   
	aStar* Ppre;

	inline aStar* GetNext()
	{
		return Pnext;
	}
	inline int GetX() const {return X;}
	inline int GetY() const {return Y;}

	inline void Release()
	{
		aStar* ptempE = this;
		aStar* p = ptempE;
		while(p != NULL)
		{
			p = ptempE->Pnext;
			delete ptempE;
			ptempE = p;
		}

	}
};

class GMapMgr
{
	GMapMgr():m_max_row(MAX_ROW),m_max_col(MAX_COL) 
	{
		memset(m_map,0,sizeof(m_map));
	}

public:
	static GMapMgr * GetInstance()
	{
		static GMapMgr gmapmgr;
		return &gmapmgr;
	}

	inline void SetMaxSize(int max_row, int max_col)
	{
		if (max_row < 0 || max_row > MAX_ROW ||
			max_col < 0 || max_col > MAX_COL)
			return;

		memset(m_map,0,sizeof(m_map));
		m_max_row = max_row;
		m_max_col = max_col;
	}

	inline void SetMapGrid(int row, int col, MAP_GRID_TYPE grid)
	{
		if (row < 0 || row > m_max_row ||
			col < 0 || col > m_max_col)
			return;

		m_map[row][col] = grid;
	}

	inline int GetMapGrid(int row, int col)
	{
		if (row < 0 || row > m_max_row ||
			col < 0 || col > m_max_col)
			return -1;

		return m_map[row][col];
	}

	aStar* AStarStart(int X,int Y,int xE,int yE);

private:
	bool AstarGetWay(aStar** pHeader,aStar** ptail,int xE,int yE);

private:
	MAP_GRID_TYPE m_map[MAX_ROW][MAX_COL];
	int m_max_row;
	int m_max_col;
};

#endif