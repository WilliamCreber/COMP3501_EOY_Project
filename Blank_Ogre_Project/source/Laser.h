#pragma once
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include "GameObject.h"


class Laser: public GameObject
{
public: 
	Laser(Ogre::SceneNode * ,Ogre::Quaternion ,Ogre::Vector3 , bool lr);
	~Laser(void);
	Ogre::SceneNode& getNode();

	void move();

	void particle();
	void update(float _timer,ObjectManager*);
	void collide();
	void collide(int);
	void shoot(GameObjectFactory* ,ObjectManager*, GameObject* );


private:
	
	float flyTime;
	int countdown;
	float accel_Rate; 
	

};

