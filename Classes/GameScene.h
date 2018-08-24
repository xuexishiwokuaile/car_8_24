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

// ��Ϸ�߼���
class Game : public cocos2d::Layer
{
protected:
	TMXTiledMap * tileMap;  // ��ͼ
	TMXLayer* collidable;  // �ϰ���
	std::string tileFile; // �ؿ���ͼ����
	int number; // �ؿ������ֶ��ٲ�����
	int currentCount; // ��ǰ���ֹ�������
	int currNum; // ��ǰ���ֹ��ﲨ��
	int goldValue; // ��ҵ�ǰ�Ľ��ֵ
	Sprite* grandFather; // үү
	int screenWidth, screenHeight;  // ��Ļ��Ⱥ͸߶�
	int count;  // ��Ϸ֡������
	int delivery; // ���ֹ���ȡģ����

//	Vector<MonsterData*> monsterDatas; // ��ǰ�ؿ��Ĺ�����Ϣ
//	Vector<TurretData*> turretDatas; // ��ǰ�ؿ���������Ϣ
//	Vector<PointDelegate*> pathPoints; // ��¼��Ч·���ĵ�
//
//	Label* numberLabel; // ��ʾ���ﲨ���ı�ǩ
//	Label* currNumLabel; // ��ʾ��ǰ���ﲨ���ı�ǩ
//	Label* goldLabel; // ��ʾ��ǰ��ҽ�ҵı�ǩ
//
//	Vector<Monster*> monsterVector;  // �洢���ֹ���ļ���
//	bool _isFinish = false; // �ؿ����й����Ƿ�ȫ�����ֱ��
//	bool _isSelect = false; // �ж��û�������ѡ��λ�û��ǽ�������
//
//	Vector<Turret*> turretVector; // �������ϣ�����Ѿ���ӵ�����
//	Vector<Bullet*> bulletVector; // �ڵ�����
//
//public:
//	static cocos2d::Scene* createSceneWithLevel(int selectLevel);

	/**
	* init��������ɳ�ʼ��������
	*/
	virtual bool init();

	// TileMap����ת��ΪOpenGL����
	Point locationForTilePos(Point pos);
	// ��OpenGL����ת��ΪTileMap����
	Point tileCoordForPosition(Point position);

	// �ص����º������ú���ÿһ֡�������
	void update(float delta);

	///**
	//* ��ö�������
	//* animName������֡������
	//* delay������֡��֮֡��ļ��ʱ��
	//* animNum������֡������
	//*/
	//Animate* getAnimateByName(std::string animName, float delay, int animNum);
	///**
	//* �������·�����ƶ�
	//* pathVector���ӹؿ�json�ļ��л�ȡ��·������
	//* monster���ƶ��Ĺ���
	//*/
	//void monsterMoveWithWayPoints(Vector<PointDelegate*> pathVector, Monster* monster);
	//// ����HUD
	//void updateHUD(float delta);
	//// ������ֹ���
	//void updateMonster(float delta);


	///**
	//* ��⹥����Χ��true��ʾ���빥����Χ��false��ʾû�н��빥����Χ
	//* monsterPoint �������ڵ������
	//* turretPoint �������ڵ������
	//* area ������Χ
	//*/
	//bool checkPointInCircle(Point monsterPoint, Point turretPoint, int area);
	///**
	//* �����ڵ�ʱ�����ڵ�����ת���򣬷��ر�ʾ��ת����ĸ�����
	//* monsterPoint �������ڵ������
	//* turret ����
	//*/
	//float getTurretRotation(Point monsterPoint, Turret* turret);
	///**
	//* �����ڵ��ƶ���������ڵ���Ҫ�ƶ�ʱ�䣬���ر�ʾʱ��ĸ�����
	//* start �ڵ��ƶ��Ŀ�ʼ����
	//* end �ڵ��ƶ��Ľ�������
	//*/
	//float getBulletMoveTime(Point start, Point end);       //����ʱ��
	//// ���������Ƿ��ϰ�
	//bool getCollidable(Point position);                    
	//// �������
	//void detectionTurret(float delta);

	//// �����ײ
	//void collisionDetection(float delta);
	//// ���үү
	//void detectionGrandFather(float delta);

	///**
	//��Ϸ������tag��0��ʾ��Ϸʧ�ܣ�1��ʾ��Ϸʤ��
	//*/
	//void gameOver(int tag);

	/**
	* ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	*/
	CREATE_FUNC(Game);
};

#endif /* defined(__ProtectPrincessGame__GameScene__) */