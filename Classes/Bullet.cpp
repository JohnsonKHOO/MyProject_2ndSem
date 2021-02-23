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
//��ʼ���ӵ�
void Bullet::initBulletWithGun(Gun* gun, Enemy* enemy)
{
	my_enemy = enemy;
	my_gun = gun;
	bullet = Sprite::create("char/slime_bullet_2.png");
	bullet->setScale(1.5);
	this->addChild(bullet);
	bullet->setVisible(false);//�Ȱ��ӵ�����Ϊ���ɼ������ӵ������Ϊ�ɼ�
}
//���������ӵ�
Bullet* Bullet::createBulletwithGun(Gun* gun,Enemy* enemy)
{
	Bullet* b = new Bullet();
	b->initBulletWithGun(gun, enemy);
	b->autorelease();//�Զ��ͷ�
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
		//����������ת�Ƕȿ����ӵ��ô�ʲô�Ƕ����
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
		//ÿһ֡�������ӵ���x��y���Ӷ�ʵ���ӵ��ƶ�
		this->scheduleUpdate();
	}
	return isFlying;
}

void Bullet::update(float dt)
{
	
	bullet->setPosition(Vec2(bullet->getPosition().x + stepX, bullet->getPosition().y + stepY));//�ӵ��ƶ�

	//���ȱ�����һ���ִ��룬��֪��Ϊʲô�ﲻ��Ԥ��Ч�����ӵ��������Զ������ײ��
	//�����˼��ְ취�����޷�ʵ�֣�����ʱ�䲻���������ҾͲ�ǿ���ˡ�

	//��ײ���
	/*Rect rectBullet = bullet->getBoundingBox();//�õ�����
	Rect rectEnemy = my_enemy->getBoundingBox();
	if (rectBullet.intersectsRect(rectEnemy))//�ж��ӵ��Ƿ��ڵ�������
	{
		unscheduleUpdate();
		this->setVisible(false);
		isFlying = false;
		this->removeAllChildren();
		CCLOG("hits");
	}*/
}

