#include <EFE.h>

using namespace efe;

class cSceneUpdater : public iUpdateable
{
public:
	cSceneUpdater();
	~cSceneUpdater();

	void Update(float afFrameTime);

	void OnDraw();

private:
	bool LoadTest(const tString &a_sFileName, int a_lIteration);

	cMeshEntity *m_pGround;
	iPhysicsBody *m_pGroundBody;

	cMeshEntity *m_pCube;
	iPhysicsBody *m_pCubeBody;

	cNeuralNetwork *m_pNet;
};
