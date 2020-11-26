
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


class GUI_Label  
{
	private:
		std::string textStr;
		sf::Text text;
		sf::Color color;
		sf::Font font;
		int size;
		sf::Vector2f position;

	public:

		GUI_Label();
		~GUI_Label();

		void setup(std::string textStr,
		sf::Color color,
		sf::Font font,
		int size,
		sf::Vector2f position);
		void render(sf::RenderWindow *window);
		void setString(std::string s) {
			 this->textStr = s; 
			 this->text.setString(textStr);
		}


};