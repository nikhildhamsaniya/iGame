#include "ChatLayer.h"
#include "MainGameScene.h"

using namespace cocos2d;

ChatLayer::ChatLayer()
{
    m_txtAccount = NULL;
    m_txtPassword = NULL;
}

ChatLayer::~ChatLayer()
{
    
}

CCScene* ChatLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        ChatLayer *layer = ChatLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChatLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        ////////////////////////////////////////////////////////////////////////////
        //// add your codes below...
        ////////////////////////////////////////////////////////////////////////////
        
        bRet = true;
    } while (0);

    return bRet;
}

//void ChatLayer::submitClicked(CCObject *pSender,CCControlEvent event)
//{
//	CCLOG("i was clicked");
//	char sAccount[20];
//	char sPassword[20];
//	sprintf(sAccount,m_txtAccount->getText());
//	sprintf(sPassword,m_txtAccount->getText());
//
//	//this->doSubmit();
//    
//    
////    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
////    //ccNodeLoaderLibrary->registerCCNodeLoader("AboutScene", AboutSceneLoader::loader());
////    
////    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
////    ccbReader->autorelease();
////    
////    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("MainGameScene.ccbi");
////    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(1.0, pScene));
//
//}

void ChatLayer::doSubmit()
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setResponseCallback(this,callfuncND_selector(ChatLayer::requestFinishedCallback));
	request->setTag("post testing!!!");
	request->setUrl("http://223.4.10.91/andon_service/ANDON_EX_USER.asmx/GetList");

	const char* postData = "cid=120000&date=";
	request->setRequestData(postData,strlen(postData));
	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void ChatLayer::requestFinishedCallback(CCNode* pSender,void *data)
{
    CCHttpResponse *response =  (CCHttpResponse*)data;
	if(response==NULL)
	{
		return;
	}
	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	CCLOG(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());

	if (!response->isSucceed())   
	{  
		CCLog("response failed");  
		CCLog("error buffer: %s", response->getErrorBuffer());  
		return;  
	}
	std::vector<char> *buffer = response->getResponseData(); 

	//for (unsigned int i = 0; i < buffer->size(); i++)  
	//{
	//	CCLog("%c", (*buffer)[i]);
	//}
	std::string content(buffer->begin(),buffer->end());
	//CCLog(content.c_str());

	XMLParser *xmlParser = XMLParser::parseWithString(content.c_str());
	//xmlParser->getString("content");
	//CCString *content = CCString::create(xmlParser->getString("content")->getCString());
	CCLOG("%s",xmlParser->getString("content")->getCString());

	parseJson();
}

void ChatLayer::parseJson()
{
//    JsonBox::Value v2;
//	v2.loadFromString(content);
//    
//    int code = v2["code"].getInt();
//    if (code!=200) {
//        
//        CCMessageBox("invoke web api failed!","ERROR");
//        return;
//    }else {
//    	CCLOG("douzhan:login successfully!");
//    }
}

void ChatLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    m_txtAccount = CCEditBox::create(CCSizeMake(134, 30), CCScale9Sprite::create("transparent.png"));
    this->addChild(m_txtAccount);
    m_txtAccount->setPosition(ccp(215, 24));
    
    m_txtAccount->setFontColor(ccc3(255,255,255));
    m_txtAccount->setFont("Arial", 16);
    
//	CCSprite *spriteOn = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gou_1.png"));
//	CCSprite *spriteOff = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gou_2.png"));
//    
//    CCMenu* m_auto_op_menu = CCMenu::create();
//    CCMenuItemSprite* auto_op_btn = CCMenuItemSprite::create(spriteOn, NULL);
//    CCMenuItemSprite* auto_op_btn2 = CCMenuItemSprite::create(spriteOff, NULL);
//    CCMenuItemToggle* item = CCMenuItemToggle::createWithTarget(this, menu_selector(ChatLayer::callbackSwitch),auto_op_btn,auto_op_btn2,NULL);
//    
//    m_auto_op_menu->addChild(item);
//    m_auto_op_menu->setPosition(ccp(116, 268));
//    this->addChild(m_auto_op_menu);
}

void ChatLayer::callbackSwitch(CCObject* pSender){
    
	CCMenuItemToggle* pSwitch = (CCMenuItemToggle*)pSender;
    
    if (pSwitch->getSelectedIndex()==0) {
        m_blnRememberMe = false;
    } else {
        m_blnRememberMe = true;
    }
}

bool ChatLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtAccount", CCEditBox*, this->m_txtAccount);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtPassword", CCEditBox*, this->m_txtPassword);
    return true;
}

void ChatLayer::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    
    CCControlButton *button = (CCControlButton*) pSender;
    
    switch (button->getTag()) {
        case 1:
        {
            CCLOG("chat");
            MainGameScene *mainScene = (MainGameScene *)this->getParent();
            mainScene->RemoveChatLayer();
            break;
        }
        case 2:
        {
            CCLOG("face");
            break;
        }
    }
}

SEL_MenuHandler ChatLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler ChatLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", ChatLayer::buttonClicked);
	return NULL;
}

