#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void Restart(cocos2d::Ref* pSender);
    void Exit(cocos2d::Ref* pSender);
    CREATE_FUNC(GameOverScene);
private:
    cocos2d::MenuItemImage* restart;
    cocos2d::MenuItemImage* exit;
    cocos2d::Menu* menu;
    cocos2d::Sprite* bg;
};


#endif // __GAME_OVER_SCENE_H__
