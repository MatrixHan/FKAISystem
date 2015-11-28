#include "TestFKAISystem/stdafx.h"
#include "Monster.h"

//--------------------------------------------------------------------
CMonster::CMonster()
	 : m_unHP			( 0 )
	 , m_unID			( 0 )
{
	m_szName.empty();
}
//--------------------------------------------------------------------
CMonster::~CMonster()
{
	m_szName.empty();
	m_unHP = 0;
	m_unID = 0;
}
//--------------------------------------------------------------------
void CMonster::Init( const std::string p_szStateMachineName )
{
	if ( ! this->InitAISystem(p_szStateMachineName) )
	{
		std::cout << "��ʼ��AIϵͳ������ʧ��!" << std::endl;
	}
	this->AIStartUp();
}
//--------------------------------------------------------------------
void CMonster::Update( float fElapsedTimes )
{
	this->AIUpdate( fElapsedTimes );
}
//--------------------------------------------------------------------
void CMonster::Destory()
{
	this->AIShutDown();
}
//--------------------------------------------------------------------
void CMonster::_RegisterProperties()
{
	RegisterProperty( "����ֵ", &(m_unHP));
	RegisterProperty( "ΨһID", &(m_unID));
	RegisterProperty( "����", &(m_szName)); 
}
//--------------------------------------------------------------------
CAttackBehavior* CMonster::CreateBehavior( FKAISystem::CBehaviorParams *pBehaviorParams )
{
	m_pAttack = new CAttackBehavior();
	m_pAttack->SetMaster( this );
	return m_pAttack;
}
//--------------------------------------------------------------------