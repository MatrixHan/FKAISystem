#include "../PreInclude.h"
//
//#include "AITriggerCondition.h"
//#include "AIStateInfoManager.h"
//#include "AIStateMachine.h"
//#include "AIBrain.h"
//#include "AIExpressionAnalyzer.h"
//
//AISYSTEM_SPACE_BEGIN
//
///*  
//@	���ܣ�	���캯������ʼ������
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//CAITriggerCondition::CAITriggerCondition( void )
//{
//}
//
//
///*  
//@	���ܣ�	�����������ͷ����е�����
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//CAITriggerCondition::~CAITriggerCondition(void)
//{
//	if( m_pExpression )
//	{
//		delete m_pExpression;
//		m_pExpression = NULL;
//	}
//}
//
//
///*  
//@	���ܣ�	����������
//@	������	
//@	����ֵ�����������������������true�����򷵻�false
//@	ע��	
//*/
//bool CAITriggerCondition::TouchOff(float fElapsedTimes)
//{
//	double res = (*m_pExpression)();
//	if( res <= 0.000001 )
//		return false;
//	return true;
//}
//
///*  
//@	���ܣ�	����������
//@	������	pTriggerData:	����������
//@	����ֵ���Ƿ�ɹ�
//@	ע��	
//*/
//bool CAITriggerCondition::Build( CAITriggerData *pTriggerData, CAIBrain *pAIObject )
//{
//	// �������е�����
//	static CExpressionAnalyzer expAnaylyze;
//	static bool bExpAnalyzeInited = false;
//	if( ! bExpAnalyzeInited )
//	{
//		expAnaylyze.Init();
//		bExpAnalyzeInited = true;
//	}
//
//	m_pExpression = expAnaylyze.Analyse( pTriggerData->m_strExpression.c_str() );
//	if( NULL == m_pExpression )
//	{
//		// AI LOG ��������ʧ��
//		return false;
//	}
//
//	m_strNextStateName = pTriggerData->m_strNextStateName;
//
//	return true;
//}
//
///*  
//@	���ܣ�	������һ��״̬
//@	������	pStateMachine:	������״̬��
//@	����ֵ���Ƿ�ɹ�
//@	ע��	
//*/
//bool CAITriggerCondition::LinkState(CAIStateMachine *pMachine)
//{	
//	if( m_strNextStateName == "" )
//		return true;
//
//	if( NULL == pMachine )
//		return false;
//
//	m_pNextState = pMachine->FindState( m_strNextStateName );
//	if( NULL == m_pNextState )
//		return false;
//	else
//		return true;
//}
//
//
//AISYSTEM_SPACE_END