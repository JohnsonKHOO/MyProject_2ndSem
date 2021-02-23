#include "GameScene.h"
#include "MainMenuScene.h"
#include "Enemy.h"
#include "Slime.h"
#include "Gun.h"
#include "GameOverScene.h"
#include "PauseScene.h"
#include "Bullet.h"
#include "VictoryScene.h"

USING_NS_CC;

GameScene::GameScene(void)
{
    EnemySkull = NULL;
    SlimeBullet = NULL;
    dis = 0;
    x = 0;
    y = 0;
    playerX = 0;
    playerY = 0;
    enemyX = 0;
    enemyY = 0;
    SlimeMe = NULL;
    SlimeGun = NULL;
    tilemap = NULL;
    menu = NULL;
    pause = NULL;
    actionMoveDown = NULL;
    actionMoveLeft = NULL;
    actionMoveUp = NULL;
    actionMoveRight = NULL;
    enemyObjGroup = NULL;
    playerObjGroup = NULL;
    listenerKeyboard = NULL;
}

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    //初始化地图，使用Tiled软件把地图做成tmx格式并导入
    tilemap = TMXTiledMap::create("map/tilemap.tmx");
    this->addChild(tilemap);

    //获取在Tiled软件里设置好的玩家与敌人的位置，在接下来用来初始化玩家与敌人
    playerObjGroup = tilemap->getObjectGroup("player");
    playerPos = playerObjGroup->getObject("slime_pos");
    playerX = playerPos["x"].asFloat() - 50;
    playerY = playerPos["y"].asFloat() - 100;
    gunPos = playerObjGroup->getObject("slime_gun");
    gunPosition.x = gunPos["x"].asFloat() - 50;
    gunPosition.y = gunPos["y"].asFloat() - 100;

    //初始化玩家
    SlimeMe = Slime::create();
    SlimeMe->initSlime("char/slime_move_down.png");
    SlimeMe->setPosition(Point(playerX, playerY));
    tilemap->addChild(SlimeMe);

    //初始化5个♥表示玩家血量
    for (int i = 0; i < 5; i++)
    {
        health[i] = Sprite::create("char/health.png");
        health[i]->setScale(0.5);
        health[i]->setPosition(50, 200 + i * 40);
        this->addChild(health[i]);
    }
    //初始化枪
    SlimeGun = Gun::create();
    SlimeGun->initGun("char/slime_gun.png");
    SlimeGun->setPosition(12, -15);
    SlimeGun->setRotation(70);
    SlimeGun->setScale(0.6);
    SlimeMe->addChild(SlimeGun, 1);

    //初始化敌人
    enemyObjGroup = tilemap->getObjectGroup("enemy_skull");
    ValueMap EnemySpawnPoint = enemyObjGroup->getObject("enemy_skull_pos");
    enemyX = EnemySpawnPoint["x"].asFloat();
    enemyY = EnemySpawnPoint["y"].asFloat();
    EnemySkull = Enemy::create();
    EnemySkull->initEnemySkull();
    EnemySkull->setScale(2);
    EnemySkull->setPosition(Point(enemyX, enemyY));
    tilemap->addChild(EnemySkull);
    startListen();

    //初始化子弹
    SlimeBullet = Bullet::createBulletwithGun(SlimeGun, EnemySkull);
    SlimeBullet->setPosition(0,0);
    SlimeGun->addChild(SlimeBullet);

    //键盘响应事件
    listenerKeyboard = EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(GameScene::keyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(GameScene::keyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
    listenerKeyboard->setEnabled(true);

    //暂停按钮
    pause = MenuItemImage::create("button/pause-button_1.png", "button/pause-button_2.png", CC_CALLBACK_1(GameScene::Pause, this));
    pause->setPosition(350, 250);
    pause->setScale(0.1);

    menu = Menu::create(pause, NULL);
    menu->setAnchorPoint(Point(0.9,0.9));
    this->addChild(menu, 10);

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::moveViewFromStart), 0.75);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::SlimeUpdate, this));
    this->scheduleUpdate();
    
    return true;
}



//键盘响应事件
void GameScene::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{

    
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
    {
        SlimeGun->rotation = 90;
        SlimeMe->initSlime("char/slime_move_up.png");
        actionMoveUp = MoveBy::create(6.5, Point(0, 1000));
        playerY += 200;
 
        //设置枪的位置与转动
        SlimeGun->setPosition(28, 19);
        SlimeGun->setRotation(0);
        SlimeGun->setRotationSkewY(0);
        SlimeGun->setRotation(-70);
 
        slimeNextPos.x = SlimeMe->getPosition().x;
        slimeNextPos.y = SlimeMe->getPosition().y+100;
        SlimeMe->runAction(actionMoveUp);
        setMapView(slimeNextPos);
        return;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        SlimeGun->rotation = 270;
        SlimeMe->initSlime("char/slime_move_down.png");
        actionMoveDown = MoveBy::create(6.5, Point(0, -1000));
        SlimeMe->runAction(actionMoveDown);
        playerY -= 200;

        SlimeGun->setPosition(12, -15);
        SlimeGun->setRotation(0);
        SlimeGun->setRotationSkewY(0);
        SlimeGun->setRotation(70);

        slimeNextPos.x = SlimeMe->getPosition().x;
        slimeNextPos.y = SlimeMe->getPosition().y - 200;

        setMapView(slimeNextPos);
        return;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        SlimeGun->rotation = 180;
        SlimeMe->initSlime("char/slime_move_left.png");
        actionMoveLeft = MoveBy::create(6.5, Point(-1000, 0));
        SlimeMe->runAction(actionMoveLeft);
        playerX -= 200;

        SlimeGun->setRotation(0);
        SlimeGun->setPosition(-37,2);
        SlimeGun->setRotation(-12);
        SlimeGun->setRotationSkewY(180);


        slimeNextPos.x = SlimeMe->getPosition().x-200;
        slimeNextPos.y = SlimeMe->getPosition().y;

        setMapView(slimeNextPos);
        return;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D)
    {
        SlimeGun->rotation = 0;
        SlimeMe->initSlime("char/slime_move_right.png");
        actionMoveRight = MoveBy::create(6.5, Point(1000, 0));
        SlimeMe->runAction(actionMoveRight);
        playerX += 200;

        SlimeGun->setRotation(0);
        SlimeGun->setPosition(36, 2);
        SlimeGun->setRotationSkewY(0);
        SlimeGun->setRotation(10);

        slimeNextPos.x = SlimeMe->getPosition().x+100;
        slimeNextPos.y = SlimeMe->getPosition().y;

        setMapView(slimeNextPos);
        return;
    }

    else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        SlimeBullet->fire();
        return;
    }
}

//键盘松开响应
void GameScene::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
    {
        SlimeMe->stopAction(actionMoveUp);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        SlimeMe->stopAction(actionMoveDown);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        SlimeMe->stopAction(actionMoveLeft);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D)
    {
        SlimeMe->stopAction(actionMoveRight);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        SlimeBullet = Bullet::createBulletwithGun(SlimeGun, EnemySkull);
        SlimeGun->addChild(SlimeBullet);
    }
    tilemap->stopAllActions();
}

//设置视角跟随玩家
void GameScene::setMapView(cocos2d::Point playerPos)
{
    tilemap->stopAllActions();

    Point playerLocation = playerPos;
    MAP_SIZE = tilemap->getContentSize();
    winSize = Director::getInstance()->getWinSize();

    middlePoint = Vec2(winSize.width / 2, winSize.height / 2);
    Point distance = middlePoint - playerLocation;
    newMapPos = Vec2(0, 0) + distance;

    newMapPos.x = (newMapPos.x > 0 ? 0 : newMapPos.x);
    newMapPos.y = (newMapPos.y > 0 ? 0 : newMapPos.y);
    newMapPos.x = (newMapPos.x < (winSize.width - MAP_SIZE.width) ? (winSize.width - MAP_SIZE.width) : newMapPos.x);
    newMapPos.y = (newMapPos.y < (winSize.height - MAP_SIZE.height) ? (winSize.height - MAP_SIZE.height) : newMapPos.y);

    MoveTo* action = MoveTo::create(0.8,newMapPos);
    tilemap->runAction(action);
}

//让视角一开始就移动至以玩家为中心。
void GameScene::moveViewFromStart(float dt)
{
    setMapView(Vec2(playerX, playerY));
}


//暂停函数
void GameScene::Pause(cocos2d::Ref* pSender)
{
    RenderTexture* renderTexture = RenderTexture::create(winSize.width,winSize.height);
    renderTexture->begin();
    //通过RenderTexture保存当前界面，然后传递给PauseScene，当成背景精灵。
    renderTexture->end();
    
    Director::getInstance()->pushScene(PauseScene::scene(renderTexture));
}

//判断玩家是否超出地图。
void GameScene::SlimeJudgePosition()
{
    //地图最上边
    if (SlimeMe->getPosition().y + 10 + SlimeMe->getContentSize().height / 2 >= MAP_SIZE.height-20)
    {
        SlimeMe->stopAction(actionMoveUp);
        SlimeMe->setPosition(SlimeMe->getPosition());
    }
    //地图最右边
    if (SlimeMe->getPosition().x + 10 + SlimeMe->getContentSize().width / 2 >= MAP_SIZE.width-20)
    {
        SlimeMe->stopAction(actionMoveRight);
        SlimeMe->setPosition(SlimeMe->getPosition());
    }
    //地图最左边
    if (SlimeMe->getPosition().x - 10 - SlimeMe->getContentSize().width / 2 <= 20)
    {
        SlimeMe->stopAction(actionMoveLeft);
        SlimeMe->setPosition(SlimeMe->getPosition());
    }
    //地图最左边
    if (SlimeMe->getPosition().y - 10 - SlimeMe->getContentSize().height / 2 <= 20)
    {
        SlimeMe->stopAction(actionMoveDown);
        SlimeMe->setPosition(SlimeMe->getPosition());
    }
}


void GameScene::SlimeUpdate(float dt)
{
    this->SlimeJudgePosition();
}

void GameScene::startListen()
{
    //每0.1秒就更新一次EnemyUpdate从而调用EnemyRun
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::EnemyUpdate),0.1f);
}

void GameScene::EnemyUpdate(float dt)
{
    EnemyRun(EnemySkull);
}

void GameScene::EnemyRun(Enemy* enemy)
{
    if (EnemySkull->isDead)//如果敌人死亡，进入胜利场景
    {
        auto scene = VictoryScene::createScene();
        Director::getInstance()->pushScene(TransitionFade::create(0.1, scene));
        return;
    }

    x = SlimeMe->getPosition().x - enemy->getPosition().x;
    y = SlimeMe->getPosition().y - enemy->getPosition().y;
    dis = sqrt(pow(x, 2) + pow(y, 2));//计算距离

    if (dis <= 120)//距离非常近就开始攻击
    {
        if (abs(y) < 50)//在y轴距离为50时开始攻击
        {
            enemy->endRun();
            SlimeMe->endHurt();
            EnemySkull->attack();

            if (SlimeMe->isDead)//如果玩家死亡，就跳到失败场景
            {
                auto scene = GameOverScene::createScene();
                Director::getInstance()->pushScene(TransitionFade::create(0.1, scene));
            }
            if (SlimeMe->gethealth() > SlimeMe->constHealth / 5)//根据血量比例扣除♥的数量
            {
                if (SlimeMe->gethealth() > SlimeMe->constHealth * 2 / 5)
                {
                    if (SlimeMe->gethealth() > SlimeMe->constHealth * 3 / 5)
                    {
                        if (SlimeMe->gethealth() > SlimeMe->constHealth * 4 / 5)
                        {
                            if (SlimeMe->gethealth() == SlimeMe->constHealth)return;

                            this->removeChild(health[4], TRUE);
                            return;
                        }
                        this->removeChild(health[3], TRUE);
                        return;
                    }
                    this->removeChild(health[2], TRUE);
                    return;
                }
                this->removeChild(health[1], TRUE);
                return;
            }
            else if (SlimeMe->gethealth() <= 0)
            {
                this->removeChild(health[0], TRUE);
            }
            return;
        }
    }
    //先计算x方向的距离，然后让敌人先在x轴走向玩家
    if (x < 0)
    {
        enemy->setRotationSkewY(180);
        enemy->setPosition(enemy->getPosition().x - 7, enemy->getPosition().y);
        enemy->run();
    }
    else if (x > 100)
    {
        enemy->setRotationSkewY(0);
        enemy->setPosition(enemy->getPosition().x + 7, enemy->getPosition().y);
        enemy->run();
    }
    //当x方向距离已经足够靠近，则敌人开始移动y方向靠近玩家
    else if (x <= 100)
    {
        if (SlimeMe->getPosition().y > enemy->getPosition().y)
        {
            enemy->setRotationSkewY(0);
            enemy->setPosition(enemy->getPosition().x, enemy->getPosition().y + 7);
            enemy->run();
        }
        else if (SlimeMe->getPosition().y < enemy->getPosition().y)
        {
            enemy->setRotationSkewY(0);
            enemy->setPosition(enemy->getPosition().x, enemy->getPosition().y - 7);
            enemy->run();
        }
    }
    enemy->endAttack();
}


//碰撞检测
bool GameScene::isRectCollision(cocos2d::Rect rect1, cocos2d::Rect rect2)
{
    float x1 = rect1.origin.x;
    float y1 = rect1.origin.y;
    float w1 = rect1.size.width;
    float h1 = rect1.size.height;
    float x2 = rect2.origin.x;
    float y2 = rect2.origin.y;
    float w2 = rect2.size.width;
    float h2 = rect2.size.height;

    if (x1 + w1 * 0.5 < x2 - w2 * 0.5)return false;
    else if (x1 - w1 * 0.5 > x2 + w2 * 0.5)return false;
    else if (y1 + h1 * 0.5 < y2 - h2 * 0.5)return false;
    else if (y1 - h1 * 0.5 > y2 + h2 * 0.5)return false;

    return true;
}

void GameScene::update(float dt)
{
    if (EnemySkull->isAttack)//当敌人在攻击时
    {
        if (!SlimeMe->isDead)
        {
            if(abs(y) < 50)//计算y方向距离，然后进行碰撞检测
            {
                Rect r1 = Rect(SlimeMe->getPosition().x, SlimeMe->getPosition().y, SlimeMe->getContentSize().width, SlimeMe->getContentSize().height);
                Rect r2 = Rect(EnemySkull->getPosition().x, EnemySkull->getPosition().y, EnemySkull->getContentSize().width, EnemySkull->getContentSize().height);
                if (this->isRectCollision(r1, r2));
                {
                    SlimeMe->hurt();//玩家受伤
                }//这里玩家的受伤检测做的不好，玩家靠近在敌人并且敌人在攻击时玩家就会受到持续伤害。
            }     
        }
    }
    if (SlimeBullet == nullptr)return;
    else if (SlimeBullet->isFlying)//如果子弹在飞
    {
  
        if (!EnemySkull->isDead)//子弹的碰撞检测基本没有，不知道为什么用了几种检测方法都没有效果，现在子弹不管射哪里敌人都会收到伤害。。。。
        {
            EnemySkull->hurt();//敌人受伤
        }
    }
   
}