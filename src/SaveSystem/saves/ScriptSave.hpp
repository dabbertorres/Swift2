#ifndef SWIFT_SCRIPT_SAVE_HPP
#define SWIFT_SCRIPT_SAVE_HPP

#include "../../Scripting/Script.hpp"

namespace swift
{
	class ScriptSave
	{
		friend class SaveManager;
		
		public:
			using Data = std::vector<std::pair<decltype(LUA_TNUMBER), std::string>>;
			
			ScriptSave(Script& s);
			virtual ~ScriptSave() = default;
			
			// loads data to the given Script
			virtual void load(Script& w);
			
			// saves data from the given Script
			virtual void save(Script& w);
			
			const std::string& getName() const;
			
		private:
			ScriptSave(const std::string& n, const Data& d);
			
			std::string name;
			
			Data variables;
			
	};
}

#endif // SWIFT_SCRIPT_SAVE_HPP
