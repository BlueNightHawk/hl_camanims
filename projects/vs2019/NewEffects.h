/******************************
MOD			:	Cookie's Half-Life: Updated
FILE		:	neweffects.h
FILE DESC	:	New Effects/Entities for the mod
CREDITS		:	sourcemodding.net, twhl.info
*******************************/

#ifndef NEW_EFFECTS
 
#include "extdll.h"		// Required for KeyValueData & Export Parts.
#include "util.h"		// Required Consts & Macros.
#include "cbase.h"		// Required for inheriting from CBaseAnimating.

/*******************************

ENV_MODEL

*******************************/

#define ENV_MODEL

class CEnvModel : public CBaseAnimating
{
private:
	void Spawn(void);
	// This float controls the model's scale, default is 1.0;
	float m_fModelScale = 1.0f;

	// m_iCollisionMode sets the current collision type, manual or sequence.
	// m_iSequence is an animation loader, telling the game which animation to load.
	unsigned short m_iCollisionMode, m_iSequence;

	// KeyValues
	bool KeyValue(KeyValueData* pkvd);
	Vector mins = {0, 0, 0}, 
		   maxs = {0, 0, 0};

	// m_bDebugBB toggles whether or not the user wants to see the collision box for models.
	// m_bAnimate toggles whether or not the model is playing an animation.
	bool m_bDebugBB = false, m_bAnimate = false;

	// Updates the model frame-by-frame, or by a custom timer.
	void EXPORT Animate(void);

	// m_flAnimationSpeed sets the animation playback speed, from 0.0. Default is 1.0.
	float m_flAnimationSpeed = 0.0f;

	#define ENV_MODEL_IS_SOLID 1
	#define ENV_MODEL_DEBUG_BB 2
	#define ENV_MODEL_ANIMATED 4
};

/*******************************

ENV_FOG

*******************************/

class CEnvFog : public CBaseEntity
{
public:
	void Spawn(void);
	void SendInitMessages(CBaseEntity* pPlayer = NULL);
	bool KeyValue(KeyValueData* pkvd);
	void UpdateFog(bool isOn, bool doBlend, CBaseEntity* pPlayer);
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value);

	virtual bool Save(CSave& save);
	virtual bool Restore(CRestore& restore);

public:
	static void SetCurrentEndDist(int enddist, float blendtime);
	static int GetCurrentEndDist(void) { return g_iCurrentEndDist; }

	static void FogThink(void);
	static bool CheckBBox(edict_t* pplayer, edict_t* pedict);

private:
	static TYPEDESCRIPTION m_SaveData[];

	int m_iStartDist;
	int m_iEndDist;
	float m_flBlendTime;
	bool m_bActive;

private:
	static int g_iCurrentEndDist;
	static int g_iIdealEndDist;
	static float g_flBlendDoneTime;
};
#endif