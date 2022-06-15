#pragma once

#include "cocos2d.h"
#include <ui/UIScrollView.h>

class CrossSprite;

class HelloWorld : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    bool init() override;
    void update(float deltaTime) override;

    CREATE_FUNC(HelloWorld);

    //bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*) override;


private:
    cocos2d::Sprite* apple{nullptr};
    std::vector<cocos2d::Sprite*> cross;

    cocos2d::Sprite* createCross(const cocos2d::Vec2& pos, const cocos2d::Vec2& origin);
};

class VisualStudioOstream
{
public:
	VisualStudioOstream& operator<<(int val);
	VisualStudioOstream& operator<<(std::string& val);
	VisualStudioOstream& operator<<(char val);
	VisualStudioOstream& operator<<(char* val);

    template <class T>
    void _OutputDebugString(T& val)
    {
        _outputDebugString(std::to_string(val).c_str());
    }
    template <class T>
    void _OutputDebugString(T*& val)
    {
        _outputDebugString(std::to_string(*val).c_str());
    }

private:
    void _outputDebugString(const char* text);
private:
};

template <>
inline void VisualStudioOstream::_OutputDebugString(char& val)
{
    _outputDebugString(std::string(1, val).c_str());
}
template <>
inline void VisualStudioOstream::_OutputDebugString(std::string& val)
{
    _outputDebugString(val.c_str());
}

template <class T, class CharT = char,
    class Traits = std::char_traits<CharT> >
class VisualStudioOstreamIterator
{
public: // usings
    using value_type = void;
    using difference_type = std::ptrdiff_t;
    using reference = void;
    using pointer = void;
    using iterator_category = std::output_iterator_tag;
    using char_type = CharT;
    using traits_type = Traits;
    using ostream_type = VisualStudioOstream;

public: // methods
    VisualStudioOstreamIterator() :_ptr(nullptr), _delim(nullptr)
    {

    }
    VisualStudioOstreamIterator(ostream_type& vtp, char_type* delim = nullptr) :_ptr(std::addressof(vtp)), _delim(delim)
    {

    }
    VisualStudioOstreamIterator& operator=(const T& value)
    {
        *_ptr << value;
        if (_delim != 0)
            *_ptr << _delim;
        return *this;
    }
    VisualStudioOstreamIterator& operator* ()
    {
        return *this;
    }
    VisualStudioOstreamIterator& operator++()
    {
        return *this;
    }
    VisualStudioOstreamIterator& operator++(int)
    {
        return *this;
    }

private: // members
    ostream_type* _ptr;
    char_type* _delim;
};


