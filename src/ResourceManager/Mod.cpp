#include "Mod.hpp"

namespace swift
{
	Mod::Mod(const std::string& n, const std::string& v, const std::string& a, const std::string& d)
	:	name(n),
		version(v),
		author(a),
		description(d),
		active(false)
	{}

	void Mod::addFile(const std::string& f)
	{
		files.push_back(f);
	}

	const std::string& Mod::getName() const
	{
		return name;
	}

	const std::string& Mod::getVersion() const
	{
		return version;
	}

	const std::string& Mod::getAuthor() const
	{
		return author;
	}

	const std::string& Mod::getDescription() const
	{
		return description;
	}

	const std::vector<std::string>& Mod::getFiles() const
	{
		return files;
	}
	
	bool Mod::isActive() const
	{
		return active;
	}

	void Mod::setName(const std::string& n)
	{
		name = n;
	}

	void Mod::setVersion(const std::string& v)
	{
		version = v;
	}

	void Mod::setAuthor(const std::string& a)
	{
		author = a;
	}

	void Mod::setDescription(const std::string& d)
	{
		description = d;
	}
	
	void Mod::setActive(bool a)
	{
		active = a;
	}

	bool operator ==(const Mod& lhs, const Mod& rhs)
	{
		return lhs.name == rhs.name && lhs.version == rhs.version && lhs.author == rhs.author;
	}

	bool operator !=(const Mod& lhs, const Mod& rhs)
	{
		return !(lhs == rhs);
	}
}
