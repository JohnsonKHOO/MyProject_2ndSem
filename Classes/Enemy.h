#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"
#include "Slime.h"

class Enemy : public cocos2d::Node
{
public:
    Enemy();
    void initEnemySkull();
    void setSkullAttackAnimation(const char* enemy_name, int num);
    void setSkullRunAnimation(const char* enemy_name, int num);
    void setSkullHurtAnimation(const char* enemy_name, const int num);
    void setSkullDeadAnimation(const char* enemy_name, const int num);

    void attack();
    void run();
    void hurt();
    void dead();
    void endAttack();
    void endRun();
    void endHurt();
    void endDead();

    bool isRunning;
    bool isAttack;
    bool isDead;
    bool isHurt;

    
    CREATE_FUNC(Enemy);
private:
    cocos2d::Sprite* EnemySprite;
    unsigned int health;
};
#endif // __ENEMY_H__
