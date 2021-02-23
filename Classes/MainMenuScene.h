#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    void Play(cocos2d::Ref* pSender);
    void Guide(cocos2d::Ref* pSender);

    CREATE_FUNC(MainMenuScene);
private:
    cocos2d::MenuItemImage* exit;
    cocos2d::MenuItemImage* guide;
    cocos2d::MenuItemImage* start;

};


#endif // __MAIN_MENU_SCENE_H__
