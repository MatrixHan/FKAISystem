#include "../PreInclude.h"
#include "../Include/AIProperty.h"
#include "../Include/IAIGlobalFunc.h"


using namespace std;

AISYSTEM_SPACE_BEGIN



/*  
@	���ܣ�	Ĭ�Ϲ��캯��
@	������	
@	����ֵ��
@	ע��	
*/
CProperty::CProperty( void )
: m_Type( EDT_End )
, m_uiID( 0 )
{
	m_Data.m_pBool = NULL;
}

/*  
@	���ܣ�	��������
@	������	
@	����ֵ��
@	ע��	
*/
CProperty::~CProperty( void )
{

}

/*  
@	���ܣ�	ע����������
@	������	
@	����ֵ��
@	ע��	
*/
void CProperty::Register( int *pInt )
{
	m_Data.m_pInt	= pInt;
	m_Type			= EDT_Int;
}

/*  
@	���ܣ�	ע�ḡ��������
@	������	
@	����ֵ��
@	ע��	
*/
void CProperty::Register( float *pFloat )
{
	m_Data.m_pFloat	= pFloat;
	m_Type			= EDT_Float;
}

/*  
@	���ܣ�	ע���޷��ų�����
@	������	
@	����ֵ��
@	ע��	
*/
void CProperty::Register( unsigned long *pUnsignedLog )
{
	m_Data.m_pUnsignedLong	= pUnsignedLog;
	m_Type					= EDT_UnsignedLong;
}

/*  
@	���ܣ�	ע�᲼����
@	������	
@	����ֵ��
@	ע��	
*/
void CProperty::Register( bool *pBool )
{
	m_Data.m_pBool	= pBool;
	m_Type			= EDT_Bool;
}

/*  
@	���ܣ�	ע���ַ�������
@	������	
@	����ֵ��
@	ע��	
*/
void CProperty::Register( string *pString )
{
	m_Data.m_pString	= pString;
	m_Type				= EDT_String;
}

/*  
@	���ܣ�	��������������
@	������	
@	����ֵ���Ƿ�ɹ�����
@	ע��	
*/
bool CProperty::SetValue( int iValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		( *m_Data.m_pInt ) = (int)iValue;
		return true;
	case EDT_Float:
		( *m_Data.m_pFloat ) = (float)iValue;
		return true;
	case EDT_UnsignedLong:
		( *m_Data.m_pUnsignedLong ) = (unsigned long)iValue;
		return true;
	case EDT_Bool:
		( *m_Data.m_pBool ) = ( iValue == 0 ? false : true );
		return true;
	}

	return false;
}

/*  
@	���ܣ�	���ø�������ֵ
@	������	
@	����ֵ���Ƿ�ɹ�����
@	ע��	
*/
bool CProperty::SetValue( float fValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		( *m_Data.m_pInt ) = (int)fValue;
		return true;
	case EDT_Float:
		( *m_Data.m_pFloat ) = (float)fValue;
		return true;
	case EDT_UnsignedLong:
		( *m_Data.m_pUnsignedLong ) = (unsigned long)fValue;
		return true;
	case EDT_Bool:
		( *m_Data.m_pBool ) = ( fValue == .0f ? false : true );
		return true;
	}

	return false;
}

/*  
@	���ܣ�	�����޷��ų�����������ֵ
@	������	
@	����ֵ���Ƿ�ɹ�����
@	ע��	
*/
bool CProperty::SetValue( unsigned long ulValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		( *m_Data.m_pInt ) = (int)ulValue;
		return true;
	case EDT_Float:
		( *m_Data.m_pFloat ) = (float)ulValue;
		return true;
	case EDT_UnsignedLong:
		( *m_Data.m_pUnsignedLong ) = (unsigned long)ulValue;
		return true;
	case EDT_Bool:
		( *m_Data.m_pBool ) = ( ulValue == 0 ? false : true );
		return true;
	}

	return false;
}

/*  
@	���ܣ�	���ò���������ֵ
@	������	
@	����ֵ���Ƿ�ɹ�����
@	ע��	
*/
bool CProperty::SetValue( bool bValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		( *m_Data.m_pInt ) = (int)bValue;
		return true;
	case EDT_Float:
		( *m_Data.m_pFloat ) = (float)bValue;
		return true;
	case EDT_UnsignedLong:
		( *m_Data.m_pUnsignedLong ) = (unsigned long)bValue;
		return true;
	case EDT_Bool:
		( *m_Data.m_pBool ) = bValue;
		return true;
	}

	return false;
}

/*  
@	���ܣ�	�����ַ���������ֵ
@	������	
@	����ֵ���Ƿ�ɹ�����
@	ע��	
*/
bool CProperty::SetValue( const string &strValue )
{
	if( m_Type == EDT_String )
	{
		( *m_Data.m_pString ) = strValue;
		return true;
	}
	return false;
}

/*  
@	���ܣ�	��ѯ������ֵ
@	������	
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CProperty::GetValue( int &iValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		iValue = (int)( *m_Data.m_pInt );
		return true;
	case EDT_Float:
		iValue = (int)( *m_Data.m_pFloat );
		return true;
	case EDT_UnsignedLong:
		iValue = (int)( *m_Data.m_pUnsignedLong );
		return true;
	case EDT_Bool:
		iValue = (int)( *m_Data.m_pBool );
		return true;
	}
	return false;
}

/*  
@	���ܣ�	��ѯ������ֵ
@	������	
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CProperty::GetValue( float &fValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		fValue = (float)( *m_Data.m_pInt );
		return true;
	case EDT_Float:
		fValue = (float)( *m_Data.m_pFloat );
		return true;
	case EDT_UnsignedLong:
		fValue = (float)( *m_Data.m_pUnsignedLong );
		return true;
	case EDT_Bool:
		fValue = (float)( *m_Data.m_pBool );
		return true;
	}
	return false;
}

/*  
@	���ܣ�	��ѯ�����޷��ų���ֵ
@	������	
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CProperty::GetValue( unsigned long &value )
{
	switch( m_Type )
	{
	case EDT_Int:
		value = (unsigned long)( *m_Data.m_pInt );
		return true;
	case EDT_Float:
		value = (unsigned long)( *m_Data.m_pFloat );
		return true;
	case EDT_UnsignedLong:
		value = (unsigned long)( *m_Data.m_pUnsignedLong );
		return true;
	case EDT_Bool:
		value = (unsigned long)( *m_Data.m_pBool );
		return true;
	}
	return false;
}

/*  
@	���ܣ�	��ѯ������ֵ
@	������	
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CProperty::GetValue( bool &value )
{
	switch( m_Type )
	{
	case EDT_Int:
		value = ( ( *m_Data.m_pInt ) == 0 ? false : true );
		return true;
	case EDT_Float:
		value = ( ( *m_Data.m_pFloat ) == .0f ? false : true );
		return true;
	case EDT_UnsignedLong:
		value = ( ( *m_Data.m_pUnsignedLong ) == 0 ? false : true );
		return true;
	case EDT_Bool:
		value = ( *m_Data.m_pBool );
		return true;
	}
	return false;
}

/*  
@	���ܣ�	��ѯ�ַ�����ֵ
@	������	
@	����ֵ���Ƿ�ɹ�
@	ע��	
*/
bool CProperty::GetValue( string &value )
{
	if( m_Type == EDT_String )
	{
		value = ( *m_Data.m_pString );
		return true;
	}
	return false;
}

double CProperty::GetDouble( void )
{
	switch( m_Type )
	{
	case EDT_Int:
		return *m_Data.m_pInt;
	case EDT_Float:
		return ( *m_Data.m_pFloat );
	case EDT_UnsignedLong:
		return ( *m_Data.m_pUnsignedLong );
	case EDT_Bool:
		return ( *m_Data.m_pBool );
	}
	// �뽫һ���ַ�������ֵ��
	OutPutErrorMsg( "��ͼ��һ��������������ȡ��һ������" );
	return 0;
}


AISYSTEM_SPACE_END