#include "Game.hpp"
#include <cmath>

Game::Game(int numPlayers, int playerStartY, int screenWidth, int screenHeight) : _screenWidth(screenWidth), _screenHeight(screenHeight)
{
	if (numPlayers < 1 || numPlayers > 2 || screenWidth < 0 || screenHeight < 0)
		throw InvalidParameters();

	if (numPlayers == 1)
		_players.push_back(new Player(screenWidth / 2, playerStartY, 1, 0, 0));
	else
	{
		_players.push_back(new Player(screenWidth / 3, playerStartY, 1, 0, 0));
		_players.push_back(new Player(2 * (screenWidth / 3), playerStartY, 1, 0, 1));
	}
}

Game::~Game()
{
	for (Player* player : _players)
		delete (player);

	for (AEnemy* entity : _enemies)
		delete (entity);

	for (Bullet* bullet : _enemiesBullets)
		delete (bullet);

	for (Bullet* bullet : _playersBullets)
			delete (bullet);

	for (Asteroid* asteroid : _asteroids)
		delete (asteroid);
}

int	Game::getPlayerHealth(int playerId) const
{
	if (playerId < 0 || playerId >= static_cast<int>(_players.size()))
		throw InvalidParameters();

	auto	it = _players.begin();
	std::advance(it, playerId);

	return (*it)->getHealth();
}

bool    Game::isRunning() const
{
	return (_started);
}

void	Game::setHeight(int newH)
{
	_screenHeight = newH;
}

void	Game::setWidth(int newW)
{
	_screenWidth = newW;
}

int	Game::getScore() const
{
	return (_score);
}

void	Game::showEntities(Screen& screen) const
{
	for (Player* player : _players)
		player->render(stdscr);

	for (AEnemy* entity : _enemies)
		entity->render(stdscr);

	for (Bullet* bullet : _playersBullets)
		bullet->render(stdscr);

	for (Asteroid* asteroid : _asteroids)
		asteroid->render(stdscr);
}

void	Game::stop()
{
	_started = false;
}

void	Game::start()
{
	_started = true;
}

void	Game::update()
{
	// Move enemies's bullets downwards and check for collisions with players
	for (Bullet* bullet : _enemiesBullets)
	{
		if (bullet->move(0, 1))
		{
			for (Player* player : _players)
			{
				if (bullet->getX() == player->getX() && bullet->getY() == player->getY())
				{
					player->takeDamage(PLAYER_DAMAGE);
					bullet->setHealth(0); // Mark bullet for deletion
				}
			}
		}
		else
			bullet->setHealth(0); // Mark bullet for deletion
	}

	// Move player's bullets upwards and check for collisions with enemies and asteroids
	for (Bullet* bullet : _playersBullets)
	{
		if (bullet->move(0, -1))
		{
			// Check bullets collision with asteroids first
			for (Asteroid* asteroid : _asteroids)
			{
				if (bullet->getX() == asteroid->getX() && bullet->getY() == asteroid->getY())
				{
					asteroid->takeDamage(PLAYER_DAMAGE);
					bullet->setHealth(0);
					_score += POINTS_PER_ASTEROID;
				}
			}
			// Then check collision with enemies
			for (AEnemy* enemy : _enemies)
			{
				if (bullet->getX() == enemy->getX() && bullet->getY() == enemy->getY())
				{
					enemy->takeDamage(dynamic_cast<Minion*>(enemy) ? MINION_DAMAGE : BOSS_DAMAGE);
					bullet->setHealth(0); // Mark bullet for deletion
					if (!enemy->isAlive())
					{
						if (dynamic_cast<Minion*>(enemy))
							_score += POINTS_PER_MINION;
						else if (dynamic_cast<Boss*>(enemy))
							_score += POINTS_PER_BOSS;
					}
				}
			}
		}
		else
			bullet->setHealth(0); // Mark bullet for deletion
	}

	// Move asteroids downwards and check for collisions with players
	for (Asteroid* asteroid : _asteroids)
	{
		if (!asteroid->move(0, 1) || asteroid->getY() >= _screenHeight - 3)
		{
			asteroid->setHealth(0);
			continue;
		}

		// Player collision
		for (Player* player : _players)
		{
			if (asteroid->getX() == player->getX() &&
				asteroid->getY() == player->getY())
			{
				player->takeDamage(ASTEROID_DAMAGE);
				asteroid->setHealth(0);
			}
		}
	}

	cleanDeathEntities();

	if (isGameOver())
		stop();
}

void Game::addMinion()
{
	try
	{
		int x = rand() % _screenWidth;
		int y = 0; // spawn at top
		_enemies.push_back(new Minion(x, y, 0, 0));
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error adding minion: " << e.what() << std::endl;
	}
}

void Game::addBoss()
{
	int x = _screenWidth / 2;
	int y = 0;
	_enemies.push_back(new Boss(x, y, 0, 0));
}

void	Game::addAsteroid()
{
	Asteroid* newAsteroid = new Asteroid(rand() % _screenWidth, 1, 0, 0);
	_asteroids.push_back(newAsteroid);
}

void	Game::cleanDeathEntities()
{
	_enemies.remove_if([](AEntity* enemy) { if (!enemy->isAlive()) { delete enemy; return true; } return false; });
	_enemiesBullets.remove_if([](Bullet* bullet) { if (!bullet->isAlive()) { delete bullet; return true; } return false; });
	_playersBullets.remove_if([](Bullet* bullet) { if (!bullet->isAlive()) { delete bullet; return true; } return false; });
	_asteroids.remove_if([](Asteroid* asteroid) { if (!asteroid->isAlive()) { delete asteroid; return true; } return false; });
}

// Return false if the move would put the player out of bounds, true otherwise
bool	Game::playerMove(int playerId, int deltaX)
{
	if (playerId < 0)
		throw InvalidParameters();

	if (playerId >= static_cast<int>(_players.size()))
		return (false);

	if (!_started)
		throw GameNotStarted();

	auto	it = _players.begin();
	std::advance(it, playerId);

	if ((*it)->getX() + deltaX < 0 || (*it)->getX() + deltaX >= _screenWidth)
		return (false);

	return ((*it)->move(deltaX, 0));
}

void	Game::playerShoot(int playerId)
{
	if (playerId < 0)
		throw InvalidParameters();

	if (playerId >= static_cast<int>(_players.size()))
		return ;

		if (!_started)
		throw GameNotStarted();

	auto	it = _players.begin();
	std::advance(it, playerId);

	Bullet*	newBullet = (*it)->shoot();
	if (newBullet)
		_playersBullets.push_back(newBullet);
}

bool	Game::isGameOver() const
{
	for (Player* player : _players)
	{
		if (player->isAlive())
			return (false);
	}
	return (true);
}

const char	*Game::InvalidParameters::what() const throw()
{
	return ("Invalid parameters provided");
}

const char	*Game::GameNotStarted::what() const throw()
{
	return ("Game has not been started yet");
}