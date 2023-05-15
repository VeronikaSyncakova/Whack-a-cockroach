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
#include <iostream>
#include "Hole.h"


class Insect
{
public:
	void setupCockroach(sf::Vector2f t_position); //sets up cockroaches
	void setupLadybug(sf::Vector2f t_position); //lets up ladybug
	
	sf::RectangleShape getBody(); //returns body
	sf::Sprite getSprite();//returns sprite
	bool getStatus(); //returns if its out of the tree or not
	void move(); //move insect out and into the tree
	void setPosition(sf::Vector2f t_position); //sets the position
	sf::Vector2f getPosition();
	bool getHit();
	void setHit(bool t_hit);
	void animateInsect(); //animates insect
	void freeLadybug(); //move ladybug from hole
	void increaseSpeed(float t_increment);
	

	static float speed ; //speed horizontal of movement
	
	

private:
	sf::RectangleShape m_body; //insects body
	sf::Vector2f m_size{ 130.0f,60.0f }; //insect size
	bool m_rightSide {false }; //determine side of the screen 
	sf::Vector2f m_bugLocation; //location of bug
	bool m_out{ true }; //if the insect is out of the tree
	bool m_hit{ false }; //if it was hit
	sf::Texture m_cockroachTexture; //cockroach texture
	sf::Texture m_ladybugTexture; //ladybug texture
	sf::Sprite m_sprite; // sprite
	int m_insectWidth; //sprite width
	int m_insectHeight; //sprite height

	float m_frameCounter = 0.0f; //which frame
	float m_frameIncrement = 0.3f; // speed of animation
	int m_frame = 0; //chooses frame
	int m_currentFrame{ -1 };
	int m_row = 0;
	int m_col = 0;

	bool m_bugMove = true;


};

