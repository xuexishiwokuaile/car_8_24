#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

static int monsterCount = 5; // ÿһ�����ֶ��ٹ���       5��Ŀǰ
static int currentLevel = 1;  // ��ǰ�ؿ�

Scene* Game::createSceneWithLevel(int selectLevel)
{
	// ��ùؿ���
	currentLevel = selectLevel;

	// ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto scene = Scene::create();

	// ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto layer = Game::create();

	// ��Game����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);

	// ���س�������
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// ����豸֧�ֵĿɼ�OpenGL��ͼ��С�������ڴ�С����
	Size visibleSize = Director::getInstance()->getVisibleSize();
	screenWidth = visibleSize.width;
	screenHeight = visibleSize.height;

	/*************��ȡ�ؿ����ݿ�ʼ**********************/
	// rapidjson����
	rapidjson::Document document;
	// �ؿ�����ʹ��json��Cocos2d-X 3.0���Դ���rapidjson�����ڽ���Json��
	// ���ݴ��ݵĹؿ�ֵ������Ӧ�Ĺؿ������ļ�
	std::string filePath = FileUtils::getInstance()->fullPathForFilename(StringUtils::format("%d.data", currentLevel));     //��Ӧ��data�ļ�
	std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
	document.Parse<0>(contentStr.c_str());

	// ��ȡ��ͼ�ļ�����               (level.data)
	tileFile = document["tileFile"].GetString();
	// ��ȡ���ﲨ��
	number = document["number"].GetInt();
	// ���ֹ���ȡģ����
	delivery = 55;
	// ��ǰ���ֹ�������
	currentCount = 0;
	// ��ǰ���ﲨ��
	currNum = 1;
	// ��ʼ���������
	goldValue = 200;

	// ����TMXTiledMap�ĺ�����ȡTileMap.tmx�ļ�����һ����Ƭ��ͼ����
	tileMap = TMXTiledMap::create(tileFile);
	// �ѵ�ͼ��ê���λ�ö�����Ϊԭ�㣬��������ʹ��ͼ�����½�����Ļ�����½Ƕ���
	tileMap->setAnchorPoint(Vec2::ZERO);
	tileMap->setPosition(Vec2::ZERO);
	// ����ͼ���Ϊ��ǰ����ӽڵ�
	this->addChild(tileMap, 1);

	// ��ȡ�ϰ��㣬�������ϰ���Ϊ���ɼ�
	collidable = tileMap->getLayer("collidable");
	collidable->setVisible(false);

//	// ��ùؿ��趨�Ĺ���
//	const rapidjson::Value& monsterArray = document["monsters"];
//	for (int i = 0; i < monsterArray.Size(); i++) {
//		// ���ÿһ�ֹ����name��lifeValue��gold����
//		std::string name = monsterArray[i]["name"].GetString();
//		int lifeValue = monsterArray[i]["lifeValue"].GetInt();
//		int gold = monsterArray[i]["gold"].GetInt();
//		// ����õ�name��lifeValue��gold���ݴ洢���Զ���MonsterData������
//		auto monsterData = MonsterData::create();
//		monsterData->setName(name);
//		monsterData->setLifeValue(lifeValue);
//		monsterData->setGold(gold);
//		// ��MonsterData�洢���ؿ��������ݵļ��ϵ���
//		monsterDatas.pushBack(monsterData);
//	}
//	// ��ùؿ��趨������
//	const rapidjson::Value& turretArray = document["turrets"];
//	for (int i = 0; i < turretArray.Size(); i++) {
//		// ���ÿһ�ֹ����name��gold��bulletName����
//		std::string name = turretArray[i]["name"].GetString();
//		int gold = turretArray[i]["gold"].GetInt();
//		std::string bulletName = turretArray[i]["bulletName"].GetString();
//		// ����õ�name��gold��bulletName���ݴ洢���Զ���TurretData������
//		auto turretData = TurretData::create();
//		turretData->setName(name);
//		turretData->setGold(gold);
//		turretData->setBulletName(bulletName);
//		// ��TurretData�洢���ؿ��������ݵļ��ϵ���
//		turretDatas.pushBack(turretData);
//	}
//	// ��ù��ﾭ����·��
//	const rapidjson::Value& pathArray = document["path"];
//	for (int i = 0; i < pathArray.Size(); i++) {
//		// ���ÿ�����ﾭ��·����x��yֵ
//		int x = pathArray[i]["x"].GetInt();
//		int y = pathArray[i]["y"].GetInt();
//		// ����x��yֵ����һ�����꣬��������һ����ͼ����
//		Vec2 tilePoint = Vec2(x, y);
//		// ����ͼ����ת����Ļ����
//		Vec2 locationPoint = locationForTilePos(tilePoint);
//		// ����Point���̳�Ref��Vector���ܴ洢�����������PointDelegate�����洢����
//		auto pointDelegate = PointDelegate::create(locationPoint.x, locationPoint.y);
//		// ��ÿһ����Ļ����洢��·�����ϵ���
//		pathPoints.pushBack(pointDelegate);
//	}
//	// �������ΪgrandFatherObject�Ķ����
//	auto grandFatherObject = tileMap->getObjectGroup("grandFatherObject");
//	// �������ΪgrandFather�ĵ�ͼ���󣬸ö����ڵ�ͼ��λ�þ���үү���ֵ�λ��
//	ValueMap grandFatherValueMap = grandFatherObject->getObject("grandFather");
//	int grandFatherX = grandFatherValueMap.at("x").asInt();
//	int grandFatherY = grandFatherValueMap.at("y").asInt();             //����
//	// ����������������ͼ�ж����x��yֵ��Ϊүү���ֵ�λ��
//	grandFather = Sprite::createWithSpriteFrameName("grandFather.png");
//	grandFather->setPosition(grandFatherX, grandFatherY);
//	// ��үү���Ϊ��ͼ���ӽڵ�
//	tileMap->addChild(grandFather, 2);
//
//	/*************��ȡ�ؿ����ݽ���**********************/
//
//	/*************������Ļ�Ϸ���ʾ����Ϸ���ݿ�ʼ**********************/
//
//	// ��ʾ�����˶��ٲ������ǰ��
//	currNumLabel = Label::createWithSystemFont("0", "Arial", 32);
//	currNumLabel->setColor(Color3B::RED);
//	currNumLabel->setPosition(screenWidth*0.45, screenHeight*0.96);
//	tileMap->addChild(currNumLabel, 2);                     //���Ϊ��ͼ���ӽڵ�
//	// �����ٲ�����
//	numberLabel = Label::createWithSystemFont(StringUtils::format("/%d������", number), "Arial", 32);
//	numberLabel->setColor(Color3B::BLUE);
//	numberLabel->setPosition(screenWidth*0.55, screenHeight*0.96);
//	tileMap->addChild(numberLabel, 2);                      //���Ϊ��ͼ���ӽڵ�
//
//	// ���Ͻ���ҽ������
//	auto gold = Sprite::createWithSpriteFrameName("gold.png");
//	gold->setPosition(50, screenHeight*0.96);               
//	tileMap->addChild(gold, 2);                             //���Ϊ��ͼ���ӽڵ�
//
//	goldLabel = Label::createWithSystemFont("200", "Arial", 32);
//	goldLabel->setColor(Color3B::RED);
//	goldLabel->setPosition(100, screenHeight*0.96);
//	tileMap->addChild(goldLabel, 2);                        //���Ϊ��ͼ���ӽڵ�
//
//	// Ԥ��׼���ÿɽ�������� add.png
//	auto addImage = Sprite::create("add.png");
//	addImage->setScale(0.75);                               //����
//	addImage->setVisible(false);
//	tileMap->addChild(addImage, 1);
//	// ���ɽ����������ΪaddImage���ӽڵ�
//	for (unsigned int i = 0; i<turretDatas.size(); i++) {
//		// ѭ���������ݵļ��ϻ�ȡÿһ������
//		auto data = turretDatas.at(i);
//		// ��������
//		auto turret = Turret::create(data->getName());
//		turret->setGold(data->getGold());
//		turret->setScale(1.8);
//		turret->setPosition(60 * i, addImage->getContentSize().height*1.5 + 10);
//		// ���������ΪaddImage���ӽڵ�
//		addImage->addChild(turret);
//	}
//
//	// �����¼�������
//	auto gameListener = EventListenerTouchOneByOne::create();
//	// ��Ӧ�����¼�����
//	gameListener->onTouchBegan = [=](Touch* touch, Event* event) {
//		// OpenGL����
//		Vec2 touchLocation = touch->getLocation();
//		// ���addImage�����ӽڵ㣨��������
//		Vector<Node*> turrets = addImage->getChildren();
//		for (unsigned int i = 0; i<turrets.size(); i++) {
//			// ���ÿһ������
//			auto node = turrets.at(i);
//			Rect rect = Rect(0, 0, node->getContentSize().width, node->getContentSize().height);
//			Turret* turret = (Turret*)node;
//			// ���addImage��ʾ��˵������ǵڶ��δ�����ѡ��������
//			if (addImage->isVisible()) {
//				// ���������ҽ�������������false
//				if (turret->getGold() > _goldValue) {
//					_isSelect = false;
//					addImage->setVisible(false);
//					return false;
//				}
//				else {
//					// ������Խ�������������_isSelect=true
//					if (rect.containsPoint(node->convertToNodeSpace(touchLocation))) {
//						addImage->setTag(i);
//						_isSelect = true;
//						return true;
//					}
//				}
//			}
//			// ����ǵ�һ�δ���
//			else
//			{
//				// �������������Ҳ�������������͸���ȣ���ʾ���ɽ���
//				if (turret->getGold() > _goldValue) {
//					turret->setOpacity(100);
//				}
//			}
//		}
//		return true;
    };
//	gameListener->onTouchEnded = [=](Touch *touch, Event *event) {
//		// OpenGL����
//		Vec2 touchLocation = touch->getLocation();
//		// ���Node������
//		Vec2 nodeLocation = this->convertToNodeSpace(touchLocation);
//		// ͬһ��λ���ϲ��ܷ�������
//		for (int i = 0; i < _turretVector.size(); i++) {
//			auto temp = _turretVector.at(i);
//			if (temp->getBoundingBox().containsPoint(nodeLocation)) {
//				return;
//			}
//		}
//		// _isSelectΪtrue���û���ѡ����������false���û�ѡ����������λ��
//		if (_isSelect) {
//			_isSelect = false;
//			// ����һ����������
//			TurretData *data = _turretDatas.at(addImage->getTag());
//			Turret *turret = Turret::create(data->getName());
//			turret->setScale(1.8);
//			// ������������addImage��λ����
//			turret->setPosition(addImage->getPosition());
//			turret->setBulletName(data->getBulletName());
//			_tileMap->addChild(turret, 1);
//			// ����addImage
//			addImage->setVisible(false);
//			// ��������ӵ���������
//			_turretVector.pushBack(turret);
//			// ���ѽ��
//			_goldValue -= data->getGold();
//		}
//		else {
//			// ���׼������������λ�ò����ϰ���ʱ
//			if (!this->getCollidable(nodeLocation)) {
//				// addImage��ʾ
//				addImage->setVisible(true);
//				// ����addImageλ��Ϊ����λ��
//				addImage->setPosition(nodeLocation);
//			}
//		}
    };
//
//	// ��ӳ��������¼�������
//	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(gameListener, this);
//
//	// ��ʼ��Ϸ������3��
//	Label* label1 = Label::createWithSystemFont("1", "Arial-BoldMT", 150);
//	Label* label2 = Label::createWithSystemFont("2", "Arial-BoldMT", 150);
//	Label* label3 = Label::createWithSystemFont("3", "Arial-BoldMT", 150);
//	label1->setColor(Color3B::BLUE);
//	label2->setColor(Color3B::BLUE);
//	label3->setColor(Color3B::BLUE);
//	label1->setPosition(screenWidth / 2, screenHeight / 2);
//	label2->setPosition(screenWidth / 2, screenHeight / 2);
//	label3->setPosition(screenWidth / 2, screenHeight / 2);
//	// ����Label����ʾ
//	label1->setVisible(false);
//	label2->setVisible(false);
//	label3->setVisible(false);
//	tileMap->addChild(label1, 2);
//	tileMap->addChild(label2, 2);
//	tileMap->addChild(label3, 2);
//	// ��ɵ�����Sequence������3��2��1��ÿ��1����ʾ1�����֣�ͬʱɾ��֮ǰ��ʾ������
//	auto countdown = Sequence::create(
//		CallFunc::create([=] {
//		label3->setVisible(true);
//	}), DelayTime::create(1), CallFunc::create([=] {
//		tileMap->removeChild(label3);
//	}), CallFunc::create([=] {
//		label2->setVisible(true);
//	}), DelayTime::create(1), CallFunc::create([=] {
//		tileMap->removeChild(label2);
//	}), CallFunc::create([=] {
//		label1->setVisible(true);
//	}), DelayTime::create(1), CallFunc::create([=] {
//		tileMap->removeChild(label1);
//		// ��Ϸ��ѭ����ʼ
//		scheduleUpdate();
//	}), NULL);
//	// ִ�е�������
//	this->runAction(countdown);
//
//	// ���ű�������
//	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);
//	// ���ñ������ִ�С
//	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
//
//	/*************������Ļ�Ϸ���ʾ����Ϸ���ݽ���**********************/
//
//	return true;
//}
//
//// ��Ϸ��ѭ��
//void Game::update(float delta) {
//	count++;
//	updateMonster(delta);
//	detectionTurret(delta);
//	collisionDetection(delta);
//	detectionPrincess(delta);
//	updateHUD(delta);
//}
//
//
//// TileMap����ת��ΪOpenGL����
//Vec2 Game::locationForTilePos(Vec2 pos) {
//	int x = (int)(pos.x*(tileMap->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
//	float pointHeight = _tileMap->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
//	int y = (int)((_tileMap->getMapSize().height * pointHeight) - (pos.y * pointHeight));
//	return Vec2(x, y);
//}
//
//// ��OpenGL����ת��ΪTileMap����
//Vec2 Game::tileCoordForPosition(Vec2 position) {
//	// CC_CONTENT_SCALE_FACTOR ��iPhone������Ĥ��ʾ����2�����򷵻�1
//	// ���λ�õ�x���Ե�ͼ�Ŀ��õ����ǵ�ͼ����ĵڼ������ӣ�tile��
//	int x = (int)(position.x / (tileMap->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
//	// ���λ�õ�y���Ե�ͼ�ĸߣ��õ����ǵ�ͼ����ڼ������ӣ�tile����
//	// ��ΪCocos2d-x��y���TileMap��y���෴������ʹ�õ�ͼ�ĸ߶ȼ�ȥ���λ�õ�y
//	float pointHeight = _tileMap->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
//	int y = (int)((_tileMap->getMapSize().height * pointHeight - position.y) / pointHeight);
//	return Vec2(x, y);
//}
//
//
///**
//* ��ö�����������
//* animName������֡������
//* delay������֡��֮֡��ļ��ʱ��
//* animNum������֡������
//*/
//Animate* Game::getAnimateByName(std::string animName, float delay, int animNum) {
//	// ��������
//	Animation* animation = Animation::create();
//	// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
//	for (unsigned int i = 1; i <= animNum; i++) {
//		// ��ȡ����ͼƬ���ƣ�����pest1.png
//		std::string frameName = animName;
//		frameName.append(StringUtils::format("%d.png", i));
//		// ������ͼƬ���Ϊ����֡��������֡��
//		animation->addSpriteFrameWithFile(frameName.c_str());
//	}
//	// ���ö������ŵ�����
//	animation->setDelayPerUnit(delay);
//	// �þ�������ڶ���ִ�����ָ������״̬
//	animation->setRestoreOriginalFrame(true);
//	// ���ض�����������
//	Animate* animate = Animate::create(animation);
//	return animate;
//}
//
//void Game::updateHUD(float delta) {
//	// ���½������
//	_goldLabel->setString(StringUtils::format("%d", _goldValue));
//	// ���¹��ﲨ����
//	_currNumLabel->setString(StringUtils::format("%d", _currNum));
//	// ����ÿһ������Ѫ��λ�ã�Ѫ����������ƶ�
//	for (unsigned int i = 0; i < _monsterVector.size(); i++) {
//		auto monster = _monsterVector.at(i);
//		// ������ﲻΪnullptr�����ҹ�������ֵ��Ϊ0��ʱ��
//		if (monster != nullptr && monster->getLifeValue() > 0) {
//			// ���ﾫ������
//			Vec2 pos = monster->getPosition();
//			// ���ù���Ѫ����ʾ������λ��
//			monster->getHP()->setPosition(Vec2(pos.x, pos.y + 40));
//		}
//	}
//}
//
//void Game::updateMonster(float delta) {
//	// isFinish���Ϊfalse��ʾ���Գ��ֹ���
//	if (!isFinish) {
//		// delivery����Ϊȡģ������ͨ�����øñ���ֵ�����Կ��ƹ������Ƶ��
//		if (count % delivery == 0) {
//			// ��ǰ���ֹ���������1   ��һ�ζ�һ����
//			currentCount++;
//			// �����ǰ���ֹ�����������ÿһ�����ֶ��ٹ����ʾһ������
//			if (currentCount > monsterCount) {
//				// �ؿ������ܲ�����1
//				number -= 1;
//				// ���ؿ������ܲ���Ϊ0
//				if (number == 0) {
//					// ���ñ�ǣ���ʾ�ؿ����й���ȫ���������
//					isFinish = true;
//				}
//				else {
//					// ���¿�ʼһ������
//					currentCount = 0; // ��ǰ���ֹ�����������
//					delivery -= 5; // �ı�ȡģ���������������ٶȼӿ�
//					currNum += 1; // ��ǰ���ֹ��ﲨ����1
//				}
//			}
//			else {
//				// ����TMXTiledMap��getObjectGroup������ȡ�����
//				auto pestObject = tileMap->getObjectGroup("monsterObject");
//				// ���ݶ������ƻ�ȡ�������Ϣ
//				ValueMap pestValueMap = pestObject->getObject("monster");
//				// ��ȡ��ͼ�����õ�player�����x��yֵ
//				int pestX = pestValueMap.at("x").asInt();
//				int pestY = pestValueMap.at("y").asInt();
//				/**
//				* һ���ؿ����ܳ��ֶ��ֹ��������json�ļ�������
//				* ����������ﾫ�飬������ͼ�ж����x��yֵ��Ϊ������ֵ�λ��
//				*/
//				int random = arc4random() % monsterDatas.size();
//				auto monsterData = monsterDatas.at(random);
//				// ���ݹ������ƴ�������
//				auto monster = Monster::create(monsterData->getName());
//
//				// ���ù������ơ�����ֵ���������Ľ��ֵ�͹����������
//				monster->setName(monsterData->getName());
//				monster->setLifeValue(monsterData->getLifeValue());
//				monster->setGold(monsterData->getGold());
//				monster->setScale(0.7);
//				monster->setPosition(pestX, pestY);
//
//				// ����������
//				auto loadingBar = LoadingBar::create("planeHP.png");
//				// ���ý���������
//				loadingBar->setDirection(LoadingBar::Direction::LEFT);
//				// ���ý�������С
//				loadingBar->setScale(0.06f, 0.1f);
//				// ���ý������ٷֱ�
//				loadingBar->setPercent(100);
//				// ������������Ϊ����Ѫ��
//				monster->setHP(loadingBar);
//				// ��ӹ���Ѫ��
//				tileMap->addChild(monster->getHP(), 2);
//				// ����Ѫ��������
//				monster->setHPInterval(100 / monster->getLifeValue());
//				// ��������Ϊ��ͼ�ӽڵ�
//				tileMap->addChild(monster, 2);
//				// ��������ӵ��ѳ��ֹ�������
//				monsterVector.pushBack(monster);
//				// �������·�����ƶ�
//				monsterMoveWithWayPoints(pathPoints, monster);
//			}
//		}
//	}
//	else {
//		// isFinish���Ϊtrue��ʾ�ؿ����й����Ѿ��������
//		if (monsterVector.size() <= 0) {
//			// ��Ϸʤ��
//			gameOver(1);
//		}
//	}
//}
//
//
///**
//* �������·�����ƶ�
//* pathVector���ӹؿ�json�ļ��л�ȡ��·������
//* monster���ƶ��Ĺ���
//*/
//void Game::monsterMoveWithWayPoints(Vector<PointDelegate*> pathVector, Monster* monster) {
//	// ���嶯�����ϣ�����������moveTo����
//	Vector<FiniteTimeAction*> actionVector;
//	// ѭ��·���㼯�ϣ��������MoveTo��������ҽ�ִ�ж��MoveTo��������ƶ�
//	for (int i = 0; i < pathVector.size(); i++) {
//		// �����Ҫ�ƶ���ÿһ����
//		PointDelegate* pd = pathVector.at(i);
//		Vec2 glPoint = Vec2(pd->getX(), pd->getY());
//		// ����MoveToһ���������þ�������ƶ���ָ����λ��
//		MoveTo* moveTo = MoveTo::create(0.2f, glPoint);
//		// ��MoveTo������ӵ���ʱ����
//		actionVector.pushBack(moveTo);
//	}
//	// ��ȡ��������
//	std::string monsterName = monster->getName();
//	size_t iPos = monsterName.find(".png");
//	monsterName = monsterName.substr(0, iPos);
//	// ����getAnimateByName���������Ҿ����ƶ�����
//	auto animate = getAnimateByName(monsterName, 0.5f, 5);
//	// ����һ���������ظ�ִ��Animate����
//	auto repeatanimate = RepeatForever::create(animate);
//	// ��Ҿ����ظ�ִ�ж�������
//	monster->runAction(repeatanimate);
//	// �����ص���������MoveTo������ɺ���ָ����վ��״̬
//	auto callfunc = CallFunc::create([=] {
//		// ֹͣ����
//		monster->stopAction(repeatanimate);
//	});
//	actionVector.pushBack(callfunc);
//	// ��˳��ִ�ж��������еĶ���
//	auto sequence = Sequence::create(actionVector);
//	// ִ��һϵ�еĶ���
//	monster->runAction(sequence);
//}
//
//// �������
//void Game::detectionTurret(float delta) {
//	// ������������
//	for (unsigned int i = 0; i < turretVector.size(); i++) {
//		// ���ÿһ������
//		auto turret = turretVector.at(i);
//		// ��Ϸ�趨����һ��ֻ�ܷ���һö�ڵ����������û�й����ڵ������ڵ��Ѿ��������
//		if (turret->getBullet() == nullptr || !turret->getBullet()->isShoot()) {
//			// �������Ｏ��
//			for (unsigned int j = 0; j < monsterVector.size(); j++) {
//				auto monster = monsterVector.at(j);
//				// �������Ƿ��������Ĺ�����Χ
//				bool flag = checkPointInCircle(monster->getPosition(), turret->getPosition(), 200);
//				if (flag) {
//					// �����ڵ�
//					auto bullet = Bullet::createWithSpriteFrameName(turret->getBulletName());
//					bullet->setScale(0.8);
//					bullet->setPosition(turret->getPosition().x, turret->getPosition().y);
//					tileMap->addChild(bullet, 2);
//					// �����Ҫ��ת�ĽǶ�
//					float cocosAngle = getTurretRotation(monster->getPosition(), turret);
//					// �����ڵ����䷽����ת����
//					turret->runAction(RotateTo::create(0.05, cocosAngle));
//					// �����ڵ��ƶ���ʱ�䣬������Ϊ���볤�̶�����ڵ����е��ٶ�����
//					float duration = getBulletMoveTime(bullet->getPosition(), monster->getPosition());
//					// �ڵ��ƶ�����
//					auto moveTo = MoveTo::create(duration, monster->getPosition());
//					bullet->runAction(moveTo);
//					// ���ڵ���ӵ��ڵ�����
//					bulletVector.pushBack(bullet);
//					// �����ڵ�������
//					bullet->setShoot(true);
//					//  �����������ڵ�����
//					turret->setBullet(bullet);
//					break;
//				}
//			}
//
//		}
//	}
//}
//
//bool Game::getCollidable(Vec2 position)
//{
//	// ����Ļ����ת�ɵ�ͼ���꣬�����ж��Ƿ���Է�������
//	Vec2 tilePos = tileCoordForPosition(position);
//	// ����������ǲ��ɷ��������������ϰ����λ�ã���ֱ��return
//	int tileGid = collidable->getTileGIDAt(tilePos);
//	if (tileGid) {
//		// ʹ��GID������ָ��tile�����ԣ�����һ��Value
//		Value properties = tileMap->getPropertiesForGID(tileGid);
//		// ���ص�Valueʵ����һ��ValueMap
//		ValueMap map = properties.asValueMap();
//		// ����ValueMap���ж��Ƿ����ϰ������У�ֱ�ӷ���
//		std::string value = map.at("collidable").asString();
//		if (value.compare("true") == 0) {
//			return true;
//		}
//	}
//	return false;
//}
//
///**
//* ����Ϸ����Բ�εĹ�����Χ��ֱ�Ӽ���������ڵ�����㵽�������ڵ������ľ������ڹ����뾶���ɡ�
//* ���һ���Ƿ���Բ�ڲ�
//* monsterPoint �������ڵ������
//* turretPoint �������ڵ������
//* area ������Χ
//*/
//bool Game::checkPointInCircle(Vec2 monsterPoint, Vec2 turretPoint, int area)
//{
//	int x = monsterPoint.x - turretPoint.x;
//	int y = monsterPoint.y - turretPoint.y;
//	// sqrt������ƽ����
//	if (sqrt(x * x + y * y) <= area) return true;             //����Ƿ���Բ��
//	return false;
//}
//
//// �����ڵ��ƶ���������ڵ���Ҫ�ƶ�ʱ��
//float Game::getBulletMoveTime(Vec2 start, Vec2 end) {
//	// �������յ������ת��ΪTileMap����
//	Vec2 tileStart = tileCoordForPosition(start);
//	Vec2 tileEnd = tileCoordForPosition(end);
//	// �ƶ�һ�������ʱ��
//	float duration = 0.1f;
//	// �����ƶ���������ƶ�ʱ��
//	duration = duration * sqrtf((tileStart.x - tileEnd.x) * (tileStart.x - tileEnd.x)
//		+ (tileStart.y - tileEnd.y) * (tileStart.y - tileEnd.y));
//	return duration;
//}
//
///**
//* �����ڵ�ʱ�����ڵ�����ת����
//* monsterPoint �������ڵ������
//* turret ����
//*/
//float Game::getTurretRotation(Vec2 monsterPoint, Turret* turret) {
//	// ����ת�ĽǶȣ���Ҫʹ�����Ǵ����������� = ���� / �ڱ�
//	// monsterPoint.x�����������x�ᣬturret->getPosition().x�����������x��
//	int offX = monsterPoint.x - turret->getPosition().x;
//	// monsterPoint.y�����������y�ᣬturret->getPosition().y�����������y��
//	int offY = monsterPoint.y - turret->getPosition().y;
//	// ��ת���� = atan2f(�����к���)������/�ڱߣ�
//	float radian = atan2f(offY, offX);
//	// CC_RADIANS_TO_DEGREES�������Խ�����ת��Ϊ�Ƕ�
//	float degrees = CC_RADIANS_TO_DEGREES(radian);
//	// ת�����ĽǶȺͱ����ڵ�ͼƬ���90�ȣ���ˣ�Ϊ�˵õ���ȷ�ķ������ǰ���Ҫ���������ת����
//	return 90 - degrees;
//}
//
//// ����ڵ��͹������ײ
//void Game::collisionDetection(float delta) {
//	// ������������
//	for (unsigned int i = 0; i < monsterVector.size(); i++) {
//		Monster* monster = monsterVector.at(i);
//		// �����ڵ�����
//		for (unsigned int j = 0; j < bulletVector.size(); j++) {
//			auto bullet = bulletVector.at(j);
//			// ����������ڵ���������ײ
//			if (monster->getBoundingBox().intersectsRect(bullet->getBoundingBox())) {
//				// ���ù��������ֵ��1
//				monster->setLifeValue(monster->getLifeValue() - 1);
//				// ���¹���Ѫ��
//				if (monster->getHP() != nullptr) {
//					monster->getHP()->setPercent(monster->getHpInterval()*monster->getLifeValue());
//				}
//				// �����������ֵΪ0
//				if (monster->getLifeValue() <= 0) {
//					// ���Ź��ﱻ�������Ч
//					SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE1);
//					// �ӹ��Ｏ����ɾ������
//					monsterVector.eraseObject(monster);
//					// �ӵ�ͼ��ɾ������
//					tileMap->removeChild(monster);
//					// �������
//					goldValue += monster->getGold();
//				}
//				// ���ڵ�������ɾ���ڵ�
//				bulletVector.eraseObject(bullet);
//				// �ӵ�ͼ��ɾ���ڵ�
//				tileMap->removeChild(bullet);
//				// �޸��ڵ�������
//				bullet->setShoot(false);
//				break;
//			}
//			else {
//				// ����ڵ����﹥�����꣬�������Ѿ��߿������ڵ�û�д��й���     ???�������
//				if (bullet->getNumberOfRunningActions() == 0) {            //�������??
//					// ɾ���ڵ�
//					bulletVector.eraseObject(bullet);
//					// �ӵ�ͼ��ɾ���ڵ�
//					tileMap->removeChild(bullet);
//					// �޸��ڵ�������
//					bullet->setShoot(false);
//				}
//			}
//		}
//	}
//}
//
//// ���үү
//void Game::detectionGrandFather(float delta) {
//	// ����ÿһ������
//	for (unsigned int j = 0; j < monsterVector.size(); j++) {
//		auto monster = monsterVector.at(j);
//		// ��������빥��үү����Ϸʧ��
//		if (monster->getBoundingBox().containsPoint(grandFather->getPosition())) {
//			// ��Ϸʧ��
//			gameOver(0);
//		}
//	}
//}
//
//
//// ��Ϸ����
//void Game::gameOver(int tag) {
//
//	// ֹͣ��Ϸ��ѭ��
//	this->unscheduleUpdate();
//	// ֹͣ���й��ﶯ��
//	for (unsigned int i = 0; i < monsterVector.size(); i++) {
//		auto monster = monsterVector.at(i);
//		monster->stopAllActions();
//	}
//	// ɾ����Ļ�����ڵ�
//	for (unsigned int i = 0; i < bulletVector.size(); i++) {
//		auto bullet = bulletVector.at(i);
//		bullet->stopAllActions();
//		tileMap->removeChild(bullet);
//	}
//	bulletVector.clear();
//
//	// ѡ����Ļ��
//	auto temp = Sprite::createWithSpriteFrameName("block.png");
//	temp->setPosition(screenWidth / 2, screenHeight / 2);
//	temp->setColor(Color3B::GRAY);
//	tileMap->addChild(temp, 2);
//
//	// ֹͣ��������
//	SimpleAudioEngine::getInstance()->stopBackgroundMusic(MUSIC_FILE);
//
//	// �㹲������10������!
//	auto messageLabel = Label::createWithSystemFont(StringUtils::format("�㹲������[%d]������!", currNum), "Arial-BoldMT", 38);
//	messageLabel->setColor(Color3B::WHITE);
//	messageLabel->setPosition(screenWidth / 2, screenHeight / 2 + 50);
//	tileMap->addChild(messageLabel, 4);
//
//	// ��ѡ��ؿ�����ť
//	auto select_button = Button::create("btn-select.png");
//	select_button->setPosition(Vec2(screenWidth / 2 - 100, screenHeight / 2 - 80));
//	select_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
//		if (type == Widget::TouchEventType::ENDED) {
//			// �ұ߻���糡Ч��
//			auto transition = TransitionSlideInR::create(2.0, LevelManager::createScene());
//			// push��Ϸ����
//			Director::getInstance()->pushScene(transition);
//		}
//	});
//	this->addChild(select_button, 3);
//
//	// ������һ�Ρ���"������һ��"��ť
//	auto play_button = Button::create();
//	if (tag == 1) {
//		// ������һ��
//		play_button->loadTextures("btn-next.png", "btn-next.png");
//		currentLevel++;
//	}
//	else {
//		// ����һ��
//		// ������Ϸʧ����Ч
//		SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE2);
//		play_button->loadTextures("btn-again.png", "btn-again.png");
//	}
//	play_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
//		if (type == Widget::TouchEventType::ENDED) {
//			// TransitionSplitRows ���һ����糡Ч��
//			auto transition = TransitionSplitRows::create(2.0, Game::createSceneWithLevel(_currentLevel));
//			// push��Ϸ����
//			Director::getInstance()->pushScene(transition);
//		}
//	});
//	play_button->setPosition(Vec2(screenWidth / 2 + 100, screenHeight / 2 - 80));
//	this->addChild(play_button, 3);
//}