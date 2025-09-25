# include "End.h"

End::End()
{

}

End::~End()
{

}

void End::endInit(sf::RenderWindow& window)
{
	font.loadFromFile(("../content/Fonts/OpenSans-Bold.ttf"));

	end_text.setString("Congratulations, you somehow managed to fight them all off, press any key to refresh");
	end_text.setFont(font);
	end_text.setCharacterSize(25);
	end_text.setFillColor(sf::Color(0, 0, 0, 255));
	end_text.setPosition((window.getSize().x / 2) - (end_text.getGlobalBounds().width / 2), 100);

}

void End::endRender(sf::RenderWindow& window)
{
	window.draw(end_text);
}