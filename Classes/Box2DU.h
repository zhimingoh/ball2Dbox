#pragma  once
#include "cocos2d.h"
#include "../../../../external/Box2D/Box2D.h"
USING_NS_CC;
class Box2DU :public cocos2d::CCLayer
{
public:
	CREATE_FUNC(Box2DU);

	static b2Body* createDynamicBody(float posx,float posy,void* userData,b2World* _world)
	{
		b2BodyDef ballBodyDef;
		ballBodyDef.type=b2_dynamicBody;
		ballBodyDef.position.Set(posx,posy);
		ballBodyDef.userData=userData;
		b2Body* ball=_world->CreateBody(&ballBodyDef);
		return ball;
	}
	static b2Fixture* createFixture(b2Shape* shape, float density,float friction,float rrestitution,b2Body* ball)
	{
		b2FixtureDef ballFixDef;
		ballFixDef.shape=shape;
		ballFixDef.density=density;
		ballFixDef.friction=friction;
		ballFixDef.restitution=rrestitution;
		return ball->CreateFixture(&ballFixDef);


	}
	//Box2DU::~Box2DU(void);
	bool init();
};