#ifndef BODY_HPP
#define BODY_HPP

namespace tg
{
	class Body
	{
		public:
			enum class Type
			{
			    Star,
			    Earthlike,	// mix of land and water
			    Barren,
			    Aquatic,
			    Rocky,
			    Gas,
			};
			
			enum class AtmosphereGas
			{
				Hydrogen,
				Nitrogen,
				Oxygen,
				Fluorine,
				Chlorine
			};
			
			enum class LifeLevel
			{
				None,
				UniCellular,
				MultiCellular,
				CNS,			// Central Nervous System
				Invertebrates,
				Vertebrates,
				Sentience,
				Humanoid
			};
			
			struct Atmosphere
			{
				AtmosphereGas primary;
				AtmosphereGas secondary;
			};

			Body(Type t, LifeLevel l, Atmosphere a);
			~Body();

		private:
			Type type;
			LifeLevel life;
			Atmosphere atmosphere;
			
			unsigned int mass;
			unsigned int radius;
	};
}

#endif // BODY_HPP
