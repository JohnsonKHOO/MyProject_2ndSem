#ifndef __Slime_H__
#define __Slime_H__

#include "cocos2d.h"

class Slime : public cocos2d::Sprite
{
public:
    Slime();
    void initSlime(char* slime_name);
    void hurt();
    void dead();
    void endHurt();
    CREATE_FUNC(Slime);
    unsigned int gethealth();
    bool isDead;
    bool isHurt;
    const unsigned int constHealth = 60;//×ÜÑªÁ¿
  
private:
    char* Slime_Name;
    cocos2d::Sprite* SlimeSprite;
    unsigned int health;
  
};

#endif // __SLIME_H__

