#include "TextureArray.h"

#include <algorithm>
#include <cstring>
#include <filesystem>
#include "Texture.h"

TextureArray::TextureArray()
{
	for (auto& entry: std::filesystem::recursive_directory_iterator("./"))
	{
		if(!entry.is_directory() && strcmp(entry.path().extension().c_str(), ".png") == 0)
		{
			m_Textures.emplace(entry.path().stem().c_str(), new Texture(entry.path().c_str()));
		}
	}

	m_Textures.emplace("null", nullptr);
}

TextureArray::~TextureArray()
{
	for(auto [key, tex] : m_Textures)
		delete tex;
}
unsigned int TextureArray::size() const
{
	return m_Textures.size();
}

Texture*& TextureArray::operator[](const char* key)
{
	for(auto [k,t]: m_Textures)
		printf("%s\n", k.c_str());
	if(m_Textures.find(key) != m_Textures.end())
		return m_Textures[key];
	else
	{
		printf("njdsahk\n");
		return m_Textures["null"];
	}
}
