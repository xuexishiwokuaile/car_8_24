#pragma once
#ifndef __ProtectPrincess__LevelData__
#define __ProtectPrincess__LevelData__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

// LevelData�࣬�����洢�ؿ�������Ϣ
// {"number": 1,"bg":"level1.png","data":"1.data"}
class LevelData : public Ref
{
protected:
	int number; // �ؿ�����
	std::string bg; // ����ͼƬ
	std::string data;  // �ؿ��������ļ�    (.data)
public:
	// ��̬��create����
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
	// setter��getter����
	void setNumber(int Number) { number = Number; }
	int getNumber() { return number; }                  //��ȡ�ؿ���

	void setBg(std::string Bg) { bg = Bg; }
	std::string getBg() { return bg; }

	void setData(std::string Data) { data = Data; }
	std::string getData() { return data; }

};


#endif /* defined(__ProtectPrincess__LevelData__) */