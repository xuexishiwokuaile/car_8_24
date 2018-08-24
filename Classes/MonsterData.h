#ifndef __ProtectPrincess__MonsterData__
#define __ProtectPrincess__MonsterData__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

// MonsterData类，用来存储关卡的怪物信息
// "monsters": [{"name":"pest.png","lifeValue":2,"gold":15}]
class MonsterData : public Ref
{
private:
    std::string name; // 怪物名称
    int lifeValue;  // 怪物的生命值
    int gold; // 消灭怪物获得的金币
public:
    // 静态的create函数           创建怪物精灵
    static MonsterData* create()
    {
        MonsterData *sprite = new MonsterData();
        if (sprite)
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    // setter和getter函数
    void setName(std::string Name){ name = Name; }
    std::string getName(){ return name; }
    
    void setLifeValue(int LifeValue){ lifeValue = LifeValue; }
    int getLifeValue(){ return lifeValue; }
    
    void setGold(int Gold){ gold = Gold; }
    int getGold(){ return gold; }
    
};


#endif /* defined(__ProtectPrincess__MonsterData__) */
