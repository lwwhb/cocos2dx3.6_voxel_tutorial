#include "HelloWorldScene.h"
#include "EffectSprite3D.h"
#include "OutlineEffect3D.h"
#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"
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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello Voxel", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    label->setColor(Color3B::BLUE);
    this->addChild(label, 1);

    auto size = Director::getInstance()->getVisibleSize();
    
    //创建摄像机
    m_pMainCamera = Camera::createPerspective(45, size.width/size.height, 1, 5000);
    if(!m_pMainCamera)
        return false;
    Vec3 camPos = Vec3(0,150.0f*cosf(M_PI/2.8f),150.0f*sinf(M_PI/2.8f));
    Vec3 lookAt = Vec3(0,0,0);
    m_pMainCamera->setPosition3D(camPos);
    m_pMainCamera->lookAt(lookAt);
    this->addChild(m_pMainCamera);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    
    ///创建天空盒子
    Skybox* skyBox = Skybox::create("sky4.png", "sky4.png", "sky4.png", "sky4.png", "sky4.png", "sky4.png");
    if(!skyBox)
        return false;
    skyBox->setScale(1000);    ///注意大于创建摄像机的最远面
    skyBox->setCameraMask((unsigned short)CameraFlag::USER1);   ///设置职能被创建的摄像机看到
    skyBox->setGlobalZOrder(-1);
    this->addChild(skyBox);
    
    ///创建环境光
    AmbientLight* ambientLight = AmbientLight::create(Color3B(150, 150, 150));
    this->addChild(ambientLight);
    ///设置天光
    DirectionLight* directionLight = DirectionLight::create(Vec3(-2, -4, -3), Color3B(158, 158, 158));
    this->addChild(directionLight);

    auto label1 = Label::createWithTTF("Without outline", "fonts/Marker Felt.ttf", 16);
    label1->setPosition(Vec2(origin.x + visibleSize.width*0.2f,
                            origin.y + visibleSize.height*0.8f - label->getContentSize().height));
    label1->setColor(Color3B::BLUE);
    this->addChild(label1, 1);

    
    ///创建无描边体素对象
    Sprite3D* spriteWithoutOutLine = Sprite3D::create("bear.c3b");
    if(!spriteWithoutOutLine)
        return false;
    spriteWithoutOutLine->setPosition3D(Vec3(-50,0,0));
    spriteWithoutOutLine->setRotation3D(Vec3(0,-140,0));
    spriteWithoutOutLine->setCameraMask((unsigned short)CameraFlag::USER1);

    spriteWithoutOutLine->setForceDepthWrite(true);
    this->addChild(spriteWithoutOutLine);
    
    DelayTime* delay = DelayTime::create(1.0f);
    EaseSineInOut* moveTo1 = EaseSineInOut::create(MoveTo::create(3.0f, Vec3(-55, 0, 5)));
    EaseSineInOut* moveTo2= EaseSineInOut::create(MoveTo::create(3.0f, Vec3(-50, 5, 0)));
    Sequence* sequence1 = Sequence::create(moveTo1, moveTo2, delay, NULL);
    RepeatForever* repeat1 = RepeatForever::create(sequence1);
    spriteWithoutOutLine->runAction(repeat1);

    
    auto label2 = Label::createWithTTF("With outline", "fonts/Marker Felt.ttf", 16);
    label2->setPosition(Vec2(origin.x + visibleSize.width*0.5f,
                             origin.y + visibleSize.height*0.8f - label->getContentSize().height));
    label2->setColor(Color3B::BLUE);
    this->addChild(label2, 1);
    
    ///创建有描边体素对象
    EffectSprite3D* spriteWitOutLine = EffectSprite3D::create("girl1.c3b");
    if(!spriteWitOutLine)
        return false;
    spriteWitOutLine->setPosition3D(Vec3(0,0,0));
    spriteWitOutLine->setRotation3D(Vec3(0,-150,0));
    spriteWitOutLine->setCameraMask((unsigned short)CameraFlag::USER1);
    
    spriteWithoutOutLine->setForceDepthWrite(true);
    this->addChild(spriteWitOutLine);
    
    OutlineEffect3D* outline = OutlineEffect3D::create();
    outline->setOutlineColor(Vec3(0.3f, 0.3f, 0.3f));
    outline->setOutlineWidth(0.03f);
    spriteWitOutLine->addEffect(outline, 3); ///设置外描边
    
    EaseSineInOut* moveTo3 = EaseSineInOut::create(MoveTo::create(3.0f, Vec3(-5, 0, 5)));
    EaseSineInOut* moveTo4= EaseSineInOut::create(MoveTo::create(3.0f, Vec3(0, 5, 0)));
    Sequence* sequence2 = Sequence::create(moveTo3, delay, moveTo4, NULL);
    RepeatForever* repeat2 = RepeatForever::create(sequence2);
    spriteWitOutLine->runAction(repeat2);
    
    auto label3 = Label::createWithTTF("With particle3D", "fonts/Marker Felt.ttf", 16);
    label3->setPosition(Vec2(origin.x + visibleSize.width*0.8f,
                             origin.y + visibleSize.height*0.8f - label->getContentSize().height));
    label3->setColor(Color3B::BLUE);
    this->addChild(label3, 1);
    ///设置粒子爆炸对象
    EffectSprite3D* spriteWitParticle = EffectSprite3D::create("girl2.c3b");
    if(!spriteWitParticle)
        return false;
    spriteWitParticle->setPosition3D(Vec3(50,0,0));
    spriteWitParticle->setRotation3D(Vec3(0,-160,0));
    spriteWitParticle->setCameraMask((unsigned short)CameraFlag::USER1);
    
    spriteWitParticle->setForceDepthWrite(true);
    this->addChild(spriteWitParticle);
    
    outline = OutlineEffect3D::create();
    outline->setOutlineColor(Vec3(0.3f, 0.3f, 0.3f));
    outline->setOutlineWidth(0.03f);
    spriteWitParticle->addEffect(outline, 3); ///设置外描边
    
    EaseSineInOut* moveTo5 = EaseSineInOut::create(MoveTo::create(3.0f, Vec3(45, 0, 5)));
    EaseSineInOut* moveTo6= EaseSineInOut::create(MoveTo::create(3.0f, Vec3(50, 5, 0)));
    CallFunc* callFunc1 = CallFunc::create(CC_CALLBACK_0(HelloWorld::spawnExplosion, this, spriteWitParticle->getPosition3D()));
    CallFunc* callFunc2 = CallFunc::create(CC_CALLBACK_0(EffectSprite3D::setVisible, spriteWitParticle, false));
    CallFunc* callFunc3 = CallFunc::create(CC_CALLBACK_0(EffectSprite3D::setVisible, spriteWitParticle, true));
    Sequence* sequence3 = Sequence::create(delay, moveTo5, callFunc1, callFunc2, moveTo6, callFunc3, NULL);
    RepeatForever* repeat3 = RepeatForever::create(sequence3);
    spriteWitParticle->runAction(repeat3);

    m_pRainbow = RibbonTrail::create("ribbontrail.png", 150, 2000);
    if(!m_pRainbow)
        return false;
    m_pRainbow->setPosition3D(Vec3(0, 25, -800));
    m_pRainbow->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(m_pRainbow);
    m_pRainbow->getTrail()->addNode(m_pRainbow);
    
    m_fTime = 0;
    Vec3 pos = m_pRainbow->getPosition3D();
    Vec3 target = m_pMainCamera->getPosition3D() + Vec3(0, -66, 0);
    m_fDirDist = target - pos;

    return true;
}
void HelloWorld::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
}
void HelloWorld::onExit()
{
    unscheduleUpdate();
    Layer::onExit();
}
void HelloWorld::update(float delta)
{
    if(m_pRainbow)
    {
        m_fTime += delta;
        if(m_fTime <=2.0f)
        {
            Vec3 pos = m_pRainbow->getPosition3D();
            Vec3 target = m_pMainCamera->getPosition3D() + Vec3(0, -66, 0);
            pos = pos + m_fDirDist*delta*0.5f - Vec3(0, cosf(M_PI*(m_fTime-0.5f))*200*delta, 0);
            m_pRainbow->setPosition3D(pos);
            m_pRainbow->update(delta);
        }
    }
}

void HelloWorld::spawnExplosion(const cocos2d::Vec3& pos)
{
    auto explosion = PUParticleSystem3D::create("explosionSystem.pu");
    if(!explosion)
        return;
    explosion->setCameraMask((unsigned short)CameraFlag::USER1);
    explosion->setPosition3D(pos);
    explosion->setScale(2.0f);
    this->addChild(explosion);
    explosion->startParticleSystem();
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
