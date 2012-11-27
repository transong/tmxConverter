#include "HelloWorldScene.h"
#include "Utility.h"
using namespace cocos2d;

#define factor_macro(a) (m_isLowToHigh ? a*2 : a/2)

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		m_isLowToHigh = true;

		m_lblLowToHigh = CCLabelTTF::create("To High", "Arial", 20);
		CCMenuItemLabel *lbl_item_lowToHigh = CCMenuItemLabel::create(m_lblLowToHigh, this, menu_selector(HelloWorld::changeCB));
		
		CCMenuItemLabel *lbl_item_convert = CCMenuItemLabel::create(CCLabelTTF::create("Convert", "Arial", 30), this, menu_selector(HelloWorld::convertCB));

		CCMenu *menuIndicator = CCMenu::create(lbl_item_lowToHigh, lbl_item_convert, NULL);
		menuIndicator->alignItemsHorizontallyWithPadding(40);
		addChild(menuIndicator);

		
		
        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::traverseNode(xmlNodePtr cur) {
	if (cur != NULL) {

		parseSingleNode(cur);

		cur = cur->xmlChildrenNode;

		while (cur != NULL){

			traverseNode(cur);
			cur = cur->next;
		}

		return;
	}else{
		return;
	}
}

void HelloWorld::parseSingleNode( xmlNodePtr curNode )
{
	if (!xmlStrcmp(curNode->name, (const xmlChar*)"map") || !xmlStrcmp(curNode->name, (const xmlChar*)"tileset"))  
	{  
		xmlChar* prop_value =  xmlGetProp(curNode, (const xmlChar*)"tilewidth");
		int tileWidth = atoi((const char*)prop_value);
		CCString* str = CCString::createWithFormat("%d", factor_macro(tileWidth));
		xmlSetProp(curNode, BAD_CAST "tilewidth", BAD_CAST str->getCString());

		prop_value =  xmlGetProp(curNode, (const xmlChar*)"tileheight");
		int tileHeight = atoi((const char*)prop_value);
		str = CCString::createWithFormat("%d", factor_macro(tileHeight));
		xmlSetProp(curNode, BAD_CAST "tileheight", BAD_CAST str->getCString());

	}
	else if (!xmlStrcmp(curNode->name, (const xmlChar*)"image"))
	{
		xmlChar* prop_value =  xmlGetProp(curNode, (const xmlChar*)"width");
		int width = atoi((const char*)prop_value);
		CCString* str = CCString::createWithFormat("%d", factor_macro(width));
		xmlSetProp(curNode, BAD_CAST "width", BAD_CAST str->getCString());

		prop_value =  xmlGetProp(curNode, (const xmlChar*)"height");
		int height = atoi((const char*)prop_value);
		str = CCString::createWithFormat("%d", factor_macro(height));
		xmlSetProp(curNode, BAD_CAST "height", BAD_CAST str->getCString());
	}
	else if (!xmlStrcmp(curNode->name, (const xmlChar*)"object"))
	{
		xmlChar* prop_value =  xmlGetProp(curNode, (const xmlChar*)"x");
		int x = atoi((const char*)prop_value);
		CCString* str = CCString::createWithFormat("%d", factor_macro(x));
		xmlSetProp(curNode, BAD_CAST "x", BAD_CAST str->getCString());

		prop_value =  xmlGetProp(curNode, (const xmlChar*)"y");
		int y = atoi((const char*)prop_value);
		str = CCString::createWithFormat("%d", factor_macro(y));
		xmlSetProp(curNode, BAD_CAST "y", BAD_CAST str->getCString());
	}
	else if (!xmlStrcmp(curNode->name, (const xmlChar*)"polygon") || !xmlStrcmp(curNode->name, (const xmlChar*)"polyline"))
	{
       xmlChar* prop_value =  xmlGetProp(curNode, (const xmlChar*)"points");

       string str_points = (const char*)prop_value;
       string str_result_points;
       int nend = 0;
	   int nbegin = 0;
	   bool isDot = true;
	   while(nend != -1)
	   {
		   if(isDot)
		      nend = str_points.find(",", nbegin);
		   else
              nend = str_points.find(" ", nbegin);

           string singleNum = str_points.substr(nbegin, nend - nbegin);
           
		   CCString *str_result = CCString::createWithFormat("%d", factor_macro(atoi(singleNum.c_str())));

		   str_result_points += str_result->m_sString;

		   if (nend != -1)
		   {
			   if (isDot)
				   str_result_points += ",";
			   else
				   str_result_points += " ";
		   }
		   
		   nbegin = nend + 1;
		   isDot = !isDot;
	   }
       
	   xmlSetProp(curNode, BAD_CAST "points", BAD_CAST str_result_points.c_str());

	}
	
	
}

void HelloWorld::convertCB( CCObject *sender )
{
   Utility::iterateFolder(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(""), this, callfuncO_selector(HelloWorld::folderCB));
}

void HelloWorld::folderCB(CCObject* sender)
{
	CCString* strCC = (CCString*)sender;

	string& str = strCC->m_sString;

	if (str.find(".tmx") != string::npos)
	{
		//xml
		xmlDocPtr doc = xmlReadFile(str.c_str(), "utf-8", XML_PARSE_RECOVER);
		xmlNodePtr curNode;

		curNode = xmlDocGetRootElement(doc);

		traverseNode(curNode);
        
		string path;
		if (m_isLowToHigh)
		{
			path = "./gaoqing";
		}
		else
		{
			path = "./diqing";
		}
		
		CreateDirectoryA(path.c_str(), NULL);

		path += "/";
		path += str;

		xmlSaveFormatFileEnc(path.c_str(), doc, "UTF-8", 1);

		xmlFreeDoc(doc);
	}

}

void HelloWorld::changeCB( CCObject *sender )
{
    m_isLowToHigh = !m_isLowToHigh;

	if (m_isLowToHigh)
	    m_lblLowToHigh->setString("To High");
	else
		m_lblLowToHigh->setString("To Low");
	
}



