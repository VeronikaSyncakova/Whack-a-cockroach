#pragma once
/// <summary>
/// author Veronika Syncakova March 2023
/// </summary>

/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Insect.h"
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>

class Hole
{
public:
	
	sf::RectangleShape getBody(); //returns body
	sf::Vector2f getLocation(); //returns location
	int getHoleHeight();
	void setupHole();
	void dislocateHole(); //changes position of hole
	void setLocation(sf::Vector2f t_location); //sets location
	sf::Sprite getSprite();
	
	

private:
	sf::RectangleShape m_body;
	sf::Vector2f m_size{ 15.0f, static_cast<float>(INSECT_H) + 10 }; //size of the hole
	sf::Vector2f m_location; //location of the hole
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	
	int m_side; //determines on which side it is
	
	
};