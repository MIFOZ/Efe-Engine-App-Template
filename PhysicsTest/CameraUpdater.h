#include <EFE.h>

using namespace efe;

class cCameraUpdater : public iUpdateable
{
public:
	cCameraUpdater(float afSpeed, cVector3f avStartPos, bool abShowFPS);
	~cCameraUpdater();

	void Update(float afFrameTime);

	void OnDraw();

	void SetActive(bool abX) {m_bActive = abX;}

private:
	cGame *g_pGame;
	iFontData* m_pFont;
	cCamera3D* m_pCamera;

	cGui *m_pGui;
	cGuiSet *m_pGuiSet;
	cGuiSkin *m_pGuiSkin;

	float m_fSpeed;
	bool m_bActive;
};
