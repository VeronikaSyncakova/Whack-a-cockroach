/// <summary>
/// @author Veronika Syncakova
/// @date March 2023
///
/// </summary>

#include "Game.h"
#include "Globals.h"


#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Whack a cockroach" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupTree(); //load tree barks
	setupHoles(); //sets up holes
	dislocateHoles();
	setupCockroaches(); //sets cockroaches
	setupLadybugs(); //sets ladybugs
	dislocateCockroach(m_cockroaches);
	
	
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	srand(time(nullptr)); // set the seed once
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type) //user released a mouse button
		{
			if (checkCollision(newEvent))
			{
				processMouseClick(newEvent);
			}
			checkReset(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::F1 == t_event.key.code)
	{//graphics mode
		if (!m_graphics)
		{//on
			m_graphics = true;
		}
		else
		{//off
			m_graphics = false;
		}
	}
	if (sf::Keyboard::F2 == t_event.key.code)
	{//instructions
		if (!m_instructions1)
		{//on
			m_instructions1 = true;
			
		}
		else
		{//off
			m_instructions1 = false;
		}
	}
}

void Game::processMouseClick(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		if (m_cockroach)
		{//is cockroach
			if (!m_cockroaches[m_collisionIndex].getHit())
			{//if not hit
				m_hits++;
				speed += 0.3;
				m_changeTime =270 / speed;
				m_cockroaches[m_collisionIndex].increaseSpeed(speed);
				m_hitsMessage.setString("Hits: " + std::to_string(m_hits));
				m_cockroaches[m_collisionIndex].setHit(true);
			}
		}
		if (!m_cockroach)
		{//if ladybug
			if (!m_ladybugs[m_collisionIndex].getHit())
			{//if not hit
				m_mistakes++;
				m_mistakesMessage.setString("Mistakes: " + std::to_string(m_mistakes));
				m_ladybugs[m_collisionIndex].setHit(true);
			}
		}

	}
	if (sf::Mouse::Right == t_event.mouseButton.button)
	{
		if (!m_cockroach)
		{//if ladybug
			if (!m_ladybugs[m_collisionIndex].getHit() && !m_freeLadybug)
			{//if not hit and not moving out of hole
				if (m_mistakes > 0)
				{
					m_mistakes--;
					m_mistakesMessage.setString("Mistakes: " + std::to_string(m_mistakes));
				}
				m_freeLadybug = true;
				moveIndex = m_collisionIndex; //only that one ladybug will move
				m_ladybugs[m_collisionIndex].setHit(true);
			}
		}
	}

}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (checkTime())
	{//checks if should relocate holes
		dislocateHoles();
		dislocateCockroach(m_cockroaches);
		dislocateLadybug(m_ladybugs);
	}
	moveInsect(m_cockroaches);
	moveInsect(m_ladybugs);
	
	if (m_freeLadybug)
	{//move ladybug out of hole
		m_ladybugs[moveIndex].freeLadybug();
		if (m_ladybugs[moveIndex].getPosition().y < -70 || m_ladybugs[moveIndex].getPosition().y >670)
		{
			m_freeLadybug = false;
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	if (m_graphics)
	{//graphics mode on
		m_window.draw(m_backgroundSprite);
		m_window.draw(m_hitsMessage);
		m_window.draw(m_mistakesMessage);
		drawCockroaches(m_cockroaches);
		drawLadybugs(m_ladybugs);
		m_window.draw(m_treeSpriteL);
		m_window.draw(m_treeSpriteR);
		m_window.draw(m_reset);
		m_window.draw(m_resetMessage);

	}
	else
	{//graphics mode off
		m_window.draw(m_hitsMessage);
		m_window.draw(m_mistakesMessage);
		drawCockroaches(m_cockroaches);
		drawLadybugs(m_ladybugs);
		m_window.draw(m_treeR);
		m_window.draw(m_treeL);
		m_window.draw(m_reset);
		m_window.draw(m_resetMessage);
	}
	drawHoles(m_holes);
	if (m_instructions1)
	{//instructions
		m_window.clear(sf::Color::White);
		m_window.draw(m_instructions);
	}
	
	
	
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	if (!m_font.loadFromFile("ASSETS\\FONTS\\font.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
		m_font = m_ArialBlackfont;
	}
	m_hitsMessage.setFont(m_font);
	m_hitsMessage.setString("Hits: ");
	m_hitsMessage.setPosition(140.0f, 30.0f);
	m_hitsMessage.setCharacterSize(50U);
	m_hitsMessage.setFillColor(sf::Color::Black);

	m_mistakesMessage.setFont(m_font);
	m_mistakesMessage.setString("Mistakes: ");
	m_mistakesMessage.setPosition(355.0f, 30.0f);
	m_mistakesMessage.setCharacterSize(50U);
	m_mistakesMessage.setFillColor(sf::Color::Black);

	m_resetMessage.setFont(m_ArialBlackfont);
	m_resetMessage.setString("RESET");
	m_resetMessage.setPosition(698, 18.0f);
	m_resetMessage.setCharacterSize(20U);
	m_resetMessage.setFillColor(sf::Color::White);

	m_instructions.setFont(m_ArialBlackfont);
	m_instructions.setString("INSTRUCTIONS\n\npress F1 for graphics mode\nleft click on cockroach = hit\nleft click on ladybug = miss\nright click on ladybug to free it and\ncompensate for mistake\nclick reset to reset the game\n\npress F2 to open/close instructions");
	m_instructions.setPosition(100, 50);
	m_instructions.setCharacterSize(30U);
	m_instructions.setFillColor(sf::Color::Black);

}

/// <summary>
/// load the texture and setup the sprites
/// </summary>
void Game::setupTree()
{
	m_treeR.setSize(sf::Vector2f{ TREE_W, SCREEN_H });
	m_treeR.setPosition(SCREEN_W-TREE_W, 0.0f);
	m_treeR.setFillColor(sf::Color::Black);

	m_treeL.setSize(sf::Vector2f{ TREE_W, SCREEN_H });
	m_treeL.setPosition(0.0f, 0.0f);
	m_treeL.setFillColor(sf::Color::Black);

	//tree sprite
	if (!m_treeTexture.loadFromFile("ASSETS\\IMAGES\\wood.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading wood" << std::endl;
	}
	m_treeSpriteR.setTexture(m_treeTexture);
	m_treeSpriteR.setPosition(SCREEN_W - TREE_W, 0.0f);
	m_treeSpriteL.setTexture(m_treeTexture);
	m_treeSpriteL.setPosition(0.0f, 0.0f);

	//background
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background2.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading background" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(0.0f, 0.0f);

	m_reset.setSize(sf::Vector2f{ 80.0f,30.0f });
	m_reset.setOrigin(40.0f, 15.0f);
	m_reset.setPosition(735, 30);
	m_reset.setFillColor(sf::Color::Black);
}

void Game::setupHoles()
{//sets up default holes
	for (int i = 0; i < HOLES_N; i++)
	{
		m_holes[i].setupHole();
		m_window.draw(m_holes[i].getBody());
	}
}

void Game::setupCockroaches()
{
	for (int i = 0; i < COCKROACH_N; i++)
	{
		m_cockroaches[i].setupCockroach(m_holes[i].getLocation());
	}
}

void Game::setupLadybugs()
{
	for (int i = 0; i < LADYBUG_N; i++)
	{
		m_ladybugs[i].setupLadybug(m_holes[HOLES_N-1-i].getLocation());
	}
}

void Game::drawHoles(Hole t_array[])
{//draw holes
	for (int i = 0; i < HOLES_N; i++)
	{
		if (m_graphics)
		{
			m_window.draw(m_holes[i].getSprite());
		}
		else
		{
			m_window.draw(m_holes[i].getBody());
		}
	}
	
}

void Game::drawCockroaches(Insect t_array[])
{//draw cockroaches
	for (int i = 0; i < COCKROACH_N; i++)
	{
		if (m_graphics)
		{//draphics on
			m_window.draw(m_cockroaches[i].getSprite());
		}
		else
		{//graphics off
			m_window.draw(m_cockroaches[i].getBody());
		}
	}
}

void Game::drawLadybugs(Insect t_array[])
{//draw ladybugs
	for (int i = 0; i < LADYBUG_N; i++)
	{
		if (m_graphics)
		{//graphics on
			m_window.draw(m_ladybugs[i].getSprite());
		}
		else
		{//graphics off
			m_window.draw(m_ladybugs[i].getBody());
		}
	}
}

void Game::moveInsect(Insect t_array[])
{//moves incects from and into the tree
	for (int i = 0; i < COCKROACH_N; i++)
	{
		t_array[i].move();
		t_array[i].animateInsect();
	}
}

void Game::dislocateHoles()
{//changes position of the holes
	int minDistance = 100;
	sf::Vector2f distance; //distance between holes
	float distanceF; //distance between holes but float
	int activeHoles = 0; //holes that have position
	bool changed = false; //check if holes were overlapping
	for (int i = 0; i < HOLES_N; i++)
	{//deletes the position of holes
		m_holes[i].setLocation(sf::Vector2f{ 0.0f,0.0f });
	}
	for (int i = 0; i < HOLES_N; i++)
	{//sets the position of a hole
		m_holes[i].dislocateHole();
		activeHoles++;
		if (i > 0)
		{//check that first one doesnt get checked
			for (int j = 0; j < activeHoles-1; j++) //activeholes -1 cuz i dont want to chect the current active hole
			{//compares position of a hole with all previus holes
				distance = m_holes[i].getLocation() - m_holes[j].getLocation(); //calculates the distance between holes
				distanceF = std::sqrtf(distance.x * distance.x + distance.y * distance.y); //puts it to float
				while (distanceF < minDistance)
				{//if they are overlapping, set new position
					m_holes[i].dislocateHole();
					distance = m_holes[i].getLocation() - m_holes[j].getLocation();
					distanceF = std::sqrtf(distance.x * distance.x + distance.y * distance.y);
					changed = true;
				}
				if (changed)
				{//check all the previus holes again if they overlapped before
					j = -1; //it will go to 0 after continue
					changed = false;
					continue;
				}
			}
		}	
	}
	
}

bool Game::checkTime()
{//timer for hole relocation
	m_timer++;
	if (m_timer >= m_changeTime)
	{
		m_change = true;
		m_timer = 0;
	}
	else
	{
		m_change = false;
	}
	return m_change;
}

void Game::dislocateCockroach(Insect t_array[])
{//moves cockroach into different holes
	for (int i = 0; i < COCKROACH_N; i++)
	{
		t_array[i].setPosition(m_holes[i].getLocation());
		t_array[i].setHit(false);
	}
}

bool Game::checkCollision(sf::Event t_event)
{ //checks if player hit or missed insect
	sf::Vector2f mouseClick;
	bool collision = false;
	mouseClick.x = static_cast<float>(t_event.mouseButton.x);
	mouseClick.y = static_cast<float>(t_event.mouseButton.y);
	for (int i = 0; i < COCKROACH_N; i++)
	{
		if (mouseClick.x > TREE_W && mouseClick.x < SCREEN_W - TREE_W)
		{
			if (m_cockroaches[i].getBody().getGlobalBounds().contains(mouseClick) )
			{
				collision = true;
				m_cockroach = true;//its a cockroach
				m_collisionIndex = i;
				break;
			}
			if (m_ladybugs[i].getBody().getGlobalBounds().contains(mouseClick))
			{
				collision = true;
				m_cockroach = false; //its a ladybug
				m_collisionIndex = i;
					break;
			}
		}
	}
	return collision;
}

void Game::dislocateLadybug(Insect t_array[])
{//moves ladybug into holes
	for (int i = 0; i < LADYBUG_N; i++)
	{
		if (m_freeLadybug && i == moveIndex)
		{
			continue;
		}
		t_array[i].setPosition(m_holes[HOLES_N - 1 - i].getLocation());
		t_array[i].setHit(false);
	}
}

 void Game::checkReset(sf::Event t_event)
{//checks if player reseted the game
	 sf::Vector2f mouseClick;
	 mouseClick.x = static_cast<float>(t_event.mouseButton.x);
	 mouseClick.y = static_cast<float>(t_event.mouseButton.y);
	 if (m_reset.getGlobalBounds().contains(mouseClick))
	 {//set speed and counts to default
		 m_hits = 0;
		 m_hitsMessage.setString("Hits: ");
		 m_mistakes = 0;
		 m_mistakesMessage.setString("Mistakes: ");
		 speed = 1.0f;
		 m_cockroaches[m_collisionIndex].increaseSpeed(speed);
		 m_changeTime = 270;
	 }
}