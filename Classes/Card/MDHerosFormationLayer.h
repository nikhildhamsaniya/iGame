#ifndef __HEROS_FORMATION_LAYER_H__
#define __HEROS_FORMATION_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "MainGameScene.h"
#include "MainLayerBase.h"
#include "SlidingMenu.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MDHerosFormationLayer : public MainLayerBase,
//	public CCTableViewDataSource,
//	public CCTableViewDelegate,
	public CCBSelectorResolver,
	public CCNodeLoaderListener,
	public CCBMemberVariableAssigner
{
public:
	MDHerosFormationLayer();
	~MDHerosFormationLayer();

	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MDHerosFormationLayer,create);

private:

	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	// a selector callback
	void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);
    
	void buttonClicked(CCObject * sender , CCControlEvent controlEvent);
	void menuItemCallback(CCObject* pSender);
	void doSearch();
	void touchUpInside(CCObject* pSender, CCControlEvent event);

    CCLabelTTF *m_lblFightCapacity;
};

#endif  // __HEROS_FORMATION_LAYER_H__