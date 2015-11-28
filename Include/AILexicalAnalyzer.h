/********************************************************************
// FileName: d:\work\FKAISystem\Include\AILexicalAnalyzer.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ����ʷ�������
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AILexicalDefine.h"



AISYSTEM_SPACE_BEGIN


struct CToken
{
	EToken		m_eTokenType;		// �Ǻ�����
	std::string	m_strTokenString;	// �Ǻ��ַ���
};

typedef std::vector<CToken> TLexTokens;

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CLexicalAnalyzer
+   ����:	�ʷ�������
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
class CLexicalAnalyzer
{
	////////////////////////////////////////////
	//	���ݳ�Ա
private:
	const char	*m_lpszString;	// Ҫ�������ַ���
	int			m_nStringLen;	// Ҫ�������ַ����ĳ���
	int			m_nCurCharPos;	// ��ǰ���ڷ������ַ�λ��
	CToken		m_curToken;		// ��ǰ�����ļǺ�
	ELexState	m_curState;		// ��ǰ����״̬
	std::map<unsigned int,TLexTokens> m_Tokens;

	////////////////////////////////////////////
	//	����/����
public:
	CLexicalAnalyzer(void);
	~CLexicalAnalyzer(void);

	////////////////////////////////////////////
	//	�����ӿ�
public:
	/*  
	@	���ܣ�	��ʼ���ʷ�������
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void Init( void );

	/*  
	@	���ܣ�	�����ַ���
	@	������	lpszString:	Ҫ�������ַ���
				vecTokens:	�������
	@	����ֵ���������ʧ�ܣ�����false
	@	ע��	
	*/
	bool Analyse( const char * lpszString, TLexTokens & vecTokens );

	/*  
	@	���ܣ�	����һ���Ǻ�
	@	������	
	@	����ֵ���������ʧ�ܣ�����false
	@	ע��	
	*/
	bool GetNextToken( void );

	bool IsWhiteChar( char ch );
	bool IsNumeric( char ch );
	bool IsCharIdentifier( char ch );
	
};


AISYSTEM_SPACE_END