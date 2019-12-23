#include <cstring>
#include <exception>
#include <string>

class SocketException : std::exception
{
public:
	explicit SocketException(const std::string& inKind) noexcept
		: kind(inKind) {}

	const std::string& what() const noexcept override
	{
		return kind + " error : " + stderror(errno);
	}

private:
	std::string kind;
}

class FileException : std::exception
{
public:
	explicit FileException(const std::string& inPath) noexcept
		: path(inPath) {}

	const std::string& what() const noexcept override
	{
		return path + " not found";
	}

private:
	std::string path;
}