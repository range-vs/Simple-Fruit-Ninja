#include "HelloWorldScene.h"

#include <CCFileUtils.h>

#include <iostream>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <filesystem>

#ifdef _WIN32
#include <tchar.h>
#endif // _WIN32

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pathApple = std::filesystem::weakly_canonical(std::filesystem::path("fruits") / std::filesystem::path("apple.png")).string();
    auto sprite = Sprite::create(pathApple);
    if (sprite == nullptr)
    {
        //problemLoading("'apple.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setAnchorPoint(cocos2d::Vec2(0, 1));
        sprite->setPosition(cocos2d::Vec2(origin.x + 10,
            origin.y + visibleSize.height - 10));
        sprite->setContentSize(Size(100, 100));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }


    return true;
}

// движение спрайтов из разных мест рандомом и скоростью и количеством - туду
// клик по одному спрайту - ок, вне - крестик
// лейбл со счетчиком очков и промахов
// 