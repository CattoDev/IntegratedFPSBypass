#pragma once

#include "../includes.h"

// idk how to name it so lol
// kinda recreated from https://github.com/absoIute/Mega-Hack-v5/blob/master/src/FPS%20Bypass/main.cpp
namespace Custom {
	typedef void*(__thiscall* fCCApplication_toggleVerticalSync)(void* instance, bool on);

	extern fCCApplication_toggleVerticalSync CCApplication_toggleVerticalSync;
}