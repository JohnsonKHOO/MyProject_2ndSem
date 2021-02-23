#include "MainMenuScene.h"
#include "SplashScene.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    return SplashScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    backgroundsprite = Sprite::create("HellOWorld.png");
    backgroundsprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundsprite);
    //在显示cocos2dx的logo2秒后就进行跳转   
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::goToMainMenuScene), 2);
}
//跳转到菜单场景
void SplashScene::goToMainMenuScene(float dt)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
 
}