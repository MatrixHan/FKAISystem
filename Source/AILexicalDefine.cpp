#include "../PreInclude.h"
#include "../Include/AILexicalDefine.h"
#include "../Include/AICrc32.h"


AISYSTEM_SPACE_BEGIN

// �������еĶ����
STokenType G_Delimiters[NUM_DELIMITER] =	
{
	"(",	EToken_BracketOpen,		0,
	")",	EToken_BracketClose,	0,
};

/*  
@	���ܣ�	�ж��ַ��ǲ���һ�������
@	������	ch:	Ҫ�жϵ��ַ�
@	����ֵ������Ƿָ�������true
@	ע��	
*/
EToken GetDelimiterType( char ch )
{
	for( int i = 0; i < NUM_DELIMITER; ++ i )
	{
		if( G_Delimiters[i].m_szToken[0] == ch )
			return G_Delimiters[i].m_eTokenType;
	}
	return EToken_Invalid;
}



// ���еĹؼ���
STokenType G_Keywords[NUM_KEYWORDS] =
{
	"if\0",			EToken_If,			0,
	"else\0",		EToken_Else,		0,
	"switch\0",		EToken_Switch,		0,
	"case\0",		EToken_Case,		0,
	"while\0",		EToken_While,		0,
	"do\0",			EToken_Do,			0,
	"continue\0",	EToken_Continue,	0,
	"break\0",		EToken_Break,		0,
	"true\0",		EToken_True,		0,
	"false\0",		EToken_False,		0,
	"return\0",		EToken_Return,		0,
};

/*  
@	���ܣ�	��ʼ���ؼ��ֱ�
@	������	
@	����ֵ��
@	ע��	
*/
bool InitKeywordsTable( void )
{
	static Crc32 theCrc32;
	for( int i = 0; i < NUM_KEYWORDS; ++ i )
	{
		STokenType &curTokenType = G_Keywords[i];
		curTokenType.m_ulIdentifier = theCrc32.GetCRC( curTokenType.m_szToken );
	}
	return true;
}

/*  
@	���ܣ�	��ѯ�ؼ�������
@	������	lpszStr:	Ҫ��ѯ���ַ�
@	����ֵ������ַ����ǹؼ��֣�����true
@	ע��	
*/
EToken GetKeywordType( const char *lpszStr )
{
	static Crc32 theCrc32;
	unsigned long ul = theCrc32.GetCRC( lpszStr );
	for( int i = 0; i < NUM_KEYWORDS; ++ i )
	{
		if( G_Keywords[i].m_ulIdentifier == ul )
			return G_Keywords[i].m_eTokenType;
	}
	return EToken_Identifier;
}


// �������
STokenType G_OptTokensTable[NUM_OPT] = 
{
	"+\0",	EToken_Add,			0,
	"-\0",	EToken_Sub,			0,
	"*\0",	EToken_Mul,			0,
	"/\0",	EToken_Div,			0,
	"%\0",	EToken_Mod,			0,
	"^\0",	EToken_Exp,			0,
	"++\0",	EToken_Inc,			0,
	"--\0",	EToken_Dec,			0,
	"+=\0",	EToken_AssignAdd,	0,
	"-=\0",	EToken_AssignSub,	0,
	"*=\0",	EToken_AssignMul,	0,
	"/=\0",	EToken_AssignDiv,	0,
	"%=\0",	EToken_AssignMod,	0,
	"^=\0",	EToken_AssignExp,	0,
	"-\0",	EToken_Neg,			0,
	"!\0",	EToken_Not,			0,
	"$\0",	EToken_And,			0,
	"||\0",	EToken_Or,			0,
	"==\0",	EToken_Equal,		0,
	"!=\0",	EToken_NotEqual,	0,
	"@\0",	EToken_Less,		0,		// < С�ڣ���ΪXML���ܽ���<��������ʶ�����������������
	">\0",	EToken_Greater,		0,
	"<=\0",	EToken_LessEqual,	0,
	">=\0",	EToken_GreaterEqual,0,
};


/*  
@	���ܣ�	��ʼ���������
@	������	
@	����ֵ��
@	ע��	
*/
bool InitOptTokensTable( void )
{
	int len = 0;
	for( int i = 0; i < NUM_OPT; ++ i )
	{
		STokenType &curOpType = G_OptTokensTable[i];
		len = (int)strlen( curOpType.m_szToken );
		if( len == 1 )
		{
			curOpType.m_ulIdentifier = curOpType.m_szToken[0];
		}
		else if( len == 2 )
		{
			curOpType.m_ulIdentifier = curOpType.m_szToken[0];
			curOpType.m_ulIdentifier += ( curOpType.m_szToken[1] ) << 8;
		}
		else if( len == 3 )
		{
			curOpType.m_ulIdentifier = curOpType.m_szToken[0];
			curOpType.m_ulIdentifier += ( curOpType.m_szToken[1] ) << 8;
			curOpType.m_ulIdentifier += ( curOpType.m_szToken[2] ) << 16;
		}
		else
		{
			return false;
		}
	}
	return true;
}

/*  
@	���ܣ�	ȡ�õ�ǰ�ļǺ�����
@	������	lpszToken:	�ַ���
@	����ֵ�������һ����������������ͣ����򷵻� EToken_Invalid
@	ע��	
*/
EToken GetOptTokenType( const char *lpszToken )
{
	int len = (int)strlen( lpszToken );
	unsigned long identifier = 0;
	if( len == 1 )
	{
		identifier = lpszToken[0];
	}
	else if( len == 2 )
	{
		identifier = lpszToken[0];
		identifier += ( lpszToken[1] ) << 8;
	}
	else if( len == 3 )
	{
		identifier = lpszToken[0];
		identifier += ( lpszToken[1] ) << 8;
		identifier += ( lpszToken[1] ) << 16;
	}
	else
	{
		return EToken_Invalid;
	}

	for( int i = 0; i < NUM_OPT; ++ i )
	{
		STokenType &curOpType = G_OptTokensTable[i];
		if( curOpType.m_ulIdentifier == identifier )
			return curOpType.m_eTokenType;
	}
	return EToken_Invalid;
}

/*  
@	���ܣ�	�ж��ǲ���һ��������ַ�
@	������	ch:	�ַ�
@	����ֵ������ַ�����Ϊ������Ŀ�ͷ���򷵻�true�����򷵻�false
@	ע��	
*/
bool IsOptChar( char ch )
{
	for( int i = 0; i < NUM_OPT; ++ i )
	{
		STokenType &curOpType = G_OptTokensTable[i];
		if( curOpType.m_szToken[0] == ch )
			return true;
	}
	if( ch == '(' || ch == ')' )
		return true;
	return false;
}


/*  
@	���ܣ�	�ж�һ����ֵ������
@	������	
@	����ֵ��
@	ע��	
*/
EToken GetIntType( const char *lpszInt )
{
	double dValue = atof( lpszInt );
	double dTemp = .0;

	// ����
	if( IsType( dValue, (int)dValue ) )
		return EToken_Int;

	// �޷�������
	if( IsType( dValue, (unsigned int)dValue ) )
		return EToken_UnsignedInt;

	// ������
	if( IsType( dValue, (long)dValue ) )
		return EToken_Long;

	// �޷��ų�����
	if( IsType( dValue, (unsigned long)dValue ) )
		return EToken_UnsignedLong;

	return EToken_Long;
}


/*  
@	���ܣ�	�ж�һ�����ݵ�����
@	������	
@	����ֵ��
@	ע��	
*/
template <typename T>
bool IsType( double dValue, T value )
{
	double dTemp;
	dTemp = (double)value;
	if( dTemp == dValue )
		return true;
	return false;
}


AISYSTEM_SPACE_END