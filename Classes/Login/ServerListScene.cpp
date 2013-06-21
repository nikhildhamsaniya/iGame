#include "ServerListScene.h"

using namespace cocos2d;

CCScene* ServerListScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        ServerListScene *layer = ServerListScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ServerListScene::init()
{
    selectedindex = 0;
    
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
        
		//mArrayList =  CCArray::create();
		CCDictionary *dict0 = CCDictionary::create();
		dict0->setObject(CCString::create("2区 花果山1"),"ServerName");
		dict0->setObject(CCString::create("良好"),"Status");
		dict0->setObject(CCString::create("1"),"Category");

		CCDictionary *dict1 = CCDictionary::create();
		dict1->setObject(CCString::create("1区 齐天大圣1"),"ServerName");
		dict1->setObject(CCString::create("流畅"),"Status");
		dict1->setObject(CCString::create("2"),"Category");

		CCDictionary *dict2 = CCDictionary::create();
		dict2->setObject(CCString::create("2区 花果山1"),"ServerName");
		dict2->setObject(CCString::create("良好"),"Status");
		dict2->setObject(CCString::create("3"),"Category");

		CCDictionary *dict3 = CCDictionary::create();
		dict3->setObject(CCString::create("3区 如来佛祖1"),"ServerName");
		dict3->setObject(CCString::create("爆满"),"Status");
		dict3->setObject(CCString::create("3"),"Category");
        mArrayList = CCArray::create(dict0,dict1,dict2,dict3,NULL);
        mArrayList->retain();

        bRet = true;
    } while (0);

    return bRet;
}

void ServerListScene::doSearch()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(ServerListScene::requestFinishedCallback));
	request->setTag("101");

    string _strUrl = CompleteUrl(URL_FRIEND_LIST);
    _strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void ServerListScene::requestFinishedCallback(CCNode* pSender,void *Rspdata)
{
	if (!this->ValidateResponseData(pSender,Rspdata))
	{
		return;
	}

	CCHttpResponse *response =  (CCHttpResponse*)Rspdata;
	std::vector<char> *buffer = response->getResponseData();

	std::string content(buffer->begin(),buffer->end());
	CCLog(content.c_str());

    CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
    if (code != 200) {
        CCMessageBox("invoke web api failed!","ERROR");
        return;
    }

	std::string requestTag(response->getHttpRequest()->getTag());

	if (requestTag == "101") {
		mArrayList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendList"));
		if (mArrayList==NULL)
		{
			return;
		}

		selectedindex = -1;
		mTableView->reloadData();
	} else if (requestTag == "102"){
		this->doSearch();
		CCMessageBox("delete friend successfully","Success");
	}
}

bool ServerListScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableView", CCTableView*, this->mTableView);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainSceneTemp", MainSceneTemplate*, this->mMainSceneTemp);
    return true;
}

SEL_MenuHandler ServerListScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", ServerListScene::menuBarBtnClicked);
	return NULL;
}

SEL_CCControlHandler ServerListScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", ServerListScene::buttonClicked);
	return NULL;
}

void ServerListScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    mTableView->setDirection(kCCScrollViewDirectionVertical);
    mTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    mTableView->setDataSource(this);
    mTableView->setViewSize(CCSizeMake(290, 210));
    mTableView->setPosition(ccp(160, 220));
    mTableView->setDelegate(this);
    mTableView->reloadData();

	//doSearchFriend();
}

//void ServerListScene::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
//{
//    //CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
//    //sSelected->setVisible(true);
//}
//
//void ServerListScene::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
//{
//    //CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
//    //sSelected->setVisible(false);
//}

void ServerListScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
    if (selectedindex == cell->getIdx()) {
        
    } else {
        selectedindex = cell->getIdx();
    }

    //table->updateCellAtIndex(cell->getIdx());
	table->refreshData();
}

unsigned int ServerListScene::numberOfCellsInTableView(CCTableView *table)
{
	return mArrayList->count();
}

CCSize ServerListScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(290, 40);
}

CCSize ServerListScene::cellSizeForIndex(CCTableView *table, unsigned int idx)
{
	CCDictionary *dict = (CCDictionary *)mArrayList->objectAtIndex(idx);
	CCString *category = (CCString *)dict->objectForKey("Category");

	if (strcmp(category->getCString(),"1")==0)
	{
		return CCSizeMake(290, 65);
	}
	else if (strcmp(category->getCString(),"2")==0)
	{
		return CCSizeMake(290, 65);
	}

    return CCSizeMake(290, 40);
}

bool ServerListScene::hasFixedCellSize()
{
    return false;
}

CCTableViewCell* ServerListScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCDictionary *dict = (CCDictionary *)mArrayList->objectAtIndex(idx);
    bool selected = (idx==selectedindex);
	CCTableViewCell *cell = table->dequeueCell();
    CCSize size = this->cellSizeForIndex(table, idx);
	CCString *category = (CCString *)dict->objectForKey("Category");
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
        
        CCSprite *sbackground = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("server_cell_bg.png"));
        sbackground->setTag(120);
		sbackground->setAnchorPoint(ccp(0.5,0));
		sbackground->setPosition(ccp(size.width/2,0));
		cell->addChild(sbackground);
        
        CCSprite *sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("yuan.png"));
        sSelected->setTag(121);
		sSelected->setAnchorPoint(ccp(0.5,0));
		sSelected->setPosition(ccp(50,10));
		cell->addChild(sSelected);
        
        if (selected ) {
            sSelected->setVisible(true);
        } else {
            sSelected->setVisible(false);
        }

		CCLabelTTF *lblName = CCLabelTTF::create(((CCString *)dict->objectForKey("ServerName"))->getCString(), "Arial", 12.0);
		lblName->setPosition(ccp(130,10));
		lblName->setAnchorPoint(ccp(0.5,0));
        lblName->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        lblName->setColor(convertColor("660000"));
		lblName->setTag(123);
		cell->addChild(lblName);

//		CCLabelTTF *lblLevel = CCLabelTTF::create("2区", "Arial", 14.0);
//		lblLevel->setPosition(ccp(165,18));
////		lblLevel->setAnchorPoint(CCPointZero);
//        lblLevel->setColor(ccc3(248, 255, 38));
//		lblLevel->setTag(124);
//		cell->addChild(lblLevel);

		CCLabelTTF *lblStatus = CCLabelTTF::create(((CCString *)dict->objectForKey("Status"))->getCString(), "Arial", 11.0);
		lblStatus->setPosition(ccp(218,10));
		lblStatus->setAnchorPoint(ccp(0.5,0));
        lblStatus->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        lblStatus->setColor(ccc3(51, 153, 00));
        lblStatus->setTag(125);
		cell->addChild(lblStatus);

		CCLabelTTF *lblTitle = CCLabelTTF::create("", "Arial", 11.0);
		lblTitle->setPosition(ccp(130,38));
		lblTitle->setAnchorPoint(ccp(0.5,0));
		lblTitle->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		lblTitle->setColor(ccc3(51, 153, 00));
		lblTitle->setTag(126);
		cell->addChild(lblTitle);
		if (strcmp(category->getCString(),"1")==0)
		{
			lblTitle->setVisible(true);
			lblTitle->setString("最近登录1");
		}
		else if (strcmp(category->getCString(),"2")==0)
		{
			lblTitle->setVisible(true);
			lblTitle->setString("选择服务器1");
		}
		else
		{
			lblTitle->setVisible(false);
		}
		
    }
	else
	{
        CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
        if (selectedindex == idx ) {
            sSelected->setVisible(true);
        } else {
            sSelected->setVisible(false);
        }
        
		CCLabelTTF *lblName = (CCLabelTTF*)cell->getChildByTag(123);
		lblName->setString(((CCString *)dict->objectForKey("ServerName"))->getCString());
        
		CCLabelTTF *lblStatus = (CCLabelTTF*)cell->getChildByTag(125);
		lblStatus->setString(((CCString *)dict->objectForKey("Status"))->getCString());


		CCLabelTTF *lblTitle = (CCLabelTTF*)cell->getChildByTag(126);
		if (strcmp(category->getCString(),"1")==0)
		{
			lblTitle->setVisible(true);
			lblTitle->setString("最近登录1");
		}
		else if (strcmp(category->getCString(),"2")==0)
		{
			lblTitle->setVisible(true);
			lblTitle->setString("选择服务器1");
		}
		else
		{
			lblTitle->setVisible(false);
		}
	}

	return cell;
}

void ServerListScene::submitSelectedServer()
{
    if (selectedindex == -1) {
        CCMessageBox(GlobalData::getLocalString("account_pwd_empty")->getCString(),"ERROR");
        return;
    }

	string character = CCUserDefault::sharedUserDefault()->getStringForKey("Character");
	if (character.length()>0) {
		this->OpenNewScene("MainGameScene");
	} else {
		this->OpenNewScene("CharacterScene");
	}
    
	//CCHttpRequest *request = new CCHttpRequest();
	//request->setRequestType(CCHttpRequest::kHttpGet);
	//request->setResponseCallback(this,callfuncND_selector(ServerListScene::requestFinishedCallback));
	//request->setTag("103");

	//string _strUrl = CompleteUrl(URL_FRIEND_DELETE);
	//_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	//_strUrl.append("/" + targetUser);

	//request->setUrl(_strUrl.c_str());

	//CCHttpClient *client = CCHttpClient::getInstance();
	//client->send(request);

	//request->release();
}

void ServerListScene::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	//case 101:
	//	CCLOG("11111");
	//	mainScene->PopLayer();
	//	break;
	case 102:
		{
			this->submitSelectedServer();
			break;
		}
	}
}

ServerListScene::ServerListScene()
{
    mTableView = NULL;
//    mMainSceneTemp = NULL;
    mArrayList = NULL;
}

ServerListScene::~ServerListScene()
{
//    mTableViewMail->release();
//    mMainSceneTemp->release();
//    mArrayList->release();
}

