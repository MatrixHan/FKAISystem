#include "../PreInclude.h"
#include "../Include/AIState.h"
#include "../Include/AIProperty.h"
#include "../Include/AIStateInfoManager.h"
#include "../Include/AIStateMachine.h"
#include "../Include/AIBrain.h"
#include "../Include/AITrigger.h"
#include "../Include/IAIBehavior.h"
#include "../Include/IAIBehaviorFactory.h"

#include "../Include/IAIGlobalFunc.h"




AISYSTEM_SPACE_BEGIN


/*  
@	���ܣ�	���캯������ʼ������
@	������	
@	����ֵ��
@	ע��	
*/
CAIState::CAIState( CAIStateMachine *pParent, CAIBrain *pMaster )
: m_pParentMachine( pParent )
, m_pSubStateMachine( NULL )
, m_pAIParams( NULL )
, m_pBehavior( NULL )
, m_pMaster( pMaster )
{
}


/*  
@	���ܣ�	�����������ͷ����еĴ�����
@	������	
@	����ֵ��
@	ע��	
*/
CAIState::~CAIState(void)
{
	// �ͷ�AI
	if( m_pBehavior )
		delete m_pBehavior;

	// �ͷŴ�����
	size_t size = m_pStateTriggers.size();
	CAITrigger *pTrigger = NULL;
	for( size_t i = 0; i < size; ++ i )
	{
		pTrigger = m_pStateTriggers[i];
		if( pTrigger )
			delete pTrigger;
	}
	m_pStateTriggers.clear();
}

/*  
@	���ܣ�	����״̬
@	������	
@	����ֵ��
@	ע��	��һЩ��ʼ���Ĺ����������AI������AI
*/
void CAIState::Enter( void )
{
	// ����AI��������
	if( m_pAIParams )
	{
		int n = (int)m_ParamProp.size();
		for( int i = 0; i < n; ++ i )
		{
			if( m_ParamProp[i] )
			{
				CProperty *pProp = m_ParamProp[i];
				switch( pProp->GetType() )
				{
				case CProperty::EDT_Int:
					{
						int data;
						pProp->GetValue( data );
						m_pAIParams->m_Params[i].SetData( data );
					}
					break;
				case CProperty::EDT_Float:
					{
						float data;
						pProp->GetValue( data );
						m_pAIParams->m_Params[i].SetData( data );
					}
					break;
				case CProperty::EDT_UnsignedLong:
					{
						unsigned long data;
						pProp->GetValue( data );
						m_pAIParams->m_Params[i].SetData( data );
					}
					break;
				case CProperty::EDT_Bool:
					{
						bool data;
						pProp->GetValue( data );
						int i = (int)data;
						m_pAIParams->m_Params[i].SetData( i );
					}
					break;
				case CProperty::EDT_String:
					{
						std::string data;
						pProp->GetValue( data );
						m_pAIParams->m_Params[i].SetData( data );
					}
					break;
				}
			}
		}
		// ���ݲ�������AI��Ϊ
		m_pBehavior = IAIBehaviorFactory::Instance()->CreateBehavior( m_pMaster->GetAIObject(), m_pAIParams );
		if( m_pBehavior && ! m_pBehavior->OnStartUp() )
		{
			IAIBehaviorFactory::Instance()->DestoryBehavior( m_pBehavior );
			m_pBehavior = NULL;
		}
	}

	if( m_pSubStateMachine )
		m_pSubStateMachine->StartUp();
}

/*  
@	���ܣ�	�뿪״̬
@	������	
@	����ֵ��
@	ע��	�������Ϊ��ɾ��AI
*/
void CAIState::Leave( void )
{
	if( m_pBehavior )
	{
		m_pBehavior->OnShutDown();
		IAIBehaviorFactory::Instance()->DestoryBehavior( m_pBehavior );
		m_pBehavior = NULL;
	}
	if( m_pSubStateMachine )
		m_pSubStateMachine->ShutDown();
}

/*  
@	���ܣ�	״ִ̬��
@	������	fElapsedTimes	:��ȥ��ʱ��
@	����ֵ�����������״̬��ת��������һ��״̬
@	ע��	�������еĴ��������������״̬��ת���򷵻��µ�״̬
			�����������״̬����ִ����״̬����û��״̬�������AI��ִ�У�
*/
CAIState * CAIState::Update( float fElapsedTimes )
{
	// ����״̬����������״̬��
	if( m_pSubStateMachine )
		m_pSubStateMachine->Update( fElapsedTimes );

	// ��AI����AI
	if( m_pBehavior )
	{
		EAIBehaviorState state = m_pBehavior->RealUpdate( fElapsedTimes );
		m_pMaster->SetCurBehaviorState( state );
	}

	// ִ�д�����
	size_t size = m_pStateTriggers.size();
	CAITrigger *pTrigger	= NULL;
	CAIState *pNextState	= NULL;
	for( size_t i = 0; i < size; ++ i )
	{
		pTrigger = m_pStateTriggers[i];
		if( pTrigger )
		{
			if( pTrigger->TouchOff( fElapsedTimes ) )
				pNextState = pTrigger->GetNextState();
			if( pNextState )
				return pNextState;
		}
	}

	return NULL;
}

/*  
@	���ܣ�	����һ��״̬
@	������	pStateData:	״̬������
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CAIState::Build( CAIStateData *pStateData, CAIMachineTable *pMachineTable )
{
	// �������״̬����������״̬��
	if( pStateData->m_strSubStateMachineName != "" )
	{
		if( NULL == pMachineTable )
			return false;
		m_pSubStateMachine = new CAIStateMachine( m_pMaster );
		bool res = m_pSubStateMachine->Build( pMachineTable, pStateData->m_strSubStateMachineName );
		if( false == res )
			return false;
		m_pSubStateMachine->SetParentState( this );
	}
	// ��AI������AI����
	if( pStateData->m_uiAIID != 0 )
	{
		m_pAIParams = new CBehaviorParams;
		m_pAIParams->m_uiAIID	= pStateData->m_uiAIID;
		int n = Parse2Strings( m_strAIParams, pStateData->m_AIParams );
		for( int i = 0; i < n; ++ i )
		{
			if( ! IsNumeric( m_strAIParams[i] ) )
			{
				CProperty *pProp = m_pMaster->FindProperty( m_strAIParams[i] );
				if( NULL == pProp )
				{
					// û���ҵ�����
					OutPutErrorMsg( "û���ҵ�����: %s", m_strAIParams[i].c_str() );
					return false;
				}
				m_ParamProp.push_back( pProp );
			}
			else
				m_ParamProp.push_back( NULL );
			CAIAny any( m_strAIParams[i] );
			m_pAIParams->m_Params.push_back( any );
		}
	}

	// �������еĴ�����
	std::vector<CAITriggerData> &TriggerDatas = pStateData->m_Triggers;
	size_t size = TriggerDatas.size();
	CAITrigger *pTrigger = NULL;
	for( size_t i = 0; i < size; ++ i )
	{
		CAITriggerData &TriggerData = TriggerDatas[i];
		pTrigger = new CAITrigger;
		if( ! pTrigger->Build( &TriggerData, m_pMaster, this ) )
		{
			// AI LOG
			OutPutErrorMsg( "����������ʧ�� ״̬��%s", pStateData->m_strName.c_str() );
			delete pTrigger;
			pTrigger = NULL;
			continue;
		}
		m_pStateTriggers.push_back( pTrigger );
	}

	m_strName = pStateData->m_strName;
	return true;
}

/*  
@	���ܣ�	Ϊ���еĴ�����������һ��״̬
@	������	pStateMachine:	������״̬��
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CAIState::LinkStates( CAIStateMachine *pMachine )
{
	size_t size = m_pStateTriggers.size();
	if( 0 == size )
		return true;

	if( NULL == pMachine )
		return false;

	CAITrigger *pTrigger = NULL;
	bool bLinked = false;
	for( size_t i = 0; i < size; ++ i )
	{
		pTrigger = m_pStateTriggers[i];
		if( pTrigger )
		{
			bLinked = pTrigger->LinkState( pMachine );
			if( false == bLinked )
				return false;
		}
	}

	if( m_pSubStateMachine )
	{
		return m_pSubStateMachine->LinkStates();
	}
	return true;
}

/*  
@	���ܣ�	�ж�ָ����Ϊ�Ƿ�����ִ��
@	������	uiBehaviorTypeID:	��Ϊ������ID
@	����ֵ��
@	ע��	
*/
bool CAIState::IsBehaviorRunning( unsigned int uiBehaviorTypeID )
{
	bool running = false;
	if( m_pSubStateMachine )
		running |= m_pSubStateMachine->IsBehaviorRunning( uiBehaviorTypeID );
	if( m_pBehavior )
		running |= ( m_pBehavior->GetAIType() == uiBehaviorTypeID );
	return running;
}

/*  
@	���ܣ�	ǿ����ֹһ����Ϊ
@	������	uiBehaviorTypeID:	Ҫ��ֹ����Ϊ��ID
@	����ֵ�������ǰ״̬����ִ����Ϊ������ֹ������true�����򷵻�false
@	ע��	
*/
bool CAIState::StopBehavior( unsigned int uiBehaviorTypeID )
{
	bool ok = false;
	if( m_pSubStateMachine )
		ok |= m_pSubStateMachine->StopBehavior( uiBehaviorTypeID );
	// ��AI����AI
	if( m_pBehavior && m_pBehavior->GetAIType() == uiBehaviorTypeID )
	{
		m_pBehavior->Stop();
		ok |= true;
	}
	return ok;
}



AISYSTEM_SPACE_END