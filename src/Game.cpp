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

	for (AEnemy* enemy : _enemies)
		delete (enemy);

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

	for (AEnemy* enemy : _enemies)
		mvaddch(enemy->getY(), enemy->getX(), enemy->getSymbol());

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
	for (Bullet* bullet : _enemiesBullets)
	{
		if (bullet->move(-1, 0))
		{
			for (Player* player : _players)
			{
				if (bullet->getX() == player->getX() && bullet->getY() == player->getY())
				{
					player->takeDamage(1);
					bullet->setHealth(0); // Mark bullet for deletion
				}
			}
		}
		else
			bullet->setHealth(0); // Mark bullet for deletion
	}
}

void	Game::addMinion()
{

}

void	Game::addBoss()
{

}

void	Game::addAsteroid()
{

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