#include "MapMgr.h"

aStar* GMapMgr::AStarStart(int X,int Y,int xE,int yE)
{
	aStar* pHeader = NULL;   
	aStar* ptail = NULL;
	pHeader = new aStar;   
	pHeader->X = X;   
	pHeader->Y = Y;   
	pHeader->Ppre = NULL;   
	pHeader->Pnext = NULL;   
	ptail = pHeader;  

	bool BRes = AstarGetWay(&pHeader,&ptail,xE,yE);

	for (int n = 0;n<m_max_row;n++)   
	{   
		for (int t = 0;t<m_max_col;t++)   
		{   
			if(m_map[n][t] & MAP_GRID_ALREADY_SEARCHED)   
			{   
				m_map[n][t] &= ~MAP_GRID_ALREADY_SEARCHED;   
			}   
		}   
	}   
	aStar* pRoot = new aStar;
	pRoot->X = ptail->X;
	pRoot->Y = ptail->Y;
	pRoot->Pnext = NULL;
	pRoot->Ppre = NULL;
	if (BRes == true)   
	{
		for (aStar* ptempE = ptail;ptempE->Ppre!=NULL;ptempE=ptempE->Ppre)    
		{
			if(ptempE->Pnext != NULL)
			{
				aStar* pLast = new aStar;
				pLast->X = ptempE->X;
				pLast->Y = ptempE->Y;
				pLast->Pnext = NULL;
				pLast->Pnext = pRoot;
				pRoot = pLast;
			}
		}   
	}
	aStar* ptempE = NULL;   
	while (pHeader!=NULL)   
	{   
		ptempE = pHeader;   
		pHeader = pHeader->Pnext;   
		delete ptempE;   
	}
	return pRoot;
}

bool GMapMgr::AstarGetWay(aStar** pHeader,aStar** ptail,int xE,int yE)
{
	aStar* pNew = 0; 
	static bool BRes = false;   
	//m_map[(*pHeader)->Y][(*pHeader)->X] = MAP_GRID_ALREADY_SEARCHED;
	for (aStar* ptemp=*pHeader;ptemp!=0;ptemp=ptemp->Pnext)   
	{
		if (!(m_map[ptemp->Y+1][ptemp->X] & MAP_GRID_DENY_MASK_ALL) && ptemp->Y+1<m_max_row)   
		{    
			pNew = new aStar;   
			pNew->X = ptemp->X;//map横坐标   
			pNew->Y = ptemp->Y+1;//map纵坐标   
			m_map[ptemp->Y+1][ptemp->X] |= MAP_GRID_ALREADY_SEARCHED;   
			pNew->Pnext = 0;   
			pNew->Ppre = ptemp;   
			(*ptail)->Pnext = pNew;   
			*ptail = pNew;   
			if (pNew->X == xE && pNew->Y == yE)//判断是否是到边界还是到终点 到终点的时候结束循环   
			{    
				BRes = true;   
				break;     
			}   
		}   
		if (!(m_map[ptemp->Y][ptemp->X+1] & MAP_GRID_DENY_MASK_ALL) && ptemp->X+1<m_max_col)   
		{   
			pNew = new aStar;   
			pNew->X = ptemp->X+1;   
			pNew->Y = ptemp->Y;
			m_map[ptemp->Y][ptemp->X+1] |= MAP_GRID_ALREADY_SEARCHED;   
			pNew->Pnext = 0;   
			pNew->Ppre = ptemp;   
			(*ptail)->Pnext = pNew;   
			*ptail = pNew;   
			if (pNew->X == xE && pNew->Y == yE)   
			{    
				BRes = true;   
				break;     
			}   
		}   
		if (!(m_map[ptemp->Y-1][ptemp->X] & MAP_GRID_DENY_MASK_ALL) && ptemp->Y-1>0)   
		{   
			pNew = new aStar;   
			pNew->X = ptemp->X;   
			pNew->Y = ptemp->Y-1;   
			m_map[ptemp->Y-1][ptemp->X] |= MAP_GRID_ALREADY_SEARCHED;   
			pNew->Pnext = 0;   
			pNew->Ppre = ptemp;   
			(*ptail)->Pnext = pNew;   
			*ptail = pNew;   
			if (pNew->X == xE && pNew->Y == yE)   
			{    
				BRes = true;   
				break;     
			}   
		}   
		if (!(m_map[ptemp->Y][ptemp->X-1] & MAP_GRID_DENY_MASK_ALL) && ptemp->X-1>0)   
		{   
			pNew = new aStar;   
			pNew->X = ptemp->X-1;   
			pNew->Y = ptemp->Y;   
			m_map[ptemp->Y][ptemp->X-1] |= MAP_GRID_ALREADY_SEARCHED;   
			pNew->Pnext = 0;   
			pNew->Ppre = ptemp;   
			(*ptail)->Pnext = pNew;   
			*ptail = pNew;   
			if (pNew->X == xE && pNew->Y == yE)   
			{    
				BRes = true;   
				break;     
			}   
		}   
#ifdef CAN_GO_LEAN
		if (   
			!(m_map[ptemp->Y][ptemp->X-1] & MAP_GRID_DENY_MASK_SET || m_map[ptemp->Y-1][ptemp->X] & MAP_GRID_DENY_MASK_SET)   
			&&   
			!(m_map[ptemp->Y-1][ptemp->X-1] & MAP_GRID_DENY_MASK_ALL) && ptemp->Y-1>0 && ptemp->X-1>0 )   
		{   
			pNew = new aStar;   
			pNew->X = ptemp->X-1;   
			pNew->Y = ptemp->Y-1;   
			m_map[ptemp->Y-1][ptemp->X-1] = MAP_GRID_ALREADY_SEARCHED;   
			pNew->Pnext = 0;   
			pNew->Ppre = ptemp;   
			(*ptail)->Pnext = pNew;   
			*ptail = pNew;   
			if (pNew->X == xE && pNew->Y == yE)   
			{    
				BRes = true;   
				break;     
			}   
		}   
		if (   
			!(m_map[ptemp->Y-1][ptemp->X] & MAP_GRID_DENY_MASK_SET || m_map[ptemp->Y][ptemp->X+1] & MAP_GRID_DENY_MASK_SET)   
			&&   
			!(m_map[ptemp->Y-1][ptemp->X+1] & MAP_GRID_DENY_MASK_ALL) &&ptemp->Y-1>0 && ptemp->X+1<m_max_col)   
		{   
			pNew = new aStar;   
			pNew->X = ptemp->X+1;   
			pNew->Y = ptemp->Y-1;   
			m_map[ptemp->Y-1][ptemp->X+1] = MAP_GRID_ALREADY_SEARCHED;   
			pNew->Pnext = 0;   
			pNew->Ppre = ptemp;   
			(*ptail)->Pnext = pNew;   
			*ptail = pNew;   
			if (pNew->X == xE && pNew->Y == yE)   
			{    
				BRes = true;   
				break;     
			}   
		}   
		if (   

			!(m_map[ptemp->Y+1][ptemp->X] & MAP_GRID_DENY_MASK_SET || m_map[ptemp->Y][ptemp->X-1] & MAP_GRID_DENY_MASK_SET)   
			&&   
			!(m_map[ptemp->Y+1][ptemp->X-1] & MAP_GRID_DENY_MASK_ALL) && ptemp->Y+1<m_max_row && ptemp->X-1>0)   
		{   
			pNew = new aStar;   
			pNew->X = ptemp->X-1;   
			pNew->Y = ptemp->Y+1;   
			m_map[ptemp->Y+1][ptemp->X-1] = MAP_GRID_ALREADY_SEARCHED;   
			pNew->Pnext = 0;   
			pNew->Ppre = ptemp;   
			(*ptail)->Pnext = pNew;   
			*ptail = pNew;   
			if (pNew->X == xE && pNew->Y == yE)   
			{    
				BRes = true;   
				break;     
			}   
		}   
		if (   
			!(m_map[ptemp->Y][ptemp->X+1] & MAP_GRID_DENY_MASK_SET || m_map[ptemp->Y+1][ptemp->X] & MAP_GRID_DENY_MASK_SET)   
			&&   
			!(m_map[ptemp->Y+1][ptemp->X+1] & MAP_GRID_DENY_MASK_ALL) &&    
			ptemp->Y+1<m_max_row && ptemp->X+1<m_max_col)   
		{   
			pNew = new aStar;   
			pNew->X = ptemp->X+1;   
			pNew->Y = ptemp->Y+1;   
			m_map[ptemp->Y+1][ptemp->X+1] = MAP_GRID_ALREADY_SEARCHED;   
			pNew->Pnext = 0;   
			pNew->Ppre = ptemp;   
			(*ptail)->Pnext = pNew;   
			*ptail = pNew;   
			if (pNew->X == xE && pNew->Y == yE)   
			{    
				BRes = true;   
				break;     
			}   
		}   
#endif
	}

	return BRes;
}