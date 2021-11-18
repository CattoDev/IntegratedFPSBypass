#pragma once

#include "../includes.h"

class MoreVideoOptionsLayer : public gd::FLAlertLayer {
	gd::CCTextInputNode* m_iFPSInput;

public:
	inline static bool(__thiscall* initO)(MoreVideoOptionsLayer*);
	static bool __fastcall initH(MoreVideoOptionsLayer*);

	void submitBtnCallback(CCObject*);

	static void mem_init();
};