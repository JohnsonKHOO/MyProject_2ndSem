#include "GameScene.h"
#include "Slime.h"


USING_NS_CC;

Slime::Slime(void)
{
	SlimeSprite = NULL;
	Slime_Name = NULL;
	health = 60;
	isDead = false;
	isHurt = false;
	
}

//初始化玩家
void Slime::initSlime(char* slime_name)
{
	Slime_Name = slime_name;
	SlimeSprite = Sprite::create(slime_name);
	this->addChild(SlimeSprite);
}

//玩家受伤
void Slime::hurt()
{
	if (isHurt || isDead)return;
	health = health - 2;//扣除血量
	CCLOG("-2");
	isHurt = true;
}

//玩家死亡
void Slime::dead()
{
	if (isDead)return;
	isDead = true;
	this->removeAllChildren();
	CCLOG("died");
}

void Slime::endHurt()
{
	if (health <= 0)this->dead();

	isHurt = false;
}

unsigned int Slime:: gethealth()
{
	return health;
}