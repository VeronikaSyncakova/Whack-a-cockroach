/// <summary>
/// author Veronika Syncakova March 2023
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Insect.h"
#include "Globals.h"
#include "Hole.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouseClick(sf::Event t_event); //user pressed mouse button
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupTree(); //sets up tree barks
	void setupHoles(); //setsup holes
	void setupCockroaches(); //setsup cockroaches
	void setupLadybugs(); //setsup ladybugs
	void drawHoles(Hole t_array[]); //draws holes
	void drawCockroaches(Insect t_array[]); //draws cockroaches
	void drawLadybugs(Insect t_array[]); //draws ladybugs
	void moveInsect(Insect t_array[]); //moves insects from and into the tree
	void dislocateHoles(); //relocates holes randomly
	void dislocateCockroach(Insect t_array[]); //relocates cockroaches
	void dislocateLadybug(Insect t_array[]); //relocates ladybugs
	bool checkTime(); //checks timer
	bool checkCollision(sf::Event t_event); //check if user hit the insect
	void checkReset(sf::Event t_event);
	



	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Font m_font;
	sf::Text m_hitsMessage; // text used to dispay hit count on screen
	sf::Text m_mistakesMessage; //message for mistakes
	sf::Text m_instructions; //instruction message
	bool m_exitGame; // control exiting game

	sf::RectangleShape m_treeR; //right tree bark
	sf::RectangleShape m_treeL; //left tree bark
	sf::Texture m_treeTexture; //tree texture
	sf::Sprite m_treeSpriteR; //tree right
	sf::Sprite m_treeSpriteL; //tree left
	sf::Texture m_backgroundTexture; //background texture
	sf::Sprite m_backgroundSprite; //backgound sprite

	Insect m_cockroaches[COCKROACH_N]; //cockroach array
	Insect m_ladybugs[LADYBUG_N]; //ladybug array
	Hole m_holes[HOLES_N]; //holes array

	int m_timer = 0; //timer for hole location change
	bool m_change = false; //if its time to change location

	int m_hits=0; //hit counter
	int m_mistakes = 0; //hit counter for ladybug
	bool m_cockroach{ false }; //type of insect
	int m_collisionIndex; //wich object was hit

	bool m_graphics{ false }; //graphics mode w F1
	bool m_freeLadybug = false; //if true moves ladybug outside the hole

	int m_changeTime = 270; //increses the speed
	float speed = 1.0f;
	
	sf::RectangleShape m_reset;
	sf::Text m_resetMessage;
	int moveIndex = -1; //index of moving insect

	bool m_instructions1; //instraction showing or not

};

#endif // !GAME_HPP

