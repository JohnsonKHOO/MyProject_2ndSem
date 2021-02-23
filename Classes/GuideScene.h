#ifndef __GUIDE_SCENE_H__
#define __GUIDE_SCENE_H__

#include "cocos2d.h"

class GuideScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GuideScene);
    void Play(cocos2d::Ref* pSender);
    void Back(cocos2d::Ref* pSender);
private:
    cocos2d::MenuItemImage* back;
    cocos2d::MenuItemImage* start;
    cocos2d::Menu* menu;
    cocos2d::Sprite* bg;

};


#endif // __GUIDE_SCENE_H__
