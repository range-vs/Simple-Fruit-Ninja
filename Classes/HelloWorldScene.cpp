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
    apple = Sprite::create(pathApple);
    if (apple == nullptr)
    {
        //problemLoading("'apple.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        apple->setAnchorPoint(cocos2d::Vec2(0, 1));
        apple->setPosition(cocos2d::Vec2(origin.x + 10,
            origin.y + visibleSize.height - 10));
        apple->setContentSize(Size(100, 100));

        // add the sprite as a child to this layer
        this->addChild(apple, 0);
    }

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* _touch, Event* _event) -> bool {
        std::ostringstream oss;
        auto pos = _touch->getLocation();
        oss << "Mouse pos: " << pos.x << ":" << pos.y << std::endl;
        std::istringstream iss(oss.str());
        iss >> std::noskipws;
        VisualStudioOstream vsOstream;
        std::copy(std::istream_iterator<char>(iss), std::istream_iterator<char>(), VisualStudioOstreamIterator<char>(vsOstream));
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto touchListenerApple = EventListenerTouchOneByOne::create();
	touchListenerApple->onTouchBegan = [this](Touch* _touch, Event* _event) -> bool {
		auto bounds = _event->getCurrentTarget()->getBoundingBox();
		auto pos = (_touch->getLocation());
		if (!bounds.containsPoint(pos))
			return false;
		pos = this->convertToWorldSpace(pos);
        std::ostringstream oss;
        oss << "Mouse pos: " << pos.x << ":" << pos.y << std::endl << "Is Apple!" << std::endl;;
        std::istringstream iss(oss.str());
        iss >> std::noskipws;
        VisualStudioOstream vsOstream;
        std::copy(std::istream_iterator<char>(iss), std::istream_iterator<char>(), VisualStudioOstreamIterator<char>(vsOstream));
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListenerApple, apple);

    this->scheduleUpdate();
    return true;
}

void HelloWorld::update(float deltaTime)
{
    Layer::update(deltaTime);
    auto oldPos = apple->getPosition();
    apple->setPosition(oldPos.x + (150 * deltaTime), oldPos.y);
}

VisualStudioOstream& VisualStudioOstream::operator<<(int val)
{
    _OutputDebugString(val);
    return *this;
}

VisualStudioOstream& VisualStudioOstream::operator<<(std::string& val)
{
    _OutputDebugString(val);
    return *this;
}

VisualStudioOstream& VisualStudioOstream::operator<<(char val)
{
    _OutputDebugString(val);
    return *this;
}

VisualStudioOstream& VisualStudioOstream::operator<<(char* val)
{
    _OutputDebugString(val);
    return *this;
}

void VisualStudioOstream::_outputDebugString(const char* text)
{
    OutputDebugStringA(text);
}

// клик по спрайту - спрайт исчезает, появляется ок на 3 секунды и плавно исчезает; вне спрайта - спрайт исчезает, появляется крестик на 3 секунды и плавно исчезает
// лейбл со счетчиком очков и промахов (клики по спрайтам и промахи)
// рандомный выбор стороны, откуда едут спрайты
// набор количества спрайтов, набор скорости
// рандомный выбор фигуры по C++ 17 

