#include "GameScene.h"
#include "Gun.h"

USING_NS_CC;

Gun::Gun(void)
{
	rotation = 270;
	Gun_Name = NULL;
	SlimeGun = NULL;
}


void Gun::initGun(char* gun_name)
{
	Gun_Name = gun_name;
	SlimeGun = Sprite::create(gun_name);
	this->addChild(SlimeGun);
}

unsigned int Gun::getRotation()
{
	return rotation;
}


