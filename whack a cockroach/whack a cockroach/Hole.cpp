/// <summary>
/// @author Veronika Syncakova
/// @date March 2023
///
/// </summary>


#include "Hole.h"



void Hole::setupHole()
{//set up hole
	m_body.setSize(m_size);
	m_body.setFillColor(sf::Color::Cyan);
	m_body.setOrigin(m_size.x / 2, m_size.y / 2);
	
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\hole.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading holes" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_size.x / 2, m_size.y / 2);

}

void Hole::dislocateHole()
{
	m_side = rand() % 2 + 1;
	if (m_side == LEFT)
	{//left side
		m_location.x = 130.0f;
		m_side = LEFT;

	}
	else
	{//right side
		m_location.x = SCREEN_W - TREE_W;
		m_side == RIGHT;
	}
	m_location.y = rand() % 401 + 150;
	m_body.setPosition(m_location);
	m_sprite.setPosition(m_location);
}

sf::RectangleShape Hole::getBody()
{//returns body
	return m_body;
}

sf::Vector2f Hole::getLocation()
{
	return m_location;
}

void Hole::setLocation(sf::Vector2f t_location)
{
	m_location = t_location;
}

int Hole::getHoleHeight()
{
	return m_size.y;
}

sf::Sprite Hole::getSprite()
{
	return m_sprite;
}

