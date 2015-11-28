#include "../PreInclude.h"
#include "../Include/IAIObject.h"
#include "../Include/AIBrain.h"




AISYSTEM_SPACE_BEGIN



IAIObject::IAIObject()
{
	m_pAIBrain = NULL;
}


/*  
@	���ܣ�	��ʼ��AIϵͳ�������������ԣ�ע������
@	������	strStateMachineName:	״̬��������
@	����ֵ�������ɹ��Ļ�����ȥ true
@	ע��	
*/
bool IAIObject::InitAISystem( const std::string & strStateMachineName )
{
	// �������Բ�����״̬��
	m_pAIBrain = new CAIBrain( this );

	// ע�����е�����
	_RegisterProperties();

	if( ! m_pAIBrain->LoadStateMachine( strStateMachineName ) )
	{
		delete m_pAIBrain;
		m_pAIBrain = NULL;
		return false;
	}



	return true;
}

/*  
@	���ܣ�	����AI
@	������	
@	����ֵ��
@	ע��	
*/
void IAIObject::AIUpdate( float fElapsedTimes )
{
	if( m_pAIBrain )
		m_pAIBrain->Update( fElapsedTimes );
}

/*  
@	���ܣ�	����AI
@	������	
@	����ֵ��
@	ע��	
*/
void IAIObject::AIStartUp( void )
{
	if( m_pAIBrain )
		m_pAIBrain->StartUp();
}

/*  
@	���ܣ�	ֹͣAI
@	������	
@	����ֵ��
@	ע��	
*/
void IAIObject::AIShutDown( void )
{
	if( m_pAIBrain )
		m_pAIBrain->ShutDown();
}

/*  
@	���ܣ�	��ͣAI
@	������	
@	����ֵ��
@	ע��	
*/
void IAIObject::AIPause( void )
{
	if( m_pAIBrain )
		m_pAIBrain->Pause();
}

/*  
@	���ܣ�	�ָ�AI������
@	������	
@	����ֵ��
@	ע��	
*/
void IAIObject::AIResume( void )
{
	if( m_pAIBrain )
		m_pAIBrain->Resume();
}


/*  
@	���ܣ�	ע�����ԣ�����һ��ID
@	������	
@	����ֵ������ID��0��ʾע��ʧ��
@	ע��	
*/
unsigned long IAIObject::RegisterProperty( const std::string & strName, int *pValue )				
{ 
	if( m_pAIBrain )
		return m_pAIBrain->RegisterProperty( strName, pValue ); 
	return 0;
}
unsigned long IAIObject::RegisterProperty( const std::string & strName, float *pValue )			
{ 
	if( m_pAIBrain )
		return m_pAIBrain->RegisterProperty( strName, pValue ); 
	return 0;
}	
unsigned long IAIObject::RegisterProperty( const std::string & strName, bool *pValue )				
{ 
	if( m_pAIBrain )
		return m_pAIBrain->RegisterProperty( strName, pValue ); 
	return 0;
}
unsigned long IAIObject::RegisterProperty( const std::string & strName, unsigned long *pValue )	
{ 
	if( m_pAIBrain )
		return m_pAIBrain->RegisterProperty( strName, pValue ); 
	return 0;
}
unsigned long IAIObject::RegisterProperty( const std::string & strName, std::string *pValue )		
{ 
	if( m_pAIBrain )
		return m_pAIBrain->RegisterProperty( strName, pValue ); 
	return 0;
}

/*  
@	���ܣ�	�ж�ָ����Ϊ�Ƿ�����ִ��
@	������	strBehaviorName:	��Ϊ������
@	����ֵ������ִ����Ϊ����true�����򷵻�false
@	ע��	
*/
bool IAIObject::IsBehaviorRunning( const std::string &strBehaviorName )
{
	return m_pAIBrain->IsBehaviorRunning( strBehaviorName );
}

/*  
@	���ܣ�	ǿ����ֹһ����Ϊ
@	������	uiBehaviorTypeID:	Ҫ��ֹ����Ϊ��ID
@	����ֵ�������ǰ״̬����ִ����Ϊ������ֹ������true�����򷵻�false
@	ע��	
*/
bool IAIObject::StopBehavior( const std::string &strBehaviorName )
{
	return m_pAIBrain->StopBehavior( strBehaviorName );
}



AISYSTEM_SPACE_END