#include "GridEffect.h"

using namespace cocos2d;

static bool s_isDebug;

enum {
	MAX_GRID_NUM = 40,
};

GridEffectSprite* GridEffectSprite::create(cocos2d::CCSprite* m_originalSprite) 
{
	GridEffectSprite* ret = new GridEffectSprite();
	ret->init(m_originalSprite);
	return ret;
}

void GridEffectSprite::init(cocos2d::CCSprite* originalSprite) 
{
	m_originalSprite = originalSprite;
	m_pobBatchNode = 0;

	this->addChild(originalSprite);

	CCSprite::init();
	this->setZOrder(m_originalSprite->getZOrder());
	originalSprite->setZOrder(0);

	m_rt = CCRenderTexture::create(m_originalSprite->getContentSize().width, m_originalSprite->getContentSize().height);
	m_rt->retain();

	drawRT();

	setGridEffect(GridEffect::create(this, 1, 0));
}

void GridEffectSprite::setGridEffect(GridEffect* gridEffect)
{
	CC_SAFE_RELEASE(m_gridEffect);

	m_gridEffect = gridEffect;
	m_gridEffect->retain();
}

void GridEffectSprite::visit()
{
	// quick return if not visible. children won't be drawn.
	if (!m_bVisible)
	{
		return;
	}
	kmGLPushMatrix();

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->beforeDraw();
	}

	this->transform();

	CCNode* pNode = NULL;
	unsigned int i = 0;

	if(m_pChildren && m_pChildren->count() > 0)
	{
		sortAllChildren();
		// draw children zOrder < 0
		ccArray *arrayData = m_pChildren->data;
		for( ; i < arrayData->num; i++ )
		{
			pNode = (CCNode*) arrayData->arr[i];
			if (pNode == m_originalSprite) continue;
			if ( pNode && pNode->getZOrder() < 0 ) 
			{
				pNode->visit();
			}
			else
			{
				break;
			}
		}
		// self draw
		this->draw();

		for( ; i < arrayData->num; i++ )
		{
			pNode = (CCNode*) arrayData->arr[i];
			if (pNode == m_originalSprite) continue;
			if (pNode)
			{
				pNode->visit();
			}
		}        
	}
	else
	{
		this->draw();
	}

	// reset for next frame
	m_uOrderOfArrival = 0;

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->afterDraw(this);
	}

	kmGLPopMatrix();
}

void GridEffectSprite::draw()
{
	CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "GridEffectSprite - draw");

	CC_NODE_DRAW_SETUP();

	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

	if (s_isDebug) {
#ifdef WIN32
		glEnable (GL_POLYGON_SMOOTH);
		glHint (GL_POLYGON_SMOOTH, GL_NICEST);
#endif
	}

	int todo_why_it_is_red_colored;

	ccGLBindTexture2D(m_rt->getSprite()->getTexture()->getName());
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

#ifdef WIN32
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, m_gridEffect->vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, m_gridEffect->vertColors);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, m_gridEffect->texCoords);

	glDrawArrays(GL_TRIANGLES, 0, 3 * m_gridEffect->m_triangleNum);
#else
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, m_gridEffect->vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, m_gridEffect->vertColors);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, m_gridEffect->texCoords);
	glDrawArrays(GL_TRIANGLES, 0, 3 * m_gridEffect->m_triangleNum);
#endif

	CHECK_GL_ERROR_DEBUG();

	CC_INCREMENT_GL_DRAWS(1);

	CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "GridEffectSprite - draw");
}

void GridEffectSprite::drawRT() 
{
	m_rt->beginWithClear(0, 0, 0, 0);

	m_originalSprite->setVisible(true);
	m_originalSprite->setPosition(ccp(m_originalSprite->getContentSize().width/2, m_originalSprite->getContentSize().height/2));
	m_originalSprite->visit();
	m_rt->end();

	CCSprite::setTexture(m_rt->getSprite()->getTexture());
	CCSprite::setTextureRect(CCRectMake(0, 0, m_originalSprite->getContentSize().width, m_originalSprite->getContentSize().height));
}

void GridEffect::startWithTarget(CCNode *pTarget) {
	GridEffectSprite* ngs = dynamic_cast<GridEffectSprite*>(pTarget);
	if (ngs == 0) return;

	ngs->setGridEffect(this);
}

bool GridEffect::init(GridEffectSprite* ngs, int gridNum, float totalSecond)
{
	CCActionInterval::initWithDuration(totalSecond);

	CCSprite* sprite = ngs->m_originalSprite;

	if (gridNum > MAX_GRID_NUM) {
		cocos2d::CCLog("GridSprite::initWithSprite(), gridNum > %d, reset gridNum to %d", (int)MAX_GRID_NUM, (int)MAX_GRID_NUM);
		gridNum = MAX_GRID_NUM;
	} else if (gridNum < 1) {
		cocos2d::CCLog("GridSprite::initWithSprite(), gridNum < 1, reset gridNum to 1");
		gridNum = 1;
	}

	this->m_gridNum = gridNum;
	this->m_triangleNum = gridNum * gridNum * 2;
	this->m_gridSize = cocos2d::CCSize(sprite->getContentSize().width / gridNum, sprite->getContentSize().height / gridNum);

	vertices = new TriangleVertices[m_triangleNum];
	texCoords = new TriangleVertices[m_triangleNum];
	vertColors = new TriangleColors[m_triangleNum];

	for(int i = 0; i < m_triangleNum; i++)
	{
		vertices[i].pt1 = ccp(0,0);
		vertices[i].pt2 = ccp(0,0);
		vertices[i].pt3 = ccp(0,0);

		texCoords[i].pt1 = ccp(0,0);
		texCoords[i].pt2 = ccp(0,0);
		texCoords[i].pt3 = ccp(0,0);

		vertColors[i].c1 = ccc4(255, 255, 255, 255);
		vertColors[i].c2 = ccc4(255, 255, 255, 255);
		vertColors[i].c3 = ccc4(255, 255, 255, 255);
	}
    
    float wid = sprite->getTexture()->getContentSizeInPixels().width;
    float hgt = sprite->getTexture()->getContentSizeInPixels().height;
    float    pieceXsize = (wid/(float)m_gridNum); //*CC_CONTENT_SCALE_FACTOR();
    float    pieceYsize = (hgt/(float)m_gridNum); //*CC_CONTENT_SCALE_FACTOR();
    
    //Texture is padded out to a power of 2!!
    float texWid = (wid/sprite->getTexture()->getPixelsWide());
    float texHgt = (hgt/sprite->getTexture()->getPixelsHigh());
    
	std::vector<std::vector<CCPoint> > ptArray(m_gridNum + 1, std::vector<CCPoint>(m_gridNum + 1, CCPointMake(0, 0)));
    for (int x = 0; x <= m_gridNum; ++x) {
        for (int y = 0; y <= m_gridNum; ++y) {
            ptArray[x][y] = CCPointMake((x * pieceXsize), (y * pieceYsize));
        }
    }
    
	int cur = 0;
	int numVertices = 0;
    for (int y = 0; y < m_gridNum; ++y) {
        for (int x = 0; x < m_gridNum; ++x) {
			vertices[cur] = tri(ptArray[x][y], ptArray[x+1][y], ptArray[x][y+1]);
			vertices[cur + 1] = tri(ptArray[x+1][y], ptArray[x+1][y+1], ptArray[x][y+1]);

			texCoords[cur] = tri(ccp((ptArray[x][y].x/wid)*texWid, (ptArray[x][y].y/hgt)*texHgt),
				ccp((ptArray[x+1][y].x/wid)*texWid, (ptArray[x+1][y].y/hgt)*texHgt),
				ccp((ptArray[x][y+1].x/wid)*texWid, (ptArray[x][y+1].y/hgt)*texHgt));
			texCoords[cur + 1] = tri(ccp((ptArray[x+1][y].x/wid)*texWid, (ptArray[x+1][y].y/hgt)*texHgt),
				ccp((ptArray[x+1][y+1].x/wid)*texWid, (ptArray[x+1][y+1].y/hgt)*texHgt),
				ccp((ptArray[x][y+1].x/wid)*texWid, (ptArray[x][y+1].y/hgt)*texHgt));
			cur += 2;
        }
    }

	return true;
}

CCObject* GridEffect::copyWithZone( CCZone* pZone )
{
	CCZone* pNewZone = NULL;
	GridEffect* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (GridEffect*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new GridEffect();
		pZone = pNewZone = new CCZone(pCopy);
	}

	CCActionInterval::copyWithZone(pZone);

	int todo_think_about_it;

	CC_SAFE_DELETE(pNewZone);

	return pCopy;
}


GE_Shake* GE_Shake::create(GridEffectSprite* ngs, int range, float totalSecond) {
	GE_Shake* ret = new GE_Shake();
	ret->init(ngs, range, totalSecond);
	ret->autorelease();
	return ret;
}

bool GE_Shake::init(GridEffectSprite* ges, int range, float totalSecond) {
	GridEffect::init(ges, 1, totalSecond);

	m_range = range;

	{
		TriangleVertices* pTri1 = getTriangle(0, 0);
		m_originalTri1.pt1 = pTri1->pt1;
		m_originalTri1.pt2 = pTri1->pt2;
		m_originalTri1.pt3 = pTri1->pt3;
	}
	{
		TriangleVertices* pTri2 = getTriangle(0, 1);
		m_originalTri2.pt1 = pTri2->pt1;
		m_originalTri2.pt2 = pTri2->pt2;
		m_originalTri2.pt3 = pTri2->pt3;
	}
	return true;
}

void GE_Shake::update(float dt) {
	CCPoint shake1(( rand() % (m_range*2) ) - m_range, ( rand() % (m_range*2) ) - m_range);
	CCPoint shake2(( rand() % (m_range*2) ) - m_range, ( rand() % (m_range*2) ) - m_range);
	CCPoint shake3(( rand() % (m_range*2) ) - m_range, ( rand() % (m_range*2) ) - m_range);
	CCPoint shake4(( rand() % (m_range*2) ) - m_range, ( rand() % (m_range*2) ) - m_range);

	TriangleVertices* pTri1 = getTriangle(0, 0);
	TriangleVertices* pTri2 = getTriangle(0, 1);

	pTri1->pt1.x = m_originalTri1.pt1.x + shake1.x;
	pTri1->pt1.y = m_originalTri1.pt1.y + shake1.y;
	pTri1->pt2.x = m_originalTri1.pt2.x + shake2.x;
	pTri1->pt2.y = m_originalTri1.pt2.y + shake2.y;
	pTri1->pt3.x = m_originalTri1.pt3.x + shake3.x;
	pTri1->pt3.y = m_originalTri1.pt3.y + shake3.y;

	pTri2->pt1.x = m_originalTri2.pt1.x + shake2.x;
	pTri2->pt1.y = m_originalTri2.pt1.y + shake2.y;
	pTri2->pt2.x = m_originalTri2.pt2.x + shake4.x;
	pTri2->pt2.y = m_originalTri2.pt2.y + shake4.y;
	pTri2->pt3.x = m_originalTri2.pt3.x + shake3.x;
	pTri2->pt3.y = m_originalTri2.pt3.y + shake3.y;
}

CCObject* GE_Shake::copyWithZone( CCZone* pZone )
{
	int todo_implements;
	return 0;
}


// ·­ÅÆÐ§¹û
GE_TurnOver* GE_TurnOver::create(GridEffectSprite* ngs, float degree, float totalSecond) {
	GE_TurnOver *pRet = new GE_TurnOver();
	pRet->init(ngs, degree, totalSecond);
	pRet->autorelease();
	return pRet;
}

void GE_TurnOver::startWithTarget(CCNode *pTarget) {
	GridEffectSprite* ngs = dynamic_cast<GridEffectSprite*>(pTarget);
	if (ngs == 0) return;

	GE_TurnOver* pOldTurnOver = dynamic_cast<GE_TurnOver*>(ngs->getGridEffect());
	if (pOldTurnOver != NULL) {
		m_startRadian = pOldTurnOver->m_radian;
	}

	GridEffect::startWithTarget(pTarget);
}

bool GE_TurnOver::init(GridEffectSprite* ges, float degree, float totalSecond) {
	GridEffect::init(ges, 1, totalSecond);

	m_xRadius = ges->getOriginalSprite()->getContentSize().width / 2;
	m_yRadius = ges->getOriginalSprite()->getContentSize().height / 2;
	m_period = degree != 0 ? totalSecond * 360.0f / degree : 1;

	if (m_xRadius == 0) m_xRadius = 1;
	if (m_yRadius == 0) m_yRadius = 1;
	if (m_period == 0) m_period = 1;
	return true;
}

void GE_TurnOver::update(float dt) {
	float elapsed = dt * m_fDuration;

	m_radian = m_startRadian + 2 * 3.1416f * (elapsed / m_period);
	float vSin = sinf(m_radian);
	float vCos = cosf(m_radian);
	float vvv = m_xRadius * m_yRadius * sqrtf(1.0f / (m_yRadius * m_yRadius * vCos * vCos + m_xRadius * m_xRadius * vSin * vSin));
	float vX = vCos * vvv;
	float vY = vSin * vvv / 16;
	CCLog("vX = %f, vY = %f", vX, vY);

	TriangleVertices* pTri1 = getTriangle(0, 0);
	TriangleVertices* pTri2 = getTriangle(0, 1);

	pTri1->pt1.x = m_xRadius - vX;
	pTri1->pt1.y = 0 - vY;
	pTri1->pt2.x = m_xRadius + vX;
	pTri1->pt2.y = 0 + vY;
	pTri1->pt3.x = m_xRadius - vX;
	pTri1->pt3.y = m_yRadius * 2 - vY;

	pTri2->pt1.x = m_xRadius + vX;
	pTri2->pt1.y = 0 + vY;
	pTri2->pt2.x = m_xRadius + vX;
	pTri2->pt2.y = m_yRadius * 2 + vY;
	pTri2->pt3.x = m_xRadius - vX;
	pTri2->pt3.y = m_yRadius * 2 - vY;
}

CCObject* GE_TurnOver::copyWithZone( CCZone* pZone )
{
	int todo_implements;
	return 0;
}


// ±ßËõ·Å
GE_EdgeScale* GE_EdgeScale::create(GridEffectSprite* ngs, float duration, float up, float down, float left, float right) {
	GE_EdgeScale *pRet = new GE_EdgeScale();
	pRet->init(ngs, duration, up, down, left, right);
	pRet->autorelease();
	return pRet;
}

void GE_EdgeScale::startWithTarget(CCNode *pTarget) {
	GridEffectSprite* ngs = dynamic_cast<GridEffectSprite*>(pTarget);
	if (ngs == 0) return;

	lastPercent = 0;
	GE_EdgeScale* pOldEdgeScale = dynamic_cast<GE_EdgeScale*>(ngs->getGridEffect());
	if (pOldEdgeScale != NULL) {
		for (int i = 0; i < 4; ++i) {
			step_scales[i] = (target_scales[i] - pOldEdgeScale->cur_scales[i]);
			cur_scales[i] = pOldEdgeScale->cur_scales[i];
		}
	} else {
		for (int i = 0; i < 4; ++i) {
			cur_scales[i] = 1.0f;
			step_scales[i] = (target_scales[i] - cur_scales[i]);
		}
	}

	GridEffect::startWithTarget(pTarget);
}

bool GE_EdgeScale::init(GridEffectSprite* ges, float duration, float up, float down, float left, float right) {
	GridEffect::init(ges, 1, duration);

	target_scales[0] = up;
	target_scales[1] = down;
	target_scales[2] = left;
	target_scales[3] = right;
	//step_scales[0] = up - cur_scales[0];
	//step_scales[1] = down - cur_scales[1];
	//step_scales[2] = left - cur_scales[2];
	//step_scales[3] = right - cur_scales[3];
	return true;
}

void GE_EdgeScale::update(float dt) {
	float delta = dt - lastPercent;
	lastPercent = dt;
	CCLog("dt-percent = %f", delta);
	for (int i = 0; i < 4; ++i) {
		cur_scales[i] += delta * step_scales[i];
	}

	TriangleVertices* pTri1 = getTriangle(0, 0);
	TriangleVertices* pTri2 = getTriangle(0, 1);

	float up = m_gridSize.width * cur_scales[0];
	float down = m_gridSize.width * cur_scales[1];
	float left = m_gridSize.height * cur_scales[2];
	float right = m_gridSize.height * cur_scales[3];

	pTri1->pt1.x = (m_gridSize.width - down) / 2;
	pTri1->pt1.y = (m_gridSize.height - left) / 2;
	pTri1->pt2.x = (m_gridSize.width + down) / 2;
	pTri1->pt2.y = (m_gridSize.height - right) / 2;
	pTri1->pt3.x = (m_gridSize.width - up) / 2;
	pTri1->pt3.y = (m_gridSize.height + left) / 2;

	pTri2->pt1.x = (m_gridSize.width + down) / 2;
	pTri2->pt1.y = (m_gridSize.height - right) / 2;
	pTri2->pt2.x = (m_gridSize.width + up) / 2;
	pTri2->pt2.y = (m_gridSize.height + right) / 2;
	pTri2->pt3.x = (m_gridSize.width - up) / 2;
	pTri2->pt3.y = (m_gridSize.height + left) / 2;
}

CCObject* GE_EdgeScale::copyWithZone( CCZone* pZone )
{
	int todo_implements;
	return 0;
}
