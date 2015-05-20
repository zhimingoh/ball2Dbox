#include "gamescene.h"
#include "Box2DU.h"

#define  PTM_RATIO 26.0f//26�����ض�Ӧһ��
USING_NS_CC;

bool gamescence::init()
{
	if (!CCLayer
		::init())
	{
		return false;
	}
	m_ball=CCSprite::create("ball.png");
	m_ball->setPosition(ccp(400,240));
	this->addChild(m_ball);
	_world=new b2World(b2Vec2(0,-2.0f));//重力加速度
	//b2BodyDef������Ϣ   b2Body

	ball=Box2DU::createDynamicBody(420/PTM_RATIO,400/PTM_RATIO,m_ball,_world);
	/*
	b2BodyDef ballBodyDef;
	ballBodyDef.type=b2_dynamicBody;
	ballBodyDef.position.Set(400/PTM_RATIO,240/PTM_RATIO);
	ballBodyDef.userData=m_ball;
	b2Body* ball=_world->CreateBody(&ballBodyDef);
	*/
	//������������ ��С ��״ �ܶ�
	b2CircleShape circle;
	circle.m_radius=(52/2)/PTM_RATIO;//��״ �뾶
	Box2DU::createFixture(&circle,3,0.2f,0.3f,ball);
	/*
	b2FixtureDef ballFixDef;
	ballFixDef.shape=&circle;
	ballFixDef.density=3;
	ballFixDef.friction=0.2;//Ħ��ϵ��
	ballFixDef.restitution=0.8;//����ϵ��
	ball->CreateFixture(&ballFixDef);
	*/
	CCSize screeenSize=CCDirector::sharedDirector()->getWinSize();

	//���ӵ���
	//b2bodydef���� b2body
	b2BodyDef groundBodyDef;
	groundBodyDef.type=b2_staticBody;//	��̬��
	groundBodyDef.position.Set(0,0);//�൱��ê��
	b2Body*  groundBody=_world->CreateBody(&groundBodyDef);//��������
	//b2FuxtureDef���� b2fixture
	//��״
	b2EdgeShape groundshape;
	groundshape.Set(b2Vec2(0,0),b2Vec2(screeenSize.width/PTM_RATIO,0));//����������յ�
	b2FixtureDef groundFixDef;
	groundFixDef.shape=&groundshape;
	groundBody->CreateFixture(&groundFixDef);//���Լ���ȥ
	//��������ǽ
	b2EdgeShape leftwall;
	leftwall.Set(b2Vec2(0,0),b2Vec2(0,screeenSize.height/PTM_RATIO));//����������յ�
	//b2FixtureDef groundFixDef;
	groundFixDef.shape=&leftwall;
	groundBody->CreateFixture(&groundFixDef);//���Լ���ȥ

	//�ұ�
	b2EdgeShape rightwall;
	rightwall.Set(b2Vec2(screeenSize.width/PTM_RATIO,0),b2Vec2(screeenSize.width/PTM_RATIO,screeenSize.height/PTM_RATIO));//����������յ�
	//b2FixtureDef groundFixDef;
	groundFixDef.shape=&rightwall;
	groundBody->CreateFixture(&groundFixDef);//���Լ���ȥ

	//����
	b2EdgeShape top;
	top.Set(b2Vec2(0,screeenSize.height/PTM_RATIO),
		b2Vec2(screeenSize.width/PTM_RATIO,screeenSize.height/PTM_RATIO));//����������յ�

	groundFixDef.shape=&top;
	groundBody->CreateFixture(&groundFixDef);//���Լ���ȥ

	this->scheduleUpdate();
	this->setTouchEnabled(true);
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);


	return true;
}
bool gamescence::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPos=pTouch->getLocation();
	b2Vec2 touchPhysicPos(touchPos.x/PTM_RATIO,touchPos.y/PTM_RATIO);//����������λ��
	b2Vec2 ballPhysicpos=ball->GetPosition();//�������λ��
	b2Vec2 impulse=touchPhysicPos-ballPhysicpos;    //impult=mass* velocity
	impulse *=(ball->GetMass());//��������
	ball->ApplyLinearImpulse(impulse,ball->GetWorldCenter());//Ϊ��ʩ�ӳ��� ����������
	return true;
}
void gamescence::update(float delta)//���������ʱ������
{
	_world->Step(delta,4,6);
	//
	for (b2Body* b=_world->GetBodyList();b;b=b->GetNext())
	{
		if (b->GetUserData())
		{
			b2Vec2 physicPos=b->GetPosition();//��ȡ����λ��
			CCSprite* sp=(CCSprite*)b->GetUserData();
			sp->setPosition(ccp(physicPos.x*PTM_RATIO,physicPos.y*PTM_RATIO));
			
		}
	}
}
cocos2d::CCScene* gamescence::scence()
{
	CCScene* cs=CCScene::create();
	gamescence* layer=gamescence::create();
	cs->addChild(layer);
	return cs;
}

void gamescence::onEnter()
{
	
CCDirector* pDirector = CCDirector::sharedDirector();

//���һ������ί�и�dispatcher���б�,ί�ж���this,

pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	CCNode::onEnter();
	
}/*

 bool gamescence::ccTouchBegan( cocos2d::CCTouch* touch, CCEvent* event)
 {
	 CCPoint loccInView=touch->getLocationInView();
	 CCPoint loc=CCDirector::sharedDirector()->convertToGL(loccInView);
	 CCLOG("%f",loc.x);
	 CCLOG("%f",loc.y);
	 
	 //m_ball->setPosition(ccp(loc.x,loc.y));
	// this->addChild(m_ball);
	 CCMoveTo* move=CCMoveTo::create(1,ccp(loc.x,loc.y));
	 m_ball->runAction(move);
	 return true;
 }
 */
