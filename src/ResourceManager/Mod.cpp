#include "Mod.hpp"

namespace swift
{
	Mod::Mod(const gfs::Path& p)
	:	folder(p),
		name(folder.name()),
		version("0.0"),
		author("unknown"),
		description("unknown"),
		active(false)
	{}
	
	Mod::Mod(const gfs::Path& p, const std::string& n, const std::string& v, const std::string& a, const std::string& d)
	:	folder(p),
		name(n),
		version(v),
		author(a),
		description(d),
		active(false)
	{}
	
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
	
	const gfs::Path& Mod::getFolder() const
	{
		return folder;
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

	bool operator==(const Mod& lhs, const Mod& rhs)
	{
		return lhs.name == rhs.name && lhs.version == rhs.version && lhs.author == rhs.author && lhs.folder == rhs.folder;
	}

	bool operator!=(const Mod& lhs, const Mod& rhs)
	{
		return !(lhs == rhs);
	}
}
