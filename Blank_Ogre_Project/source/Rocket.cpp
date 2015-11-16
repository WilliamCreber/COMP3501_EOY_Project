#include "Rocket.h"


Rocket::Rocket(Ogre::SceneNode * newRocket,Ogre::Quaternion shipOrientation,Ogre::Vector3 shipPosition, Ogre::Vector3 shipDirection):GameObject(GameObject::empty)
{
	
	m_pNode = newRocket;
	
	m_pNode->setOrientation(shipOrientation*(Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_Y)));
	drift_Direction = shipDirection;
	forward_Direction = shipOrientation *  Ogre::Vector3::NEGATIVE_UNIT_Z;
	Ogre::Vector3 down_Direction = shipOrientation *  Ogre::Vector3::NEGATIVE_UNIT_Y;

	m_pNode->setPosition(shipPosition + (forward_Direction *10) + (down_Direction*2));
	
	accel_Rate = 0.03;

	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);

}


Rocket::~Rocket(void)
{
}

void Rocket::update(void)
{
	move();
}

void Rocket::move(){

	drift_Direction = drift_Direction += forward_Direction * accel_Rate;
	m_pNode->translate(drift_Direction);
	m_pNode->needUpdate();
}

void Rocket::collide(){
	//add these for anything that could collide
}

void Rocket::explode(){
	//run explosion particle effect
}

Ogre::SceneNode& Rocket::getNode()
{
	return *m_pNode;
}

