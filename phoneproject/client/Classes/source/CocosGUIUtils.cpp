#include "CocosGUIUtils.h"
//#include "Logic/Utils.h"
//#include "InputLayer.h"
#include "Configs.h"
//#include "Effect.h"
#include "CocoGUILIB/System/CocosGUI.h"

extern ccFontDefinition getFontDefinition(const std::string& fontXmlPath);
ccFontDefinition FindFontByWidgetName(const char* pWidgetName);

static cc_timeval s_last_time_for_effect;
float CalcCostMS(char* str) {
	assert(str != NULL);
	cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	float deltaMS = CCTime::timersubCocos2d(&s_last_time_for_effect, &now);
	s_last_time_for_effect = now;
	if (strlen(str) > 0) {
		CCLog("[CostMS] %s ---- %f second", str, deltaMS / 1000.0);
	}
	return deltaMS;
}

static cc_timeval s_last_time_for_effect2[16];
float CalcCostMS2(int index,char* str) {
	assert(str != NULL && index >= 0 && index <= 15);
	cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	float deltaMS = CCTime::timersubCocos2d(&(s_last_time_for_effect2[index]), &now);
	s_last_time_for_effect2[index] = now;
	if (strlen(str) > 0) {
		CCLog("[CostMS] %s ---- %f second", str, deltaMS / 1000.0);
	}
	return deltaMS;
}

// <c=0x880000>赏金猎人初段<c=0x445588>（物理）
class ColorAndText {
public:
	ColorAndText() : fontSize(0), color(0), str(""), lineNumber(0), offset(0){}
	ColorAndText(int _fontSize, std::string _str, int _color, int _lineNumber, float _offset) : fontSize(_fontSize), color(_color), str(_str), lineNumber(_lineNumber), offset(_offset) {}

	int color;
	std::string str;
	int lineNumber;
	float offset;
	int fontSize;
};

// UTF-8 转成 UTF-16LE编码的octets
static const float GetLengthOfBlock (std::string str)  
{  
	//EF BB BF
	unsigned char *ch = (unsigned char*)str.c_str();
	float ret_size = 0;
	int unicode = 0;
	int str_len = str.length();
	const unsigned char *end = ch + str_len; // terminate '\0'

	for (;;) {
		if(*ch >= 0xfc)  
		{  
			assert(ch + 6 <= end);
			unicode = (ch[0] & 0x01) << 30;  
			unicode |= (ch[1] & 0x3f) << 24;  
			unicode |= (ch[2] & 0x3f) << 18;  
			unicode |= (ch[3] & 0x3f) << 12;  
			unicode |= (ch[4] & 0x3f) << 6;  
			unicode |= (ch[5] & 0x3f);  
			ch += 6; 
		}  
		else if(*ch >= 0xf8)   
		{  
			assert(ch + 5 <= end);
			unicode = (ch[0] & 0x03) << 24;  
			unicode |= (ch[1] & 0x3f) << 18;  
			unicode |= (ch[2] & 0x3f) << 12;  
			unicode |= (ch[3] & 0x3f) << 6;  
			unicode |= (ch[4] & 0x3f);  
			ch += 5;
		}  
		else if(*ch >= 0xf0)  
		{  
			assert(ch + 4 <= end);
			unicode = (ch[0] & 0x07) << 18;  
			unicode |= (ch[1] & 0x3f) << 12;  
			unicode |= (ch[2] & 0x3f) << 6;  
			unicode |= (ch[3] & 0x3f);  
			ch += 4;  
		}  
		else if(*ch >= 0xe0)  
		{  
			assert(ch + 3 <= end);
			unicode = (ch[0] & 0x0f) << 12;  
			unicode |= (ch[1] & 0x3f) << 6;  
			unicode |= (ch[2] & 0x3f);  
			ch += 3;  
		}  
		else if(*ch >= 0xc0)   
		{  
			assert(ch + 2 <= end);
			unicode = (ch[0] & 0x1f) << 6;  
			unicode |= (ch[1] & 0x3f);  
			ch += 2;  
		}  
		else if (*ch > 0x00)  
		{  
			assert(ch + 1 <= end);
			unicode = ch[0];  
			ch += 1;  
		}
		else // *ch == 0x00 ???
		{
			assert(ch == end);
			unicode = 0;
		}

		// LE
		if (unicode != 0) { // 终止符忽略
			ret_size += (unicode < 0xc0) ? 0.5 : 1;
		}

		if (ch >= end) {
			break;
		}
	}
	return ret_size;
}

static void ParseColorBlock(const int fontSize, const std::string& curBlock, const int color, int& lineNumber, float& offset, std::vector<ColorAndText>& ret) {
	size_t start_of_line = 0;
	size_t end_of_line = 0;
	while ((end_of_line = curBlock.find("\n", start_of_line)) != std::string::npos) {
		if (end_of_line - start_of_line > 0) {
			std::string curStr;
			if (curBlock[end_of_line - 1] == '\r') {
				curStr = curBlock.substr(start_of_line, end_of_line - start_of_line - 1);
			} else {
				curStr = curBlock.substr(start_of_line, end_of_line - start_of_line);
			}
			ret.push_back(ColorAndText(fontSize, curStr, color, lineNumber, offset));
			offset += GetLengthOfBlock(curStr);
		}
		++lineNumber;
		offset = 0;

		start_of_line = end_of_line + 1;
	}

	if (start_of_line < curBlock.size()) {
		std::string curStr = curBlock.substr(start_of_line, curBlock.size() - start_of_line);
		ret.push_back(ColorAndText(fontSize, curStr, color, lineNumber, offset));
		offset += GetLengthOfBlock(curStr);
	}
}

// @return  is Color And Text Format
static bool ParseColorAndText(const std::string& str, std::vector<ColorAndText>& ret, int& autoLine, std::string& fontDefPath, float& gap, CCPoint& anchor) {
	int lineNumber = 0;
	float offset = 0;
	bool isColorAndTextFormat = false;

	int color = 0xFFFFFF;
	size_t start_pos = 0;
	size_t color_tag_start_pos = 0;
	size_t color_tag_end_pos = 0;
	int fontSize = 34;	// default
	gap = 1.0f;
	anchor = ccp(1.0f, 0.0f);
	while(true) {
		if (str.substr(start_pos, 7) == std::string("<fsize=")) {
			size_t endPos = str.find(">", start_pos);
			if (endPos != std::string::npos) {
				std::string fontSizeStr = str.substr(start_pos + 7, endPos - start_pos - 7);
				sscanf(fontSizeStr.c_str(), "%d", &fontSize);
				start_pos = endPos + 1;
				isColorAndTextFormat = true;
			}
		} else if (str.substr(start_pos, 10) == std::string("<autoline=")) {
			size_t endPos = str.find(">", start_pos);
			if (endPos != std::string::npos) {
				std::string autoLineStr = str.substr(start_pos + 10, endPos - start_pos - 10);
				sscanf(autoLineStr.c_str(), "%d", &autoLine);
				start_pos = endPos + 1;
				isColorAndTextFormat = true;
			}
		} else if (str.substr(start_pos, 6) == std::string("<fdef=")) {
			size_t endPos = str.find(">", start_pos);
			if (endPos != std::string::npos) {
				fontDefPath = str.substr(start_pos + 6, endPos - start_pos - 6);
				start_pos = endPos + 1;
				isColorAndTextFormat = true;
			}
		} else if (str.substr(start_pos, 5) == std::string("<gap=")) {
			size_t endPos = str.find(">", start_pos);
			if (endPos != std::string::npos) {
				std::string strGap = str.substr(start_pos + 5, endPos - start_pos - 5);
				sscanf(strGap.c_str(), "%f", &gap);
				start_pos = endPos + 1;
				isColorAndTextFormat = true;
			}
		} else if (str.substr(start_pos, 8) == std::string("<anchor=")) {
			size_t endPos = str.find(">", start_pos);
			if (endPos != std::string::npos) {
				std::string strAnchor = str.substr(start_pos + 8, endPos - start_pos - 8);
				sscanf(strAnchor.c_str(), "%f,%f", &anchor.x, &anchor.y);
				start_pos = endPos + 1;
				isColorAndTextFormat = true;
			}
		} else {
			break;
		}
	}

	while ((color_tag_start_pos = str.find("<c=", start_pos)) != std::string::npos) {
		color_tag_end_pos = str.find(">", color_tag_start_pos);
		if (color_tag_end_pos == std::string::npos) { // error
			break;
		}

		isColorAndTextFormat = true;
		if (color_tag_start_pos - start_pos > 0) {
			ParseColorBlock(fontSize, str.substr(start_pos, color_tag_start_pos - start_pos), color, lineNumber, offset, ret);
		}

		// next color
		std::string strColor = str.substr(color_tag_start_pos + 3, color_tag_end_pos - color_tag_start_pos - 3);
		sscanf(strColor.c_str(), "%x", &color);

		start_pos = color_tag_end_pos + 1;
	}

	if (start_pos < str.size()) {
		ParseColorBlock(fontSize, str.substr(start_pos, str.size() - start_pos), color, lineNumber, offset, ret);
	}
	return isColorAndTextFormat;
}

static bool ParseColorAndText(const std::string& str, std::vector<ColorAndText>& ret, int& autoLine, std::string& fontDefPath) {
	float gap;
	CCPoint anchor;
	return ParseColorAndText(str, ret, autoLine, fontDefPath, gap, anchor);
}

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif


void SetMultiColorLabelText(UIWidget* pRoot, const char* szLabelName, const char* szText)
{
	UIWidget* pFather = CCUIHELPER->seekWidgetByName(pRoot, szLabelName);
	std::string fontName;
	if(pFather)
	{
		{
			UILabel* pLabel = dynamic_cast<UILabel*>(pFather);
			if (pLabel != NULL) {
#ifndef WIN32
				pLabel->getFontName(fontName);
#endif
				pLabel->setText("");
			}
			UITextArea* pArea = dynamic_cast<UITextArea*>(pFather);
			if (pArea != NULL) {
#ifndef WIN32
				//fontName = pLabel->getFontName();
#endif
				pArea->setText("");
			}
		}

		pFather->setVisible(true);
		pFather->setAnchorPoint(ccp(0, 1));
		std::vector<ColorAndText> ret;
		int autoLine = 0;	// default no autoLine
		std::string fontDefPath;
		float gap;
		CCPoint anchor;
		ParseColorAndText(std::string(szText), ret, autoLine, fontDefPath, gap, anchor);
		
		{
			UIContainerWidget* pToRmv = (UIContainerWidget*)pFather->getChildByTag(12345);
			if (pToRmv != NULL) {
				pToRmv->removeFromParentAndCleanup(true);
			}
		}

		UIContainerWidget* pSubContainer = UIContainerWidget::create();
		pSubContainer->setWidgetTag(12345);	// hardcode

		int curLineNumber = 0;
		float curLineOffset = 0;		// 像素级别
		float maxWidth = 0;
		int curAutoAddedLine = 0;
		float fontSize = 0;
		std::vector<UILabel*> subLabels;
		for (std::vector<ColorAndText>::iterator it = ret.begin(); it != ret.end(); ++it) {
			if (it->lineNumber != curLineNumber) {
				curLineNumber = it->lineNumber;
				curLineOffset = 0;
			}

			fontSize = it->fontSize;
			UILabel* pSubLabel = UILabel::create();
			subLabels.push_back(pSubLabel);
			pSubLabel->setPosition(ccp(curLineOffset, (float)it->fontSize/2 - (it->fontSize + gap) * (it->lineNumber + curAutoAddedLine + 1)));
			CCLOG("[Pos] = (%f,%f)\n", pSubLabel->getPosition().x, pSubLabel->getPosition().y);
			pSubLabel->setAnchorPoint(ccp(0, 0));
			pSubLabel->setVisible(true); 
			pSubLabel->setText(it->str.c_str());
			if (fontDefPath.size() != 0) {
				ccFontDefinition fontDef = getFontDefinition(fontDefPath);
				fontDef.m_fontSize = it->fontSize;		// 修正fontSize, xxx 如果fontSize跟def不一致，描边阴影是否需要缩放
				fontDef.m_fontFillColor = ccc3(it->color >> 16 & 0xff, it->color >> 8 & 0xff, it->color & 0xff);
				fontDef.m_stroke.m_strokeColor = fontDef.m_fontFillColor;
				pSubLabel->setTextDefinition(&fontDef);
#ifdef WIN32
				// windows 无fontDef实现，所以这里设置下
				pSubLabel->setColor(ccc3(it->color >> 16 & 0xff, it->color >> 8 & 0xff, it->color & 0xff));
				pSubLabel->setFontSize(it->fontSize);
#endif
			} else {
				pSubLabel->setColor(ccc3(it->color >> 16 & 0xff, it->color >> 8 & 0xff, it->color & 0xff));
				// todo fontName
				pSubLabel->setFontSize(it->fontSize);
			}
#ifdef WIN32
			pSubLabel->setFontName("simhei");
#endif
			pSubContainer->addChild(pSubLabel);

			float curLabelWidth = pSubLabel->getContentSize().width * pSubLabel->getScale();
			curLineOffset += curLabelWidth;
			if (autoLine > 0 && curLineOffset > autoLine) { // 拆分autoLine
				curLineOffset -= curLabelWidth;
				size_t last_i = 0;
				size_t i = 0;
				while (i < it->str.size()) {
					unsigned char ch = it->str[i];
					last_i = i;
					if(ch >= 0xfc)  
					{   
						i += 6; 
					}  
					else if(ch >= 0xf8)   
					{   
						i += 5;
					}  
					else if(ch >= 0xf0)  
					{  
						i += 4;  
					}  
					else if(ch >= 0xe0)  
					{  
						i += 3;  
					}  
					else if(ch >= 0xc0)   
					{  
						i += 2;  
					}  
					else if (ch > 0x00)  
					{ 
						i += 1;  
					}
					else {
						break;
					}

					pSubLabel->setText(it->str.substr(0, i).c_str());
					curLabelWidth = pSubLabel->getContentSize().width * pSubLabel->getScale();
					if (curLineOffset + curLabelWidth > autoLine) {
						maxWidth = max(curLineOffset + curLabelWidth, maxWidth);
						break;
					}
				}

				if (last_i != 0) i = last_i;

				curAutoAddedLine += 1;
				curLineOffset = 0;
				pSubLabel->setText(it->str.substr(0, i).c_str());

				if (i != it->str.size()) {
					ColorAndText cat(it->fontSize, it->str.substr(i, it->str.size() - i), it->color, it->lineNumber, it->offset);
					it = ret.insert(it + 1, cat);
					-- it;
				}
			}

			maxWidth = max(curLineOffset, maxWidth);

			CCLOG("[fontSize=%d][line=%d][offset=%f][%0x] %s\n", it->fontSize, it->lineNumber, it->offset, it->color, it->str.c_str());
		}
		pFather->addChild(pSubContainer);
		pFather->getValidNode()->setContentSize(CCSizeMake(maxWidth, (curAutoAddedLine + curLineNumber + 1) * (fontSize + gap)));

		for (std::vector<UILabel*>::iterator itSub = subLabels.begin(); itSub != subLabels.end(); ++itSub) {
			CCPoint pos = (*itSub)->getPosition();
			pos.x -= pFather->getValidNode()->getContentSize().width * anchor.x;
			pos.y += (pFather->getValidNode()->getContentSize().height - fontSize) * (1.0f - anchor.y);
			(*itSub)->setPosition(pos);
		}
	}
	else
	{
		CCLOGERROR("CCLOGERROR:SetMultiColorLabelText(pRoot = %s.json, szName = %s)", pRoot->getName(), szLabelName);
	}
}

CCSprite* CreateStrideLabelContainer(const char* szText, int fontSize, const ccColor3B& color, const ccColor3B& strideColor, const CCPoint& anchor) {
	CCSprite* ret = CCSprite::create();

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x != 0 && y != 0) {
				//cs::CCLabelTTF* pSubLabel = cs::CCLabelTTF::create();
//				UILabel* pSubLabel = UILabel::create();
				CCLabelTTF* pSubLabel = CCLabelTTF::create();
				//pSubLabel->setFontName(g_szDefaultFontName);
				pSubLabel->setFontSize(fontSize);
				pSubLabel->setString(szText);
				pSubLabel->setColor(strideColor);
				pSubLabel->setPosition(ccp(x, y));
				pSubLabel->setAnchorPoint(anchor);
				ret->addChild(pSubLabel);
			}
		}
	}

//	cs::CCLabelTTF* pSubLabel = cs::CCLabelTTF::create();
	CCLabelTTF* pSubLabel = CCLabelTTF::create();
	//pSubLabel->setFontName(g_szDefaultFontName);
	pSubLabel->setFontSize(fontSize);
	pSubLabel->setString(szText);
	pSubLabel->setColor(color);
	pSubLabel->setPosition(ccp(0, 0));
	pSubLabel->setAnchorPoint(anchor);
	ret->addChild(pSubLabel);

	return ret;
}

void SetLabelColor(UIWidget* pRoot, const char* szLabelName, const ccColor3B& color)
{
	UIWidget* pWidget = CCUIHELPER->seekWidgetByName(pRoot, szLabelName);
	if(pWidget)
	{
		int nWidgetName = pWidget->getWidgetName();
		if(nWidgetName == WIDGET_LABEL)
		{
			UILabel* pLabel = (UILabel*)pWidget;
			pLabel->setColor(color);
		}
		else if(nWidgetName == WIDGET_LABELATLAS)
		{
			UILabelAtlas* pLabelAtlas = (UILabelAtlas*)pWidget;
			pLabelAtlas->setColor(color);
		}
		else if(nWidgetName == WIDGET_LABELBMFONT)
		{
			UILabelBMFont* pLabelBMFont = (UILabelBMFont*)pWidget;
			pLabelBMFont->setColor(color);
		}
		else if(nWidgetName == WIDGET_TEXTAREA)
		{
			UITextArea* pTextArea = (UITextArea*)pWidget;
			pTextArea->setColor(color);
		}
	}
	else
	{
		CCLOGERROR("CCLOGERROR:SetLabelColor(pRoot = %s.json, szName = %s)", pRoot->getName(), szLabelName);
	}
// 	UILabel* pLabel = (UILabel*)(CCUIHELPER->seekWidgetByName(pRoot, szLabelName));
// 	if(pLabel)
// 	{
// 		pLabel->setColor(color);
// 	}
}
int GetLabelValue(UIWidget* pRoot, const char* szLabelName)
{
	int nRet = 0;
	char szText[64];
	UIWidget* pWidget = CCUIHELPER->seekWidgetByName(pRoot, szLabelName);
	if(pWidget)
	{
		int nWidgetName = pWidget->getWidgetName();
		if(nWidgetName == WIDGET_LABEL)
		{
			UILabel* pLabel = (UILabel*)pWidget;
			strcpy(szText, pLabel->getStringValue());
		}
		else if(nWidgetName == WIDGET_LABELATLAS)
		{
			UILabelAtlas* pLabelAtlas = (UILabelAtlas*)pWidget;
			strcpy(szText, pLabelAtlas->getStringValue());
		}
		else if(nWidgetName == WIDGET_LABELBMFONT)
		{
			UILabelBMFont* pLabelBMFont = (UILabelBMFont*)pWidget;
			strcpy(szText, pLabelBMFont->getStringValue());
		}
		else if(nWidgetName == WIDGET_TEXTAREA)
		{
			UITextArea* pTextArea = (UITextArea*)pWidget;
			strcpy(szText, pTextArea->getStringValue());
		}
	}
	else
	{
		CCLOGERROR("CCLOGERROR:GetLabelValue(pRoot = %s.json, szName = %s)", pRoot->getName(), szLabelName);
	}

	nRet = atoi(szText);
	return nRet;
}
void SetLabelText(UIWidget* pRoot, const char* szLabelName, const char* szText)
{
	if(strcmp(szText, "") == 0)
	{
		UIContainerWidget* pToRmv = (UIContainerWidget*)pRoot->getChildByTag(12345);
		if (pToRmv != NULL) {
			pToRmv->removeFromParentAndCleanup(true);
		}
	}

	std::vector<ColorAndText> ret;
	int autoline = 0;
	std::string fontDefPath;
	if (ParseColorAndText(std::string(szText), ret, autoline, fontDefPath)) { // a little not effective
		SetMultiColorLabelText(pRoot, szLabelName, szText);
	} else {
		UIWidget* pWidget = CCUIHELPER->seekWidgetByName(pRoot, szLabelName);
		if(pWidget)
		{
			int nWidgetName = pWidget->getWidgetName();
			if(nWidgetName == WIDGET_LABEL)
			{
				UILabel* pLabel = (UILabel*)pWidget;
				pLabel->setText(szText);
			}
			else if(nWidgetName == WIDGET_LABELATLAS)
			{
				UILabelAtlas* pLabelAtlas = (UILabelAtlas*)pWidget;
				pLabelAtlas->setStringValue(szText);
			}
			else if(nWidgetName == WIDGET_LABELBMFONT)
			{
				UILabelBMFont* pLabelBMFont = (UILabelBMFont*)pWidget;
				pLabelBMFont->setText(szText);
			}
			else if(nWidgetName == WIDGET_TEXTAREA)
			{
				UITextArea* pTextArea = (UITextArea*)pWidget;
				pTextArea->setText(szText);
			}
		}
		else
		{
			CCLOGERROR("CCLOGERROR:SetLabelText(pRoot = %s.json, szName = %s)", pRoot->getName(), szLabelName);
		}
	}
}

void SetTextAreaText(UIWidget* pRoot, const char* szName, const char* szText)
{
	std::vector<ColorAndText> ret;
	int autoline = 0;
	std::string fontDefPath;
	if (ParseColorAndText(std::string(szText), ret, autoline, fontDefPath)) { // a little not effective
		SetMultiColorLabelText(pRoot, szName, szText);
	} else {
		UITextArea* pTextArea = dynamic_cast<UITextArea*>((CCUIHELPER->seekWidgetByName(pRoot, szName)));
		if(pTextArea)
		{
			pTextArea->setText(szText);
		}
		else
		{
			CCLOGERROR("CCLOGERROR:SetTextAreaText(pRoot = %s.json, szName = %s)", pRoot->getName(), szName);
		}
	}
}

void SetWidgetAnchorPoint(UIWidget* pRoot, const char* szName, CCPoint vAnchorPoint)
{
	UIWidget* pWidget = dynamic_cast<UIWidget*>(CCUIHELPER->seekWidgetByName(pRoot, szName));
	if(pWidget)
		pWidget->setAnchorPoint(vAnchorPoint);
	else
	{
		CCLOGERROR("CCLOGERROR:SetWidgetAnchorPoint(pRoot = %s.json, szName = %s)", pRoot->getName(), szName);
	}
}

void SetLabelTextWithInt(UIWidget* pRoot, const char* szLabelName, int nNumber, bool bAnim)
{
	char szTemp[12];
	sprintf(szTemp, "%d", nNumber);
	if(!bAnim)
		SetLabelText(pRoot, szLabelName, szTemp);
	else
	{
		// get current value
		int nOldValue = GetLabelValue(pRoot, szLabelName);
		AddDynamicDigitLabel(pRoot, szLabelName, 0.5f, nOldValue, nNumber);
	}
}

void SetLabelAtlasText(UIWidget* pRoot, const char* szLabelName, const char* szText)
{
	UILabelAtlas* pLabel = dynamic_cast<UILabelAtlas*>(CCUIHELPER->seekWidgetByName(pRoot, szLabelName));
	if(pLabel)
		pLabel->setStringValue(szText);
	else
	{
		CCLOGERROR("CCLOGERROR:SetLabelAtlasText(pRoot = %s.json, szName = %s)", pRoot->getName(), szLabelName);
	}
}

void SetLabelAtlasTextWithInt(UIWidget* pRoot, const char* szLabelName, int nNumber)
{
	char szTemp[12];
	sprintf(szTemp, "%d", nNumber);
	SetLabelAtlasText(pRoot, szLabelName, szTemp);
}

void SetLabelTextWithIntSign(UIWidget* pRoot, const char* szLabelName, int nNumber)
{
	ccColor3B color;
	char szTemp[12];
	if(nNumber > 0)
	{
		sprintf(szTemp, "+%d", nNumber);
		color = ccGREEN;
	}
	else if(nNumber < 0)
	{
		sprintf(szTemp, "%d", nNumber);
		color = ccRED;
	}
	else if(nNumber == 0)
	{
		sprintf(szTemp, "0");
		color = ccWHITE;
	}

	SetLabelText(pRoot, szLabelName, szTemp);
	SetLabelColor(pRoot, szLabelName, color);
}

void SetProgressBarPercent(UIWidget* pRoot, const char* szPBName, int nPercent)
{
	UILoadingBar* bar = dynamic_cast<UILoadingBar*>(CCUIHELPER->seekWidgetByName(pRoot, szPBName));
	if(bar)
		bar->setPercent(nPercent);
	else
	{
		CCLOGERROR("CCLOGERROR:SetProgressBarPercent(pRoot = %s.json, szName = %s)", pRoot->getName(), szPBName);
	}
}

void HideWidget(UIWidget* pRoot, const char* szName)
{
	UIWidget* pWidget = CCUIHELPER->seekWidgetByName(pRoot, szName);
	if(pWidget)
		pWidget->setVisible(false);
	else
	{
		CCLOGERROR("CCLOGERROR:HideWidget(pRoot = %s.json, szName = %s)", pRoot->getName(), szName);
	}
}

void ShowWidget(UIWidget* pRoot, const char* szName)
{
	UIWidget* pWidget = CCUIHELPER->seekWidgetByName(pRoot, szName);
	if(pWidget)
		pWidget->setVisible(true);
	else
	{
		CCLOGERROR("CCLOGERROR:ShowWidget(pRoot = %s.json, szName = %s)", pRoot->getName(), szName);
	}
}

void SetTabHighlight(UIWidget* pRoot, const char* szTabBtn, const char* szHighlightPic)
{
	UIImageView* pPicTab = dynamic_cast<UIImageView*>(CCUIHELPER->seekWidgetByName(pRoot, szHighlightPic));
	if(pPicTab)
	{
		UIButton* pBtn = dynamic_cast<UIButton*>(CCUIHELPER->seekWidgetByName(pRoot, szTabBtn));
		if(pBtn)
			pPicTab->setPosition(pBtn->getPosition());
		else
		{
			CCLOGERROR("CCLOGERROR:SetTabHighlight(pRoot = %s.json, szName = %s)", pRoot->getName(), szTabBtn);
		}
	}
	else
	{
		CCLOGERROR("CCLOGERROR:SetTabHighlight(pRoot = %s.json, szName = %s)", pRoot->getName(), szHighlightPic);
	}
}

void SetWidgetTag(UIWidget* pRoot, const char* szName, int tag)
{
	UIWidget* pWidget = CCUIHELPER->seekWidgetByName(pRoot, szName);
	if(pWidget)
		pWidget->setWidgetTag(tag);
	else
	{
		CCLOGERROR("CCLOGERROR:SetWidgetTag(pRoot = %s.json, szName = %s)", pRoot->getName(), szName);
	}
}

void EnableWidget(UIWidget* pRoot, const char* szName)
{
	UIWidget* pWidget = CCUIHELPER->seekWidgetByName(pRoot, szName);
	if(pWidget)
		pWidget->active();
	else
	{
		CCLOGERROR("CCLOGERROR:EnableWidget(pRoot = %s.json, szName = %s)", pRoot->getName(), szName);
	}
}

void DisableWidget(UIWidget* pRoot, const char* szName)
{
	UIWidget* pWidget = CCUIHELPER->seekWidgetByName(pRoot, szName);
	if(pWidget)
		pWidget->disable();
	else
	{
		CCLOGERROR("CCLOGERROR:DisableWidget(pRoot = %s.json, szName = %s)", pRoot->getName(), szName);
	}
}

CCPoint GetWidgetPosition(UIWidget* pRoot, const char* szName)
{
	UIWidget* pWidget = CCUIHELPER->seekWidgetByName(pRoot, szName);
	if(pWidget)
		return pWidget->getPosition();
	else
	{
		CCLOGERROR("CCLOGERROR:GetWidgetPosition(pRoot = %s.json, szName = %s)", pRoot->getName(), szName);
	}

	return CCPointZero;
}

void AddEffectToWidget(UIWidget* pRoot, const char* szWidgetName, const char* szEffectName)
{
	/*UINodeContainer* pContainer = UINodeContainer::create();

	CCNode* pNode  = CCNode::create();
	MPEffect* pEffect = new MPEffect;
	if(!pEffect->LoadFromFile(szEffectName))
	{
		CCLOGERROR("CCLOGERROR:AddEffectToWidget(pRoot = %s.json, szEffectName = %s)", pRoot->getName(), szEffectName);
		return;
	}

	PlayParticleEffect(pNode,pEffect, 1);

	pContainer->addCCNode(pNode);
	pContainer->setWidgetZOrder(1);

	UIImageView* pImage = dynamic_cast<UIImageView*>(CCUIHELPER->seekWidgetByName(pRoot, szWidgetName));
	if(pImage)
	{
		pContainer->setPosition(ccp(pImage->getContainerNode()->getContentSize().width/2, pImage->getContainerNode()->getContentSize().height/2));
		pImage->addChild(pContainer);
	}
	else
	{
		CCLOGERROR("CCLOGERROR:AddEffectToWidget(pRoot = %s.json, szName = %s)", pRoot->getName(), szWidgetName);
	}*/
}

void AddDynamicDigitLabel(UIWidget* pRoot, const char* szLabelName, float fDuration, int nBeginValue, int nEndValue)
{
	/*if(nBeginValue == nEndValue)
		return;

	DynamicLabel dynamicLabel;
	dynamicLabel.pRoot = pRoot;
	strcpy(dynamicLabel.szLabelName, szLabelName);
	int nDeltaValue = (nEndValue - nBeginValue)/(fDuration * 60.0f);
	if(nDeltaValue == 0)
		nDeltaValue =  1;
	
	dynamicLabel.nDeltaValue = nDeltaValue;
	dynamicLabel.nBeginValue = nBeginValue;
	dynamicLabel.nEndValue = nEndValue;

	dynamicLabel.nCurrValue = nBeginValue;

	g_pPlayerData->m_vecDynamicLabel.push_back(dynamicLabel);*/
}

void RunProgressBarEffect(CCProgressTimer* progressTimer, float fDestPercent)
{
	float fOldPercent = progressTimer->getPercentage();

	float fTotalTime = 0.5f;
	float fTotalDistance = 100.0f;
	if((fDestPercent > fOldPercent && fabs(fDestPercent-fOldPercent) > 1e-6) || 
		(fDestPercent <= fOldPercent && fabs(fDestPercent-fOldPercent) <= 1e-6))
	{
		fTotalDistance = fDestPercent - fOldPercent;
		float fTime1 = fTotalTime* (fTotalDistance/100.0f);
		CCProgressTo *pProgressTo = CCProgressTo::create(fTime1, fDestPercent);
		progressTimer->runAction( pProgressTo);
	}
	else
	{
		fTotalDistance = 100.0f- fOldPercent + fDestPercent;
		fTotalTime = fTotalTime*(fTotalDistance/100.0f);
		float fTime1 = fTotalTime* ((100.0f - fOldPercent)/fTotalDistance);
		float fTime2 = fTotalTime* (fDestPercent/fTotalDistance);
		CCProgressTo *pProgressTo1 = CCProgressTo::create(fTime1, 100);
		CCProgressTo *pProgressTo2 = CCProgressTo::create(fTime2, fDestPercent);
		progressTimer->runAction( CCSequence::create(pProgressTo1, pProgressTo2, NULL));
	}
}

void RecursiveSetWidgetFont(UIWidget* pWidget) {
	if (pWidget == NULL) return;

	cocos2d::CCObject* curObject = NULL;
	CCARRAY_FOREACH(pWidget->getChildren(), curObject) {
		UIWidget* childWidget = dynamic_cast<UIWidget*>(curObject);
		if (childWidget == NULL) continue;

		if (childWidget->getWidgetName() != WIDGET_LABEL && childWidget->getWidgetName() != WIDGET_TEXTFIELD && childWidget->getWidgetName() != WIDGET_TEXTAREA && childWidget->getWidgetName() != WIDGET_TEXTBUTTON) {
			if (childWidget->getChildren()->count() > 0) {
				RecursiveSetWidgetFont(childWidget);
			}
			continue;
		}

		ccFontDefinition fontDef = FindFontByWidgetName(childWidget->getName());
		if (childWidget->getWidgetName() == WIDGET_LABEL) {
			UILabel* tf = dynamic_cast<UILabel*>(childWidget);
			assert(tf);
			CCLabelTTF* cctf = dynamic_cast<CCLabelTTF*>(tf->getValidNode());
			assert(cctf);
			fontDef.m_fontSize = cctf->getFontSize();
			fontDef.m_fontFillColor = cctf->getColor();
			fontDef.m_stroke.m_strokeColor = cctf->getColor();
			cctf->setTextDefinition(&fontDef);
#ifdef WIN32
			long len = 2;
			cctf->setFontName("simhei");
			cctf->setFontSize(fontDef.m_fontSize);
			cctf->setColor(fontDef.m_fontFillColor);
#endif
		} else if (childWidget->getWidgetName() == WIDGET_TEXTFIELD) {
			UITextField* tf = dynamic_cast<UITextField*>(childWidget);
			assert(tf);
			CCTextFieldTTF* cctf = dynamic_cast<CCTextFieldTTF*>(tf->getValidNode());
			assert(cctf);
			fontDef.m_fontSize = cctf->getFontSize();
			fontDef.m_fontFillColor = cctf->getColor();
			fontDef.m_stroke.m_strokeColor = cctf->getColor();
			cctf->setTextDefinition(&fontDef);
#ifdef WIN32
			long len = 2;
			cctf->setFontName("simhei");
			cctf->setFontSize(fontDef.m_fontSize);
			cctf->setColor(fontDef.m_fontFillColor);
#endif
		} else if (childWidget->getWidgetName() == WIDGET_TEXTAREA) {
			UITextArea* tf = dynamic_cast<UITextArea*>(childWidget);
			assert(tf);
			CCLabelTTF* cctf = dynamic_cast<CCLabelTTF*>(tf->getValidNode());
			assert(cctf);
			fontDef.m_fontSize = cctf->getFontSize();
			fontDef.m_fontFillColor = cctf->getColor();
			fontDef.m_stroke.m_strokeColor = cctf->getColor();
			fontDef.m_dimensions = cctf->getDimensions();  // fix textarea cannot change line bug.
			fontDef.m_alignment = cctf->getHorizontalAlignment();
			fontDef.m_vertAlignment = cctf->getVerticalAlignment();
			cctf->setTextDefinition(&fontDef);
#ifdef WIN32
			long len = 2;
			cctf->setFontName("simhei");
			cctf->setFontSize(fontDef.m_fontSize);
			cctf->setColor(fontDef.m_fontFillColor);
#endif
		} else if (childWidget->getWidgetName() == WIDGET_TEXTBUTTON) {
			UITextButton* tf = dynamic_cast<UITextButton*>(childWidget);
			assert(tf);
			CCNode* node = dynamic_cast<CCNode*>(tf->getContainerNode());
			assert(node);
			cocos2d::CCObject* subObject = NULL;
			CCARRAY_FOREACH(node->getChildren(), subObject) {
				CCLabelTTF* label = dynamic_cast<CCLabelTTF*>(subObject);
				if (label != NULL) {
					fontDef.m_fontSize = label->getFontSize();
					fontDef.m_fontFillColor = label->getColor();
					fontDef.m_stroke.m_strokeColor = label->getColor();
					label->setTextDefinition(&fontDef);
#ifdef WIN32
					long len = 2;
					label->setFontName("simhei");
					label->setFontSize(fontDef.m_fontSize);
					label->setColor(fontDef.m_fontFillColor);
#endif
					break;
				}
			}
		}
	}
}

UIWidget* CreateWidgetFromJsonFile(const char* pFileName)
{
	char szBuff[128];
	CalcCostMS("");
	UIWidget* ret = CCUIHELPER->createWidgetFromJsonFile(pFileName);
	sprintf(szBuff, "createWidgetFromJsonFile: %s", pFileName);
	CalcCostMS(szBuff);
	RecursiveSetWidgetFont(ret);
	sprintf(szBuff, "RecursiveSetWidgetFont: %s", pFileName);
	CalcCostMS(szBuff);
	return ret;
}

class CharDict {
	std::map<char, CharDict> dict;
	std::string property;

public:
	void add(std::string name, std::string property) {
		CharDict* cur = this;
		for (std::string::iterator it = name.begin(); it != name.end(); ++it) {
			cur = &cur->dict[*it];
		}

		cur->property = property;
	}

	std::string findMatch(std::string name) {
		CharDict* cur = this;
		for (std::string::iterator it = name.begin(); it != name.end(); ++it) {
			if (cur->dict.find(*it) != cur->dict.end()) {
				cur = &cur->dict[*it];

				if (cur->property.size() != 0) {
					return cur->property;
				}
			} else {
				break;
			}
		}
		return std::string();
	}
};

static CharDict s_ui2Font;
static ccFontDefinition s_defaultFontDef;
void SetWidgetName2Font(const char* pFileName)
{
	unsigned long size;
	unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(pFileName, "rb", &size);
	assert(pData != NULL);
	tinyxml2::XMLDocument doc;
	char* szBuff = new char[size + 1];
	szBuff[size] = 0;
	memcpy(szBuff, pData, size);
	delete[] pData;

	doc.ParseDeep(szBuff, 0 );
	tinyxml2::XMLElement* eRoot = doc.RootElement();
	std::string defaultFontFile = eRoot->Attribute("default");
	defaultFontFile.insert(0, "ui/");
	s_defaultFontDef = getFontDefinition(defaultFontFile);
	for (tinyxml2::XMLElement* eUiFont = doc.RootElement()->FirstChildElement("ui"); eUiFont != NULL; eUiFont = eUiFont->NextSiblingElement("ui")) {
		s_ui2Font.add(eUiFont->Attribute("name"), eUiFont->Attribute("font"));
	}

	delete[] szBuff;
}

ccFontDefinition FindFontByWidgetName(const char* pWidgetName)
{
	std::string fontFileName = s_ui2Font.findMatch(pWidgetName);
	if (fontFileName.size() == 0) {
		return s_defaultFontDef;
	}

	fontFileName.insert(0, "ui/");
	return getFontDefinition(fontFileName);
}

// void RestoreUISystemTouch(cs::CCNode* pUiSystemContainer)
// {
// 	cocos2d::CCObject* curObject = NULL;
// 	CCARRAY_FOREACH(pUiSystemContainer->getChildren(), curObject) {
// 		cs::InputLayer* inputLayer = dynamic_cast<cs::InputLayer*>(curObject);
// 		if (inputLayer == NULL) continue;
// 
// 		cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(inputLayer);
// 		cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(inputLayer, 1, false);
// 	}
// }
// void CloseUISystemTouch(cs::CCNode* pUiSystemContainer)
// {
// 	cocos2d::CCObject* curObject = NULL;
// 	CCARRAY_FOREACH(pUiSystemContainer->getChildren(), curObject) {
// 		cs::InputLayer* inputLayer = dynamic_cast<cs::InputLayer*>(curObject);
// 		if (inputLayer == NULL) continue;
// 
// 		cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(inputLayer);
// 	}
// }
