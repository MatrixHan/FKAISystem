/********************************************************************
// FileName: d:\work\FKAISystem\Include\AITriggerCondition.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ����������
*********************************************************************/

//#pragma once

//--------------------------------------------------------------------
//
//#include "CAITrigger.h"
//
//#pragma warning(disable:4251)
//
//AISYSTEM_SPACE_BEGIN
//
//
//class CAITriggerData;
//class CExpression;
//class CAIBrain;
//
//
///****************************************************************
//+	CLASS
//-----------------------------------------------------------------
//+   ����:	CAITrigger
//+   ����:	AI����Ĵ�����
//+   ����:	������ά��һϵ������������������ʱ������һ��״̬
//-----------------------------------------------------------------
//*****************************************************************/
//class CAITriggerCondition : public CAITrigger
//{
//	////////////////////////////////////////////
//	//	���ݳ�Ա
//protected:
//	CExpression		*m_pExpression;		// �������ʽ
//
//	////////////////////////////////////////////
//	//	����/����
//public:
//	CAITriggerCondition( void );
//	~CAITriggerCondition( void );
//
//	////////////////////////////////////////////
//	//	�����ӿ�
//public:
//	/*  
//	@	���ܣ�	����������
//	@	������	pTriggerData:	����������
//	@	����ֵ���Ƿ�ɹ�
//	@	ע��	
//	*/
//	bool Build( CAITriggerData *pTriggerData, CAIBrain *pAIObject );
//
//	/*  
//	@	���ܣ�	����������
//	@	������	
//	@	����ֵ�����������������������true�����򷵻�false
//	@	ע��	
//	*/
//	virtual bool TouchOff( float fElapsedTimes );
//
//	/*  
//	@	���ܣ�	���ô�����������״̬
//	@	������	
//	@	����ֵ��
//	@	ע��	
//	*/
//	void SetParentState( CAIState *pState )
//	{
//		m_pParentState = pState;
//	}
//
//	/*  
//	@	���ܣ�	������һ��״̬
//	@	������	pMachine:	������״̬��
//	@	����ֵ���Ƿ�ɹ�
//	@	ע��	
//	*/
//	bool LinkState( CAIStateMachine *pMachine );
//
//};
//
//
//
//
//AISYSTEM_SPACE_END
//
//#pragma warning(default:4251)