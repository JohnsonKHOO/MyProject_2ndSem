#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "Slime.h"
#include "Gun.h"
#include "Bullet.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
    GameScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void setMapView(cocos2d::Point playerPos);
    void moveViewFromStart(float dt);
    void Pause(cocos2d::Ref* pSender);
    void SlimeJudgePosition();
    void SlimeUpdate(float dt);
    void EnemyRun(Enemy* enemy);
    void startListen();
    void EnemyUpdate(float dt);
    bool isRectCollision(cocos2d::Rect rect1, cocos2d::Rect rect2);
    void update(float dt);

    Bullet* SlimeBullet;
    Slime* SlimeMe;
    Gun* SlimeGun;
    Enemy* EnemySkull;
    cocos2d::TMXTiledMap* tilemap;
    cocos2d::Sprite* health[5];

private:
    float dis;
    float x;
    float y;
    float playerX;
    float playerY;
    float enemyX;
    float enemyY;

    cocos2d::Menu* menu;
    cocos2d::MenuItemImage* pause;
    MoveBy* actionMoveDown;
    MoveBy* actionMoveUp;
    MoveBy* actionMoveLeft;
    MoveBy* actionMoveRight;

    cocos2d::TMXObjectGroup* playerObjGroup;
    cocos2d::TMXObjectGroup* enemyObjGroup;
    cocos2d::ValueMap playerPos;
    cocos2d::ValueMap enemyPos;
    cocos2d::ValueMap gunPos;

    cocos2d::Size MAP_SIZE;
    cocos2d::Size winSize;
    cocos2d::Point middlePoint;
    cocos2d::Point newMapPos;
    cocos2d::Point newPlayerPos;
    cocos2d::Point slimeNextPos;
    cocos2d::Point gunPosition;
    cocos2d::EventListenerKeyboard* listenerKeyboard;
};
#endif // __GAME_SCENE_H__
