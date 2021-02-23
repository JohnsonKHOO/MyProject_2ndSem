#include "MainMenuScene.h"
#include "PauseScene.h"
#include "GameScene.h"
#include "Slime.h"

USING_NS_CC;

bool PauseScene::init()
{

    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    exit = MenuItemImage::create("button/exit_game_button_1.png", "button/exit_game_button_2.png", CC_CALLBACK_1(PauseScene::Exit, this));
    exit->setPosition(Point(visibleSize.width * 1 / 2+10, visibleSize.height * 1 / 5));
    exit->setScale(0.7);

    start = MenuItemImage::create("button/goback_button_1.png", "button/goback_button_2.png", CC_CALLBACK_1(PauseScene::Pause, this));
    start->setPosition(Point(visibleSize.width * 1 / 2, visibleSize.height * 3 / 5-60));
    start->setScale(0.7);

    restart = MenuItemImage::create("button/restart_button_1.png", "button/restart_button_2.png", CC_CALLBACK_1(PauseScene::Restart, this));
    restart->setPosition(Point(visibleSize.width * 1 / 2 , visibleSize.height * 2 / 5-25));
    restart->setScale(0.7);

    menu = Menu::create(exit, start, restart, NULL);
    menu->setPosition(Point(0, 0)); 
    this->addChild(menu, 1);

    title = Sprite::create("button/pause_button_1.png");
    title->setPosition(Point(visibleSize / 2));
    title->setScale(1.5);
    title->setPosition(Point(visibleSize.width * 1 / 2+5, visibleSize.height * 4 / 5 - 50));
    this->addChild(title,1);


    bg = Sprite::create("button/puase_scene.png");
    bg->setPosition(Point(visibleSize / 2));
    bg->setScale(1.44);
    bg->setScaleX(1.91);
    this->addChild(bg);

    return true;
}

void PauseScene::Exit(cocos2d::Ref* pSender)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.75, scene));
}
void PauseScene::Pause(cocos2d::Ref* pSender)
{
    Director::getInstance()->popScene();
}
void PauseScene::Restart(cocos2d::Ref* pSender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.75, scene));
}

Scene* PauseScene::scene(RenderTexture* sqr)
{
    Scene* scene = Scene::create();
    Sprite* sprite = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    PauseScene* layer = PauseScene::create();
    scene->addChild(layer);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    sprite->setPosition(visibleSize/2);
    sprite->setFlippedY(true);
    scene->addChild(sprite);


    return scene;
}