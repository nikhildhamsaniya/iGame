//
//  MDCardPlayer.h
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#ifndef __mengdou__MDCardPlayer__
#define __mengdou__MDCardPlayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class MDCardPlayer
{
public:

private:s
	CCString *m_strCardName;
	CCSprite *m_sCardPlayer;

	float m_fltPowerPoint;//��-������
	float m_fltMagicPoint;//��-��������
	float m_fltDefencePoint;//��-���Ʒ���

	float m_fltSuperAttackPoint;//����-���Ʊ���
	float m_fltDodgePoint;//����-��������
	float m_fltSpiritPoint;//��-����ȫ����

	int battleMode;//Ĭ���ֶ�ģʽ0���Զ�ģʽ1
public:
	void forwardAnnimation();
};

#endif /* defined(__mengdou__MDCardPlayer__) */
