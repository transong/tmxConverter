#include "Utility.h"


xmlNodePtr Utility::addKeyAndDict(xmlNodePtr parent, const char* keyContent)
{
	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
	return xmlNewChild(parent, NULL, BAD_CAST "dict", NULL);
}

xmlNodePtr Utility::addKeyAndString(xmlNodePtr parent, const char* keyContent, const char* strContent)
{
	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
	return xmlNewTextChild(parent, NULL, BAD_CAST "string", BAD_CAST strContent);
}

xmlNodePtr Utility::addKeyAndBool(xmlNodePtr parent, const char* keyContent, bool bValue)
{
	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
	return xmlNewChild(parent, NULL, BAD_CAST (bValue ? "true" : "false"), NULL);
}

xmlNodePtr Utility::addKeyAndFloat(xmlNodePtr parent, const char* keyContent, float fValue)
{
	CCString* str = CCString::createWithFormat("%.2f", fValue);

	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
	return xmlNewTextChild(parent, NULL, BAD_CAST "real", BAD_CAST str->getCString());
}

xmlNodePtr Utility::addKeyAndPoint(xmlNodePtr parent, const char* keyContent, CCPoint point)
{
	CCString* str = CCString::createWithFormat("{%.2f,%.2f}", point.x, point.y);

	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
	return xmlNewTextChild(parent, NULL, BAD_CAST "string", BAD_CAST str->getCString());
}

xmlNodePtr Utility::addKeyAndRect(xmlNodePtr parent, const char* keyContent, CCRect rect)
{
	CCString* str = CCString::createWithFormat("{{%.2f,%.2f},{%.2f,%.2f}}", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
	return xmlNewTextChild(parent, NULL, BAD_CAST "string", BAD_CAST str->getCString());
}

xmlNodePtr Utility::addKeyAndArray(xmlNodePtr parent, const char* keyContent)
{
	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
	return xmlNewChild(parent, NULL, BAD_CAST "array", NULL);
}

xmlNodePtr Utility::addDictToArray(xmlNodePtr parent)
{
   return xmlNewChild(parent, NULL, BAD_CAST "dict", NULL);
}

xmlNodePtr Utility::addStringToArray(xmlNodePtr parent, const char* strContent)
{
   return xmlNewTextChild(parent, NULL, BAD_CAST "string", BAD_CAST strContent);
}

CCSprite* Utility::spriteWithColor(ccColor4F bgColor, CCSize size)
{
	CCRenderTexture* rt = CCRenderTexture::renderTextureWithWidthAndHeight(size.width, size.height);

	rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

	rt->end();

	return CCSprite::spriteWithTexture(rt->getSprite()->getTexture());
}