#include <map>
#include <string>

class Texture;

class TextureArray
{
public:
	using iterator = std::map<std::string, Texture*>::iterator;
private:
	std::map<std::string, Texture*> m_Textures;
public:
	TextureArray();
	~TextureArray();

	unsigned int size() const;
	Texture*& operator[](const char* key);

	iterator begin();
	iterator end();
};
