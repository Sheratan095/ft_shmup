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

	for (AEntity* entity : _enemies)
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

int	Game::getScore() const
{
	return (_score);
}

void	Game::showEntities(Screen& screen) const
{
	for (Player* player : _players)
		mvaddch(player->getY(), player->getX(), player->getSymbol());

	for (AEntity* entity : _enemies)
		mvaddch(entity->getY(), entity->getX(), entity->getSymbol());

	for (Bullet* bullet : _playersBullets)
		mvaddch(bullet->getY(), bullet->getX(), bullet->getSymbol());

	for (Asteroid* asteroid : _asteroids)
		mvaddch(asteroid->getY(), asteroid->getX(), asteroid->getSymbol());
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
			for (Asteroid* asteroid : _asteroids)
			{
				if (bullet->getX() == asteroid->getX() && bullet->getY() == asteroid->getY())
				{
					asteroid->takeDamage(ASTEROID_DAMAGE);
					bullet->setHealth(0);
					_score += POINTS_PER_MINION;
				}
			}
			for (AEntity* enemy : _enemies)
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
}

void Game::addMinion()
{
    int x = rand() % _screenWidth;
    int y = 0; // spawn at top
    _enemies.push_back(new Minion(x, y, 0, 0));
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
	_enemiesBullets.remove_if([](Bullet* bullet) { if (bullet->getHealth() <= 0) { delete bullet; return true; } return false; });
	_playersBullets.remove_if([](Bullet* bullet) { if (bullet->getHealth() <= 0) { delete bullet; return true; } return false; });
	_asteroids.remove_if([](Asteroid* asteroid) { if (asteroid->getHealth() <= 0) { delete asteroid; return true; } return false; });
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

const char	*Game::InvalidParameters::what() const throw()
{
	return ("Invalid parameters provided");
}

const char	*Game::GameNotStarted::what() const throw()
{
	return ("Game has not been started yet");
}