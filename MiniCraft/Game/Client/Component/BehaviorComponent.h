/********************************************************************
	created:	27:3:2013   22:24
	filename	BehaviorComponent.h
	author:		maval

	purpose:	行为组件,采用行为树来构建NPC
*********************************************************************/

#ifndef BehaviorComponent_h__
#define BehaviorComponent_h__

#include "Component.h"
#include "KratosPrerequisites.h"

class aiBehaviorTreeTemplate;
class aiBlackBoard;
class FactionAI;

class BehaviorComponent : public Component
{
public:
	BehaviorComponent(SelectableObject* pOwner);
	~BehaviorComponent();

public:
	virtual void	Update(float dt);
	//设置该单位要应用的行为树模板
	void			SetTempalte(const STRING& name);

private:
	aiBehaviorTreeTemplate*	m_pTemplate;
	aiBlackBoard*			m_pOwnBB;		//该单位独立的行为树黑板
	STRING					m_curBehavior;	//当前所处行为
};

#endif // BehaviorComponent_h__