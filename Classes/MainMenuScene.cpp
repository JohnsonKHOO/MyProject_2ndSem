#include "MainMenuScene.h"
#include "GameScene.h"
#include "GuideScene.h"

USING_NS_CC;


Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

bool MainMenuScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    exit = MenuItemImage::create("button/exit_game_button_1.png","button/exit_game_button_2.png", CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
    exit->setPosition(Point(visibleSize.width * 2 / 3 +50, visibleSize.height * 2 / 5-50));
    exit->setScale(0.8);

    guide = MenuItemImage::create("button/guide_button_1.png", "button/guide_button_2.png", CC_CALLBACK_1(MainMenuScene::Guide, this));
    guide->setPosition(Point(visibleSize.width * 2 / 3+50, visibleSize.height * 3 / 5-50));
    guide->setScale(0.8);

    start = MenuItemImage::create("button/start_game_button_1.png","button/start_game_button_2.png",CC_CALLBACK_1(MainMenuScene::Play, this));
    start->setPosition(Point(visibleSize.width * 2 / 3+50, visibleSize.height * 4 / 5-50));
    start->setScale(0.8);

    Menu* menu = Menu::create(exit,guide, start, NULL);
    menu->setPosition(Vec2(0,0));
    this->addChild(menu,1);

    LayerColor* bgColor = LayerColor::create(Color4B(21,40,52,255));
    this->addChild(bgColor);

    Sprite* title = Sprite::create("button/title_1.png");
    title->setPosition(200,180);
    title->setScale(1);
    this->addChild(title);

    Sprite* pic = Sprite::create("button/gaming_pic.png");
    pic->setPosition(200, 472);
    pic->setScale(1.1);
    this->addChild(pic);


    return true;
}

//退出
void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
//跳转到游戏场景
void MainMenuScene::Play(cocos2d::Ref* pSender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.75,scene));
}
//跳转到教学场景
void MainMenuScene::Guide(cocos2d::Ref* pSender)
{
    auto scene = GuideScene::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.75, scene));
}