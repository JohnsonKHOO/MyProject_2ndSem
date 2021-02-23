#include "GameScene.h"
#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(void)
{
	EnemySprite = NULL;
	isRunning = false;
	isAttack = false;
	isHurt = false;
	isDead = false;
	health = 300;
}

//��ʼ������
void Enemy::initEnemySkull()
{
	EnemySprite = Sprite::create("enemy/enemy_skull_standing/enemy_skull_standing.png");
	this->addChild(EnemySprite);

}

void Enemy::run()
{
	this->setSkullRunAnimation("enemy/enemy_skull_walking/enemy_skull_walking_", 25);
}
void Enemy::attack()
{
	this->setSkullAttackAnimation("enemy/enemy_skull_fight/enemy_skull_fight_", 17);
}

void Enemy::hurt()
{
	this->setSkullHurtAnimation("enemy/enemy_skull_damaged/enemy_skull_damaged", 6);
}

void Enemy::dead()
{
	endRun();
	endAttack();
	this->setSkullDeadAnimation("enemy/enemy_skull_die/enemy_skull_die", 15);
}

//���ñ��ܶ���
void Enemy::setSkullRunAnimation(const char* enemy_name, const int num)
{
	if (isRunning || isAttack)return;
	Animation* animation = Animation::create();
	for (int i = 1; i <= num; i++)
	{
		char fileName[100] = { 0 };
		sprintf(fileName, "%s%d.png", enemy_name, i);
		animation->addSpriteFrameWithFile(fileName);
	}
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);

	animation->setLoops(-1);
	Animate* animate = Animate::create(animation);
	this->endRun();
	EnemySprite->runAction(animate);
	isRunning = true;
}

//���ù�������
void Enemy::setSkullAttackAnimation(const char* enemy_name,const int num)
{
	if (isRunning || isAttack)return;
	Animation* animation = Animation::create();
	for (int i = 1; i <= num; i++)
	{
		char fileName[100] = { 0 };
		sprintf(fileName, "%s%d.png", enemy_name, i);
		animation->addSpriteFrameWithFile(fileName);
	}
	animation->setDelayPerUnit(0.05f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);

	Animate* animate = Animate::create(animation);
	this->endAttack();
	EnemySprite->runAction(animate);
	isAttack = true;
}

//�������˶���
void Enemy::setSkullHurtAnimation(const char* enemy_name, const int num)
{
	if (isDead || isHurt)return;

	if (isRunning || isAttack)
	{
		EnemySprite->stopAllActions();
		this->removeChild(EnemySprite, TRUE);
		this->initEnemySkull();
		isRunning = false;
		isAttack = false;
	}
	isHurt = true;
	Animation* animation = Animation::create();
	for (int i = 1; i <= num; i++)
	{
		char fileName[100] = { 0 };
		sprintf(fileName, "%s%d.png", enemy_name, i);
		animation->addSpriteFrameWithFile(fileName);
	}
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);

	Animate* animate = Animate::create(animation);
	this->endHurt();
	EnemySprite->runAction(animate);
}

//������������
//�����û�뵽�취ʵ�֣�����һ����ֱ������ʤ���ĳ�����
void Enemy::setSkullDeadAnimation(const char* enemy_name, const int num)
{
	isDead = true;
	Animation* animation = Animation::create();
	for (int i = 1; i <= num; i++)
	{
		char fileName[100] = { 0 };
		sprintf(fileName, "%s%d.png", enemy_name, i);
		animation->addSpriteFrameWithFile(fileName);
	}
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);

	Animate* animate = Animate::create(animation);
	EnemySprite->runAction(animate);

}

void Enemy::endAttack()
{
	if (!isAttack)return;
	EnemySprite->stopAllActions();
	this->removeChild(EnemySprite, TRUE);
	this->initEnemySkull();
	isAttack = false;
}

void Enemy::endRun()
{
	if (!isRunning)return;
	EnemySprite->stopAllActions();
	this->removeChild(EnemySprite, TRUE);
	this->initEnemySkull();
	isRunning = false;
}

void Enemy::endHurt()
{
	isHurt = false;

	health = health - 1;
	CCLOG("hurt");
	if (health <= 0)
	{
		this->dead();
	}
}

void Enemy::endDead()
{
	if (!isDead)return;
	EnemySprite->stopAllActions();
	this->removeChild(EnemySprite, TRUE);
}
