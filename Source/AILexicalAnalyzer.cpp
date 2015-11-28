#include "../PreInclude.h"
#include "../Include/AILexicalAnalyzer.h"
#include "../Include/AICrc32.h"


AISYSTEM_SPACE_BEGIN

CLexicalAnalyzer::CLexicalAnalyzer(void)
{
}

CLexicalAnalyzer::~CLexicalAnalyzer(void)
{
}

/*  
@	���ܣ�	��ʼ���ʷ�������
@	������	
@	����ֵ��
@	ע��	
*/
void CLexicalAnalyzer::Init( void )
{
	InitKeywordsTable();
	InitOptTokensTable();
}

/*  
@	���ܣ�	�����ַ���
@	������	lpszString:	Ҫ�������ַ���
			vecTokens:	�������
@	����ֵ���������ʧ�ܣ�����false
@	ע��	
*/
bool CLexicalAnalyzer::Analyse( const char * lpszString, TLexTokens & vecTokens )
{
	static Crc32 crcGen;
	unsigned int crc = crcGen.GetCRC( lpszString );
	std::map<unsigned int,TLexTokens>::iterator iter = m_Tokens.find( crc );
	if( iter != m_Tokens.end() )
	{
		vecTokens = iter->second;
		return true;
	}

	vecTokens.clear();
	if( NULL == lpszString )
		return false;

	m_nStringLen	= (int)strlen( lpszString );
	if( m_nStringLen == 0 )
		return true;

	char * pszStr = new char[m_nStringLen+1];
	memcpy( pszStr, lpszString, m_nStringLen );
	pszStr[m_nStringLen] = '\0';

	m_nCurCharPos	= 0;
	m_lpszString = lpszString;
	
	while( true )
	{
		m_curState	= ELexState_Start;
		if( ! GetNextToken() )
		{
			vecTokens.clear();
			return false;
		}

		if( m_curToken.m_eTokenType == EToken_Complete )
			break;

		vecTokens.push_back( m_curToken );
		m_curToken.m_eTokenType = EToken_Invalid;
	}
	m_Tokens.insert( make_pair( crc, vecTokens ) );
	return true;
}

/*  
@	���ܣ�	����һ���Ǻ�
@	������	
@	����ֵ���������ʧ�ܣ�����false
@	ע��	
*/
bool CLexicalAnalyzer::GetNextToken( void )
{
	if( m_nCurCharPos >= m_nStringLen )
	{
		m_curToken.m_eTokenType = EToken_Complete;
		return true;
	}
	bool bAddToLex = false;	// ��ǰ�����Ƿ����Ǻŷ�����
	bool bDone = false;		// �Ƿ���ɵ�ǰ�ǺŵĽ���
	char cCurChar = 0;		// ��ǰ�ַ�
	static char szBuffer[1024];
	static char szOpt[8];
	int w = 0;
	int optW = 0;
	EToken	curTokenType;
	memset( szBuffer, 0, sizeof( szBuffer ) );
	memset( szOpt, 0, sizeof( szOpt ) );

	while( true )
	{
		cCurChar = m_lpszString[m_nCurCharPos++];
		if( cCurChar == '\0' )
			break;
		bAddToLex = true;

		switch( m_curState )
		{
			//--------��ʼ״̬
		case ELexState_Start:
			{
				// �Թ�ǰ���ո�
				if( IsWhiteChar( cCurChar) )
				{
					bAddToLex = false;
				}
				// �Ƿ���һ������
				else if( IsNumeric( cCurChar ) )
				{
					m_curState = ELexState_Int;
				}
				// �Ƿ���һ��������
				else if( cCurChar == '.' )
				{
					m_curState = ELexState_Float;
				}
				// �Ƿ��Ǳ�ʶ��
				else if( IsCharIdentifier( cCurChar ) )
				{
					m_curState = ELexState_Identifier;
				}
				// �ָ���
				else if( GetDelimiterType( cCurChar ) != EToken_Invalid )
				{
					m_curState = ELexState_Delimiter;
					curTokenType = GetDelimiterType( cCurChar );
					bDone = true;
				}
				// ��ʼ�ַ�������
				else if( cCurChar == '"' )
				{
					m_curState = ELexState_String;
					bAddToLex = false;
				}
				// �����
				else if( IsOptChar( cCurChar ) )
				{
					m_curState = ELexState_Operator;
					szOpt[optW++] = cCurChar;
				}
				// �Ƿ��ַ�������ʧ��
				else
				{
					return false;
				}
			}
			break;

			//--------����״̬
		case ELexState_Int:
			{
				// �������ֵ�ǰ״̬
				if( IsNumeric( cCurChar ) )
					m_curState = ELexState_Int;
				// �����С���㣬��ת��������
				else if( cCurChar == '.' )
					m_curState = ELexState_Float;
				// ����ǿո����ʶ��
				else if( IsWhiteChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
				}
				// ���������������ʶ��
				else if( IsOptChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
					-- m_nCurCharPos;
				}
				// �������ǷǷ���
				else
					return false;
			}
			break;

			//--------������״̬
		case ELexState_Float:
			{
				if( IsNumeric( cCurChar ) )
					m_curState = ELexState_Float;
				// ����ǿո����ʶ��
				else if( IsWhiteChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
				}
				// ���������������ʶ��
				else if( IsOptChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
					-- m_nCurCharPos;
				}
				// �������ǷǷ���
				else
					return false;
			}
			break;

			//--------��ʶ��״̬
		case ELexState_Identifier:
			{
				// ����Ǳ�ʶ���ַ����򱣳ֵ�ǰ״̬
				if( IsCharIdentifier( cCurChar ) )
				{
					m_curState = ELexState_Identifier;
				}
				// ����ǿո����ʶ��
				else if( IsWhiteChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
				}
				// ���������������ʶ��
				else if( IsOptChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
					-- m_nCurCharPos;
				}
				// �������ǷǷ���
				else
					return false;
			}
			break;

			//---------�ַ���
		case ELexState_String:
			{
				// ����� " �ַ���ʶ�����
				if( cCurChar == '"' )
				{
					bAddToLex = false;
					m_curState = ELexState_StringEnd;
				}
				// �����ת���ַ�����ת��ת���ַ�״̬
				else if( cCurChar == '\\' )
				{
					bAddToLex = false;
					m_curState = ELexState_StringEscape;
				}
				// �����ַ�ȫ����ӵ��ַ�����
			}
			break;

			//---------ת���ַ�
		case ELexState_StringEscape:
			{
				// TODO ת����ǰ�ַ�
				m_curState = ELexState_String;
			}
			break;

			//---------����ַ���ʶ��
		case ELexState_StringEnd:
			{
				bAddToLex = false;
				bDone = true;
			}
			break;

			//---------�����
		case ELexState_Operator:
			{
				szOpt[optW++] = cCurChar;
				if( GetOptTokenType( szOpt ) == EToken_Invalid )
				{
					bAddToLex = false;
					bDone = true;
					-- m_nCurCharPos;
				}
			}
			break;


		}	// end switch

		if( bAddToLex )
			szBuffer[w++] = cCurChar;
		if( bDone )
			break;

	}
	szBuffer[w++] = '\0';

	// ȷ���Ǻ�����
	switch( m_curState )
	{
	case ELexState_Int:
		curTokenType = GetIntType( szBuffer );
		break;

	case ELexState_Float:
		curTokenType = EToken_Float;
		break;

	case ELexState_Identifier:
		curTokenType = GetKeywordType( szBuffer );
		break;

	case ELexState_Delimiter:
		curTokenType = GetDelimiterType( szBuffer[0] );
		break;

	case ELexState_Operator:
		curTokenType = GetOptTokenType( szBuffer );
		break;

	case ELexState_Start:
	default:
		curTokenType = EToken_Complete;
		break;
	}
	m_curToken.m_strTokenString = szBuffer;
	m_curToken.m_eTokenType		= curTokenType;

	return true;
}

bool CLexicalAnalyzer::IsWhiteChar( char ch )
{
	if( ch == ' ' || ch == '\t' || ch == '\n' )
		return true;
	return false;
}

bool CLexicalAnalyzer::IsNumeric( char ch )
{
	if( ch >= '0' && ch <= '9' )
		return true;
	return false;
}

bool CLexicalAnalyzer::IsCharIdentifier(char ch)
{
	if( ( ch >= '0' && ch <= '9' ) ||
		( ch >= 'A' && ch <= 'Z' ) ||
		( ch >= 'a' && ch <= 'z' ) ||
		( ch == '_' ) )
		return true;
	return false;
}

AISYSTEM_SPACE_END