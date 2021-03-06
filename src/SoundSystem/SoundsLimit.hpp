#ifndef SOUNDS_LIMIT_HPP
#define SOUNDS_LIMIT_HPP

namespace swift
{
	class SoundsLimit
	{
		protected:
			SoundsLimit() = default;
			
			static unsigned total;
			static const unsigned limit;
	};
}

#endif // SOUNDS_LIMIT_HPP
