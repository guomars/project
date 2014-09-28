#include "GridSprite.h"
#include <cmath>
USING_NS_CC;

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef RANDF
static float randf(float base, float range) {
    if (range==0) return base;
    long        lRange = rand()%(int)((range*2)*10000);
    float        fRange = ((float)lRange/10000.0) - range;
    return    base + fRange;
}
#endif
#ifdef WIN32
#define roundf(x) ((int)(x + 0.5))
#endif

bool s_isDebug = false;

static cocos2d::CCPoint tmpPoint;

static void rotateTriangle(TriangleVertices* pTri, float angel)
{
	tmpPoint.x = (pTri->pt1.x + pTri->pt2.x + pTri->pt3.x) / 3;
	tmpPoint.y = (pTri->pt1.y + pTri->pt2.y + pTri->pt3.y) / 3;

	pTri->pt1 = ccpRotateByAngle(pTri->pt1, tmpPoint, angel);
	pTri->pt2 = ccpRotateByAngle(pTri->pt2, tmpPoint, angel);
	pTri->pt3 = ccpRotateByAngle(pTri->pt3, tmpPoint, angel);
}

GridSprite::GridSprite() : 
	m_gridNum(1), vertices(NULL), texCoords(NULL), m_rt(NULL), m_originalSprite(NULL),
	m_totalSecond(-1.0f), m_t(0)
{}

GridSprite::~GridSprite()
{
	CC_SAFE_RELEASE(m_originalSprite);
	if (vertices != NULL) {
		delete [] vertices;
		vertices = NULL;
	}
	if (texCoords != NULL) {
		delete [] texCoords;
		texCoords = NULL;
	}
	CC_SAFE_RELEASE(m_rt);
}

GridSprite* GridSprite::create(cocos2d::CCSprite *sprite, int gridNum, float totalSecond)
{
    GridSprite *pRet = new GridSprite();
    pRet->initWithSprite(sprite, gridNum, totalSecond);
    pRet->autorelease();
    return pRet;
}

bool GridSprite::initWithSprite(cocos2d::CCSprite *sprite, int gridNum, float totalSecond)
{
	m_totalSecond = totalSecond;
	m_pobBatchNode = 0;
	this->addChild(sprite);

	if (gridNum > MAX_GRID_NUM) {
		CCLog("GridSprite::initWithSprite(), gridNum > %d, reset gridNum to %d", (int)MAX_GRID_NUM, (int)MAX_GRID_NUM);
		gridNum = MAX_GRID_NUM;
	} else if (gridNum < 1) {
		CCLog("GridSprite::initWithSprite(), gridNum < 1, reset gridNum to 1");
		gridNum = 1;
	}

    if(CCSprite::init())
    {
		sprite->retain();
		this->m_originalSprite = sprite;
		this->m_gridNum = gridNum;
		this->m_triangleNum = gridNum * gridNum * 2;
		this->m_gridSize = cocos2d::CCSize(sprite->getContentSize().width / gridNum, sprite->getContentSize().height / gridNum);

		vertices = new TriangleVertices[m_triangleNum];
		texCoords = new TriangleVertices[m_triangleNum];

		for(int i = 0; i < m_triangleNum; i++)
		{
			vertices[i].pt1 = ccp(0,0);
			vertices[i].pt2 = ccp(0,0);
			vertices[i].pt3 = ccp(0,0);

			texCoords[i].pt1 = ccp(0,0);
			texCoords[i].pt2 = ccp(0,0);
			texCoords[i].pt3 = ccp(0,0);
		}

        makeTextrueAndGrid();
        return true;
    }
    return false;
}

void GridSprite::visit()
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

	// not draw children
	this->draw();

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->afterDraw(this);
	}

	kmGLPopMatrix();
}

void GridSprite::draw()
{
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture));

    CC_NODE_DRAW_SETUP();
	ccGLBindTexture2D(m_rt->getSprite()->getTexture()->getName());
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);
	
#ifdef WIN32
	if (s_isDebug) {
		glEnable(GL_POLYGON_SMOOTH);
	}
	glVertexAttribPointerARB(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointerARB(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, texCoords);
	glDrawArrays(GL_TRIANGLES, 0, 3 * m_triangleNum);
#else
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, texCoords);
	glDrawArrays(GL_TRIANGLES, 0, 3 * m_triangleNum);
#endif
}

void GridSprite::step(float dt)
{
	m_t += dt;
	m_originalSprite->update(dt);
	drawRT();
}

void GridSprite::setTexture(CCTexture2D *texture) 
{
	if (m_originalSprite == NULL) return;

	m_originalSprite->setTexture(texture);
}

void GridSprite::setTextureRect(const CCRect& rect)
{
	if (m_originalSprite == NULL) return;

	m_originalSprite->setTextureRect(rect);
}

void GridSprite::setOpacity(GLubyte opacity) 
{
	if (m_originalSprite == NULL) return;

	this->m_originalSprite->setOpacity(opacity);
}

void GridSprite::drawRT() 
{
	m_rt->beginWithClear(0, 0, 0, 0);

	//ccBlendFunc originalBlend = m_originalSprite->getBlendFunc();
	ccBlendFunc func = { GL_ONE, GL_ZERO};
	m_originalSprite->setBlendFunc(func);
	m_originalSprite->setVisible(true);
	m_originalSprite->setPosition(ccp(m_originalSprite->getContentSize().width/2, m_originalSprite->getContentSize().height/2));
	m_originalSprite->visit();
	m_rt->end();

	CCSprite::setTexture(m_rt->getSprite()->getTexture());
	CCSprite::setTextureRect(CCRectMake(0, 0, m_originalSprite->getContentSize().width, m_originalSprite->getContentSize().height));
}


void GridSprite::makeTextrueAndGrid()
{
	m_rt = CCRenderTexture::create(m_originalSprite->getContentSize().width, m_originalSprite->getContentSize().height);
	m_rt->retain();

	drawRT();
    
    float wid = m_originalSprite->getTexture()->getContentSizeInPixels().width;
    float hgt = m_originalSprite->getTexture()->getContentSizeInPixels().height;
    float    pieceXsize = (wid/(float)m_gridNum); //*CC_CONTENT_SCALE_FACTOR();
    float    pieceYsize = (hgt/(float)m_gridNum); //*CC_CONTENT_SCALE_FACTOR();
    
    //Texture is padded out to a power of 2!!
    float texWid = (wid/getTexture()->getPixelsWide());
    float texHgt = (hgt/getTexture()->getPixelsHigh());
    
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
}

GS_RegionShake::~GS_RegionShake() {
	if (m_original_vertices != NULL) {
		delete[] m_original_vertices;
	}
	for (std::vector<RegionParam>::iterator it = m_params.begin(); it != m_params.end(); ++it) {
		if (it->m_distance_factor != NULL)
			delete[] it->m_distance_factor;
	}
}

GS_RegionShake* GS_RegionShake::create(cocos2d::CCSprite *sprite, int gridNum, const std::string& fileName, float scale) {
	unsigned long size;
	tinyxml2::XMLDocument doc;
	char* szBuff = NULL;
	unsigned char* pData = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", &size);
	if (pData != NULL) {
		szBuff = new char[size + 1];
		szBuff[size] = 0;
		memcpy(szBuff, pData, size);
		delete[] pData;
		doc.ParseDeep(szBuff, 0 );
	} else {
		const char* pData = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><ry testBackGround=\"\" originalSize=\"(768,1024)\"></ry>";
		size = strlen(pData);
		szBuff = new char[size + 1];
		szBuff[size] = 0;
		memcpy(szBuff, pData, size);
		doc.ParseDeep(szBuff, 0 );
	}

	CCAssert(!doc.Error(), "Read RegionShake Tempalte File Failed !!!!");

	GS_RegionShake* ret = create(sprite, gridNum, doc.RootElement(), scale);
	delete szBuff;
	return ret;
}

GS_RegionShake* GS_RegionShake::create(cocos2d::CCSprite *sprite, int gridNum, tinyxml2::XMLElement* e, float scale)
{
	GS_RegionShake *pRet = new GS_RegionShake();
	pRet->initWithSprite(sprite, gridNum, e, scale);
	pRet->autorelease();
	return pRet;
}

static bool IsInEllipse(RegionParam& param, cocos2d::CCPoint& point) {
	return (point.x - param.center.x)*(point.x - param.center.x) / (param.radius.x * param.radius.x) 
		+ (point.y - param.center.y)*(point.y - param.center.y) / (param.radius.y * param.radius.y) <= 1; 
}

bool GS_RegionShake::initWithSprite(cocos2d::CCSprite *sprite, int gridNum, tinyxml2::XMLElement* e, float scale)
{
	GridSprite::initWithSprite(sprite, gridNum, -1);

	scheduleUpdateWithPriority(100000);

	if (e->Attribute("originalSize") != NULL && strlen(e->Attribute("originalSize")) != 0) {
		sscanf(e->Attribute("originalSize"), "(%f,%f)", &m_originalSize.x, &m_originalSize.y);
	}
	for (tinyxml2::XMLElement* eParam = e->FirstChildElement("RegionParam"); eParam != NULL; eParam = eParam->NextSiblingElement("RegionParam")) {
		m_params.push_back(RegionParam(eParam, gridNum, scale));
	}

	m_original_vertices = new TriangleVertices[getTriangleNum()];
	for (int i = 0; i < getTriangleNum(); ++i) {
		m_original_vertices[i] = vertices[i];
	}

	for (std::vector<RegionParam>::iterator it = m_params.begin(); it != m_params.end(); ++it) {
		float maxRadius = 0;
		it->m_distance_factor = new Distance3[getTriangleNum()];
		for (int i = 0; i < getTriangleNum(); ++i) {
			if (IsInEllipse(*it, vertices[i].pt1)) {
				it->m_distance_factor[i].d1 = ccpDistance(vertices[i].pt1, it->moveCenter);
				maxRadius = max(maxRadius, it->m_distance_factor[i].d1);
			} else {
				it->m_distance_factor[i].d1 = -1;
			}

			if (IsInEllipse(*it, vertices[i].pt2)) {
				it->m_distance_factor[i].d2 = ccpDistance(vertices[i].pt2, it->moveCenter);
				maxRadius = max(maxRadius, it->m_distance_factor[i].d2);
			} else {
				it->m_distance_factor[i].d2 = -1;
			}

			if (IsInEllipse(*it, vertices[i].pt3)) {
				it->m_distance_factor[i].d3 = ccpDistance(vertices[i].pt3, it->moveCenter);
				maxRadius = max(maxRadius, it->m_distance_factor[i].d3);
			} else {
				it->m_distance_factor[i].d3 = -1;
			}
		}

		for (int i = 0; i < getTriangleNum(); ++i) {
			if (it->m_distance_factor[i].d1 < 0) {
				it->m_distance_factor[i].d1 = 0;
			} else {
				it->m_distance_factor[i].d1 = abs(maxRadius - it->m_distance_factor[i].d1) / maxRadius;
			}
			if (it->m_distance_factor[i].d2 < 0) {
				it->m_distance_factor[i].d2 = 0;
			} else {
				it->m_distance_factor[i].d2 = abs(maxRadius - it->m_distance_factor[i].d2) / maxRadius;
			}
			if (it->m_distance_factor[i].d3 < 0) {
				it->m_distance_factor[i].d3 = 0;
			} else {
				it->m_distance_factor[i].d3 = abs(maxRadius - it->m_distance_factor[i].d3) / maxRadius;
			}
		}
	}
	return true;
}

void GS_RegionShake::step(float dt)
{
	m_damping_left_second -= dt;
	if (m_damping_left_second < 0) m_damping_left_second = 0;
	GridSprite::step(dt);

	for (int i = 0; i < getTriangleNum(); ++i) {
		vertices[i].pt1 = m_original_vertices[i].pt1;
		vertices[i].pt2 = m_original_vertices[i].pt2;
		vertices[i].pt3 = m_original_vertices[i].pt3;
	}

	for (std::vector<RegionParam>::iterator it = m_params.begin(); it != m_params.end(); ++it) {
		CCPoint dir;
		if (it->dir < 0) {
			it->dir = rand() % 360;
		}

		float dumpingFactor = m_damping_left_second / DUMPING_TOTAL_SECOND;
		float amplitude = it->amplitude * sin(dumpingFactor * 1.57);
		if (it->dir >= 0) {
			dir.x = cos(it->dir / 180 * 3.14) * amplitude * sin(m_t / it->period * 6.28 * (1.4 - dumpingFactor / 2.5) * (1.4 - dumpingFactor / 2.5));
			dir.y = sin(it->dir / 180 * 3.14) * amplitude * sin(m_t / it->period * 6.28 * (1.4 - dumpingFactor / 2.5) * (1.4 - dumpingFactor / 2.5));
		} 
		/*else {
			int random = rand() % 360; 
			dir.x = cos(random / 180 * 3.14) * it->amplitude * sin(m_t / it->period * 6.28);
			dir.y = sin(random / 180 * 3.14) * it->amplitude * sin(m_t / it->period * 6.28);
		}*/

		for (int i = 0; i < getTriangleNum(); ++i) {
			vertices[i].pt1.x = vertices[i].pt1.x + dir.x * it->m_distance_factor[i].d1;
			vertices[i].pt1.y = vertices[i].pt1.y + dir.y * it->m_distance_factor[i].d1;

			vertices[i].pt2.x = vertices[i].pt2.x + dir.x * it->m_distance_factor[i].d2;
			vertices[i].pt2.y = vertices[i].pt2.y + dir.y * it->m_distance_factor[i].d2;

			vertices[i].pt3.x = vertices[i].pt3.x + dir.x * it->m_distance_factor[i].d3;
			vertices[i].pt3.y = vertices[i].pt3.y + dir.y * it->m_distance_factor[i].d3;
		}
	}
}

GS_Shake* GS_Shake::create(cocos2d::CCSprite *sprite, int range, float totalSecond) 
{
	GS_Shake *pRet = new GS_Shake();
	pRet->initWithSprite(sprite, range, totalSecond);
	pRet->autorelease();
	return pRet;
}

bool GS_Shake::initWithSprite(cocos2d::CCSprite *sprite, int range, float totalSecond) {
	GridSprite::initWithSprite(sprite, 1, totalSecond);

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

	m_range = range;
	return true;
}

void GS_Shake::step(float dt) {
	GridSprite::step(dt);

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

GS_TurnOver* GS_TurnOver::create(cocos2d::CCSprite *sprite,  float degree, float totalSecond) 
{
	GS_TurnOver *pRet = new GS_TurnOver();
	pRet->initWithSprite(sprite, degree, totalSecond);
	pRet->autorelease();
	return pRet;
}

bool GS_TurnOver::initWithSprite(cocos2d::CCSprite *sprite, float degree, float totalSecond) {
	GridSprite::initWithSprite(sprite, 1, totalSecond);

	m_xRadius = sprite->getContentSize().width / 2;
	m_yRadius = sprite->getContentSize().height / 2;
	m_degree = degree;
	m_period = degree != 0 ? totalSecond / abs(degree) : 1;

	if (m_xRadius == 0) m_xRadius = 1;
	if (m_yRadius == 0) m_yRadius = 1;
	if (m_period == 0) m_period = 1;
	return true;
}

void GS_TurnOver::step(float dt) {
	if (isExpired()) return;
	GridSprite::step(dt);

	float radian = 2 * 3.1416f * (m_t / m_period);
	float vSin = sinf(radian);
	float vCos = cosf(radian);
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

GS_MoveShow* GS_MoveShow::create(cocos2d::CCSprite *sprite, int gridNum, float t, float speed, bool isDirX, bool isFadeIn)
{
	GS_MoveShow *pRet = new GS_MoveShow();
	pRet->initWithSprite(sprite, gridNum, t, speed, isDirX, isFadeIn);
	pRet->autorelease();
	return pRet;
}

bool GS_MoveShow::initWithSprite(cocos2d::CCSprite *sprite, int gridNum, float t, float speed, bool isDirX, bool isFadeIn)
{
	GridSprite::initWithSprite(sprite, gridNum, -1);
	m_t = t;	// ???
	m_speed = speed;
	m_isDirX = isDirX;
	m_isFadeIn = isFadeIn;

	if (isFadeIn) {
		for (int x = 0; x < gridNum * 2; ++x) {
			for (int y = 0; y < gridNum; ++y) {
				setTriangleShow(y, x, false);
			}
		}
	}
	return true;
}

void GS_MoveShow::step(float dt)
{
	GridSprite::step(dt);

	int gridNum = getGridNum();

	float cur = m_t * m_speed;
	for (int x = 0; x < gridNum * 2; ++x) {
		for (int y = 0; y < gridNum; ++y) {
			if (m_isDirX) {
				if (cur > 0 && x / 2 < cur) { // ÏòÓÒ
					setTriangleShow(y, x, m_isFadeIn);
				} else if (cur < 0 && x / 2 > gridNum + cur) {
					setTriangleShow(y, x, m_isFadeIn);
				}
			} else {
				if (cur > 0 && y / 2 < cur) { // ÏòÉÏ
					setTriangleShow(y, x, m_isFadeIn);
				} else if (cur < 0 && y / 2 > gridNum + cur) {
					setTriangleShow(y, x, m_isFadeIn);
				}
			}
		}
	}
}

GS_Flow* GS_Flow::create(cocos2d::CCSprite *sprite, int gridNum, const CCPoint& startSpeed, const cocos2d::CCPoint& flowPosition, const cocos2d::CCPoint& flowSpeed, const cocos2d::CCPoint& rotateSpeed) 
{
	GS_Flow *pRet = new GS_Flow();
	pRet->initWithSprite(sprite, gridNum, startSpeed, flowPosition, flowSpeed, rotateSpeed);
	pRet->autorelease();
	return pRet;
}

bool GS_Flow::initWithSprite(cocos2d::CCSprite *sprite, int gridNum, const CCPoint& startSpeed, const cocos2d::CCPoint& flowPosition, const cocos2d::CCPoint& flowSpeed, const cocos2d::CCPoint& rotateSpeed) 
{
	GridSprite::initWithSprite(sprite, gridNum, -1);
	m_startSpeed = startSpeed;
	m_flowPosition = flowPosition;
	m_flowSpeed = flowSpeed;
	m_rotateSpeed = rotateSpeed;
	m_curFlowSpeed = new float[getTriangleNum()];
	m_curRotateSpeed = new float[getTriangleNum()];

	for (int i = 0; i < getTriangleNum(); ++i) {
		m_curFlowSpeed[i] = m_flowSpeed.x;
		m_curRotateSpeed[i] = m_rotateSpeed.x;
	}
	return true;
}

static bool isRightOfLine(const cocos2d::CCPoint& p, const cocos2d::CCPoint& p1, const cocos2d::CCPoint& p2) {
	return ((p.y - p1.y) * (p1.x - p2.x) > (p.x - p1.x) * (p1.y - p2.y));
}

void GS_Flow::step(float dt) 
{
	int gridNum = getGridNum();

	CCPoint cur(2 * gridNum - m_startSpeed.x * m_t * m_t, gridNum - m_startSpeed.y * m_t * m_t);
	CCPoint center;
	for (int x = 0; x < gridNum * 2; ++x) {
		for (int y = 0; y < gridNum; ++y) 
		{
			if (isRightOfLine(ccp(x, y), ccp(cur.x, gridNum), ccp(2*gridNum, cur.y))) continue;

			center.x = (getTriangle(y, x)->pt1.x + getTriangle(y, x)->pt2.x + getTriangle(y, x)->pt3.x) / 3;
			center.y = (getTriangle(y, x)->pt1.y + getTriangle(y, x)->pt2.y + getTriangle(y, x)->pt3.y) / 3;

			if (!isTriangleShow(y, x)) {
				continue;
			}
			if (ccpDistance(center, m_flowPosition) < 15.0f) {
				setTriangleShow(y, x, false);
				continue;
			}

			float& curFlowSpeed = m_curFlowSpeed[x + y * gridNum * 2];
			curFlowSpeed += m_flowSpeed.y * dt;
			{
				CCPoint dir = ccpNormalize(ccpSub(m_flowPosition, getTriangle(y, x)->pt1));
				getTriangle(y, x)->pt1.x += dir.x * dt * curFlowSpeed;
				getTriangle(y, x)->pt1.y += dir.y * dt * curFlowSpeed;
			}
			{
				CCPoint dir = ccpNormalize(ccpSub(m_flowPosition, getTriangle(y, x)->pt2));
				getTriangle(y, x)->pt2.x += dir.x * dt * curFlowSpeed;
				getTriangle(y, x)->pt2.y += dir.y * dt * curFlowSpeed;
			}
			{
				CCPoint dir = ccpNormalize(ccpSub(m_flowPosition, getTriangle(y, x)->pt3));
				getTriangle(y, x)->pt3.x += dir.x * dt * curFlowSpeed;
				getTriangle(y, x)->pt3.y += dir.y * dt * curFlowSpeed;
			}

			float& curRotateSpeed = m_curRotateSpeed[x + y * gridNum * 2];
			curRotateSpeed += m_rotateSpeed.y * dt;
			rotateTriangle(getTriangle(y, x), curRotateSpeed);
		}
	}

	GridSprite::update(dt);
}
