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
	//	 获得每个怪物经过路径的x和y值
	//	int x = pathArray[i]["x"].GetInt();
	//	int y = pathArray[i]["y"].GetInt();
	//	 根据x和y值创建一个坐标，该坐标是一个地图坐标
	//	Vec2 tilePoint = Vec2(x, y);
	//	 将地图坐标转成屏幕坐标
	//	Vec2 locationPoint = locationForTilePos(tilePoint);
	//	 由于Point不继承Ref，Vector不能存储，所以设计了PointDelegate类代理存储数据
	//	auto pointDelegate = PointDelegate::create(locationPoint.x, locationPoint.y);
	//	 将每一个屏幕坐标存储到路径集合当中
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

	//move to移动
		
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

// 将OpenGL坐标转换为TileMap坐标
Vec2 Game::tileCoordForPosition(Vec2 position)
{
	// CC_CONTENT_SCALE_FACTOR 在iPhone上视网膜显示返回2。否则返回1
	// 玩家位置的x除以地图的宽，得到的是地图横向的第几个格子（tile）
	int x = (int)(position.x / (tileMap->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
	// 玩家位置的y除以地图的高，得到的是地图纵向第几个格子（tile），
	// 因为Cocos2d-x的y轴和TileMap的y轴相反，所以使用地图的高度减去玩家位置的y
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
	// 定义动作集合，用来保存多个moveTo动作
	Vector<FiniteTimeAction*> actionVector;
	// 循环路径点集合，创建多个MoveTo动作，玩家将执行多个MoveTo动作完成移动
	for (int i = 0; i < pathVector.size(); i++) {
		// 获得需要移动的每一个点
		PointDelegate* pd = pathVector.at(i);
		Vec2 glPoint = Vec2(pd->getX(), pd->getY());
		// 创建MoveTo一个动作，让精灵对象移动到指定的位置
		MoveTo* moveTo = MoveTo::create(0.2f, glPoint);
		// 将MoveTo动作添加到临时数组
		actionVector.pushBack(moveTo);
	}
	//// 截取怪物名称
	//std::string monsterName = monster->getName();
	//size_t iPos = monsterName.find(".png");
	//monsterName = monsterName.substr(0, iPos);
	//// 调用getAnimateByName函数获得玩家精灵移动动画
	//auto animate = getAnimateByName(monsterName, 0.5f, 5);
	//// 创建一个动作，重复执行Animate动画
	/*auto repeatanimate = RepeatForever::create(animate);*/
	//// 玩家精灵重复执行动画动作
	//monster->runAction(repeatanimate);
	//// 创建回调动作，当MoveTo动作完成后精灵恢复最初站立状态
	//auto callfunc = CallFunc::create([=] {
	//	// 停止动画
	//	monster->stopAction(repeatanimate);
	//});
	//actionVector.pushBack(callfunc);
	//// 按顺序执行动作集合中的动作
	//auto sequence = Sequence::create(actionVector);
	//// 执行一系列的动作
	//monster->runAction(sequence);
}
