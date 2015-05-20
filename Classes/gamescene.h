#ifndef __GAMESCENCE_H__
#define __GAMESCENCE_H__

#include "cocos2d.h"
#include "../../../../external/Box2D/Box2D.h"
USING_NS_CC;
class gamescence :public cocos2d::CCLayer
{
	b2World* _world;//�������ٶ�
	b2Body* ball;

public:
	CREATE_FUNC(gamescence);
	static cocos2d::CCScene* scence();
	virtual bool init();  


	//�Ƴ������¼�����ֹ�ڴ����
	virtual void onEnter();
	//	virtual void   onExit();
	//	virtual void endRotate();
	//������Ӧ��д����������

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);//����
	//	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);//�϶�
	//	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);//�ɿ�
	CCSprite* m_ball;

	void update(float delta);
	//void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};
#endif