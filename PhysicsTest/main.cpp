#include <EFE.h>

#include <impl/D3D11GameSetup.h>

#include "CameraUpdater.h"

using namespace efe;

cGame *g_pGame;

int efeMain(const efe::tString &a_sCommandLine)
{

	cConfigFile *pConfig = efeNew(cConfigFile, (_W("Config.xml")));
	pConfig->Load();
	cSetupVarContainer SettingVars;
	SettingVars.AddInt("ScreenWidth", pConfig->GetInt("Screen", "Width", 1204));
	SettingVars.AddInt("ScreenHeight", pConfig->GetInt("Screen", "Height", 768));

	g_pGame = efeNew(cGame, (efeNew(cD3D11GameSetup, (0)), SettingVars));

	cCameraUpdater *pCameraUpdater = efeNew(cCameraUpdater, (5.0f, cVector3f(0), true));
	g_pGame->GetUpdater()->AddUpdate("Default", pCameraUpdater);

	g_pGame->GetResources()->LoadResourceDirsFile("resources.cfg");

	g_pGame->Run();

	efeDelete(g_pGame);

	return 0;
}