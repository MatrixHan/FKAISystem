#include "../PreInclude.h"
#include "../Include/AITrigger.h"
#include "../Include/AIStateMachine.h"
#include "../Include/AIState.h"
#include "../Include/AIBrain.h"
#include "../Include/AIExpressionAnalyzer.h"
#include "../Include/AIStateInfoManager.h"

#include "../Include/IAIGlobalFunc.h"



AISYSTEM_SPACE_BEGIN

/*  
@	���ܣ�	���캯������ʼ������
@	������	
@	����ֵ��
@	ע��	
*/
CAITrigger::CAITrigger( void )
: m_pExpression( NULL )
, m_pParentState( NULL )
, m_pNextState( NULL )
{
}


/*  
@	���ܣ�	�����������ͷ����е�����
@	������	
@	����ֵ��
@	ע��	
*/
CAITrigger::~CAITrigger(void)
{
	if( m_pExpression )
	{
		delete m_pExpression;
		m_pExpression = NULL;
	}
}

/*  
@	���ܣ�	����������
@	������	pTriggerData:	����������
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CAITrigger::Build( CAITriggerData *pTriggerData, CAIBrain *pAIObject, CAIState *pParentState )
{
	// �������е�����
	static CExpressionAnalyzer expAnaylyzer;
	static bool bExpAnalyzeInited = false;
	if( ! bExpAnalyzeInited )
	{
		expAnaylyzer.Init();
		bExpAnalyzeInited = true;
	}

	static CLexicalAnalyzer lexAnaylyzer;
	static bool bLexAnaylzerInited = false;
	if( ! bLexAnaylzerInited )
	{
		lexAnaylyzer.Init();
		bLexAnaylzerInited = true;
	}

	m_pParentState = pParentState;

	static TLexTokens tokens;
	if( ! lexAnaylyzer.Analyse( pTriggerData->m_strExpression.c_str(), tokens ) )
	{
		// �����ʷ�����ʧ��
		OutPutErrorMsg( "�ʷ�����ʧ�ܣ����ʽ��%s", pTriggerData->m_strExpression.c_str() );
		return false;
	}
	m_pExpression = expAnaylyzer.Analyse( tokens, m_pParentState->GetBrain(), pTriggerData->m_strExpression.c_str() );
	if( NULL == m_pExpression )
	{
		// ��������ʧ��
		OutPutErrorMsg( "��������ʧ�ܣ����ʽ��%s", pTriggerData->m_strExpression.c_str() );
		return false;
	}

	m_strNextStateName = pTriggerData->m_strNextStateName;

	m_strExp = pTriggerData->m_strExpression;

	return true;
}

/*  
@	���ܣ�	����������
@	������	
@	����ֵ�����������������������true�����򷵻�false
@	ע��	
*/
bool CAITrigger::TouchOff(float fElapsedTimes)
{
	double res = (*m_pExpression)();
	if( res <= 0.000001 )
		return false;
	return true;
}

/*  
@	���ܣ�	��ѯ��������������
@	������	
@	����ֵ��
@	ע��	
*/
IAIObject * CAITrigger::GetTriggerOwner( void )
{
	return m_pParentState->GetBrain()->GetAIObject();
}


/*  
@	���ܣ�	������һ��״̬
@	������	pStateMachine:	������״̬��
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CAITrigger::LinkState(CAIStateMachine *pMachine)
{	
	if( m_strNextStateName == "" )
		return true;

	if( NULL == pMachine )
		return false;

	m_pNextState = pMachine->FindState( m_strNextStateName );
	if( NULL == m_pNextState )
		return false;
	else
		return true;
}


AISYSTEM_SPACE_END