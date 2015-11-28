/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIPropertySet.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ���Լ���
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AIProperty.h"
#include "IAIGlobalFunc.h"

//--------------------------------------------------------------------

#pragma warning(disable:4251)

AISYSTEM_SPACE_BEGIN

//--------------------------------------------------------------------

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CPropertySet
+   ����:	���Լ�
+   ����:	�ṩ����ͷ������ԵĽӿ�
-----------------------------------------------------------------
*****************************************************************/
class CPropertySet
{
	////////////////////////////////////////////
	//	���ݳ�Ա
private:
	// �����ֵ�
	typedef std::map<unsigned long,CProperty> TPropertyDictionary;
	typedef TPropertyDictionary::iterator TPropertyIter;

	TPropertyDictionary	m_Properties;	// �����ֵ�

	////////////////////////////////////////////
	//	����/����
public:
	CPropertySet( void );
	~CPropertySet( void );

	////////////////////////////////////////////
	//	�����ӿ�
public:
	// ����һ������
	CProperty *FindProperty( unsigned long ID );
	CProperty *FindProperty( const std::string & strName );

	// ע�����ԣ�����һ��ID
	unsigned long Register( const std::string & strName, int *pValue )				{ return __Register( strName, pValue ); }
	unsigned long Register( const std::string & strName, float *pValue )			{ return __Register( strName, pValue ); }
	unsigned long Register( const std::string & strName, bool *pValue )				{ return __Register( strName, pValue ); }
	unsigned long Register( const std::string & strName, unsigned long *pValue )	{ return __Register( strName, pValue ); }
	unsigned long Register( const std::string & strName, std::string *pValue )		{ return __Register( strName, pValue ); }

	// ��������ֵ
	bool SetValue( const std::string & strName, int value )							{ return __SetValue( strName, value );	}
	bool SetValue( const std::string & strName, float value )						{ return __SetValue( strName, value );	}
	bool SetValue( const std::string & strName, bool value )						{ return __SetValue( strName, value );	}
	bool SetValue( const std::string & strName, unsigned long value )				{ return __SetValue( strName, value );	}
	bool SetValue( const std::string & strName, const std::string & value )			{ return __SetValue( strName, value );	}

	bool SetValue( unsigned long ulID, int value )									{ return __SetValue( ulID, value );		}
	bool SetValue( unsigned long ulID, float value )								{ return __SetValue( ulID, value );		}
	bool SetValue( unsigned long ulID, bool value )									{ return __SetValue( ulID, value );		}
	bool SetValue( unsigned long ulID, unsigned long value )						{ return __SetValue( ulID, value );		}
	bool SetValue( unsigned long ulID, const std::string & value )					{ return __SetValue( ulID, value );		}

	// ����ȡ����ֵ
	bool GetValue( const std::string & strName, int & value )						{ return __GetValue( strName, value );	}
	bool GetValue( const std::string & strName, float & value )						{ return __GetValue( strName, value );	}
	bool GetValue( const std::string & strName, bool & value )						{ return __GetValue( strName, value );	}
	bool GetValue( const std::string & strName, unsigned long & value )				{ return __GetValue( strName, value );	}
	bool GetValue( const std::string & strName, std::string & value )				{ return __GetValue( strName, value );	}

	bool GetValue( unsigned long ulID, int & value )								{ return __GetValue( ulID, value );		}
	bool GetValue( unsigned long ulID, float & value )								{ return __GetValue( ulID, value );		}
	bool GetValue( unsigned long ulID, bool & value )								{ return __GetValue( ulID, value );		}
	bool GetValue( unsigned long ulID, unsigned long & value )						{ return __GetValue( ulID, value );		}
	bool GetValue( unsigned long ulID, std::string & value )						{ return __GetValue( ulID, value );		}


	////////////////////////////////////////////
	//	˽�нӿ�
private:
	/*  
	@	���ܣ�	����һ������ID
	@	������	
	@	����ֵ������ID
	@	ע��	
	*/
	unsigned long __GenerateID( const char *lpszStr );

	/*  
	@	���ܣ�	ע��һ��������������
	@	������	strName:	���Ե�����
				pValue:		����ָ��
	@	����ֵ������ID��0��ʾע��ʧ��
	@	ע��	ģ�巽��
	*/
	template<typename T>
	inline unsigned long __Register( const std::string & strName, T *pValue );

	/*  
	@	���ܣ�	���������������Ե�ֵ
	@	������	strName:	��������
				value:		ֵ
	@	����ֵ���Ƿ�ɹ�
	@	ע��	ģ�巽��
	*/
	template<typename T>
	inline bool __SetValue( const std::string & strName, T value );

	/*  
	@	���ܣ�	����ID�������Ե�ֵ
	@	������	ID:		���Ե�ID
				value:	ֵ
	@	����ֵ���Ƿ�ɹ�
	@	ע��	ģ�巽��
	*/
	template<typename T>
	inline bool __SetValue( unsigned long uiID, T value );

	/*  
	@	���ܣ�	�������ַ������Ե�ֵ
	@	������	strName:	��������
				value:		ֵ
	@	����ֵ���Ƿ�ɹ�
	@	ע��	ģ�巽��
	*/
	template<typename T>
	inline bool __GetValue( const std::string & strName, T & value );

	/*  
	@	���ܣ�	����ID���÷������Ե�ֵ
	@	������	ID:		���Ե�ID
				value:	ֵ
	@	����ֵ���Ƿ�ɹ�
	@	ע��	ģ�巽��
	*/
	template<typename T>
	inline bool __GetValue( unsigned long uiID, T & value );

};



/*  
@	���ܣ�	ע��һ��������������
@	������	strName:	���Ե�����
			pValue:		����ָ��
@	����ֵ������ID��0��ʾע��ʧ��
@	ע��	ģ�巽��
*/
template< typename T >
inline unsigned long CPropertySet::__Register(const std::string &strName, T* pValue)
{
	unsigned long ID = __GenerateID( strName.c_str() );

	// ���ֲ����ظ�
	TPropertyIter iter = m_Properties.find( ID );
	if( iter != m_Properties.end() )
		return 0;

	static CProperty NullProperty;
	std::pair<TPropertyIter,bool> res = m_Properties.insert( std::make_pair( ID, NullProperty ) );
	if( res.second == false )
	{
		OutPutErrorMsg( "�������ֵ����������ʧ�ܣ�%s", strName.c_str() );
		return 0;
	}
	CProperty & NewProperty = ( res.first )->second;
	NewProperty.SetName( strName );
	NewProperty.SetID( ID );
	NewProperty.Register( pValue );
	return NewProperty.GetID();
}

/*  
@	���ܣ�	���������������Ե�ֵ
@	������	strName:	��������
			value:		ֵ
@	����ֵ���Ƿ�ɹ�
@	ע��	ģ�巽��
*/
template< typename T >
inline bool CPropertySet::__SetValue( const std::string & strName, T value )
{
	if( m_Properties.size() == 0 )
		return false;

	unsigned long ID = __GenerateID( strName.c_str() );
	TPropertyIter iter = m_Properties.find( ID );
	if( iter == m_Properties.end() )
		return false;
	iter->second.SetValue( value );
	return true;
}

/*  
@	���ܣ�	����ID�������Ե�ֵ
@	������	ID:		���Ե�ID
			value:	ֵ
@	����ֵ���Ƿ�ɹ�
@	ע��	ģ�巽��
*/
template< typename T >
inline bool CPropertySet::__SetValue( unsigned long ID, T value )
{
	if( m_Properties.size() == 0 )
		return false;

	TPropertyIter iter = m_Properties.find( ID );
	if( iter == m_Properties.end() )
		return false;
	iter->second.SetValue( value );
	return true;
}

/*  
@	���ܣ�	�������ַ������Ե�ֵ
@	������	strName:	��������
			value:		ֵ
@	����ֵ���Ƿ�ɹ�
@	ע��	ģ�巽��
*/
template< typename T >
inline bool CPropertySet::__GetValue( const std::string & strName, T & value )
{
	if( m_Properties.size() == 0 )
		return false;

	unsigned long ID = __GenerateID( strName.c_str() );
	TPropertyIter iter = m_Properties.find( ID );
	if( iter == m_Properties.end() )
		return false;
	return iter->second.GetValue( value );
}

/*  
@	���ܣ�	����ID���÷������Ե�ֵ
@	������	ID:		���Ե�ID
			value:	ֵ
@	����ֵ���Ƿ�ɹ�
@	ע��	ģ�巽��
*/
template< typename T >
inline bool CPropertySet::__GetValue( unsigned long ID, T & value )
{
	if( m_Properties.size() == 0 )
		return false;

	TPropertyIter iter = m_Properties.find( ID );
	if( iter == m_Properties.end() )
		return false;
	return iter->second.GetValue( value );
}



AISYSTEM_SPACE_END

#pragma warning(default:4251)