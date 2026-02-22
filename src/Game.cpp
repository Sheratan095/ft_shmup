#include "Game.hpp"

Game::Game(int numPlayers, int playerStartY, int screenWidth, int screenHeight) : _screenWidth(screenWidth), _screenHeight(screenHeight)
{
	if (numPlayers < 1 || numPlayers > 2 || screenWidth < 0 || screenHeight < 0)
		throw InvalidParameters();

	if (numPlayers == 1)
		_players.push_back(new Player(screenWidth / 2, playerStartY, PLAYER_WIDTH, 1, 0));
	else
	{
		_players.push_back(new Player(screenWidth / 3, playerStartY, PLAYER_WIDTH, 1, 0));
		_players.push_back(new Player(2 * (screenWidth / 3), playerStartY, PLAYER_WIDTH, 1, 1));
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

	for (Star* star : _props)
		delete (star);
}

int	Game::getPlayerHealth(int playerId) const
{
	if (playerId < 0 || playerId >= static_cast<int>(_players.size()))
		return 0;

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

int		Game::getScore() const
{
	return (_score);
}

void	Game::showEntities() const
{
	for (Star* star : _props)
		star->render(stdscr);

	for (Player* player : _players)
		if (player->isAlive())
			player->render(stdscr);

	for (AEnemy* entity : _enemies)
		entity->render(stdscr);

	for (Bullet* bullet : _playersBullets)
		bullet->render(stdscr);

	for (Bullet* bullet : _enemiesBullets)
		bullet->render(stdscr);

	for (Asteroid* asteroid : _asteroids)
		asteroid->render(stdscr);
}

void	Game::addStar()
{
	const char *starSymbols[] = { ".", "+", "*"};

	Star* newStar = new Star(rand() % (_screenWidth - 2) + 1, 1, 0, 0);
	
	_props.push_back(newStar);
}

void	Game::start()
{
	_started = true;
}

void	Game::stop()
{
	_started = false;
}

void    Game::updateStars()
{
	// Update stars position and remove those that go off-screen
	for (Star* star : _props)
	{
		if (!star->move(0, star->getSpeed()) || star->getY() >= _screenHeight - 4)
			star->setHealth(0); // Mark star for deletion
	}
}

void	Game::update()
{
	// Move enemies's bullets downwards and check for collisions with players
	for (Bullet* bullet : _enemiesBullets)
	{
		if (bullet->move(0, 1))
		{
			if (bullet->getY() >= _screenHeight - 3)
				bullet->setHealth(0);

			for (Player* player : _players)
			{
				if (bullet->checkCollision(*player))
				{
					player->takeDamage(bullet->getSymbol() == MINION_BULLET_SYMBOL ? MINION_DAMAGE : BOSS_DAMAGE);
					bullet->setHealth(0); // Mark bullet for deletion
				}
				if (bullet->getY() >= _screenHeight - 3)
					bullet->setHealth(0); // Mark bullet for deletion
			}

			for (Bullet *playerBullet : _playersBullets)
			{
				if (bullet->checkCollision(*playerBullet))
				{
					bullet->setHealth(0); // Mark enemy bullet for deletion
					playerBullet->setHealth(0); // Mark player bullet for deletion
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
			if (bullet->getY() <= 0)
				bullet->setHealth(0);

			// Check bullets collision with asteroids first
			for (Asteroid* asteroid : _asteroids)
			{
				if (bullet->checkCollision(*asteroid))
				{
					asteroid->takeDamage(PLAYER_DAMAGE);
					bullet->setHealth(0);
					_score += POINTS_PER_ASTEROID;
				}
			}

			// Then check collision with enemies
			for (AEnemy* enemy : _enemies)
			{
				if (bullet->checkCollision(*enemy))
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

			for (Bullet *enemyBullet : _enemiesBullets)
			{
				if (bullet->checkCollision(*enemyBullet))
				{
					bullet->setHealth(0); // Mark player bullet for deletion
					enemyBullet->setHealth(0); // Mark enemy bullet for deletion
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
			if (asteroid->checkCollision(*player))
			{
				player->takeDamage(ASTEROID_DAMAGE);
				asteroid->setHealth(0);
			}
		}
	}

	// Enemies shooting
	for (AEnemy* enemy : _enemies)
	{
		if (rand() % 100 < 5) // 5% chance to shoot each frame
		{
			Bullet* newBullet = enemy->shoot();
			if (newBullet)
				_enemiesBullets.push_back(newBullet);
		}
		if (Boss* boss = dynamic_cast<Boss*>(enemy))
		{
			bossBehavior(boss);
			// Check the boss collision with players after moving
			for (Player* player : _players)
			{
				if (boss->checkCollision(*player))
					player->setHealth(0); // Instant death on collision with boss
			}
		}
	}

	cleanDeathEntities();

	if (isGameOver())
		stop();
}

void	Game::renderBackground()
{
	// Move stars downwards and remove those that go off-screen
	for (Star* star : _props)
	{
		if (!star->move(0, 1) || star->getY() >= _screenHeight - 3)
			star->setHealth(0); // Mark star for deletion
	}
}

void	Game::addMinion()
{
	int x = 1 + rand() % (_screenWidth - 2 - PLAYER_WIDTH);
	int y = 2; // spawn at top
	_enemies.push_back(new Minion(x, y, PLAYER_WIDTH, 1));
}

void	Game::addBoss()
{
	int x = 1 + rand() % (_screenWidth - 2 - BOSS_WIDTH);
	int y = 2;
	_enemies.push_back(new Boss(x, y, BOSS_WIDTH, 1));
}

void	Game::addAsteroid()
{
	int ax = 1 + rand() % (_screenWidth - 2 - 3);
	Asteroid* newAsteroid = new Asteroid(ax, 1, 3, 1);
	_asteroids.push_back(newAsteroid);
}

void	Game::cleanDeathEntities()
{
	_enemies.remove_if([](AEntity* enemy) { if (!enemy->isAlive()) { delete enemy; return true; } return false; });
	_enemiesBullets.remove_if([](Bullet* bullet) { if (!bullet->isAlive()) { delete bullet; return true; } return false; });
	_playersBullets.remove_if([](Bullet* bullet) { if (!bullet->isAlive()) { delete bullet; return true; } return false; });
	_asteroids.remove_if([](Asteroid* asteroid) { if (!asteroid->isAlive()) { delete asteroid; return true; } return false; });
	_props.remove_if([](Star* star) { if (!star->isAlive()) { delete star; return true; } return false; });
}

// Return false if the move would put the player out of bounds, true otherwise
bool	Game::playerMove(int playerId, int deltaX)
{
    if (playerId < 0)
        throw InvalidParameters();

    if (playerId >= static_cast<int>(_players.size()))
        return false;

    if (!_started)
        throw GameNotStarted();

    auto it = _players.begin();
    std::advance(it, playerId);

    Player* player = *it;
	if (!player->isAlive())
		return false;

    int newX = player->getX() + deltaX;
    int width = PLAYER_WIDTH;

    if (newX < 1 || newX + width > _screenWidth - 1)
        return false;

    return player->move(deltaX, 0);
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

	if (!(*it)->isAlive())
		return;

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

int		Game::getEnemyCount() const
{
	return (_enemies.size());
}

void	Game::bossBehavior(Boss *enemy)
{
	if (rand() % 100 < 90) // Move the boss towards the nearest player 2% of the time
		return;

	// Find the nearest living player
	Player* nearestPlayer = nullptr;
	double minDistance = std::numeric_limits<double>::max();

	for (Player* player : _players)
	{
		if (!player->isAlive())
			continue;

		double dx = player->getX() - enemy->getX();
		double dy = player->getY() - enemy->getY();
		double distance = dx * dx + dy * dy; // squared distance (no need for sqrt for comparison)

		if (distance < minDistance)
		{
			minDistance = distance;
			nearestPlayer = player;
		}
	}

	// Move towards the nearest player
	if (nearestPlayer)
	{
		int moveX = 0;
		int moveY = 0;

		int dx = abs(nearestPlayer->getX() - enemy->getX());
		int dy = abs(nearestPlayer->getY() - enemy->getY());

		// If horizontal distance is greater, move horizontally; otherwise move vertically
		if (dx > dy)
		{
			if (nearestPlayer->getX() > enemy->getX())
				moveX = 1;
			else if (nearestPlayer->getX() < enemy->getX())
				moveX = -1;
		}
		else
		{
			if (nearestPlayer->getY() > enemy->getY())
				moveY = 1;
			else if (nearestPlayer->getY() < enemy->getY())
				moveY = -1;
		}

		enemy->move(moveX, moveY);
	}
}

const char	*Game::InvalidParameters::what() const throw()
{
	return ("Invalid parameters provided");
}

const char	*Game::GameNotStarted::what() const throw()
{
	return ("Game has not been started yet");
}