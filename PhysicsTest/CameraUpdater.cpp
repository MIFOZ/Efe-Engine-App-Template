/*
* Copyright 2007-2010 (C) - Frictional Games
*
* This file is part of HPL1Engine
*
* For conditions of distribution and use, see copyright notice in LICENSE-tests
*/
#include "CameraUpdater.h"

extern cGame *g_pGame;

cCameraUpdater::cCameraUpdater(float afSpeed, cVector3f avStartPos, bool abShowFPS)
	: iUpdateable("SimpleCamera")
{
	m_fSpeed = afSpeed;

	//Add actions
	g_pGame->GetInput()->AddAction(efeNew(cActionKeyboard, ("Escape", g_pGame->GetInput(), eKey_ESCAPE)));

	g_pGame->GetInput()->AddAction(efeNew(cActionKeyboard, ("Forward", g_pGame->GetInput(), eKey_w)));
	g_pGame->GetInput()->AddAction(efeNew(cActionKeyboard, ("Backward", g_pGame->GetInput(), eKey_s)));
	g_pGame->GetInput()->AddAction(efeNew(cActionKeyboard, ("Right", g_pGame->GetInput(), eKey_d)));
	g_pGame->GetInput()->AddAction(efeNew(cActionKeyboard, ("Left", g_pGame->GetInput(), eKey_a)));

	g_pGame->GetInput()->GetLowLevel()->LockInput(true);

	//g_pGame->GetGraphics()->GetLowLevel()->ShowCursor(true);

	cWorld3D *pWorld = g_pGame->GetScene()->CreateWorld3D("Test");
	g_pGame->GetScene()->SetWorld3D(pWorld);

	m_pCamera = g_pGame->GetScene()->CreateCamera3D(eCameraMoveMode_Fly);
	g_pGame->GetScene()->SetCamera(m_pCamera);
	m_pCamera->SetPosition(avStartPos);

	m_pGui = g_pGame->GetGui();
	m_pGuiSkin = m_pGui->CreateSkin("gui_default.skin");
	m_pGuiSet = m_pGui->CreateSet("Text", m_pGuiSkin);

	if (abShowFPS)
		m_pFont = g_pGame->GetResources()->GetFontManager()->CreateFontData("bebas.ttf", 12, 32, 128);
	else
		m_pFont = NULL;

	m_bActive = true;
}

//-----------------------------------------------------------------------

cCameraUpdater::~cCameraUpdater()
{

}

//-----------------------------------------------------------------------

void cCameraUpdater::Update(float afFrameTime)
{
	if (g_pGame->GetInput()->IsTriggered("Escape"))
	{
		g_pGame->Exit();
	}

	if (m_bActive == false) return;

	float fMul = g_pGame->GetStepSize();

	if (g_pGame->GetInput()->IsTriggered("Forward")) m_pCamera->MoveForward(m_fSpeed * fMul);
	if (g_pGame->GetInput()->IsTriggered("Backward")) m_pCamera->MoveForward(-m_fSpeed* fMul);
	if (g_pGame->GetInput()->IsTriggered("Right")) m_pCamera->MoveRight(m_fSpeed * fMul);
	if (g_pGame->GetInput()->IsTriggered("Left")) m_pCamera->MoveRight(-m_fSpeed * fMul);

	cVector2f vRel = g_pGame->GetInput()->GetMouse()->GetRelPosition();
	m_pCamera->AddYaw(-vRel.x * 0.003f);
	m_pCamera->AddPitch(-vRel.y * 0.003f);
}

//-----------------------------------------------------------------------

void cCameraUpdater::OnDraw()
{
	if (m_pFont)
	{
		m_pGuiSet->DrawFont(_W("FPS: ") + cString::ToStringW(g_pGame->GetFPS()), m_pFont, cVector3f(5, 5, 5), 14, cColor(1, 1),
			eFontAlign_Left, eGuiMaterial_FontNormal);
	}
}

//-----------------------------------------------------------------------
