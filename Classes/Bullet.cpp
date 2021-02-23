#include "GameScene.h"
#include "Bullet.h"
#include "Gun.h"
#include "Enemy.h"

USING_NS_CC;

Bullet::Bullet(void)
{
	my_enemy = NULL;
	bullet = NULL;
	my_gun = NULL;
	isFlying = false;
	stepX = 0.0f;
	stepY = 0.0f;
}
//初始化子弹
void Bullet::initBulletWithGun(Gun* gun, Enemy* enemy)
{
	my_enemy = enemy;
	my_gun = gun;
	bullet = Sprite::create("char/slime_bullet_2.png");
	bullet->setScale(1.5);
	this->addChild(bullet);
	bullet->setVisible(false);//先把子弹设置为不可见，当子弹射出才为可见
}
//无限生成子弹
Bullet* Bullet::createBulletwithGun(Gun* gun,Enemy* enemy)
{
	Bullet* b = new Bullet();
	b->initBulletWithGun(gun, enemy);
	b->autorelease();//自动释放
	return b;
}

bool Bullet::fire()
{
	if (!isFlying)
	{
		bullet->setVisible(true);
		isFlying = true;
		setPosition(my_gun->getPosition());
		unsigned int rotation = my_gun->getRotation();
		//根据抢的旋转角度控制子弹该从什么角度射出
		switch (rotation)
		{
		case 0:
			stepX = 50.0f, stepY = 10.0f;
			break;
		case 90:
			stepX = 50.0f, stepY = 20.0f;
			break;
		case 180:
			stepX = 50.0f, stepY = 0.0f;
			break;
		case 270:
			stepX = 50.0f, stepY = -20.0f;
			break;	
		default:
			break;
		}
		//每一帧都增加子弹的x和y，从而实现子弹移动
		this->scheduleUpdate();
	}
	return isFlying;
}

void Bullet::update(float dt)
{
	
	bullet->setPosition(Vec2(bullet->getPosition().x + stepX, bullet->getPosition().y + stepY));//子弹移动

	//我先保留这一部分代码，不知道为什么达不到预期效果，子弹与敌人永远不会碰撞。
	//我用了几种办法但都无法实现，由于时间不够了所以我就不强求了。

	//碰撞检测
	/*Rect rectBullet = bullet->getBoundingBox();//得到矩形
	Rect rectEnemy = my_enemy->getBoundingBox();
	if (rectBullet.intersectsRect(rectEnemy))//判断子弹是否在敌人里面
	{
		unscheduleUpdate();
		this->setVisible(false);
		isFlying = false;
		this->removeAllChildren();
		CCLOG("hits");
	}*/
}

