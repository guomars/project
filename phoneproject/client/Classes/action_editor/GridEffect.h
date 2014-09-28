#pragma  once

#include "cocos2d.h"

using namespace cocos2d;

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

// GridEffectXXX 目的是把之前的继承，改成组合，继承跟Action的配合不好弄
class GridEffectSprite;
class GridEffect : public cocos2d::CCActionInterval {
	friend class GridEffectSprite; 

protected:
	TriangleVertices* vertices;
	TriangleVertices* texCoords;
	TriangleColors*   vertColors;
	int m_gridNum;
	int m_triangleNum;
	cocos2d::CCSize m_gridSize;

	GridEffect() 
		: vertices(0), texCoords(0), vertColors(0), m_gridNum(0), m_triangleNum(0), m_gridSize(0, 0)
	{}

	bool init(GridEffectSprite* ngs, int gridNum, float totalSecond);

public:
	virtual CCObject* copyWithZone(CCZone* pZone);

	static GridEffect* create(GridEffectSprite* ngs, int gridNum, float totalSecond) {
		GridEffect* ret = new GridEffect();
		ret->init(ngs, gridNum, totalSecond);
		ret->autorelease();
		return ret;
	}

	virtual void startWithTarget(cocos2d::CCNode *pTarget) ;

	virtual ~GridEffect() {
		CC_SAFE_DELETE(vertices);
		CC_SAFE_DELETE(texCoords);
		CC_SAFE_DELETE(vertColors);
	}

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
};

// GridEffectXXX 目的是把之前的继承，改成组合，继承跟Action的配合不好弄
class GridEffectSprite : public cocos2d::CCSprite
{
	friend class GridEffect;

private:
	GridEffect* m_gridEffect;
	cocos2d::CCRenderTexture* m_rt;
	cocos2d::CCSprite* m_originalSprite;

public:
	GridEffectSprite() : m_gridEffect(0), m_rt(0), m_originalSprite(0) {}

	static GridEffectSprite* create(cocos2d::CCSprite* m_originalSprite);

	void init(cocos2d::CCSprite* originalSprite);

	void setGridEffect(GridEffect* gridEffect);

	GridEffect* getGridEffect() {
		return m_gridEffect;
	}

	cocos2d::CCSprite* getOriginalSprite() {
		return m_originalSprite;
	}

	void drawRT();

	virtual void draw();

	virtual void visit();

	~GridEffectSprite() {
		CC_SAFE_RELEASE(m_gridEffect);
		CC_SAFE_RELEASE(m_rt);
		CC_SAFE_RELEASE(m_originalSprite);
	}
};

// 翻牌效果
class GE_TurnOver : public GridEffect {
private:
	float m_startRadian;
	float m_radian;
	float m_period;
	float m_xRadius;
	float m_yRadius;
public:
	GE_TurnOver() : m_period(1), m_xRadius(1), m_yRadius(1), m_startRadian(0), m_radian(0) {}

	static GE_TurnOver* create(GridEffectSprite* ngs, float degree, float totalSecond);

	virtual void startWithTarget(CCNode *pTarget);

	virtual CCObject* copyWithZone(CCZone* pZone);

	bool init(GridEffectSprite* ges, float degree, float totalSecond);

	virtual void update(float dt);
};

// 边缩放
class GE_EdgeScale : public GridEffect {
private:
	float lastPercent;
	float cur_scales[4];		// up,down,left,right
	float step_scales[4];		// up,down,left,right
	float target_scales[4];
public:
	GE_EdgeScale() : lastPercent(0.0f) {
		for (int i = 0; i < 4; ++i) {
			cur_scales[i] = 1.0f;
			step_scales[i] = 0.0f;
			target_scales[i] = 1.0f;
		}
	}

	static GE_EdgeScale* create(GridEffectSprite* ngs, float duration, float up, float down, float left, float right);

	virtual void startWithTarget(CCNode *pTarget);

	virtual CCObject* copyWithZone(CCZone* pZone);

	bool init(GridEffectSprite* ges, float duration, float up, float down, float left, float right);

	virtual void update(float dt);
};

// 震动效果
class GE_Shake : public GridEffect {
private:
	int m_range;
	TriangleVertices m_originalTri1;
	TriangleVertices m_originalTri2;
public:
	GE_Shake() : m_range(0) {}

	static GE_Shake* create(GridEffectSprite* ngs, int range, float totalSecond);

	bool init(GridEffectSprite* ges, int range, float totalSecond);

	virtual CCObject* copyWithZone(CCZone* pZone);

	virtual void update(float dt);
};