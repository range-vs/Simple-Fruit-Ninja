#pragma once

#include "cocos2d.h"
#include <ui/UIScrollView.h>

class HelloWorld : public cocos2d::Layer, std::basic_streambuf<char, std::char_traits<char>>
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(HelloWorld);

private:

};