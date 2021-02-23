#ifndef __BULLET_H__
#define __BULLET_H__
#include "Gun.h"
#include "cocos2d.h"
#include "Enemy.h"
class Bullet : public cocos2d::Node
{
public:
    Bullet();
    void initBulletWithGun(Gun* gun, Enemy* enemy);
    static Bullet* createBulletwithGun(Gun* gun,Enemy* enemy);
    bool fire();
    virtual void update(float dt);
    bool isFlying;
    CREATE_FUNC(Bullet);

private:
    Enemy* my_enemy;
    Gun* my_gun;
    float stepX, stepY;
    cocos2d::Sprite* bullet;
    
};

#endif // __BULLET_H__

