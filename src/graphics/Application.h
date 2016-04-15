/*
This source file is part of the Ogre Wiki Tutorial Framework
http://www.ogre3d.org/tikiwiki/
*/
#pragma once
#include "BaseApplication.h"

class Application : public BaseApplication
{
public:
	Application();
	void setScale(double scale);
	virtual ~Application();

protected:
	virtual void createScene();
};
