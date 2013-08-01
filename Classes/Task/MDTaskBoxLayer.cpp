#include "MDTaskBoxLayer.h"

#define TASK_COLUMN  3
#define TASK_ROW  3

CCScene* MDTaskBoxLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MDTaskBoxLayer *layer = MDTaskBoxLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MDTaskBoxLayer::init()
{
	selectedindex = 0;

	bool bRet = false;
	do 
	{

		CC_BREAK_IF(! CCLayer::init());

		//mArrayList =  CCArray::create();
//		mTaskList = CCArray::create(CCString::create("Li1"),CCString::create("’≈»˝"),CCString::create("Li3"),CCString::create("¿ÓÀƒ"),CCString::create("Li1653"),CCString::create("Li1qwe"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li409"),CCString::create("Li134"),CCString::create("Li51"),CCString::create("Li18974523"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li124"),CCString::create("Li1998"),CCString::create("Li3561"),NULL);
//		mTaskList->retain();

		bRet = true;
	} while (0);

	return bRet;
}

void MDTaskBoxLayer::doSearch()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDTaskBoxLayer::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_FRIEND_LIST);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MDTaskBoxLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
{
	if (!this->ValidateResponseData(client,response))
	{
		return;
	}
    
	std::vector<char> *buffer = response->getResponseData();
	std::string content(buffer->begin(),buffer->end());

	CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
	if (code != 200) {
		CCMessageBox("invoke web api failed!","ERROR");
		return;
	}

	std::string requestTag(response->getHttpRequest()->getTag());

	if (requestTag == "101") {
//		mArrayList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendList"));
//		if (mArrayList==NULL)
//		{
//			return;
//		}
//
//		selectedindex = -1;
//		mTableView->reloadData();
	} else if (requestTag == "102"){
		this->doSearch();
		CCMessageBox("delete friend successfully","Success");
	}
}

bool MDTaskBoxLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sCard", CCSprite*, this->m_sCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblTitle", CCLabelTTF*, this->m_lblTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblLife", CCLabelTTF*, this->m_lblLife);
	return true;
}

SEL_MenuHandler MDTaskBoxLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDTaskBoxLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDTaskBoxLayer::buttonClicked);
	return NULL;
}


void MDTaskBoxLayer::showTaskInfo()
{


    
//    CCString *str = (CCString *)mTaskList->objectForKey("TaskName");
//    CCArray *subTasks = (CCArray *)mTaskList->objectForKey("SubTasks");
    
//    m_lblTitle->setString("大唐西行(1)  河边放生");
    

    
}

void MDTaskBoxLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	//doSearchFriend();
    
    this->setFntTitle(101);
    
    mTaskList = GlobalData::getTasks("");
    mTaskList->retain();
    
    showTaskInfo();
}

void MDTaskBoxLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
        {
		mainScene->PopLayer();
		break;
        }
	case 102:
        {
		CCLOG("22222");
//            string test("test");
//            executeTask(test);
            selectedindex++;
            showTaskInfo();
        }
		break;
//	case 103:
//		CCLOG("33333");
//		break;
	}
}

MDTaskBoxLayer::MDTaskBoxLayer()
{
//	mTableView = NULL;
	//    mMainSceneTemp = NULL;
	mTaskList = NULL;
    m_lblTitle = NULL;
    m_sCard = NULL;
    m_lblLife = NULL;
}

MDTaskBoxLayer::~MDTaskBoxLayer()
{
	m_sCard->release();
	m_lblTitle->release();
//	mTaskList->release();
    m_lblLife->release();
}

