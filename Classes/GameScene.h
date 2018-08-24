#pragma once
#ifndef __ProtectPrincessGame__GameScene__
#define __ProtectPrincessGame__GameScene__

#include <iostream>
#include "cocos2d.h"
//#include "PointDelegate.h"
//#include "SpriteBase.h"
//#include "Monster.h"
//#include "Turret.h"
//#include "Bullet.h"
//#include "SimpleAudioEngine.h"
//#include "MonsterData.h"
//#include "TurretData.h"
//#include "json/document.h"
//#include "LevelManager.h"
//#include "GameMenuScene.h"

USING_NS_CC;
//using namespace CocosDenshion;

// 游戏逻辑类
class Game : public cocos2d::Layer
{
protected:
	TMXTiledMap * tileMap;  // 地图
	TMXLayer* collidable;  // 障碍层
	std::string tileFile; // 关卡地图名称
	int number; // 关卡共出现多少波怪物
	int currentCount; // 当前出现怪物数量
	int currNum; // 当前出现怪物波数
	int goldValue; // 玩家当前的金币值
	Sprite* grandFather; // 爷爷
	int screenWidth, screenHeight;  // 屏幕宽度和高度
	int count;  // 游戏帧计数器
	int delivery; // 出现怪物取模基数

//	Vector<MonsterData*> monsterDatas; // 当前关卡的怪物信息
//	Vector<TurretData*> turretDatas; // 当前关卡的炮塔信息
//	Vector<PointDelegate*> pathPoints; // 记录有效路径的点
//
//	Label* numberLabel; // 显示怪物波数的标签
//	Label* currNumLabel; // 显示当前怪物波数的标签
//	Label* goldLabel; // 显示当前玩家金币的标签
//
//	Vector<Monster*> monsterVector;  // 存储出现怪物的集合
//	bool _isFinish = false; // 关卡所有怪物是否全部出现标记
//	bool _isSelect = false; // 判断用户触碰是选择位置还是建造炮塔
//
//	Vector<Turret*> turretVector; // 炮塔集合，存放已经添加的炮塔
//	Vector<Bullet*> bulletVector; // 炮弹集合
//
//public:
//	static cocos2d::Scene* createSceneWithLevel(int selectLevel);

	/**
	* init函数，完成初始化操作。
	*/
	virtual bool init();

	// TileMap坐标转换为OpenGL坐标
	Point locationForTilePos(Point pos);
	// 将OpenGL坐标转换为TileMap坐标
	Point tileCoordForPosition(Point position);

	// 回调更新函数，该函数每一帧都会调用
	void update(float delta);

	///**
	//* 获得动画动作
	//* animName：动画帧的名字
	//* delay：动画帧与帧之间的间隔时间
	//* animNum：动画帧的数量
	//*/
	//Animate* getAnimateByName(std::string animName, float delay, int animNum);
	///**
	//* 怪物根据路径点移动
	//* pathVector：从关卡json文件中获取的路径集合
	//* monster：移动的怪物
	//*/
	//void monsterMoveWithWayPoints(Vector<PointDelegate*> pathVector, Monster* monster);
	//// 更新HUD
	//void updateHUD(float delta);
	//// 随机出现怪物
	//void updateMonster(float delta);


	///**
	//* 检测攻击范围，true表示进入攻击范围，false表示没有进入攻击范围
	//* monsterPoint 怪物所在的坐标点
	//* turretPoint 炮塔所在的坐标点
	//* area 攻击范围
	//*/
	//bool checkPointInCircle(Point monsterPoint, Point turretPoint, int area);
	///**
	//* 发射炮弹时计算炮弹的旋转方向，返回表示旋转方向的浮点数
	//* monsterPoint 怪物所在的坐标点
	//* turret 炮塔
	//*/
	//float getTurretRotation(Point monsterPoint, Turret* turret);
	///**
	//* 根据炮弹移动距离计算炮弹需要移动时间，返回表示时间的浮点数
	//* start 炮弹移动的开始坐标
	//* end 炮弹移动的结束坐标
	//*/
	//float getBulletMoveTime(Point start, Point end);       //返回时间
	//// 检测坐标点是否障碍
	//bool getCollidable(Point position);                    
	//// 检测炮塔
	//void detectionTurret(float delta);

	//// 检测碰撞
	//void collisionDetection(float delta);
	//// 检测爷爷
	//void detectionGrandFather(float delta);

	///**
	//游戏结束，tag，0表示游戏失败，1表示游戏胜利
	//*/
	//void gameOver(int tag);

	/**
	* 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
	*/
	CREATE_FUNC(Game);
};

#endif /* defined(__ProtectPrincessGame__GameScene__) */