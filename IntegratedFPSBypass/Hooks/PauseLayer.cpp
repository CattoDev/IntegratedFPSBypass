#include "PauseLayer.hpp"

void PauseLayer::vSyncCheckbox(CCObject* pSender) {
	auto box = (gd::CCMenuItemToggler*)pSender;

	auto gm = gd::GameManager::sharedState();
	gm->setGameVariable("0030", box->isToggled());

	// run toggleVerticalSync
	Custom::CCApplication_toggleVerticalSync(CCApplication::sharedApplication(), box->isToggled());
}

void PauseLayer::submitBtnCallback(CCObject*) {
	auto valueStr = this->m_iFPSInput->getString();

	// stack overflow stuff
	char* pEnd = nullptr;
	double value = std::strtod(valueStr, &pEnd);

	// if failed to convert
	if (*pEnd) {
		gd::FLAlertLayer::create(nullptr, "ERROR", "OK", nullptr, "<cr>Invalid FPS value.</c>")->show();
	}
	else {
		// restricting yall from going badonkers with fps values
		// well, not restricting anymore but just giving a warning
		if (value >= 1) {
			// check if V-Sync is enabled
			auto gm = gd::GameManager::sharedState();

			// 0030 is V-Sync
			if (!gm->getGameVariable("0030")) {
				CCDirector::sharedDirector()->setAnimationInterval(1 / value);
				if (value > 1000)
				{
					gd::FLAlertLayer::create(nullptr, "WARNING", "OK", nullptr, "<cy>Not recommended to use a value higher than 1000, as it can cause system instability and visual glitches.</c>")->show();
				}
			}
			else {
				gd::FLAlertLayer::create(nullptr, "ERROR", "OK", nullptr, "<cy>V-Sync is enabled. Please disable V-Sync to use FPS Bypass.</c>")->show();
			}
		}
		else {
			gd::FLAlertLayer::create(nullptr, "ERROR", "OK", nullptr, "<cy>Cannot use a value lower than 1.</c>")->show();
		}
	}
}

bool __fastcall PauseLayer::initH(PauseLayer* self) {
	if (!self->initO(self)) return false;

	/*
		Literally copy pasted from MoreVideoOptionsLayer.cpp
		I should probably just make a custom class for all this
	*/

	// haha fuck you custom menu
	auto menu = CCMenu::create();
	auto togglerMenu = CCMenu::create();
	togglerMenu->setPosition(0, 0);

	// label
	auto label = CCLabelBMFont::create("FPS Bypass", "bigFont.fnt");
	label->setScale(.4);
	menu->addChild(label);

	// black bg
	auto bg = extension::CCScale9Sprite::create("square02_001.png", { 0, 0, 80, 80 });
	bg->setContentSize({ 180, 80 });
	bg->setScale(.5);
	bg->setOpacity(100);

	menu->addChild(bg);

	// a
	menu->alignItemsVerticallyWithPadding(5);

	// input thingy
	self->m_iFPSInput = gd::CCTextInputNode::create("FPS", self, "bigFont.fnt", 80, 40);
	self->m_iFPSInput->setMaxLabelLength(5);
	self->m_iFPSInput->setAllowedChars("0123456789");
	int FPS = std::round(1 / CCDirector::sharedDirector()->getAnimationInterval());
	self->m_iFPSInput->setString(std::to_string(FPS).c_str());
	self->m_iFPSInput->setLabelPlaceholderColor({ 120, 170, 240 });
	self->m_iFPSInput->setPosition(bg->getPosition());

	self->m_iFPSInput->setMaxLabelScale(.8);
	self->m_iFPSInput->setLabelPlaceholerScale(.8);

	menu->addChild(self->m_iFPSInput, 1);

	// submit button
	auto submitBtnSpr = gd::ButtonSprite::create("Submit", 160, true, "bigFont.fnt", "GJ_button_01.png", 50, 1);
	submitBtnSpr->setScale(.5);
	auto submitBtn = gd::CCMenuItemSpriteExtra::create(
		submitBtnSpr,
		self,
		menu_selector(PauseLayer::submitBtnCallback)
	);
	submitBtn->setPositionY(bg->getPositionY() - 35);

	menu->addChild(submitBtn, 3);

	// v-sync toggle
	auto gm = gd::GameManager::sharedState();
	self->createToggleButton(menu_selector(PauseLayer::vSyncCheckbox), !gm->getGameVariable("0030"), togglerMenu, "V-Sync", CCPoint(470, 165));

	self->addChild(togglerMenu, 9);
	self->addChild(menu, 10);
	menu->setPosition(505, 240);

	return true;
}

void PauseLayer::mem_init() {
	MH_CreateHook(
		(PVOID)(gd::base + 0x1E4620),
		PauseLayer::initH,
		(LPVOID*)&PauseLayer::initO);
}