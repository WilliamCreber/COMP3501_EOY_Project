#include "PhysicsManager.h"


PhysicsManager::PhysicsManager(ObjectManager* _manager)
{
	objectManager = _manager;
}


PhysicsManager::~PhysicsManager(void)
{
	objectManager = 0;
}

void PhysicsManager::pollTotalEvents()
{
	std::vector<GameObject*> tempList = objectManager->getObjectList();
	
	for(unsigned int i = 0; i < tempList.size(); i++)
	{
		for(unsigned int j = 0; j < tempList.size(); j++){
			bool collide = false;
			
			if(i != j){
				collide = testcollidableDistance(tempList.at(i), tempList.at(j));
			}

			if(collide){
				elasticCollision(tempList.at(i), tempList.at(j));
			}
			else{
				
			}
		}
		tempList.at(i)->update();
	}
}

/*
 * Private Functions
 * 
 */


/*	
*	sphere test // not fully calibrated, i shall blame shields
*/
bool PhysicsManager::testcollidableDistance(GameObject* _focus, GameObject* _collidie)
{	
	static int i = 0;

	if( _focus->getAABBCenter().squaredDistance(_collidie->getAABBCenter()) < Math::Sqr((_focus->getAABBSize() * 0.5).length()) + Math::Sqr((_collidie->getAABBSize() * 0.5).length())){
		//std::cout << "collide" + std::to_string(i) << std::endl;
		i++;
		return true;
	}
	
	return false;
}

void PhysicsManager::elasticCollision(GameObject* _focus, GameObject* _collidie)
{
	Vector3 pos1 = _focus->getNode()._getDerivedPosition();
	Vector3 pos2 = _collidie->getNode()._getDerivedPosition();

	Vector3 vel1 = _focus->getMotionDirection();
	Vector3 vel2 = _collidie->getMotionDirection();

	Vector3 dif = pos1 - pos2;
	Vector3 half = pos1 - (0.5 * dif);

	std::cout << "old:: " << dif << std::endl;

	vel1 = vel1.dotProduct(dif);

	std::cout << "new:: " << vel1 << std::endl;

}