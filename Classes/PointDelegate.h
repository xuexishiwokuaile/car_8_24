#pragma once
#ifndef __ProtectPrincess__PointDelegate__
#define __ProtectPrincess__PointDelegate__

#include <iostream>
#include "cocos2d.h"

// Point的代理类，继承cocos2d::Ref类
class PointDelegate : public cocos2d::Ref {
private:
	float x;
	float y;
public:
	static PointDelegate* create(float X, float Y) {
		PointDelegate* p = new PointDelegate();
		if (p && p->initPoint(X, Y)) {
			p->autorelease();
			return p;
		}
		CC_SAFE_DELETE(p);
		return nullptr;
	}
	bool initPoint(float X, float Y) {
		x = X;
		y = Y;
		return true;
	}
	void setX(float X) { x = X; }
	float getX() { return x; }

	void setY(float Y) { y = Y; }
	float getY() { return y; }

};

#endif /* defined(__ProtectPrincess__PointDelegate__) */