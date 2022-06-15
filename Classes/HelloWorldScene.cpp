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
        apple->setOpacity(100);

        // add the sprite as a child to this layer
        this->addChild(apple, 0);
    }

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this, origin, visibleSize](Touch* _touch, Event* _event) -> bool {
        std::ostringstream oss;
        auto pos = _touch->getLocation();
        oss << "Mouse pos: " << pos.x << ":" << pos.y << std::endl;
        std::istringstream iss(oss.str());
        iss >> std::noskipws;
        VisualStudioOstream vsOstream;
        std::copy(std::istream_iterator<char>(iss), std::istream_iterator<char>(), VisualStudioOstreamIterator<char>(vsOstream));

        auto _child = createCross(pos, origin);
        cross.emplace_back(_child);
        this->addChild(_child);
        
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

    std::transform(cross.begin(), cross.end(), cross.begin(), [deltaTime](auto& _cross)
        {
            _cross->setOpacity(_cross->getOpacity() - 35 * deltaTime);
            return _cross;
        }
    );
    cross.erase(std::remove_if(cross.begin(), cross.end(), [](auto& _cross)
        {
            return _cross->getOpacity() <= 0;
        }
    ), cross.end());
}

cocos2d::Sprite* HelloWorld::createCross(const cocos2d::Vec2& pos, const cocos2d::Vec2& origin)
{
    auto pathCross = std::filesystem::weakly_canonical(std::filesystem::path("fruits") / std::filesystem::path("error.png")).string();
    auto _cross = Sprite::create(pathCross);
    if (_cross == nullptr)
    {
        //problemLoading("'error.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        //cross->setAnchorPoint(cocos2d::Vec2(0, 1));
        _cross->setPosition(cocos2d::Vec2(origin.x + pos.x,
            origin.y + pos.y));
        _cross->setContentSize(Size(100, 100));

        //// add the sprite as a child to this layer
        //this->addChild(_cross, 0);
    }
    return _cross;
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

// ј–’»“≈ “”–Ќќ ѕ–ј¬»Ћ№Ќќ !!!
// физически выбрасывать спрайт с падением вниз
// рандомный выбор фрукта
// клик по фрутку - удал€ем, показываем крестик(плавное затухание), мимо фрукта - крестик (плавное затухание)
// наращивание количества фруктов
// наращивание скорости
// проработать уровни
// метка со счетчиком попаданий и промахов
// мультитач дл€ Android
// может быть плавный вылет?