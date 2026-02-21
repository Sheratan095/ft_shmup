#ifndef AENTITY_HPP
#define AENTITY_HPP

class AEntity
{
	protected:
		int		_x;
		int		_sx = 0;
		int		_y;
		int		_sy = 0;
		char	_symbol;
		int		_health = -1;

	public:
		AEntity(int x, int y, int sx, int sy, char symbol, int health = -1)
			: _x(x), _sx(sx), _y(y), _sy(sy), _symbol(symbol), _health(health)
		{}

		virtual ~AEntity() {}

		int		getX() const { return _x; }
		int		getY() const { return _y; }
		int		getSx() const { return _sx; }
		int		getSy() const { return _sy; }
		char	getSymbol() const { return _symbol; }

		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }

		void	takeDamage(int d) { _health -= d; if (_health < 0) _health = 0; }

		bool	isAlive() const { return _health > 0; }

		
		virtual void	move(int dx, int dy) = 0;
};

#endif