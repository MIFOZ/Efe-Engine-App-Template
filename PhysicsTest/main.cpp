#include <EFE.h>

#include <impl/D3D11GameSetup.h>

#include "CameraUpdater.h"
#include "SceneUpdater.h"

using namespace efe;

cGame *g_pGame;

int efeMain(const efe::tString &a_sCommandLine)
{

	cConfigFile *pConfig = efeNew(cConfigFile, (_W("Config.xml")));
	pConfig->Load();
	cSetupVarContainer SettingVars;
	SettingVars.AddInt("ScreenWidth", pConfig->GetInt("Screen", "Width", 1204));
	SettingVars.AddInt("ScreenHeight", pConfig->GetInt("Screen", "Height", 768));
	SettingVars.AddInt("Multisampling", 1);

	g_pGame = efeNew(cGame, (efeNew(cD3D11GameSetup, (0)), SettingVars));

	g_pGame->GetResources()->LoadResourceDirsFile("resources.cfg");

	cCameraUpdater *pCameraUpdater = efeNew(cCameraUpdater, (5.0f, cVector3f(0.0f, 5.0f, 0.0f), true));
	g_pGame->GetUpdater()->AddUpdate("Default", pCameraUpdater);

	cSceneUpdater *pSceneUpdater = efeNew(cSceneUpdater, ());
	g_pGame->GetUpdater()->AddUpdate("Default", pSceneUpdater);

	g_pGame->Run();

	efeDelete(g_pGame);

	return 0;
}