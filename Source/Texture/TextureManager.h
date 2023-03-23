#pragma once
#include <unordered_map>
#include <string>

class Texture;
class Renderer;

class TextureManager
{
public:
	TextureManager(Renderer* renderer);
	~TextureManager();

	void UnloadData();
	void Shutdown();
	Texture* GetTexture(const std::string& fileName);

private:
	std::unordered_map<std::string, Texture*> mTextures;
	Renderer* mRenderer = nullptr;
};

