#include "MainMenuScene.h"
#include "GuideScene.h"
#include "GameScene.h"

USING_NS_CC;


Scene* GuideScene::createScene()
{
    return GuideScene::create();
}

bool GuideScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    back = MenuItemImage::create("button/goback_button_1.png", "button/goback_button_2.png", CC_CALLBACK_1(GuideScene::Back, this));
    back->setPosition(Point(visibleSize.width * 1 / 7+40 , visibleSize.height * 2 / 5));
    back->setScale(0.65);

    start = MenuItemImage::create("button/start_game_button_1.png", "button/start_game_button_2.png", CC_CALLBACK_1(GuideScene::Play, this));
    start->setPosition(Point(visibleSize.width * 5 / 7+75 , visibleSize.height * 2 / 5));
    start->setScale(0.65);

    menu = Menu::create(back, start, NULL);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu, 1);

    bg = Sprite::create("button/caozuo_final.png");
    bg->setPosition(visibleSize/2 );
    bg->setScale(1.44);
    bg->setScaleX(1.91);
    this->addChild(bg);

    return true;
}

void GuideScene::Play(cocos2d::Ref* pSender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.75, scene));
}
void GuideScene::Back(cocos2d::Ref* pSender)
{
    Director::getInstance()->popScene();
}