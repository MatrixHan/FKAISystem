#include "../PreInclude.h"
#include "../Include/IAIBehaviorFactory.h"
#include "../Include/IAIBehavior.h"
#include "../Include/AIStateDefine.h"
#include "../Include/AICrc32.h"

#include "../Include/IAIGlobalFunc.h"



AISYSTEM_SPACE_BEGIN


using namespace std;

IAIBehaviorFactory *IAIBehaviorFactory::s_pFactory = NULL;


IAIBehaviorFactory::IAIBehaviorFactory(void) 
{
}

IAIBehaviorFactory::~IAIBehaviorFactory(void)
{
	m_BehaviorCreators.clear();
}

/*  
@	���ܣ�	��ȡAI�����ľ�̬ʵ��
@	������	
@	����ֵ��
@	ע��	
*/
IAIBehaviorFactory *IAIBehaviorFactory::Instance( void )
{
	return s_pFactory;
}

/*  
@	���ܣ�	����һ��AI��Ϊ
@	������	pBehaviorParams:	��Ϊ�Ĳ���
@	����ֵ��������AI
@	ע��	
*/
IAIBehavior *IAIBehaviorFactory::CreateBehavior( IAIObject *pAIObject, CBehaviorParams *pBehaviorParams /*= NULL*/ )
{
	if( NULL == pBehaviorParams || NULL == pAIObject )
		return NULL;

	std::map<unsigned int,FuncCreateBehavior>::iterator iter = m_BehaviorCreators.find( pBehaviorParams->m_uiAIID );
	if( iter == m_BehaviorCreators.end() )
	{
		// ��ͼ����һ��û��ע�����Ϊ
		OutPutErrorMsg( "��ͼ����һ��û��ע�����Ϊ" );
		return NULL;
	}

	FuncCreateBehavior pFunc = iter->second;
	IAIBehavior *pNewBehavior = pFunc( pBehaviorParams );
	if( pNewBehavior )
		pNewBehavior->SetMaster( pAIObject );
	return pNewBehavior;
}

/*  
@	���ܣ�	����һ����Ϊ����ID
@	������	strName:	��Ϊ������
@	����ֵ��ID
@	ע��	
*/
unsigned int IAIBehaviorFactory::GenerateID( const string & strName )
{
	static Crc32 theCrc;
	return theCrc.GetCRC( strName.c_str() );
}

/*  
@	���ܣ�	ע��һ����Ϊ������
@	������	strName:	��Ϊ������������
			pCreator:	��Ϊ������ָ��
@	����ֵ������Ѿ�����������������ˣ�����ʧ��
@	ע��	
*/
bool IAIBehaviorFactory::_RegisterCreator( const string & strName, FuncCreateBehavior pCreator )
{
	unsigned int ID = GenerateID( strName );
	TCreatorDictionary::iterator iter = m_BehaviorCreators.find( ID );
	if( iter != m_BehaviorCreators.end() )
		return false;

	m_BehaviorCreators.insert( make_pair( ID, pCreator ) );
	return true;
}

/*  
@	���ܣ�	ע��һ����Ϊ������
@	������	strName:	Ҫע������Ϊ������������
@	����ֵ��
@	ע��	
*/
void IAIBehaviorFactory::_UnregisterCreator( const string & strName )
{
	unsigned int ID = GenerateID( strName );
	TCreatorDictionary::iterator iter = m_BehaviorCreators.find( ID );
	if( iter != m_BehaviorCreators.end() )
		m_BehaviorCreators.erase( iter );
}






AISYSTEM_SPACE_END