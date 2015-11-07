#include "PlayerInput.h"




	float camera_near_clip_distance_g = 0.001f;
	float camera_far_clip_distance_g = 10000.0;
	Ogre::Vector3 camera_position_g(0.0, 0.0, 0.0);
	Ogre::Vector3 camera_look_at_g(0.0, 0.0, 0.0);
	Ogre::Vector3 camera_up_g(0.0, 1.0, 0.0);
	bool space_down_ = false;
	bool camState = true;

PlayerInput::PlayerInput(  Ogre::SceneManager* manager,OIS::Keyboard* _keyboard, OIS::Mouse* _mouse)
{

		currentDir = (0,0,0);
		rightDir = (0,0,0);
		upDir = (0,0,0);
		forwDir = (0,0,0);
		
		scene_manager = manager;
		root_scene_node = scene_manager->getRootSceneNode();

		playerMouse_ = _mouse;
		playerMouse_->setBuffered(true);
		playerKeyboard_ = _keyboard;


		player_camera = scene_manager->createCamera("MyCamera");
        camera_scene_node = root_scene_node->createChildSceneNode("MyCameraNode");
        camera_scene_node->attachObject(player_camera);
		camera_scene_node->setPosition(0.0, 0.0, 0.0);

		camera_scene_node->resetOrientation();

        player_camera->setNearClipDistance(camera_near_clip_distance_g);
        player_camera->setFarClipDistance(camera_far_clip_distance_g); 

		player_camera->setPosition(camera_position_g);
		player_camera->lookAt(camera_look_at_g);
		//camera->setFixedYawAxis(true, camera_up_g);
		player_camera->setFixedYawAxis(false);
		camera_scene_node->setFixedYawAxis(false);


		camera_first_person_node = root_scene_node->createChildSceneNode("MyFirstPersonCameraNode");
		camera_first_person_node->setPosition(0,0,0);
		camera_first_person_node->setFixedYawAxis(false);

		
		camera_chase_node = camera_first_person_node->createChildSceneNode("MyChaseCameraNode");
		camera_chase_node->setPosition(0.0, 2.0, 10.0);
		camera_chase_node->setInheritOrientation(false);
		camera_chase_node->setFixedYawAxis(false);
}


PlayerInput::~PlayerInput(void)
{
}


void PlayerInput::updateCamera(void){

	/* Capture input */
	playerKeyboard_->capture();
	playerMouse_->capture();

	handleInput();
	if(camState){
		camera_scene_node->setPosition(camera_first_person_node->getPosition());
		camera_scene_node->setOrientation(camera_first_person_node->getOrientation());
	}else{
		camera_scene_node->setPosition(camera_chase_node->_getDerivedPosition());
		camera_scene_node->setOrientation(camera_first_person_node->getOrientation());
		

	}

}

void PlayerInput::handleInput(void){
	/* This event is called after a frame is queued for rendering */
	/* Do stuff in this event since the GPU is rendering and the CPU is idle */	
	
	if(playerMouse_->getMouseState().buttonDown(OIS::MB_Right)){
		

		Ogre::Quaternion pitchQuat(Ogre::Radian(playerMouse_->getMouseState().Y.rel * -0.01f),Ogre::Vector3::UNIT_X);
		Ogre::Quaternion yawQuat(Ogre::Radian(playerMouse_->getMouseState().X.rel * -0.01f),Ogre::Vector3::UNIT_Y);
		Ogre::Quaternion rotQuat =  pitchQuat * yawQuat;
		//camera_first_person_node->rotate(pitchQuat,Ogre::Node::TS_LOCAL); //this allows us to have no roll when pitch and yaw are combined
		//camera_first_person_node->rotate(yawQuat,Ogre::Node::TS_WORLD); //  this will also cause a forced lock

		camera_first_person_node->rotate(rotQuat); // quaternion camera with rotations embedded from pitch and yaws

		//camera_first_person_node->pitch(Ogre::Radian(playerMouse_->getMouseState().Y.rel * -0.01f));
		///camera_first_person_node->yaw(Ogre::Radian(playerMouse_->getMouseState().X.rel * -0.01f));
	
	}
	

	Ogre::Radian rot_factor(Ogre::Math::PI / 180); // Camera rotation with directional thrusters
	
	if(playerKeyboard_->isKeyDown(OIS::KC_Q)){
		camera_first_person_node->rotate(Ogre::Quaternion(rot_factor,Ogre::Vector3::UNIT_Z));
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_E)){
		camera_first_person_node->rotate(Ogre::Quaternion(-1*rot_factor,Ogre::Vector3::UNIT_Z));
	}

	
	if(playerKeyboard_->isKeyDown(OIS::KC_A)){
		Ogre::Vector3 newRightDir = player_camera->getDerivedRight() * -0.01;
		rightDir= rightDir + newRightDir;
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_D)){
		Ogre::Vector3 newRightDir = player_camera->getDerivedRight() * 0.01;
		rightDir= rightDir + newRightDir;
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_W)){
		Ogre::Vector3 newForwardDir = player_camera->getDerivedDirection() * 0.01;
		forwDir = forwDir + newForwardDir;
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_S)){
		Ogre::Vector3 newForwardDir = player_camera->getDerivedDirection() * -0.01;
		forwDir = forwDir + newForwardDir;
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_R)){
		Ogre::Vector3 newUpDir = player_camera->getDerivedUp() * 0.01;
		upDir = upDir + newUpDir;
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_F)){
		Ogre::Vector3 newUpDir = player_camera->getDerivedUp() * -0.01;
		upDir = upDir + newUpDir;
	}

	currentDir = upDir + rightDir + forwDir;
	camera_first_person_node->translate(currentDir);

	if (playerKeyboard_->isKeyDown(OIS::KC_SPACE)){
		space_down_ = true;
	}
	if ((!playerKeyboard_->isKeyDown(OIS::KC_SPACE)) && space_down_){
		camState = !camState;
		space_down_ = false;
	}


}