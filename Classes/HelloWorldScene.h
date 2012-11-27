#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <libxml/parser.h>

using namespace cocos2d;
using namespace std;

class HelloWorld : public cocos2d::CCLayer
{
public:
    virtual bool init();  

    static cocos2d::CCScene* scene();
    CREATE_FUNC(HelloWorld);

	bool m_isLowToHigh;//高清转低清 or 低清转高清
	
	CCLabelTTF *m_lblLowToHigh;

	void traverseNode(xmlNodePtr cur);

	void parseSingleNode(xmlNodePtr cur);
    
	void changeCB(CCObject *sender);
	void convertCB(CCObject *sender);

	void folderCB(CCObject* sender);
};

#endif  // __HELLOWORLD_SCENE_H__