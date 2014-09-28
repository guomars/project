#pragma once

#include <string>
#include "cocos2d.h"

extern std::map<std::string, cocos2d::CCPoint> g_uiNameToOriginalPos;
extern bool g_ae_isSoundOn;

namespace aeditor {
	class ActionTemplateTable;
}

NS_CC_BEGIN

/** 
@brief Modify Data
*/
class AE_SetData : public CCActionInstant
{
public:
	AE_SetData() {}
	bool init(std::string k, std::string v);
	virtual ~AE_SetData() {}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);
private:
	std::string key;
	std::string value;
public:
	/** Allocates and initializes the action */
	static AE_SetData * create(std::string k, std::string v);
};

/** 
@brief Modify ZOrder
*/
class AE_ZOrder : public CCActionInstant
{
public:
	AE_ZOrder() : m_zOrder(0) {}
	bool init(int zOrder);
	virtual ~AE_ZOrder(){}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);
private:
	int m_zOrder;
public:

	/** Allocates and initializes the action */
	static AE_ZOrder * create(int zOrder);
};

/** 
@brief Play Wav
*/
class AE_PlayWav : public CCActionInstant
{
private:
	std::string wavFile;

public:
	AE_PlayWav() {}
	virtual ~AE_PlayWav(){}
	bool init(std::string wavFile);
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);
public:
	/** Allocates and initializes the action */
	static AE_PlayWav * create(std::string wavFile);
};

/** 
@brief Modify ZOrder
*/
class GE_Stop : public CCActionInstant
{
public:
	GE_Stop() {}
	virtual ~GE_Stop(){}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);
public:

	/** Allocates and initializes the action */
	static GE_Stop * create();
};

/** 
@brief Run With Child Tag
*/
class AE_ChildTagRun : public CCActionInstant
{
public:
	AE_ChildTagRun() : m_childTag(0), m_childAction(NULL) {}
	virtual ~AE_ChildTagRun(){
		CC_SAFE_RELEASE(m_childAction);
	}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);
private:
	int m_childTag;
	CCAction* m_childAction;
public:

	/** Allocates and initializes the action */
	static AE_ChildTagRun * create(int childTag, CCAction* childAction);
	bool init(int childTag, CCAction* childAction);
};


/** 
@brief Scale
*/
class AE_Scale : public CCActionInstant
{
public:
	AE_Scale() : m_scale(0) {}
	virtual ~AE_Scale(){}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);
private:
	float m_scale;
public:

	/** Allocates and initializes the action */
	static AE_Scale * create(float scale);
	bool init(float scale);
};

/** 
@brief Immediately add particle
*/
class AE_Particle_Plist : public CCActionInstant
{
public:
	AE_Particle_Plist() {}
	virtual ~AE_Particle_Plist(){}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);
private:
	std::string m_plist;
	CCPoint m_pos;
	int m_zOrder;
	int m_tag;
	float m_scale;
	float m_rotate;
	cocos2d::tCCPositionType m_posType;
public:

	/** Allocates and initializes the action */
	static AE_Particle_Plist * create(std::string plist, float scale, CCPoint pos, int zOrder, int tag, tCCPositionType posType, float rotate);
	bool init(std::string plist, float scale, CCPoint pos, int zOrder, int tag, tCCPositionType posType, float rotate);
};

/** 
@brief Immediately add particle
*/
class AE_Particle_Sys : public CCActionInstant
{
public:
	AE_Particle_Sys() {}
	virtual ~AE_Particle_Sys(){}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);
private:
	std::string m_name;
	std::string m_res;
	unsigned int m_number;
	float m_scale;
	CCPoint m_pos;
	int m_zOrder;
	int m_tag;
public:

	/** Allocates and initializes the action */
	static AE_Particle_Sys * create(std::string name, std::string res,unsigned int number, float scale, CCPoint pos, int zOrder, int tag);
	bool init(std::string name, std::string res,unsigned int number, float scale, CCPoint pos, int zOrder, int tag);
};

/** 
@brief Immediately add AE subScene
*/
class AE_AddSubAE : public CCActionInstant
{
public:
	AE_AddSubAE() : m_scale(1.0f), m_zOrder(0), m_tag(0) {}
	virtual ~AE_AddSubAE(){}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);

	/** Allocates and initializes the action */
	static AE_AddSubAE * create(aeditor::ActionTemplateTable* table, const std::string& aeFile, const std::string& alignSprite, CCPoint pos, float scale, std::map<std::string, std::string>& resReplaced, int zOrder, int tag);
	bool init(aeditor::ActionTemplateTable* table, const std::string& aeFile, const std::string& alignSprite, CCPoint pos, float scale, std::map<std::string, std::string>& resReplaced, int zOrder, int tag);
private:
	aeditor::ActionTemplateTable* m_table;
	std::string m_aeFile;
	std::string m_alignSprite;
	CCPoint m_pos;
	float m_scale;
	std::map<std::string, std::string> m_resReplaced;
	int m_zOrder;
	int m_tag;
};

/** 
@brief Immediately add AE subScene
*/
class AE_AddMpEffect : public CCActionInstant
{
public:
	AE_AddMpEffect() : m_scale(1.0f), m_zOrder(0), m_tag(0) {}
	virtual ~AE_AddMpEffect(){}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);

	/** Allocates and initializes the action */
	static AE_AddMpEffect * create(const std::string& mpFile, CCPoint pos, float extraAnimationScale, float scale, int zOrder, int tag);
	bool init(const std::string& mpFile, CCPoint pos, float extraAnimationScale, float scale, int zOrder, int tag);
private:
	std::string m_mpFile;
	CCPoint m_pos;
	float m_extraAnimationScale;
	float m_scale;
	int m_zOrder;
	int m_tag;
};

/** 
@brief Immediately add child animation
*/
class AE_ChildAnimation : public CCActionInstant
{
public:
	AE_ChildAnimation() {}
	virtual ~AE_ChildAnimation(){}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);
private:
	std::list<std::string> m_fileNames;
	std::string m_prefix;
	int m_prefixNum;
	std::string m_plist;
	float m_delayPerUnit;
	int m_loops;
	float m_scale;
	CCPoint m_pos;
	int m_srcBlendFunc;
	int m_dstBlendFunc;
	int m_zOrder;
	int m_tag;
public:

	/** Allocates and initializes the action */
	static AE_ChildAnimation * create(const std::list<std::string>& fileNames, const std::string& prefix, int prefixNum, std::string plist, float delayPerUnit,
		int loops, float scale, CCPoint pos, int srcBlendFunc, int dstBlendFunc, int zOrder, int tag);

	bool init(const std::list<std::string>& fileNames, const std::string& prefix, int prefixNum, std::string plist, float delayPerUnit,
		int loops, float scale, CCPoint pos, int srcBlendFunc, int dstBlendFunc, int zOrder, int tag);
};

/** 
@brief Immediately add particle
*/
class AE_Add_Label : public CCActionInstant
{
public:
	AE_Add_Label() : m_fontSize(12){
		m_fontColor = ccc3(255,255,255);
	}
	virtual ~AE_Add_Label(){}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);

	void showMoreText();
private:
	CCPoint m_pos;
	std::string m_label;
	std::string m_fontDefFile;
	std::string m_font;
	float m_fontSize;
	ccColor3B m_fontColor;
	float m_duration;
	int m_srcBlendFactor;
	int m_dstBlendFactor;
	int m_tag;
public:

	/** Allocates and initializes the action */
	static AE_Add_Label * create(CCPoint pos, const std::string& label, const std::string& fontDefFile, const std::string& font, float fontSize, ccColor3B fontColor, float duration, int srcBlendFactor, int dstBlendFactor, int tag);
	bool init(CCPoint pos, const std::string& label, const std::string& fontDefFile, const std::string& font, float fontSize, ccColor3B fontColor, float duration, int srcBlendFactor, int dstBlendFactor, int tag);
};

/** 
@brief Immediately add particle
*/
class AE_Remove_Child : public CCActionInstant
{
public:
	AE_Remove_Child() {}
	virtual ~AE_Remove_Child(){}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);
private:
	int m_tag;
public:

	/** Allocates and initializes the action */
	static AE_Remove_Child * create(int tag);
	bool init(int tag);
};

/** @brief NewFlip, explore more params  TODO */
class AE_New_Flip3D : public CCGrid3DAction
{
public:
	/** initializes the action with duration */
	virtual bool initWithDuration(float duration);
	virtual bool initWithSize(const CCSize& gridSize, float duration);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void update(float time);

public:
	/** creates the action with duration */
	static AE_New_Flip3D* create(float duration, float delta, bool isFlipX);

private:
	float m_delta;
	bool m_isFilpX;
};

class AE_UiMoveFromDelta : public CCActionInterval {
public:
	static CCActionInterval* create(const char* spriteName, float d);
};

/** @brief Fades In, with all Child
 */
class AE_FadeIn_WithAllChild : public CCActionInterval
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    /** creates the action */
    static AE_FadeIn_WithAllChild* create(float d);
};

/** @brief Fades Out, with all Child
*/
class AE_FadeOut_WithAllChild : public CCActionInterval
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    static AE_FadeOut_WithAllChild* create(float d);
};

class AE_FaceToPos : public CCActionInterval
{
public:
    AE_FaceToPos() : m_faceToPos(0,0), m_initDegree(0)
    {}
    virtual ~AE_FaceToPos(void)
	{}

    bool init(const CCPoint& faceToPos, float initDegree, float duration) { 
		this->m_faceToPos = faceToPos; 
		this->m_initDegree = initDegree;
		this->initWithDuration(duration);
		return true; 
	}

    virtual void update(float dt);
	virtual CCObject* copyWithZone(CCZone *pZone);

	void adjustFaceTo();

public:
    static AE_FaceToPos* create(const CCPoint& faceToPos, float initDegree, float duration);
protected:
    CCPoint m_faceToPos;
	float m_initDegree;
};

class AE_ChangeShader : public CCActionInstant
{
public:
	AE_ChangeShader():m_Shader(0){}
	virtual ~AE_ChangeShader(){CC_SAFE_RELEASE(m_Shader);}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);

private:
	CCGLProgram *m_Shader;

public:

	/** Allocates and initializes the action */
	static AE_ChangeShader * create(CCGLProgram *shader);
	static AE_ChangeShader * create(const char *name);
	bool init(CCGLProgram *shader);
	bool init(const char *name);
};

struct ShaderParams1f
{
	float from, to;
};
typedef std::map<std::string, ShaderParams1f> ShaderParams1ffMap;

class AE_FadeShaderParams1f : public CCActionInterval
{
public:
	AE_FadeShaderParams1f() {}
	virtual ~AE_FadeShaderParams1f(){}
	//super methods
	virtual void update(float time);
	virtual CCObject* copyWithZone(CCZone *pZone);
	void startWithTarget(CCNode *pTarget);

private:
	std::string m_strName;
	ShaderParams1ffMap m_mapParams;

public:
	/** Allocates and initializes the action */
	static AE_FadeShaderParams1f * create(const char *name, const ShaderParams1ffMap& params, float duration);
	bool init(const char *name, const ShaderParams1ffMap& params, float duration);
};

NS_CC_END