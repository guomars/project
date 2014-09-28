#pragma once

#ifndef GridSprite_h
#define GridSprite_h

#include "cocos2d.h"
#include "AEAction.h"
#include "support/tinyxml2/tinyxml2.h"

using namespace cocos2d;

enum {
	MAX_GRID_NUM = 40,
};

#ifndef DEFTriangleVertices
typedef struct _TriangleVertices {
    cocos2d::CCPoint        pt1;
    cocos2d::CCPoint        pt2;
    cocos2d::CCPoint        pt3;
} TriangleVertices;

static inline TriangleVertices
tri(cocos2d::CCPoint pt1, cocos2d::CCPoint pt2, cocos2d::CCPoint pt3) {
    TriangleVertices t;
    t.pt1 = pt1; t.pt2 = pt2; t.pt3 = pt3;
    return t;
}

typedef struct _TriangleColors {
    cocos2d::ccColor4B        c1;
    cocos2d::ccColor4B        c2;
    cocos2d::ccColor4B        c3;
} TriangleColors;
#define DEFTriangleVertices
#endif

extern bool s_isDebug;

class AEGridAction;
class GridSprite : public cocos2d::CCSprite
{  
	friend class AEGridAction;
public:
	static void setDebug() {
		s_isDebug = true;
	}

    GridSprite();
    virtual ~GridSprite();

	void setTotalSecond(float t) { m_totalSecond = t; }

	bool isExpired() { return m_totalSecond > 0 && m_t > m_totalSecond; }
    
    static GridSprite* create(cocos2d::CCSprite *sprite, int gridNum, float totalSecond = -1);
    bool initWithSprite(cocos2d::CCSprite *sprite, int gridNum, float totalSecond);
    
    virtual void draw();

	virtual void visit();

	virtual void drawRT();

	virtual void setTexture(cocos2d::CCTexture2D *texture);

	virtual void setTextureRect(const cocos2d::CCRect& rect);

	virtual void setOpacity(GLubyte opacity);

protected:

	virtual void step(float dt);
    
private:
	void makeTextrueAndGrid();
    
protected:
    TriangleVertices* vertices;
    TriangleVertices* texCoords;
	float m_t;

	bool isTriangleShow(int row, int col) {
		TriangleVertices* pTri = getTriangle(row, col);
		return pTri->pt1.x > -1000.0f;
	}

	void setTriangleShow(int row, int col, bool isShow) {
		TriangleVertices* pTri = getTriangle(row, col);
		if (isShow == isTriangleShow(row, col)) return;

		if (isShow) {
			vertices[row * m_gridNum * 2 + col].pt1.x += 10000.0f;
			vertices[row * m_gridNum * 2 + col].pt1.y += 10000.0f;
			vertices[row * m_gridNum * 2 + col].pt2.x += 10000.0f;
			vertices[row * m_gridNum * 2 + col].pt2.y += 10000.0f;
			vertices[row * m_gridNum * 2 + col].pt3.x += 10000.0f;
			vertices[row * m_gridNum * 2 + col].pt3.y += 10000.0f;
		} else {
			vertices[row * m_gridNum * 2 + col].pt1.x -= 10000.0f;
			vertices[row * m_gridNum * 2 + col].pt1.y -= 10000.0f;
			vertices[row * m_gridNum * 2 + col].pt2.x -= 10000.0f;
			vertices[row * m_gridNum * 2 + col].pt2.y -= 10000.0f;
			vertices[row * m_gridNum * 2 + col].pt3.x -= 10000.0f;
			vertices[row * m_gridNum * 2 + col].pt3.y -= 10000.0f;
		}
	}

	TriangleVertices* getTriangle(int row, int col) {
		return &vertices[row * m_gridNum * 2 + col];
	}

protected:
	cocos2d::CCSize& getGridSize() { return m_gridSize; };
	int getGridNum() { return m_gridNum; }
	int getTriangleNum() { return m_triangleNum; }
	cocos2d::CCSprite* getOriginalSprite() { return m_originalSprite; }

private:
	float m_totalSecond;
	int m_gridNum;
	cocos2d::CCSize m_gridSize;
	int m_triangleNum;
	cocos2d::CCRenderTexture* m_rt;
	cocos2d::CCSprite* m_originalSprite;
};

// TODO 修改成网格放在精灵身上?? 直接开启动作??
//  GridSprite 即有网格的精灵， has a Grid

class AEGridAction : public cocos2d::CCActionInterval {
public:
	AEGridAction() : mGridSprite(NULL) {}

	virtual void startWithTarget(cocos2d::CCNode *pTarget) {
		CCActionInterval::startWithTarget(pTarget);

		mGridSprite = dynamic_cast<GridSprite*>(pTarget);
		if (mGridSprite != NULL) {
			mGridSprite->setTotalSecond(getDuration());
		}
	}

	virtual void update(float time) {
		if (mGridSprite != NULL)
			mGridSprite->step(time);
	}

public:
	static AEGridAction* create(float duration) 
	{
		AEGridAction *pRet = new AEGridAction();
		pRet->initWithDuration(duration);
		if (pRet) {
			pRet->autorelease();
		}
		return pRet;
	}

private:
	GridSprite* mGridSprite;
};

struct Distance3 {
public:
	float d1;
	float d2;
	float d3;

	Distance3(float _d1, float _d2, float _d3) : d1(_d1), d2(_d2), d3(_d3) { }
	Distance3() : d1(0), d2(0), d3(0) { }
};

class RegionParam {
	enum {
		eTypeSin,
	};

public:
	cocos2d::CCPoint center;
	cocos2d::CCPoint radius;
	cocos2d::CCPoint moveCenter;
	float dir;
	float amplitude;
	float period;
	int type;
	Distance3* m_distance_factor;

	RegionParam() : dir(-1), amplitude(10), period(2), type(eTypeSin), m_distance_factor(NULL) {

	}

	RegionParam(tinyxml2::XMLElement* e, int triangleNum, float scale) : dir(-1), amplitude(10), period(2), type(eTypeSin) {
		if (e->Attribute("center") != NULL && strlen(e->Attribute("center")) != 0) sscanf(e->Attribute("center"), "(%f,%f)", &center.x, &center.y);
		if (e->Attribute("radius") != NULL && strlen(e->Attribute("radius")) != 0) sscanf(e->Attribute("radius"), "(%f,%f)", &radius.x, &radius.y);
		if (e->Attribute("moveCenter") != NULL && strlen(e->Attribute("moveCenter")) != 0) sscanf(e->Attribute("moveCenter"), "(%f,%f)", &moveCenter.x, &moveCenter.y);
		if (e->Attribute("dir") != NULL && strlen(e->Attribute("dir")) != 0) dir = e->FloatAttribute("dir");
		if (e->Attribute("amplitude") != NULL && strlen(e->Attribute("amplitude")) != 0) amplitude = e->FloatAttribute("amplitude");
		if (e->Attribute("period") != NULL && strlen(e->Attribute("period")) != 0) period = e->FloatAttribute("period");
		if (e->Attribute("type") != NULL && strlen(e->Attribute("type")) != 0) {
			if (strcmp(e->Attribute("type"), "sin") == 0) {
				type = eTypeSin;
			}
		}

		if (scale != 1.0f) {
			center.x = center.x * scale;
			center.y = center.y * scale;
			radius.x = radius.x * scale;
			radius.y = radius.y * scale;
			moveCenter.x = moveCenter.x * scale;
			moveCenter.y = moveCenter.y * scale;
			amplitude = amplitude * scale;
		}
		if (period < 0.1) period = 0.1f;


		m_distance_factor = new Distance3[triangleNum];
	}
};

class GS_RegionShake : public GridSprite {
public:
	enum {
		DUMPING_TOTAL_SECOND = 4,
	};

private:
	cocos2d::CCPoint m_originalSize;
	std::vector<RegionParam> m_params;

	TriangleVertices* m_original_vertices;
	float m_damping_left_second;

public:
	GS_RegionShake() : m_damping_left_second(0) {}

	static GS_RegionShake* create(cocos2d::CCSprite *sprite, int gridNum, const std::string& fileName, float scale = 1);

	static GS_RegionShake* create(cocos2d::CCSprite *sprite, int gridNum, tinyxml2::XMLElement* e, float scale = 1);

	void trigger() { m_damping_left_second = DUMPING_TOTAL_SECOND; m_t = 0; }

	bool initWithSprite(cocos2d::CCSprite *sprite, int gridNum, tinyxml2::XMLElement* e, float scale = 1);

	virtual void step(float dt);

	virtual void update(float dt) {
		if (isExpired()) return;
		step(dt);
	}

	virtual ~GS_RegionShake();
};

// 震动效果
class GS_Shake : public GridSprite {
private:
	int m_range;
	TriangleVertices m_originalTri1;
	TriangleVertices m_originalTri2;
public:
	GS_Shake() : m_range(0) {}

	static GS_Shake* create(cocos2d::CCSprite *sprite, int range, float totalSecond = -1);

	bool initWithSprite(cocos2d::CCSprite *sprite, int range, float totalSecond);

	virtual void step(float dt);
};

// 翻牌效果
class GS_TurnOver : public GridSprite {
private:
	float m_degree;
	float m_period;
	float m_xRadius;
	float m_yRadius;
public:
	GS_TurnOver() : m_period(1), m_xRadius(1), m_yRadius(1), m_degree(360.0f) {}

	static GS_TurnOver* create(cocos2d::CCSprite *sprite, float degree, float totalSecond = -1);

	bool initWithSprite(cocos2d::CCSprite *sprite, float degree, float totalSecond);

	virtual void step(float dt);
};

class GS_MoveShow : public GridSprite {
private:
	float m_speed;
	bool m_isDirX;
	bool m_isFadeIn;

public:
	GS_MoveShow() :  m_speed(0), m_isDirX(true), m_isFadeIn(true) {}

	static GS_MoveShow* create(cocos2d::CCSprite *sprite, int gridNum, float t, float speed, bool isDirX, bool isFadeIn);

	bool initWithSprite(cocos2d::CCSprite *sprite, int gridNum, float t, float speed, bool isDirX, bool isFadeIn);

	virtual void step(float dt);

	virtual ~GS_MoveShow() {
	}
};

class GS_Flow : public GridSprite {
private:
	float m_t;
	cocos2d::CCPoint m_startSpeed;
	cocos2d::CCPoint m_flowPosition;
	cocos2d::CCPoint m_flowSpeed;		// 速度，加速度
	cocos2d::CCPoint m_rotateSpeed;		// 速度，加速度
	float* m_curFlowSpeed;
	float* m_curRotateSpeed;
public:
	GS_Flow() : m_curFlowSpeed(0), m_curRotateSpeed(0) {}

	static GS_Flow* create(cocos2d::CCSprite *sprite, int gridNum, const cocos2d::CCPoint& startSpeed, const cocos2d::CCPoint& flowPosition, const cocos2d::CCPoint& flowSpeed, const cocos2d::CCPoint& rotateSpeed);

	bool initWithSprite(cocos2d::CCSprite *sprite, int gridNum, const cocos2d::CCPoint& startSpeed, const cocos2d::CCPoint& flowPosition, const cocos2d::CCPoint& flowSpeed, const cocos2d::CCPoint& rotateSpeed);

	virtual void step(float dt);

	virtual ~GS_Flow() {
		CC_SAFE_DELETE(m_curRotateSpeed);
		CC_SAFE_DELETE(m_curFlowSpeed);
	}
};
#endif







