#include "ToggleVerticalSync.hpp"

Custom::fCCApplication_toggleVerticalSync Custom::CCApplication_toggleVerticalSync = (Custom::fCCApplication_toggleVerticalSync)GetProcAddress(GetModuleHandleA("libcocos2d.dll"), "?toggleVerticalSync@CCApplication@cocos2d@@QAEX_N@Z");