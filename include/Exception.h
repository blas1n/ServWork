#pragma once

#include <cstring>
#include <string>

class SocketException
{
public:
	explicit SocketException(const std::string& inKind) noexcept
		: kind(inKind) {}

	std::string Message() const noexcept
	{
		return kind + " error : " + strerror(errno);
	}

private:
	std::string kind;
};

class FileException
{
public:
	explicit FileException(const std::string& inPath) noexcept
		: path(inPath) {}

	std::string Get() const noexcept
	{
		return path + " not found";
	}

private:
	std::string path;
};

class ThreadException
{
public:
	explicit ThreadException(const std::string& inMsg) noexcept
		: msg(inMsg) {}

	const std::string& Message() const noexcept
	{
		return msg;
	}

private:
	std::string msg;
};
