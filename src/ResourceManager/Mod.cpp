#include "Mod.hpp"

namespace swift
{
	Mod::Mod()
	{

	}

	Mod::Mod(const std::string& n, const std::string& v, const std::string& a)
	{
		name = n;
		version = v;
		author = a;
	}

	Mod::~Mod()
	{
	}

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

	bool Mod::operator ==(const Mod& other) const
	{
		return name == other.name && version == other.version && author == other.author;
	}

	bool Mod::operator !=(const Mod& other) const
	{
		return !(*this == other);
	}
}
