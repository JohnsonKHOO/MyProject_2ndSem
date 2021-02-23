#ifndef __GUN_H__
#define __GUN_H__
#include "cocos2d.h"

class Gun : public cocos2d::Node
{
public:
    Gun();
    void initGun(char* gun_name);
    unsigned int getRotation();
    int rotation;
    CREATE_FUNC(Gun);
private:
    char* Gun_Name;
    cocos2d::Sprite* SlimeGun;

};

#endif // __GUN_H__

