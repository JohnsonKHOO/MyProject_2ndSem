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

//��ʼ�����
void Slime::initSlime(char* slime_name)
{
	Slime_Name = slime_name;
	SlimeSprite = Sprite::create(slime_name);
	this->addChild(SlimeSprite);
}

//�������
void Slime::hurt()
{
	if (isHurt || isDead)return;
	health = health - 2;//�۳�Ѫ��
	CCLOG("-2");
	isHurt = true;
}

//�������
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