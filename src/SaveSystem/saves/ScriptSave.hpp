#ifndef SWIFT_SCRIPT_SAVE_HPP
#define SWIFT_SCRIPT_SAVE_HPP

#include "Scripting/Script.hpp"

namespace swift
{
	class ScriptSave
	{
		friend class SaveManager;
		friend class Save;
		friend class Allocator;
			
		public:
			using Variable = std::pair<decltype(LUA_TNUMBER), std::string>;
			using Data = std::vector<Variable>;
			
			virtual ~ScriptSave() = default;
			
			// loads data to the given Script
			virtual void load(Script& w);
			
			// saves data from the given Script
			virtual void save(Script& w);
			
			const std::string& getName() const;
			
		protected:
			ScriptSave(Script& s);
			ScriptSave(const std::string& n);
			
			Data variables;
			
		private:
			std::string name;
			
		public:
			struct Allocator : std::allocator<ScriptSave>
			{
				template<typename T, typename... Args>
				void construct(T* p, Args&&... args)
				{
					new (static_cast<void*>(p)) T(std::forward<Args>(args)...);
				}

				template<typename T>
				struct rebind
				{
					using other = ScriptSave::Allocator;
				};
				
				using value_type = ScriptSave;
			};
	};
}

#endif // SWIFT_SCRIPT_SAVE_HPP
