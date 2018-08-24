#pragma once
#ifndef __ProtectPrincess__Monster__
#define __ProtectPrincess__Monster__

#include <iostream>
#include "cocos2d.h"
#include "SpriteBase.h"
#include "ui/CocosGUI.h"
using namespace ui;

// 怪物类
class Monster : public SpriteBase
{
public:

	// 静态的create函数
	static Monster* create(const std::string& filename)
	{
		Monster *sprite = new Monster();
		if (sprite && sprite->initWithFile(filename))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	static Monster* createWithSpriteFrameName(const std::string& filename)
	{
		Monster *sprite = new Monster();
		if (sprite && sprite->initWithSpriteFrameName(filename))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
};

#endif /* defined(__ProtectPrincess__Monster__) */
