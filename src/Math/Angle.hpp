#ifndef ANGLE_HPP
#define ANGLE_HPP

namespace swift
{
	namespace math
	{
		const float PI = 3.14159265359;

		enum class AngleType
		{
		    Degrees,
		    Radians,
			Norm
		};

		class Angle
		{
			public:
				Angle();
				Angle(float val, AngleType at);
				Angle(const Angle& other);

				float getDegrees() const;
				float getRadians() const;
				float getValue() const;

			private:
				void convertToAngle(AngleType at);

				float value;	// stored as a percetange of rotation around a circle
		};

		bool operator ==(const Angle& left, const Angle& right);
		bool operator !=(const Angle& left, const Angle& right);

		Angle operator -(const Angle& right);
		Angle& operator +=(Angle& left, const Angle& right);
		Angle& operator -=(Angle& left, const Angle& right);
		Angle operator +(const Angle& left, const Angle& right);
		Angle operator -(const Angle& left, const Angle& right);

		template<typename T>
		Angle operator *(const Angle& left, T right)
		{
			return {left.getValue() * right, AngleType::Norm};
		}

		template<typename T>
		Angle operator *(T left, const Angle& right)
		{
			return {left * right.getValue(), AngleType::Norm};
		}

		template<typename T>
		Angle& operator *=(Angle& left, T right)
		{
			left = {left.getValue() * right, AngleType::Norm};
			return left;
		}

		template<typename T>
		Angle operator /(const Angle& left, T right)
		{
			return {left.getValue() / right, AngleType::Norm};
		}

		template<typename T>
		Angle operator /(T left, const Angle& right)
		{
			return {left / right.getValue(), AngleType::Norm};
		}

		template<typename T>
		Angle& operator /=(Angle& left, T right)
		{
			left = {left.getValue() / right, AngleType::Norm};
			return left;
		}
	}
}

#endif // ANGLE_HPP
