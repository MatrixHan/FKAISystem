#include "../PreInclude.h"
#include "../Include/AIBrain.h"
#include "../Include/AIStateMachine.h"
#include "../Include/AIStateInfoManager.h"
#include "../Include/AIPropertySet.h"
#include "../Include/IAIBehaviorFactory.h"


AISYSTEM_SPACE_BEGIN


int CAIBrain::s_eExecuting = EAIBS_Executing;
int CAIBrain::s_eInterrupt = EAIBS_Interrupt;
int CAIBrain::s_eFailed	= EAIBS_Failed;
int CAIBrain::s_eSucced	= EAIBS_Succeed;

/*  
@	���ܣ�	���캯������ʼ����Ա����
@	������	
@	����ֵ��
@	ע��	
*/
CAIBrain::CAIBrain( IAIObject *pAIObject )
{
	m_pStateMachine = NULL;
	m_pAIObject = pAIObject;
	m_pPropertySet = new CPropertySet;

	RegisterProperty( "BehaviorState", &m_eBehaviorState );
	RegisterProperty( "Succeed", &CAIBrain::s_eSucced );
	RegisterProperty( "Failed", &CAIBrain::s_eFailed );
	RegisterProperty( "Interrupt", &CAIBrain::s_eInterrupt );
	RegisterProperty( "Executing", &CAIBrain::s_eExecuting );
}

/*  
@	���ܣ�	������������һЩ������
@	������	
@	����ֵ��
@	ע��	ɾ��״̬��
*/
CAIBrain::~CAIBrain( void )
{
	if( m_pStateMachine )
		delete m_pStateMachine;
}

/*  
@	���ܣ�	���½ӿ�
@	������	fElapsedTimes:	��ȥ��ʱ��
@	����ֵ��
@	ע��	�����ʵ��ֻ������״̬��
*/
void CAIBrain::Update( float fElapsedTimes )
{
	if( m_pStateMachine )
		m_pStateMachine->Update( fElapsedTimes );
}

/*  
@	���ܣ�	��������
@	������	
@	����ֵ��
@	ע��	
*/
void CAIBrain::StartUp( void )
{
	m_pStateMachine->StartUp();
}

/*  
@	���ܣ�	ֹͣ���ԵĹ���
@	������	
@	����ֵ��
@	ע��	
*/
void CAIBrain::ShutDown( void )
{
	m_pStateMachine->ShutDown();
}

/*  
@	���ܣ�	�ô�����ͣ
@	������	
@	����ֵ��
@	ע��	
*/
void CAIBrain::Pause( void )
{
	m_pStateMachine->Pause();
}

/*  
@	���ܣ�	�ָ����ԵĶ���
@	������	
@	����ֵ��
@	ע��	
*/
void CAIBrain::Resume( void )
{
	m_pStateMachine->Resume();
}

/*  
@	���ܣ�	����״̬��
@	������	strStateMachineName:	״̬��������
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CAIBrain::LoadStateMachine( const std::string strStateMachineName )
{
	if( m_pStateMachine != NULL )
	{
		delete m_pStateMachine;
		m_pStateMachine = NULL;
	}
	m_pStateMachine = new CAIStateMachine( this );
	CAIMachineTable *pMachineTable = CAIStateInfoManager::Instance()->FindMachineTable( strStateMachineName );
	if( NULL == pMachineTable )
		return false;

	bool res = m_pStateMachine->Build( pMachineTable, pMachineTable->m_strMainMachine );
	if( res )
	{
		res = m_pStateMachine->LinkStates( );
		return res;
	}
	return res;
}

/*  
@	���ܣ�	����һ������
@	������	strName:	���Ե�����
@	����ֵ������ָ��
@	ע��	
*/
CProperty *CAIBrain::FindProperty( const std::string & strName )							
{ 
	return m_pPropertySet->FindProperty( strName ); 
}

/*  
@	���ܣ�	ע�����ԣ�����һ��ID
@	������	
@	����ֵ������ID��0��ʾע��ʧ��
@	ע��	
*/
unsigned long CAIBrain::RegisterProperty( const std::string & strName, int *pValue )				
{ 
	return m_pPropertySet->Register( strName, pValue ); 
}
unsigned long CAIBrain::RegisterProperty( const std::string & strName, float *pValue )			
{ 
	return m_pPropertySet->Register( strName, pValue ); 
}	
unsigned long CAIBrain::RegisterProperty( const std::string & strName, bool *pValue )				
{ 
	return m_pPropertySet->Register( strName, pValue ); 
}
unsigned long CAIBrain::RegisterProperty( const std::string & strName, unsigned long *pValue )	
{ 
	return m_pPropertySet->Register( strName, pValue ); 
}
unsigned long CAIBrain::RegisterProperty( const std::string & strName, std::string *pValue )		
{ 
	return m_pPropertySet->Register( strName, pValue ); 
}

/*  
@	���ܣ�	�ж�ָ����Ϊ�Ƿ�����ִ��
@	������	strBehaviorName:	��Ϊ������
@	����ֵ������ִ����Ϊ����true�����򷵻�false
@	ע��	
*/
bool CAIBrain::IsBehaviorRunning( const std::string &strBehaviorName )
{
	unsigned int uiTypeID = IAIBehaviorFactory::Instance()->GenerateID( strBehaviorName );
	return m_pStateMachine->IsBehaviorRunning( uiTypeID );
}

/*  
@	���ܣ�	ǿ����ֹһ����Ϊ
@	������	uiBehaviorTypeID:	Ҫ��ֹ����Ϊ��ID
@	����ֵ�������ǰ״̬����ִ����Ϊ������ֹ������true�����򷵻�false
@	ע��	
*/
bool CAIBrain::StopBehavior( const std::string &strBehaviorName )
{
	unsigned int uiTypeID = IAIBehaviorFactory::Instance()->GenerateID( strBehaviorName );
	return m_pStateMachine->StopBehavior( uiTypeID );
}




AISYSTEM_SPACE_END