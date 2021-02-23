#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    return GameOverScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bg = Sprite::create("button/game_over_1.png");
    bg->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 130);
    bg->setScale(2);

    this->addChild(bg);
   
    restart = MenuItemImage::create("button/restart_button_1.png", "button/restart_button_2.png", CC_CALLBACK_1(GameOverScene::Restart, this));
    restart->setPosition(Point(visibleSize.width * 1 / 2, visibleSize.height * 2 / 5));
    restart->setScale(0.8);

    exit = MenuItemImage::create("button/exit_game_button_1.png", "button/exit_game_button_2.png", CC_CALLBACK_1(GameOverScene::Exit, this));
    exit->setPosition(Point(visibleSize.width * 1 / 2 + 10, visibleSize.height * 1 / 5));
    exit->setScale(0.8);

    menu = Menu::create(restart, exit, NULL);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu, 1);
}

void GameOverScene::Restart(cocos2d::Ref* pSender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.75, scene));
}

void GameOverScene::Exit(cocos2d::Ref* pSender)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.75, scene));
}