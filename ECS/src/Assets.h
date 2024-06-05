#include "SFML/Graphics.hpp"
#include "SFML/Audio/Sound.hpp"
#include "Animation.h"
class Assets {
	//TEXTURES AND ANIMATIONS
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, Animation>   m_animations;
	std::map<std::string, sf::Sound>   m_sounds;
	std::map<std::string, sf::Font>	   m_fonts;
public:
	void addTexture(std::string& name, std::string& path);
	void addAnimation(std::string& name, Animation& anim);
	void addSound(std::string& name, std::string& path);
	void addFont(std::string& name, std::string& path);

	sf::Texture&	getTexture(std::string& name);
	Animation&		getAnimation(std::string& name);
	sf::Sound&		getSound(std::string& name);
	sf::Font&		getFont(std::string& name);
 };
