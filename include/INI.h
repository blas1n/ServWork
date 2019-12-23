#include <string>
#include <map>

class INI
{
public:
    INI(const std::string& inPath)
        : map(), path(inPath)
    {
        Init();
    }

    INI(std::string&& inPath)
        : map(), path(std::move(inPath))
    {
        Init();
    }

    INI(const INI& other) = default;
    INI(INI&& other) = default;

    INI& operator=(const INI& other) = default;
    INI& operator=(INI&& other) = default;

    ~INI() = default;

    const std::string& Get(const std::string& key) const
    {
        return (*map.find(key)).second;
    }

	void Set(const std::string& key, const std::string& value);

private:
	void Init();

    std::map<std::string, std::string> map;
    std::string path;
};
