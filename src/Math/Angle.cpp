#include "Angle.hpp"

namespace swift
{
	namespace math
	{
		Angle::Angle()
		:	value(0.f)
		{}

		Angle::Angle(float val, AngleType at)
		:	value(val)
		{
			convertToAngle(at);
		}
		
		Angle::Angle(const Angle& other)
		:	value(other.getValue())
		{}

		float Angle::getDegrees() const
		{
			return value * 360.f;
		}

		float Angle::getRadians() const
		{
			return value * 2 * PI;
		}

		float Angle::getValue() const
		{
			return value;
		}

		void Angle::convertToAngle(AngleType at)
		{
			do
			{
				switch(at)
				{
					case AngleType::Degrees:
						value /= 360.f;
						break;
					case AngleType::Radians:
						value /= 2 * PI;
						break;
					case AngleType::Norm:
						value /= 100;
						break;
				}
			}
			while(value > 1.f || value <= -1.f);
			
			if(value < 0.f)
				value += 1.f;
		}

		bool operator ==(const Angle& left, const Angle& right)
		{
			return left.getValue() == right.getValue();
		}

		bool operator !=(const Angle& left, const Angle& right)
		{
			return left.getValue() != right.getValue();
		}

		Angle operator -(const Angle& right)
		{
			return {-right.getValue(), AngleType::Norm};
		}
		
		Angle& operator +=(Angle& left, const Angle& right)
		{
			left = left + right;
			return left;
		}
		
		Angle& operator -=(Angle& left, const Angle& right)
		{
			left = left - right;
			return left;
		}
		
		Angle operator +(const Angle& left, const Angle& right)
		{
			return {left.getValue() + right.getValue(), AngleType::Norm};
		}
		
		Angle operator -(const Angle& left, const Angle& right)
		{
			return {left.getValue() - right.getValue(), AngleType::Norm};
		}
		
	}
}
