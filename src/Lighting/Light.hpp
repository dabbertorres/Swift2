#ifndef LIGHT_HPP
#define LIGHT_HPP

class Light
{
	public:
		Light();
		Light(const int Radius, const sf::Color Color, const int PosX, const int PosY, bool IsBinded = 0, int UnitVecID = 0);
		int radius;
		sf::Color color;
		int posX, posY;

		bool isBindedToUnit;
		int unitVecID;
};

#endif // LIGHT_HPP