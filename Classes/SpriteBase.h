#pragma once
#ifndef __ProtectPrincess__SpriteBase__
#define __ProtectPrincess__SpriteBase__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
// ��չ�����࣬����ͨ�õ�����
class SpriteBase : public cocos2d::Sprite
{
private:
	std::string name; // ���������
	int gold; // ����Ľ��ֵ
public:
	// ��̬��create����
	static SpriteBase* create(const std::string& filename)
	{
		SpriteBase *sprite = new SpriteBase();
		if (sprite && sprite->initWithFile(filename))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	static SpriteBase* createWithSpriteFrameName(const std::string& filename)
	{
		SpriteBase *sprite = new SpriteBase();
		if (sprite && sprite->initWithSpriteFrameName(filename))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	// setter��getter����
	void setName(std::string Name) { name = Name; }
	std::string getName() { return name; }

	void setGold(int Gold) { gold = Gold; }
	int getGold() { return gold; }
};

#endif /* defined(__ProtectPrincess__SpriteBase__) */