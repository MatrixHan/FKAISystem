#include "../PreInclude.h"
//#include "IAITriggerFactory.h"
//#include "AIStateInfoManager.h"
//#include "AICrc32.h"
//#include "AITriggerCondition.h"
//
//
//AISYSTEM_SPACE_BEGIN
//
//
//using namespace std;
//
//
//IAITriggerFactory::IAITriggerFactory(void)
//{
//	m_uiConditionID = GenerateID( "Condition" );
//}
//
//IAITriggerFactory::~IAITriggerFactory(void)
//{
//	m_TriggerCreators.clear();
//}
//
///*  
//@	���ܣ�	��ȡAI�����ľ�̬ʵ��
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//IAITriggerFactory *IAITriggerFactory::Instance( void )
//{
//	static IAITriggerFactory CTriggerFactoryObj;
//	return &CTriggerFactoryObj;
//	return NULL;
//}
//
///*  
//@	���ܣ�	����һ��AI��Ϊ
//@	������	pBehaviorParams:	��Ϊ�Ĳ���
//@	����ֵ��������AI
//@	ע��	
//*/
//CAITrigger *IAITriggerFactory::CreateTrigger( CAICustomTriggerParams *pTriggerData /*= NULL*/ )
//{
//	if( NULL == pTriggerData )
//		return NULL;
//
//	std::map<unsigned int,FuncCreateTrigger>::iterator iter = m_TriggerCreators.find( pTriggerData->m_uiTriggerTypeID );
//	if( iter == m_TriggerCreators.end() )
//	{
//		// AI LOG ��ͼ����һ��û��ע����û��Զ��崥����
//		return NULL;
//	}
//
//	FuncCreateTrigger pFunc = iter->second;
//	return pFunc( pTriggerData );
//}
//
///*  
//@	���ܣ�	����һ����Ϊ����ID
//@	������	strName:	��Ϊ������
//@	����ֵ��ID
//@	ע��	
//*/
//unsigned int IAITriggerFactory::GenerateID( const string & strName )
//{
//	static Crc32 theCrc;
//	return theCrc.GetCRC( strName.c_str() );
//}
//
///*  
//@	���ܣ�	��ѯ��������������ID
//@	������	strName:	��������������
//@	����ֵ��
//@	ע��	
//*/
//unsigned int IAITriggerFactory::GetConditionTypeID( void )
//{
//	return m_uiConditionID;
//}
//
///*  
//@	���ܣ�	ע��һ����Ϊ������
//@	������	strName:	��Ϊ������������
//pCreator:	��Ϊ������ָ��
//@	����ֵ������Ѿ�����������������ˣ�����ʧ��
//@	ע��	
//*/
//bool IAITriggerFactory::_RegisterCreator( const string & strName, FuncCreateTrigger pCreator )
//{
//	unsigned int ID = GenerateID( strName );
//	TCreatorDictionary::iterator iter = m_TriggerCreators.find( ID );
//	if( iter != m_TriggerCreators.end() )
//		return false;
//
//	m_TriggerCreators.insert( make_pair( ID, pCreator ) );
//	return true;
//}
//
///*  
//@	���ܣ�	ע��һ����Ϊ������
//@	������	strName:	Ҫע������Ϊ������������
//@	����ֵ��
//@	ע��	
//*/
//void IAITriggerFactory::_UnregisterCreator( const string & strName )
//{
//	unsigned int ID = GenerateID( strName );
//	TCreatorDictionary::iterator iter = m_TriggerCreators.find( ID );
//	if( iter != m_TriggerCreators.end() )
//		m_TriggerCreators.erase( iter );
//}
//
//
//AISYSTEM_SPACE_END