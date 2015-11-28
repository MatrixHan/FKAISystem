#include "../PreInclude.h"
#include "../Include/AIStateInfoManager.h"
#include "../Include/IAIBehaviorFactory.h"
#include "../Include/IAITriggerFactory.h"
#include "../Include/AITinyxml.h"

using namespace std;


AISYSTEM_SPACE_BEGIN

/*  
@	���ܣ�	����һ��״̬
@	������	strStateName:	״̬������
@	����ֵ��״ָ̬��
@	ע��	
*/
CAIStateData * CAIMachineData::FindState( const std::string & strStateName )
{
	if( m_StateMap.size() == 0 )
		return NULL;

	map<string,CAIStateData>::iterator iter = m_StateMap.find( strStateName );
	if( iter != m_StateMap.end() )
		return &iter->second;

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


/*  
@	���ܣ�	����һ��״̬��
@	������	strMachineName:	״̬��������
@	����ֵ�����ҵ���״̬������ָ��
@	ע��	
*/
CAIMachineData * CAIMachineTable::FindMachine( const std::string & strMachineName )
{
	if( m_MachineMap.size() == 0 )
		return NULL;

	map<string,CAIMachineData>::iterator iter = m_MachineMap.find( strMachineName );
	if( iter != m_MachineMap.end() )
		return &iter->second;

	return NULL;
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



CAIStateInfoManager::CAIStateInfoManager(void)
: m_bInited( false )
{
	m_strFilePath = "";
}

CAIStateInfoManager::~CAIStateInfoManager(void)
{
}


/*  
@	���ܣ�	��ø���ĵ���ʵ��
@	������	
@	����ֵ������ĵ���ʵ��
@	ע��	
*/
CAIStateInfoManager * CAIStateInfoManager::Instance( void )
{
	static CAIStateInfoManager CStateInfoManagerObj;
	return &CStateInfoManagerObj;
}

/*  
@	���ܣ�	����һ��״̬����
@	������	strMachineName:	Ҫ���ҵ�״̬���������
@	����ֵ��״̬����ָ�룬���û���ҵ�������NULL
@	ע��	
*/
CAIMachineTable * CAIStateInfoManager::FindMachineTable( const std::string & strMachineTableName )
{
	if( ! m_bInited || m_MachineTableMap.size() == 0 )
		return NULL;

	map<string,CAIMachineTable>::iterator iter = m_MachineTableMap.find( strMachineTableName );
	if( iter != m_MachineTableMap.end() )
		return &iter->second;
	return NULL;
}

/*  
@	���ܣ�	����״̬�������ļ���·��
@	������	strFilePath:	·������
@	����ֵ��
@	ע��	
*/
void CAIStateInfoManager::SetAIFileDirectory( const std::string & strFilePath )
{
	m_strFilePath = strFilePath;
}

/*  
@	���ܣ�	��AIĿ¼�������е�״̬��
@	������	
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CAIStateInfoManager::_LoadInfo( void )
{
	// ö�����е��ļ���������
	WIN32_FIND_DATA FindData;
	size_t len = m_strFilePath.length();
	char ch = m_strFilePath.at( len - 1 );
	string strFileFilter;
	if( ch != '/' && ch != '\\' )
		m_strFilePath += "/";

	strFileFilter = m_strFilePath + "*.xml";
	HANDLE hFileFind = FindFirstFile( strFileFilter.c_str(), &FindData );
	if( INVALID_HANDLE_VALUE == hFileFind )
		return false;

	BOOL bSuccFound = FALSE;
	string strFileFullPath;
	do 
	{
		strFileFullPath = m_strFilePath + FindData.cFileName;
		if( ! _LoadInfoFromFile( strFileFullPath ) )
		{
			// AILOG;
		}
		bSuccFound = FindNextFile( hFileFind, &FindData );
	} while( bSuccFound == TRUE );

	m_bInited = true;
	return true;
}

/*  
@	���ܣ�	��ָ���ļ�����һ��״̬����
@	������	strFileName:	״̬�����ļ���
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CAIStateInfoManager::_LoadInfoFromFile( const std::string & strFileName )
{
	TiXmlDocument Doc;
	if( ! Doc.LoadFile( strFileName.c_str() ) )
		return false;

	CAIMachineTable MachineTable;

	// �������е�״̬��
	TiXmlElement *pMachineTable = Doc.FirstChildElement();
	TiXmlElement *pMachine		= pMachineTable->FirstChildElement();

	while( pMachine )
	{
		if( !_LoadMachine( pMachine, MachineTable ) )
		{
			// AILOG;	
		}		
		pMachine = pMachine->NextSiblingElement();
	}

	MachineTable.m_strName = pMachineTable->Value();	// �ļ�����Ϊ״̬���������
	MachineTable.m_strMainMachine = pMachineTable->Attribute( "StartMachine" );
	m_MachineTableMap.insert( make_pair( MachineTable.m_strName, MachineTable ) );
	MachineTable.m_MachineMap.clear();
	return true;
}

/*  
@	���ܣ�	���ļ�����һ��״̬��
@	������	pMachine:		״̬�����ļ�����ָ��
			MachineTable:	�����״̬��������
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CAIStateInfoManager::_LoadMachine( TiXmlElement *pMachine, CAIMachineTable &MachineTable )
{
	if( NULL == pMachine )
		return false;
	CAIMachineData MachineData;

	// �������е�״̬
	TiXmlElement *pState = pMachine->FirstChildElement();
	while( pState )
	{
		if( ! _LoadState( pState, MachineData ) )
		{
			// AILOG;
		}
		pState = pState->NextSiblingElement();
	}
	MachineData.m_strName = pMachine->Attribute( "MachineName" );
	MachineData.m_strDefaultState	= pMachine->Attribute( "DefaultState" );
	MachineTable.m_MachineMap.insert( make_pair( MachineData.m_strName, MachineData ) );
	MachineData.m_StateMap.clear();
	return true;
}

/*  
@	���ܣ�	���ļ�����һ��״̬
@	������	pState:			״̬���ļ�����ָ��
			MachineData:	״̬���������״̬������
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CAIStateInfoManager::_LoadState( TiXmlElement *pState, CAIMachineData &MachineData )
{
	if( NULL == pState )
		return false;

	CAIStateData StateData;
	// ����AI����
	TiXmlElement *pAI = pState->FirstChildElement( "AI" );
	if( pAI )
	{
		// AI����
		static std::string strAIType = "";
		strAIType = pAI->Attribute( "AIType" );
		if( strAIType != "" )
		{
			StateData.m_uiAIID = IAIBehaviorFactory::Instance()->GenerateID( strAIType );
			// AI����
			StateData.m_AIParams = pAI->Attribute( "AIParams" );
		}
		else
		{
			StateData.m_uiAIID = 0;
		}

	}

	// ���봥��������
	TiXmlElement *pTrigger	= pState->FirstChildElement( "Triggers" )->FirstChildElement();
	while( pTrigger )
	{
		if( ! _LoadTrigger( pTrigger, StateData ) )
		{
			// AILOG;
		}
		pTrigger = pTrigger->NextSiblingElement();
	}

	// ��״̬��
	StateData.m_strSubStateMachineName = pState->Attribute( "SubState" );

	StateData.m_strName = pState->Attribute( "StateName" );
	MachineData.m_StateMap.insert( make_pair( StateData.m_strName, StateData ) );

	return true;
}

/*  
@	���ܣ�	���ļ����봥����
@	������	pTrigger:	���������ļ�����ָ��
			StateData:	״̬��������������
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CAIStateInfoManager::_LoadTrigger( TiXmlElement *pTrigger, CAIStateData &StateData )
{
	if( NULL == pTrigger )
		return false;

	CAITriggerData TriggerData;
	TriggerData.m_strNextStateName = pTrigger->Attribute( "NextState" );
	TriggerData.m_strExpression = pTrigger->Attribute( "TriParams" );
	StateData.m_Triggers.push_back( TriggerData );

	return true;
}


AISYSTEM_SPACE_END