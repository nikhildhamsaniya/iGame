#include "AddFriendScene.h"
#include "json/json.h"

using namespace cocos2d;

CCScene* AddFriendScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        AddFriendScene *layer = AddFriendScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AddFriendScene::init()
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

void AddFriendScene::submitClicked(CCObject *pSender,CCControlEvent event)
{
	CCLOG("i was clicked");
	char sAccount[20];
	char sPassword[20];
	sprintf(sAccount,m_txtAccount->getText());
	sprintf(sPassword,m_txtAccount->getText());

	//this->doSubmit();
    
    
//    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
//    
//    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
//    ccbReader->autorelease();
//    
//    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("MainGameScene.ccbi");
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(1.0, pScene));

}

void AddFriendScene::doSubmit()
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setResponseCallback(this,callfuncND_selector(AddFriendScene::requestFinishedCallback));
	request->setTag("post testing!!!");
	request->setUrl("http://223.4.10.91/andon_service/ANDON_EX_USER.asmx/GetList");

	const char* postData = "cid=120000&date=";
	request->setRequestData(postData,strlen(postData));
	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void AddFriendScene::requestFinishedCallback(CCNode* pSender,void *data)
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

void AddFriendScene::parseJson()
{
	Json::Reader reader;  
	Json::Value root; 

//	const char* str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";  
//	if (reader.parse(str, root)) 
//	{  
//		std::string upload_id = root["uploadid"].asString();
//		int code = root["code"].asInt();
//	}
}

void AddFriendScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CCLOG("TEST");
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_txtAccount->setPlaceHolder("this is account");
    m_txtPassword->setPlaceHolder("this is password");

}

bool AddFriendScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtAccount", CCEditBox*, this->m_txtAccount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtPassword", CCEditBox*, this->m_txtPassword);
    return true;
}

void AddFriendScene::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}

void AddFriendScene::menuBarBtnClicked(CCObject *pSender)
{
//    CCControlButton *button = (CCControlButton*) pSender;
//    switch (button->getTag()) {
//        case TOOLBAR_BTN_COMPETITION_TAG:
//            CCLOG("11111");
//            break;
//        case TOOLBAR_BTN_GOD_DEMON_TAG:
//            CCLOG("22222");
//            break;
//        case TOOLBAR_BTN_RANKLIST_TAG:
//            CCLOG("33333");
//            break;
//        case TOOLBAR_BTN_FRIENDS_TAG:
//            CCLOG("44444");
//            break;
//        case TOOLBAR_BTN_ITEMS_TAG:
//            CCLOG("55555");
//            break;
//        case TOOLBAR_BTN_MAIL_TAG:
//            CCLOG("66666");
//            break;
//        case TOOLBAR_BTN_SETTING_TAG:
//            CCLOG("77777");
//            
//            CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//            ccNodeLoaderLibrary->registerCCNodeLoader("AboutScene", AboutSceneLoader::loader());
//            
//            cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
//            ccbReader->autorelease();
//            
//            CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("AboutScene.ccbi");
//            CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(1.0, pScene));
//            break;
//    }
}

SEL_MenuHandler AddFriendScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", LoginScene::menuBarBtnClicked);
    
	return NULL;
}

SEL_CCControlHandler AddFriendScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "submitClicked:", AddFriendScene::submitClicked);
    
	return NULL;
}
