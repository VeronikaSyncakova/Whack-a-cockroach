/// <summary>
/// @author Veronika Syncakova
/// @date March 2023
///
/// </summary>


#include "Insect.h"

float Insect::speed = 1.0;

void Insect::setupCockroach(sf::Vector2f t_position)
{
	m_body.setSize(m_size);
	m_body.setOrigin(sf::Vector2f{ 0.0f,m_size.y / 2 });
	m_body.setPosition(t_position);
	m_body.setFillColor(sf::Color::Yellow);
	m_rightSide = false; //on the left
	m_out = true;
	m_hit = false;

	if (!m_cockroachTexture.loadFromFile("ASSETS\\IMAGES\\cockroach-spritesheet.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading cockroach" << std::endl;
	}
	m_sprite.setTexture(m_cockroachTexture);
	m_sprite.setPosition(t_position);
	m_sprite.setOrigin(sf::Vector2f{ 0.0f,65.0f });
	m_sprite.setTextureRect(sf::IntRect(0, 0, 130, 130));
	m_sprite.setScale(1.0f, 1.0f);
	m_insectWidth = 130;
	m_insectHeight = 130;
}

void Insect::setupLadybug(sf::Vector2f t_position)
{
	m_body.setSize(m_size);
	m_body.setOrigin(sf::Vector2f{ 0.0f, m_size.y / 2 });
	m_body.setPosition(t_position);
	m_body.setFillColor(sf::Color::Red);
	m_rightSide = true; //on the right
	m_out = false;
	m_hit = false;

	if (!m_ladybugTexture.loadFromFile("ASSETS\\IMAGES\\ladybug-spritesheet.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading ladybug" << std::endl;
	}
	m_sprite.setTexture(m_ladybugTexture);
	m_sprite.setPosition(t_position);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 152, 152));
	m_sprite.setOrigin(sf::Vector2f{ 130.0f,76.0f });
	m_sprite.setScale(-1.0f, 1.0f);
	m_insectWidth = 152;
	m_insectHeight = 152;
}

sf::RectangleShape Insect::getBody()
{
	return m_body;
}

sf::Sprite Insect::getSprite()
{
	return m_sprite;
}




void Insect::move()
{ //move insect out and into the tree
	m_bugLocation = m_body.getPosition();
	if (m_bugMove)
	{
		if (m_out)
		{//moves insect into the tree
			if (m_rightSide)
			{//right side
				if (m_bugLocation.x < SCREEN_W - TREE_W)
				{
					m_bugLocation.x += speed;
				}
				else
				{
					m_out = false;
				}
				m_body.setPosition(m_bugLocation);
				m_sprite.setPosition(m_bugLocation);
			}
			else
			{//left side
				if (m_bugLocation.x > 0)
				{
					m_bugLocation.x -= speed;
				}
				else
				{
					m_out = false;
				}
				m_body.setPosition(m_bugLocation);
				m_sprite.setPosition(m_bugLocation);

			}

		}
		else
		{//moves insect out of the tree
			if (m_rightSide)
			{//right side
				if (m_bugLocation.x > SCREEN_W - TREE_W - INSECT_W)
				{
					m_bugLocation.x -= speed;
				}
				else
				{
					m_out = true;
				}
				m_body.setPosition(m_bugLocation);
				m_sprite.setPosition(m_bugLocation);
			}
			else
			{//left side
				if (m_bugLocation.x + INSECT_W < TREE_W + INSECT_W)
				{
					m_bugLocation.x += speed;
				}
				else
				{
					m_out = true;
				}
				m_body.setPosition(m_bugLocation);
				m_sprite.setPosition(m_bugLocation);
			}
		}
	}
}

void Insect::freeLadybug()
{//move ladybug outside treetrunk
	if (m_rightSide)
	{
		m_bugLocation -= sf::Vector2f{ speed,speed };
	}
	else
	{
		m_bugLocation += sf::Vector2f{ speed,speed };
	}
	m_body.setPosition(m_bugLocation);
	m_sprite.setPosition(m_bugLocation);
	m_bugMove = false;
}

void Insect::increaseSpeed(float t_increment)
{//makes it faster
	speed = t_increment;
}

void Insect::setPosition(sf::Vector2f t_position)
{//sets position to the hole
	m_bugLocation = t_position;
	float originY = m_sprite.getOrigin().y;
	
	if (t_position.x == 130.0f)
	{//left side
		m_rightSide = false;
		m_bugLocation.x -= INSECT_W;//put it inside the tree
		m_sprite.setScale(1.0f, 1.0f);
		m_sprite.setOrigin(0.0f, originY);
	}
	else
	{//right side
		m_rightSide = true;
		m_sprite.setScale(-1.0f, 1.0f);
		m_sprite.setOrigin(sf::Vector2f{ 130.0f,originY });

	}
	m_body.setPosition(m_bugLocation);
	m_out = false;
	m_bugMove = true;

}

void Insect::animateInsect()
{
	m_frameCounter += m_frameIncrement;
	m_frame = static_cast<int>(m_frameCounter);
	if (m_frame > FRAMES-1)
	{
		m_frame = 0;
		m_frameCounter -= 12.0f;
	}
	if(m_frame!=m_currentFrame)
	{
		m_currentFrame = m_frame;
		m_col = m_frame % 6;
		m_row = m_frame / 6;
		m_sprite.setTextureRect(sf::IntRect(m_col * m_insectWidth, m_row*m_insectHeight, m_insectWidth, m_insectHeight));
	}
}

bool Insect::getStatus()
{ //returns if the insect is out of the tree or not
	return m_out;
}

bool Insect::getHit()
{//returns if it was or wasn't hit
	return m_hit;
}
void Insect::setHit(bool t_hit)
{// setd up if it was or wasn't hit
	m_hit = t_hit;
}

sf::Vector2f Insect::getPosition()
{
	return m_bugLocation;
}


