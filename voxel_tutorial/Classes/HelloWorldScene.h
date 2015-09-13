#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "RibbonTrail.h"
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void spawnExplosion(const cocos2d::Vec3& pos);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
private:
    cocos2d::Vec3       m_fDirDist;
    cocos2d::Camera*    m_pMainCamera;
    float               m_fTime;
    RibbonTrail*        m_pRainbow;
};

#endif // __HELLOWORLD_SCENE_H__
