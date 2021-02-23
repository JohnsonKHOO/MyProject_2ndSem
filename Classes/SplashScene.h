#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

class SplashScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void goToMainMenuScene(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
private:
    cocos2d::Sprite* backgroundsprite;
};


#endif // __SPLASH_SCENE_H__
