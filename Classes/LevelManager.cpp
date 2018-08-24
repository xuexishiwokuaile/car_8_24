#include "LevelManager.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* LevelManager::createScene()
{
	// ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto scene = Scene::create();

	// ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto layer = LevelManager::create();

	// ��LevelManager����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);

	// ���س�������
	return scene;
}

//  "init" �����г�ʼ��ʵ��
bool LevelManager::init()
{
	// ���ø����init����
	if (!Layer::init())
	{
		return false;
	}

	// ����豸֧�ֵĿɼ�OpenGL��ͼ��С�������ڴ�С����
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// ��ÿɼ�OpenGL��ͼ����Դ�㣨Ĭ��x=0��y=0����
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ���һ���رղ˵�����������˳�����
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",       
		"CloseSelected.png",                      //����ͼƬ
		CC_CALLBACK_1(LevelManager::menuCloseCallback, this));
	// ���ùر�ͼ������Ļ��λ��
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));              //origin��Դ��

	// ����һ���˵��Menu�����ö�����Զ������ڴ���ͷ�
	auto menu = Menu::create(closeItem, NULL);
	// ���ò˵�������Ļ��λ��
	menu->setPosition(Vec2::ZERO);
	// ���˵�����ӵ���ǰ����ӽڵ�
	this->addChild(menu, 1);

	// Ĭ��ѡ���1�أ������±��0��ʼ
	selectLevelIndex = 0;

	//������ҳ������PageView
	auto pageView = PageView::create();
	// ����PageView��ContentSize
	pageView->setContentSize(Size(480.0f, 320.0f));
	// ����PageView����Ļ����λ��
	pageView->setPosition(Vec2((visibleSize.width - pageView->getContentSize().width) / 2.0f,
		(visibleSize.height - pageView->getContentSize().height)*0.6));
	// ѭ�����3��Layout���ؿ�ͼƬ��                 ��ѡ����
	for (int i = 0; i < 3; ++i)
	{
		// ����һ��Layout
		Layout* layout = Layout::create();
		// ����Layout��ContentSize
		layout->setContentSize(Size(480.0f, 320.0f));
		// ����һ��ImageView
		ImageView* imageView = ImageView::create(StringUtils::format("preview%d.png", i + 1));              //ͼƬ
		imageView->setContentSize(Size(480.0f, 320.0f));
		imageView->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
		// ��ImageView���ΪLayout���ӽڵ�
		layout->addChild(imageView);
		// ��i��ʾ��λ���ϲ���Layout
		pageView->insertPage(layout, i);
	}
	// ����¼�������
	pageView->addEventListener([=](Ref* pSender, PageView::EventType type) {
		switch (type)
		{
		case PageView::EventType::TURNING:
		{
			PageView* pageView = dynamic_cast<PageView*>(pSender);
			// CurPageIndex��Ӧ�ľ��ǵ�ǰ�ؿ�������
			selectLevelIndex = pageView->getCurPageIndex();
		}
		break;

		default:
			break;
		}
	});
	// ��PageView���Ϊ������ӽڵ�
	this->addChild(pageView, 1);

	

	return true;
}


void LevelManager::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif
	// ����ִ�н���,�ͷ����г�����
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}