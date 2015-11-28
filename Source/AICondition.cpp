#include "../PreInclude.h"
//#include "AICondition.h"
//#include "AIProperty.h"
//
//
//
//
//AISYSTEM_SPACE_BEGIN
//
//
//
//
//////////////////////////////////////////////
////	ע��ȽϺ���
//CAICondition::CompFunc CAICondition::s_CompFunc[EAISTestOperator_End] = 
//{	
//	&CAICondition::_TestAllways,
//	&CAICondition::_TestNever,
//	&CAICondition::_TestLess,
//	&CAICondition::_TestGreate,
//	&CAICondition::_TestEqual,
//	&CAICondition::_TestLessEqual,
//	&CAICondition::_TestGreateEqual,
//	&CAICondition::_TestNotEqual,
//	&CAICondition::_TestInner,
//	&CAICondition::_TestOutter
//};
//
//
///*  
//@	���ܣ�	���캯��
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//CAICondition::CAICondition()
//: m_pProperty( NULL )
//, m_eOpType( EAISTestOperator_End )
//{
//	m_RefData[0].m_dwData	= 0;
//	m_RefData[1].m_dwData	= 0;
//	m_eRefType[0]			= ERT_End;
//	m_eRefType[1]			= ERT_End;
//}
//
///*  
//@	���ܣ�	��������
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//CAICondition::~CAICondition( void )
//{
//}
//
///*  
//@	���ܣ�	��������
//@	������	fElapsedTimes:	��ȥ��ʱ��
//@	����ֵ���Ƿ����
//@	ע��	
//*/
//bool CAICondition::Test( float fElapsedTimes )
//{
//	return ( this->*s_CompFunc[m_eOpType] )( );
//}
//
///*  
//@	���ܣ�	���������Ƚϲ���
//@	������	pProperty:	����
//			eOpType:	��������
//			dwRefValue0:���Բο�ֵ0
//			dwRefValue1:���Բο�ֵ1
//@	����ֵ��
//@	ע��	
//*/
//void CAICondition::SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, DWORD dwRefValue0, DWORD dwRefValue1 /*= 0*/ )
//{
//	m_pProperty				= pProperty;
//	m_eOpType				= eOpType;
//	m_RefData[0].m_dwData	= dwRefValue0;
//	m_eRefType[0]			= ERT_Dword;
//	m_RefData[1].m_dwData	= dwRefValue1;
//	m_eRefType[1]			= ERT_Dword;
//}
//
///*  
//@	���ܣ�	���������Ƚϲ���
//@	������	pProperty:	����
//			eOpType:	��������
//			fRefValue0:	���Բο�ֵ0
//			fRefValue1:	���Բο�ֵ1
//@	����ֵ��
//@	ע��	
//*/
//void CAICondition::SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, float fRefValue0, float fRefValue1 /*= .0f*/ )
//{
//	m_pProperty				= pProperty;
//	m_eOpType				= eOpType;
//	m_RefData[0].m_fData	= fRefValue0;
//	m_eRefType[1]			= ERT_Float;
//	m_RefData[1].m_fData	= fRefValue1;
//	m_eRefType[1]			= ERT_Float;
//}
//
///*  
//@	���ܣ�	���������Ƚϲ���
//@	������	pProperty:		����
//			eOpType:		��������
//			pRefProperty:	�ο�����
//@	����ֵ��
//@	ע��	
//*/
//void CAICondition::SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, CProperty *pRefProperty0, CProperty *pRefProperty1 /*= NULL*/ )
//{
//	m_pProperty	= pProperty;
//	m_eOpType	= eOpType;
//	m_RefData[0].m_pProperty= pRefProperty0;
//	m_eRefType[0]			= ERT_Property;
//	m_RefData[1].m_pProperty= pRefProperty1;
//	if( m_RefData[1].m_pProperty == NULL )
//		m_eRefType[1]		= ERT_End;
//	else
//		m_eRefType[1]		= ERT_Property;
//}
//
///*  
//@	���ܣ�	С��
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//bool CAICondition::_TestLess( void )			
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) < m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) < m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) < m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) < *m_RefData[0].m_pProperty;
//	}
//	return false;
//}	
//
///*  
//@	���ܣ�	����
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//bool CAICondition::_TestGreate( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) > m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) > m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) > m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) > *m_RefData[0].m_pProperty;
//	}
//	return false;
//}
//
///*  
//@	���ܣ�	����
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//bool CAICondition::_TestEqual( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) == m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) == m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) == m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) == *m_RefData[0].m_pProperty;
//	}
//	return false;
//}
//
///*  
//@	���ܣ�	С�ڵ���
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//bool CAICondition::_TestLessEqual( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) <= m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) <= m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) <= m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) <= *m_RefData[0].m_pProperty;
//	}
//	return false;
//}
//
///*  
//@	���ܣ�	���ڵ���
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//bool CAICondition::_TestGreateEqual( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) >= m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) >= m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) >= m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) >= *m_RefData[0].m_pProperty;
//	}
//	return false;
//}
//
///*  
//@	���ܣ�	������
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//bool CAICondition::_TestNotEqual( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) != m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) != m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) != m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) != *m_RefData[0].m_pProperty;
//	}
//	return false;
//}
//
///*  
//@	���ܣ�	�ڷ�Χ��
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//bool CAICondition::_TestInner( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return m_pProperty->Inner( m_RefData[0].m_iData, m_RefData[1].m_iData );
//	case ERT_Dword:
//		return m_pProperty->Inner( m_RefData[0].m_dwData, m_RefData[1].m_dwData );
//	case ERT_Float:
//		return m_pProperty->Inner( m_RefData[0].m_fData, m_RefData[1].m_fData );
//	case ERT_Property:
//		return m_pProperty->Inner( *m_RefData[0].m_pProperty, *m_RefData[1].m_pProperty );
//	}
//	return false;
//}
//
///*  
//@	���ܣ�	�ڷ�Χ��
//@	������	
//@	����ֵ��
//@	ע��	
//*/
//bool CAICondition::_TestOutter( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return m_pProperty->Inner( m_RefData[0].m_iData, m_RefData[1].m_iData );
//	case ERT_Dword:
//		return m_pProperty->Inner( m_RefData[0].m_dwData, m_RefData[1].m_dwData );
//	case ERT_Float:
//		return m_pProperty->Inner( m_RefData[0].m_fData, m_RefData[1].m_fData );
//	case ERT_Property:
//		return m_pProperty->Inner( *m_RefData[0].m_pProperty, *m_RefData[1].m_pProperty );
//	}
//	return false;
//}
//
//AISYSTEM_SPACE_END