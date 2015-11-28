#include "../PreInclude.h"
#include "../Include/AIpropertyset.h"
#include "../Include/AICrc32.h"


using namespace std;


AISYSTEM_SPACE_BEGIN



/*  
@	���ܣ�	���캯��
@	������	
@	����ֵ��
@	ע��	
*/
CPropertySet::CPropertySet( void )
{

}

/*  
@	���ܣ�	��������
@	������	
@	����ֵ��
@	ע��	
*/
CPropertySet::~CPropertySet( void )
{

}

/*  
@	���ܣ�	����ID����һ������
@	������	ID:	
@	����ֵ��
@	ע��	
*/
CProperty *CPropertySet::FindProperty(unsigned long ID)
{
	if( m_Properties.size() == 0 )
		return NULL;

	TPropertyIter iter = m_Properties.find( ID );
	if( iter != m_Properties.end() )
	{
		return &iter->second;
	}

	return NULL;
}

/*  
@	���ܣ�	�������ֲ���һ������
@	������	strName:	��������
@	����ֵ��
@	ע��	
*/
CProperty *CPropertySet::FindProperty(const std::string &strName)
{
	if( m_Properties.size() == 0 )
		return NULL;

	unsigned long ID = __GenerateID( strName.c_str() );
	TPropertyIter iter = m_Properties.find( ID );
	if( iter != m_Properties.end() )
	{
		return &iter->second;
	}

	return NULL;
}

/*  
@	���ܣ�	����һ������ID
@	������	
@	����ֵ������ID
@	ע��	
*/
unsigned long CPropertySet::__GenerateID( const char *lpszStr )
{
	static Crc32 theCrc32Gen;
	return theCrc32Gen.GetCRC( lpszStr );
}



AISYSTEM_SPACE_END