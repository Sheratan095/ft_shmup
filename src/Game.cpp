#include "Game.hpp"
#include <cmath>

Game::Game(int numPlayers, int screenWidth, int playerStartY) : _screenWidth(screenWidth)
{
	if (numPlayers < 1 || numPlayers > 2 || screenWidth < 0)
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

		for (Bullet* bullet : _bullets)
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

void	Game::start()
{
	_started = true;
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
		_bullets.push_back(newBullet);
}

const char	*Game::InvalidParameters::what() const throw()
{
	return ("Invalid parameters provided");
}

const char	*Game::GameNotStarted::what() const throw()
{
	return ("Game has not been started yet");
}