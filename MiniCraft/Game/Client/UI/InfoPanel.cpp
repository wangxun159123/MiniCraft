#include "stdafx.h"
#include "InfoPanel.h"
#include "GUIManager.h"
#include "ObjectState.h"
#include "Building.h"
#include "AIComponent.h"
#include "GameDataDef.h"

using namespace CEGUI;

UiInfoPanel::UiInfoPanel()
:m_pLayout(nullptr)
,m_pActiveObject(nullptr)
{

}

void UiInfoPanel::Init()
{
	m_pLayout = GUIMANAGER.LoadWindowLayout("InfoPanel.layout");
	assert(m_pLayout);
	ShowInfoIcon(false);
	ShowProgressQueue(false);
}

void UiInfoPanel::Destroy()
{
	GUIMANAGER.UnloadWindowLayout(m_pLayout);
	m_pLayout = nullptr;
}

void UiInfoPanel::ShowInfoIcon( bool bShow, const std::string& imgSetName, const std::string& imgName )
{
	Window* wnd = m_pLayout->getChild("InfoIcon");
	STRING prop("set:");
	prop += imgSetName;
	prop += " image:";
	prop += imgName;
	wnd->setProperty("Image", prop);
	wnd->setVisible(bShow);
}

void UiInfoPanel::ShowProgressQueue( bool bShow )
{
	m_pLayout->getChild("InfoPanel/ProgressBar")->setVisible(bShow);
}

void UiInfoPanel::SetProgress( float fPercent )
{
	m_pLayout->getChild("InfoPanel/ProgressBar")->setProperty("CurrentProgress", Ogre::StringConverter::toString(fPercent));
}

void UiInfoPanel::SetVisible( bool bVisible )
{
	Window* wnd = m_pLayout->getChild("InfoIcon");
	wnd->setVisible(bVisible);
	ShowProgressQueue(bVisible);
}

void UiInfoPanel::Update()
{
	if (!m_pActiveObject || m_pActiveObject->GetAi()->GetCurState() != eObjectState_Produce)
	{
		SetVisible(false);
	}
	else
	{
		Building* pObj = dynamic_cast<Building*>(m_pActiveObject);
		float fProgress = pObj->GetCurProgress();
		SUnitData* unitData = &GameDataDefManager::GetSingleton().m_unitData[m_pActiveObject->GetActiveAbility()->m_param];

		ShowInfoIcon(true, m_pActiveObject->GetActiveAbility()->m_iconName, "full_image");
		float fCurProgress = fProgress / Ogre::StringConverter::parseReal(unitData->params["timecost"]);
		SetProgress(fCurProgress);
		ShowProgressQueue(true);
	}
}
