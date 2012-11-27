#include "Utility.h"

#include <io.h>

void Utility::iterateFolder(const char* path, CCObject* target, SEL_CallFuncO selector)
{
	struct   _finddata_t   filefind; 
	string   curr = string(path) + "\\*.* "; 
	int   done = 0, i, handle; 
	if((handle = _findfirst(curr.c_str(),&filefind)) == -1)
		return; 
	while(!(done = _findnext(handle, &filefind))) 
	{ 
		if(!strcmp(filefind.name, ".."))
			continue; 

		if   ((_A_SUBDIR == filefind.attrib)) 
		{
			continue;
			curr= string(path) + "\\" + filefind.name; 
			iterateFolder(curr.c_str(), target, selector); 
		} 
		else   
		{ 
			if(target && selector)
			{
				CCString* str = new CCString(filefind.name);
				str->autorelease();
				(target->*selector)(str);
			}
		} 
	}
	_findclose(handle);

}

