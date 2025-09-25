#include "Cutscene.h"

Cutscene::Cutscene()
{
	player_life = 2;

}

Cutscene::~Cutscene()
{

}

void Cutscene::cutscenePlay()
{
	player_life++;

}