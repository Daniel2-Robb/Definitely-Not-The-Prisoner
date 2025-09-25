#include "Cutscene.h"

Cutscene::Cutscene()
{
	player_life = 2;
	if (!font.loadFromFile(("../content/Fonts/OpenSans-Bold.ttf")))
	{
		std::cout << "font failed to load" << std::endl;
	}

}

Cutscene::~Cutscene()
{

}

void Cutscene::cutsceneInit()
{
	std::cout << "Cutscene prepared \n";
	player_text.setString("Who are you?");
	player_text.setFont(font);
	player_text.setCharacterSize(25);
	player_text.setFillColor(sf::Color(0, 0, 0, 255));
	player_text.setPosition(50, 100);

	number_2_text.setString("Good evening.");
	number_2_text.setFont(font);
	number_2_text.setCharacterSize(25);
	number_2_text.setFillColor(sf::Color(0, 0, 0, 255));
	number_2_text.setPosition(1030 - number_2_text.getGlobalBounds().width, 150 + player_text.getGlobalBounds().height);
}

void Cutscene::cutscenePlay(sf::RenderWindow& window)
{
	window.clear(sf::Color::Cyan);

	timer.restart();

	

	std::cout << "Cutscene started \n";
	player_life++;
	window.draw(number_2_text);
	//sleep argument is given in milliseconds
	Sleep(3000);
	window.draw(player_text);
	Sleep(3000);

	number_2_text.setString("");
	player_text.setString("");
	window.draw(number_2_text);
	window.draw(player_text);

	number_2_text.setString("The New Number 2.");
	player_text.setString("Who is Number 1?");
	window.draw(number_2_text);
	Sleep(3000);
	window.draw(player_text);
	Sleep(3000);

	number_2_text.setString("");
	player_text.setString("");
	window.draw(number_2_text);
	window.draw(player_text);

	number_2_text.setString("You are number " + std::to_string(player_life) + ".");
	player_text.setString("I am not a number, I am a free man.");
	window.draw(number_2_text);
	Sleep(3000);
	window.draw(player_text);
	Sleep(3000);

	number_2_text.setString("");
	player_text.setString("");
	window.draw(number_2_text);
	window.draw(player_text);

	std::cout << "Cutscene ended \n";
}