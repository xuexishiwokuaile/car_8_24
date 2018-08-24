/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "json/document.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}



// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	tileMap = TMXTiledMap::create("level1.tmx");
	tileMap->setAnchorPoint(Vec2::ZERO);
	tileMap->setPosition(Vec2::ZERO);
	addChild(tileMap, -1);

	///*rapidjson::Document document;

	//std::string filePath = FileUtils::getInstance()->fullPathForFilename("pest.data");
	//std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
	//document.Parse<0>(contentStr.c_str());


	//const rapidjson::Value& pathArray = document["path"];
	//for (int i = 0; i < pathArray.Size(); i++) {
	//	 ���ÿ�����ﾭ��·����x��yֵ
	//	int x = pathArray[i]["x"].GetInt();
	//	int y = pathArray[i]["y"].GetInt();
	//	 ����x��yֵ����һ�����꣬��������һ����ͼ����
	//	Vec2 tilePoint = Vec2(x, y);
	//	 ����ͼ����ת����Ļ����
	//	Vec2 locationPoint = locationForTilePos(tilePoint);
	//	 ����Point���̳�Ref��Vector���ܴ洢�����������PointDelegate�����洢����
	//	auto pointDelegate = PointDelegate::create(locationPoint.x, locationPoint.y);
	//	 ��ÿһ����Ļ����洢��·�����ϵ���
	//	pathPoints.pushBack(pointDelegate);
	//}*/
//
//	/////////////////////////////
//	// 2. add a menu item with "X" image, which is clicked to quit the program
//	//    you may modify it.
//
//	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	
	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Fuck World", "Consolas", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	//// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("pest.png");

	//// position the sprite on the center of the screen
	//sprite->setPosition(Vec2(85,85));
	////visibleSize.width / 5.8 + origin.x, visibleSize.height / 3.9 + origin.y

	//// add the sprite as a child to this layer
	//this->addChild(sprite, 0);

	//move to�ƶ�
		
	schedule(schedule_selector(HelloWorld::MoveTo), 1.0f);

	return true;
}
//
//
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::MoveTo(float dt)
{
	Size size = Director::getInstance()->getWinSize();
	Sprite *spriteMoveTo = Sprite::create("pest.png");
	spriteMoveTo->setPosition(Vec2(75, 78));
	spriteMoveTo->setAnchorPoint(Point(0.5, 0.5));
	Size size_back = spriteMoveTo->getContentSize();
	float scaleX = (float)size.width*0.06f / (float)size_back.width;
	float scaleY = (float)size.height*0.06f / (float)size_back.height;
	spriteMoveTo->setScale(scaleX, scaleY);
	this->addChild(spriteMoveTo, 1);

	ActionInterval *forward_1 = MoveTo::create(2, Vec2(75, 285));
	ActionInterval *forward_2 = MoveTo::create(2, Vec2(405, 285));
	ActionInterval *forward_3 = MoveTo::create(2, Vec2(405, 75));

	Action* action = Sequence::create(forward_1, forward_2, forward_3, NULL);
	spriteMoveTo->runAction(action);

}

void HelloWorld::timer(float dt)
{
	schedule(schedule_selector(HelloWorld::MoveTo), 1.0f);
}


Vec2 Game::locationForTilePos(Vec2 pos)
{
    int x = (int)(pos.x*(tileMap->getTileSize().width/CC_CONTENT_SCALE_FACTOR()));
	float pointHeight = tileMap->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (int)((tileMap->getMapSize().height * pointHeight) - (pos.y * pointHeight));
	return Vec2(x,y);
}

// ��OpenGL����ת��ΪTileMap����
Vec2 Game::tileCoordForPosition(Vec2 position)
{
	// CC_CONTENT_SCALE_FACTOR ��iPhone������Ĥ��ʾ����2�����򷵻�1
	// ���λ�õ�x���Ե�ͼ�Ŀ��õ����ǵ�ͼ����ĵڼ������ӣ�tile��
	int x = (int)(position.x / (tileMap->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
	// ���λ�õ�y���Ե�ͼ�ĸߣ��õ����ǵ�ͼ����ڼ������ӣ�tile����
	// ��ΪCocos2d-x��y���TileMap��y���෴������ʹ�õ�ͼ�ĸ߶ȼ�ȥ���λ�õ�y
	float pointHeight = tileMap->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (int)((tileMap->getMapSize().height * pointHeight - position.y) / pointHeight);
	return Vec2(x, y);
}

//

//void updateMonster(float delta)
//{
//	monsterMoveWithWayPoints(pathPoints,monster)
//}

void monsterMoveWithWayPoints(Vector<PointDelegate*> pathVector, Monster* monster)
{
	// ���嶯�����ϣ�����������moveTo����
	Vector<FiniteTimeAction*> actionVector;
	// ѭ��·���㼯�ϣ��������MoveTo��������ҽ�ִ�ж��MoveTo��������ƶ�
	for (int i = 0; i < pathVector.size(); i++) {
		// �����Ҫ�ƶ���ÿһ����
		PointDelegate* pd = pathVector.at(i);
		Vec2 glPoint = Vec2(pd->getX(), pd->getY());
		// ����MoveToһ���������þ�������ƶ���ָ����λ��
		MoveTo* moveTo = MoveTo::create(0.2f, glPoint);
		// ��MoveTo������ӵ���ʱ����
		actionVector.pushBack(moveTo);
	}
	//// ��ȡ��������
	//std::string monsterName = monster->getName();
	//size_t iPos = monsterName.find(".png");
	//monsterName = monsterName.substr(0, iPos);
	//// ����getAnimateByName���������Ҿ����ƶ�����
	//auto animate = getAnimateByName(monsterName, 0.5f, 5);
	//// ����һ���������ظ�ִ��Animate����
	/*auto repeatanimate = RepeatForever::create(animate);*/
	//// ��Ҿ����ظ�ִ�ж�������
	//monster->runAction(repeatanimate);
	//// �����ص���������MoveTo������ɺ���ָ����վ��״̬
	//auto callfunc = CallFunc::create([=] {
	//	// ֹͣ����
	//	monster->stopAction(repeatanimate);
	//});
	//actionVector.pushBack(callfunc);
	//// ��˳��ִ�ж��������еĶ���
	//auto sequence = Sequence::create(actionVector);
	//// ִ��һϵ�еĶ���
	//monster->runAction(sequence);
}
