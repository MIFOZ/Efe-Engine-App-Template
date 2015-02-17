
#include "SceneUpdater.h"

extern cGame *g_pGame;

cSceneUpdater::cSceneUpdater()
	: iUpdateable("SceneCamera")
{
	g_pGame->GetPhysics()->LoadSurfaceData("materials.cfg");
	//iPhysicsWorld *pPhysicsWorld = g_pGame->GetPhysics()->CreateWorld(true);
	//g_pGame->GetScene()->GetWorld3D()->SetPhysicsWorld(pPhysicsWorld);

	cMesh *pMesh = g_pGame->GetGraphics()->GetMeshCreator()->CreateBox("Ground", cVector3f(20.0f, 0.5f, 20.0f), "floor");
	m_pGround = g_pGame->GetScene()->GetWorld3D()->CreateMeshEntity("Ground", pMesh);
	//iCollideShape *pShape = g_pGame->GetScene()->GetWorld3D()->GetPhysicsWorld()->CreateMeshShape(pMesh->GetSubMesh(0)->GetVertexBuffer());
	//m_pGroundBody = g_pGame->GetScene()->GetWorld3D()->GetPhysicsWorld()->CreateBody("Ground_body", pShape);

	pMesh = g_pGame->GetGraphics()->GetMeshCreator()->CreateBox("Cube", cVector3f(5.0f, 4.5f, 5.0f), "floor");
	m_pCube = g_pGame->GetScene()->GetWorld3D()->CreateMeshEntity("Cube", pMesh);
	//pShape = g_pGame->GetScene()->GetWorld3D()->GetPhysicsWorld()->CreateMeshShape(pMesh->GetSubMesh(0)->GetVertexBuffer());
	//m_pCubeBody = g_pGame->GetScene()->GetWorld3D()->GetPhysicsWorld()->CreateBody("Cube_body", pShape);
	//m_pCubeBody->SetWorldPosition(cVector3f(0, 5, 0));

	tUIntVec vTopology;
	vTopology.push_back(2);
	vTopology.push_back(3);
	vTopology.push_back(1);
	m_pNet = efeNew(cNeuralNetwork, (vTopology));

	LoadTest("Tests.csv", 100);

}

//-----------------------------------------------------------------------

cSceneUpdater::~cSceneUpdater()
{

}

//-----------------------------------------------------------------------

void cSceneUpdater::Update(float afFrameTime)
{
	//m_pCube->SetMatrix(m_pCubeBody->GetLocalMatrix());
}

//-----------------------------------------------------------------------

void cSceneUpdater::OnDraw()
{
	
}

//-----------------------------------------------------------------------

bool cSceneUpdater::LoadTest(const tString &a_sFileName, int a_lIteration)
{
	FILE *pFile;
	fopen_s(&pFile, a_sFileName.c_str(), "r");
	if (pFile == NULL)
		return false;

	enum eTestMap
	{
		eTestMap_Input,
		eTestMap_Target
	};
	std::vector<eTestMap> vMap;
	struct cTest
	{
		tFloatVec inputs;
		tFloatVec targets;
	};
	std::vector<cTest> vTests;

	int lInputNum = 0;
	int lTargetNum = 0;

	char Str[256];
	fgets(Str, sizeof(Str), pFile);
	tStringList lstColumns;
	char *pContext = NULL;
	char *pToken = strtok_s(Str, ";,", &pContext);
	while (pToken != NULL)
	{
		tString sCleared = cString::ReplaceCharTo(pToken, "\n", "");
		if (!strcmp(sCleared.c_str(), "i"))
			vMap.push_back(eTestMap_Input);
		if (!strcmp(sCleared.c_str(), "t"))
			vMap.push_back(eTestMap_Target);

		pToken = strtok_s(NULL, ";,", &pContext);
	}

	while (!feof(pFile))
	{
		vTests.push_back(cTest());
		cTest &Test = vTests.back();

		fgets(Str, sizeof(Str), pFile);

		pContext = NULL;
		pToken = strtok_s(Str, ";,", &pContext);
		int lColumn = 0;
		while (pToken != NULL)
		{
			tString sCleared = cString::ReplaceCharTo(pToken, "\n", "");
			if (vMap[lColumn] == eTestMap_Input)
				Test.inputs.push_back(cString::ToFloat(sCleared.c_str(), 0));
			else if (vMap[lColumn] == eTestMap_Target)
				Test.targets.push_back(cString::ToFloat(sCleared.c_str(), 0));

			lColumn++;

			pToken = strtok_s(NULL, ";,", &pContext);
		}
	}

	for (int i = 0; i < a_lIteration; i++)
	{
		for (cTest &Test : vTests)
		{
			m_pNet->Test(Test.inputs, Test.targets);
		}
	}
	return true;
}

//-----------------------------------------------------------------------
