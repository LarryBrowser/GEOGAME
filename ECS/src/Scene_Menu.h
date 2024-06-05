#include "Scene.h"

class Scene_Menu : Scene {
	std::vector<std::string> m_menuStrings;
	sf::Text				 m_menuText;
	std::vector<std::string> m_levelPaths;
	int						 m_menuIndex{};
public:
	void init();
	void update();

	void sRender();
	void sDoAction(Action& action);
};