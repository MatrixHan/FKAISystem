#include "../PreInclude.h"
#include "../Include/AIStateMachine.h"
#include "../Include/AIStateInfoManager.h"
#include "../Include/AIState.h"
#include "../Include/AIBrain.h"
#include "../Include/IAIGlobalFunc.h"



AISYSTEM_SPACE_BEGIN

using namespace std;


/*  
@	���ܣ�	���캯������ʼ������
@	������	
@	����ֵ��
@	ע��	
*/
CAIStateMachine::CAIStateMachine( CAIBrain * pMaster )
: m_eMachineState( ESMachineState_End )
, m_pActiveState( NULL )
, m_pParentState( NULL )
, m_pMaster( pMaster )
{
}


/*  
@	���ܣ�	�����������ͷ����е�״̬
@	������	
@	����ֵ��
@	ע��	
*/
CAIStateMachine::~CAIStateMachine(void)
{
	size_t size = m_pStates.size();
	CAIState *pState = NULL;

	map<string,CAIState*>::iterator iter = m_pStates.begin();
	while( iter != m_pStates.end() )
	{
		pState = iter->second;
		if( pState )
			delete pState;
		iter = m_pStates.erase( iter );
	}
	m_pStates.clear();
}


/*  
@	���ܣ�	����״̬��
@	������	
@	����ֵ��
@	ע��	
*/
bool CAIStateMachine::StartUp( void )
{
	if( ESMachineState_Running == m_eMachineState )
		return true;

	m_eMachineState = ESMachineState_Running;
	m_pActiveState = m_pDefaultState;
	m_pActiveState->Enter();
	return true;
}

/*  
@	���ܣ�	ֹͣ״̬��
@	������	
@	����ֵ��
@	ע��	
*/
bool CAIStateMachine::ShutDown( void )
{
	if( ESMachineState_Stopped == m_eMachineState )
		return true;

	m_eMachineState = ESMachineState_Stopped;
	m_pActiveState->Leave();
	return true;
}

/*  
@	���ܣ�	����״̬��
@	������	fElapsedTimes	:��ȥ��ʱ��
@	����ֵ��
@	ע��	
*/
void CAIStateMachine::Update( float fElapsedTimes )
{
	if( m_eMachineState != ESMachineState_Running )
		return;

	if( m_pActiveState )
	{
		CAIState *pNewState;
		pNewState = m_pActiveState->Update( fElapsedTimes );
		if( NULL != pNewState && pNewState != m_pActiveState )
		{
			m_pActiveState->Leave();
			m_pActiveState = pNewState;
			m_pActiveState->Enter();
		}
	}
}


/*  
@	���ܣ�	����һ��״̬
@	������	strStateName:	״̬������
@	����ֵ��״ָ̬��
@	ע��	
*/
CAIState * CAIStateMachine::FindState( const std::string & strStateName )
{
	if( m_pStates.size() == 0 )
		return NULL;

	map<string,CAIState*>::iterator iter = m_pStates.find( strStateName );
	if( iter != m_pStates.end() )
		return iter->second;
	return NULL;
}


/*  
@	���ܣ�	����״̬��
@	������	strMachineName:			״̬��������
			strMachineTableName:	״̬���������
@	����ֵ�������ɹ�������true�����򷵻�false
@	ע��	�������״̬�������ñ����ҵ����״̬������������
*/
bool CAIStateMachine::Build( const std::string & strMachineTableName, const std::string & strMachineName )
{
	// �ҵ�״̬����
	CAIMachineTable *pMachineTable = CAIStateInfoManager::Instance()->FindMachineTable( strMachineTableName );
	if( NULL == pMachineTable )
		return false;

	Build( pMachineTable, strMachineName );
	return true;
}

/*  
@	���ܣ�	����״̬��
@	������	strMachineName:	״̬��������
			pMachineTable:	״̬�����ָ��
@	����ֵ�������ɹ�������true�����򷵻�false
@	ע��	�������״̬�������ñ����ҵ����״̬������������
*/
bool CAIStateMachine::Build( CAIMachineTable *pMachineTable, const std::string & strMachineName )
{
	if( NULL == pMachineTable )
		return false;

	// �ҵ�״̬��
	CAIMachineData *pMachineData = pMachineTable->FindMachine( strMachineName );
	if( NULL == pMachineData || pMachineData->m_StateMap.size() == 0 )
		return false;

	// �������е�״̬
	CAIState		*pState		= NULL;
	CAIStateData	*pStateData = NULL;
	map<string,CAIStateData> &StateMap = pMachineData->m_StateMap;
	map<string,CAIStateData>::iterator iter = StateMap.begin();
	for( ; iter != StateMap.end(); ++ iter )
	{
		pStateData = &iter->second;
		pState = new CAIState( this, m_pMaster );
		if( ! pState->Build( pStateData, pMachineTable ) )
		{
			if( pState )
				delete pState;
			return false;
		}
		else
		{
			m_pStates.insert( make_pair( pStateData->m_strName, pState ) );
		}
	}

	m_strName = pMachineData->m_strName;
	m_pDefaultState	= FindState( pMachineData->m_strDefaultState );
	if( NULL == m_pDefaultState )
		OutPutErrorMsg( "û��ָ��Ĭ��״̬��Ĭ��״̬����ʧ�ܣ��� ״̬����%s", strMachineName.c_str() );

	return true;
}

/*  
@	���ܣ�	�������е�״̬
@	������	
@	����ֵ��
@	ע��	
*/
bool CAIStateMachine::LinkStates( void )
{
	if( m_pStates.size() == 0 )
		return true;

	map<string,CAIState*>::iterator iter = m_pStates.begin();
	bool bLinked = false;
	for( ; iter != m_pStates.end(); ++ iter )
	{
		bLinked = iter->second->LinkStates( this );
		if( false == bLinked )
			return false;
	}
	return true;
}


/*  
@	���ܣ�	�ж�ָ����Ϊ�Ƿ�����ִ��
@	������	uiBehaviorTypeID:	��Ϊ������ID
@	����ֵ��
@	ע��	
*/
bool CAIStateMachine::IsBehaviorRunning( unsigned int uiBehaviorTypeID )
{
	if( m_pActiveState )
	{
		return m_pActiveState->IsBehaviorRunning( uiBehaviorTypeID );
	}
	return false;
}

/*  
@	���ܣ�	ǿ����ֹһ����Ϊ
@	������	uiBehaviorTypeID:	Ҫ��ֹ����Ϊ��ID
@	����ֵ�������ǰ״̬����ִ����Ϊ������ֹ������true�����򷵻�false
@	ע��	
*/
bool CAIStateMachine::StopBehavior( unsigned int uiBehaviorTypeID )
{
	if( m_pActiveState )
	{
		return m_pActiveState->StopBehavior( uiBehaviorTypeID );
	}
	return false;
}



AISYSTEM_SPACE_END