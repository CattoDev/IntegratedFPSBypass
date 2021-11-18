#pragma once

#include "../includes.h"

#include "../Other/ToggleVerticalSync.hpp"

class PauseLayer : public gd::PauseLayer {
	gd::CCTextInputNode* m_iFPSInput;

public:
	inline static bool(__thiscall* initO)(PauseLayer*);
	static bool __fastcall initH(PauseLayer*);

	void submitBtnCallback(CCObject*);
	void vSyncCheckbox(CCObject*);

	static void mem_init();
};