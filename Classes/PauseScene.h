#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class PauseScene : public cocos2d::Layer
{
public:
    virtual bool init();

    CREATE_FUNC(PauseScene);
    void Exit(cocos2d::Ref* pSender);
    void Pause(cocos2d::Ref* pSender);
    void Restart(cocos2d::Ref* pSender);
    static cocos2d::Scene* scene(cocos2d::RenderTexture* sqr);
private:
    cocos2d::MenuItemImage* exit;
    cocos2d::MenuItemImage* start;
    cocos2d::MenuItemImage* restart;
    cocos2d::Menu* menu;
    cocos2d::Sprite* title;
    cocos2d::Sprite* bg;
};


#endif // __PAUSE_SCENE_H__
