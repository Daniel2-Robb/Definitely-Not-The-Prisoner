
#include "Settings.h"

Settings::Settings()
{

}


Settings::Keybinds& Settings::getKeybindMain()
{
	return keybind_main;
}

Settings::Keybinds& Settings::getKeybindAlternate()
{
	return keybind_alt;
}