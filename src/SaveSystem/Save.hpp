#ifndef SWIFT_SAVE_HPP
#define SWIFT_SAVE_HPP

#include <string>

namespace swift
{
	class Save
	{
		public:
			Save(const std::string& n);
			~Save() = default;
			
			bool isValid() const;
			
			const std::string& getName() const;
			
			const std::string& getLastWorld() const;
			void setLastWorld(const std::string& worldName);

		private:
			std::string name;
			std::string lastWorld;
	};
}

#endif // SWIFT_SAVE_HPP
