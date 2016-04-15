/*
This source file is part of the Ogre Wiki Tutorial Framework
http://www.ogre3d.org/tikiwiki/
*/
#include "Application.h"

Application::Application(void)
{
}

Application::~Application(void)
{
}

void Application::createScene(void)
{
	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	// Create a Light and set its position
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);

	// Create an Entity
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
	headNode->attachObject(ogreHead);

	headNode->scale(2.0f, 2.0f, 2.0f);
	headNode->yaw(Ogre::Degree(-90));

	Ogre::Entity* ogreHead2 = mSceneMgr->createEntity("Head2", "ogrehead.mesh");
	Ogre::SceneNode* headNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode2", Ogre::Vector3(100, 0, 0));
	headNode2->attachObject(ogreHead2);

	headNode2->pitch(Ogre::Degree(90));

	Ogre::Entity* ogreHead3 = mSceneMgr->createEntity("Head3", "ogrehead.mesh");
	Ogre::SceneNode* headNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode3", Ogre::Vector3(-100, 0, 0));
	headNode3->attachObject(ogreHead3);

	headNode3->roll(Ogre::Degree(90));
}

void Application::setScale(double scale)
{
	auto root_node = mSceneMgr->getRootSceneNode();
	root_node->setScale(scale, scale, scale);
}
