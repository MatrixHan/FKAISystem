#include "../PreInclude.h"
#include "../Include/IAIBehavior.h"


AISYSTEM_SPACE_BEGIN




/*  
@	���ܣ�	���캯������ʼ�����ݳ�Ա
@	������	
@	����ֵ��
@	ע��	
*/
IAIBehavior::IAIBehavior(void)
: m_uiAIType( 0 )
, m_pAIObject( NULL )
, m_bStopped( false )
{
}

/*  
@	���ܣ�	��������
@	������	
@	����ֵ��
@	ע��	
*/
IAIBehavior::~IAIBehavior(void)
{
}

/*  
@	���ܣ�	����AI����һЩ���µĲ��ԣ��������û�ʵ�ֵĸ��·���
@	������	fElpasedTimes:	��ȥ��ʱ��
@	����ֵ��������Ϊ��ִ��״̬
@	ע��	
*/
EAIBehaviorState IAIBehavior::RealUpdate( float fElpasedTimes )
{
	if( m_bStopped )
		return EAIBS_Succeed;
	return Update( fElpasedTimes );
}


AISYSTEM_SPACE_END