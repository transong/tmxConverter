#pragma once

#include "cocos2d.h"
#include <libxml/tree.h>

using namespace cocos2d;
using namespace std;

class Utility
{
public:
   static void iterateFolder(const char* path, CCObject* target, SEL_CallFuncO selector);

   //xml methods
   static xmlNodePtr addKeyAndDict(xmlNodePtr parent, const char* keyContent = "");
   static xmlNodePtr addKeyAndString(xmlNodePtr parent, const char* keyContent, const char* strContent);
   static xmlNodePtr addKeyAndBool(xmlNodePtr parent, const char* keyContent, bool bValue);
   static xmlNodePtr addKeyAndFloat(xmlNodePtr parent, const char* keyContent, float fValue);
   static xmlNodePtr addKeyAndPoint(xmlNodePtr parent, const char* keyContent, CCPoint point);
   static xmlNodePtr addKeyAndRect(xmlNodePtr parent, const char* keyContent, CCRect rect);

   static xmlNodePtr addKeyAndArray(xmlNodePtr parent, const char* keyContent = "");
   static xmlNodePtr addDictToArray(xmlNodePtr parent);
   static xmlNodePtr addStringToArray(xmlNodePtr parent, const char* strContent);

   //
   static CCSprite* spriteWithColor(ccColor4F bgColor, CCSize size);

};