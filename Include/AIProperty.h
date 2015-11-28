/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIProperty.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ���Զ�����
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	
+   ����:	
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
class CProperty
{
	////////////////////////////////////////////
	//	���Ͷ���
public:
	union UData
	{
		int				*m_pInt;			
		float			*m_pFloat;
		bool			*m_pBool;
		unsigned long	*m_pUnsignedLong;
		std::string		*m_pString;
	};

	enum EDataType
	{
		EDT_Int,
		EDT_Float,
		EDT_Bool,
		EDT_UnsignedLong,
		EDT_String,
		EDT_End
	};

	////////////////////////////////////////////
	//	���ݳ�Ա
private:


	UData			m_Data;		// ����
	EDataType		m_Type;		// ��������
	std::string		m_strName;	// ����
	unsigned long	m_uiID;		// ID

	////////////////////////////////////////////
	//	����/����
public:
	CProperty( void );
	~CProperty( void );

	////////////////////////////////////////////
	//	�ṩ�����Լ��Ľӿ�
public:
	// ��������
	void SetName( const std::string	& strName )	{ m_strName = strName; }
	// ��������
	const std::string & GetName( void )			{ return m_strName; }
	// ����ID
	void SetID( unsigned long uiID )			{ m_uiID = uiID; }
	// ����ID
	unsigned long GetID( void )					{ return m_uiID; }
	// ע������
	void Register( int *pInt );
	void Register( float *pFloat );
	void Register( unsigned long *pUnsignedLog );
	void Register( bool *pBool );
	void Register( std::string *pString );

	////////////////////////////////////////////
	//	�����ӿ� ���ú�ȡ������ֵ
public:
	// ����ֵ
	bool SetValue( int iValue );
	bool SetValue( float fValue );
	bool SetValue( bool bValue );
	bool SetValue( unsigned long ulValue );
	bool SetValue( const std::string & strVlaue );

	// ����ֵ
	bool GetValue( int &iValue );
	bool GetValue( float &fValue );
	bool GetValue( bool &bValue );
	bool GetValue( unsigned long &ulValue );
	bool GetValue( std::string &strValue );

	double GetDouble( void );

	EDataType GetType( void )					{ return m_Type; }

	////////////////////////////////////////////
	//	���������
public:


};




AISYSTEM_SPACE_END