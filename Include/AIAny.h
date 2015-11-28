/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIAny.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ʵ��һ���������������Դ洢�������͵�����
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CAIAny
+   ����:	�洢�������͵����ݣ����ܹ�ȡ������
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
class CAIAny_
{
	friend class CAIAny;
private:
	std::string m_strData;
	double		m_dData;
	bool		m_bIsNumeric;
	bool		m_bNeg;
public:
	CAIAny_( void );
	CAIAny_( const std::string strData );
	~CAIAny_(void);

	void SetData( int & value );
	void SetData( unsigned int & value );
	void SetData( long & value );
	void SetData( unsigned long & value );
	void SetData( const std::string & strData );
	void SetData( float &value );

	bool GetInt( int &ret );
	bool GetUnsignedInt( unsigned int &ret );
	bool GetLong( long &ret );
	bool GetUnsignedLong( unsigned long &ret );
	bool GetString( std::string & ret );
	bool GetFloat( float &ret );
	bool GetDoulbe( double &ret );

	template< typename T >
	void SetNumeric( T data )
	{
		m_strData = "";
		m_bIsNumeric = true;
		m_dData = (double)data;
		if( m_dData < 0 )
			m_bNeg = true;
		else
			m_bNeg = false;
	}

	bool IsNumeric( void );
};


AISYSTEM_SPACE_END