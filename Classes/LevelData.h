#pragma once
#ifndef __ProtectPrincess__LevelData__
#define __ProtectPrincess__LevelData__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

// LevelData类，用来存储关卡数据信息
// {"number": 1,"bg":"level1.png","data":"1.data"}
class LevelData : public Ref
{
protected:
	int number; // 关卡数量
	std::string bg; // 背景图片
	std::string data;  // 关卡的数据文件    (.data)
public:
	// 静态的create函数
	static LevelData* create(int number, std::string bg, std::string data)
	{
		LevelData *sprite = new LevelData();
		if (sprite)
		{
			sprite->autorelease();
			sprite->setNumber(number);
			sprite->setBg(bg);
			sprite->setData(data);
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	// setter和getter函数
	void setNumber(int Number) { number = Number; }
	int getNumber() { return number; }                  //获取关卡数

	void setBg(std::string Bg) { bg = Bg; }
	std::string getBg() { return bg; }

	void setData(std::string Data) { data = Data; }
	std::string getData() { return data; }

};


#endif /* defined(__ProtectPrincess__LevelData__) */