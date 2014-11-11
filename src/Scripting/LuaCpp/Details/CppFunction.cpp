#include "CppFunction.hpp"

namespace lpp
{
	std::unordered_map<std::string, std::unique_ptr<BaseCppFunction>> BaseCppFunction::functions;
}
