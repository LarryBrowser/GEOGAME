#include "Scene.h"
class Scene_Play : Scene
{
	std::string				m_levelPath{};
	std::shared_ptr<Entity> m_player;
	PlayerConfig			m_playerConfig;

public:
	void init();
	void update();
	void sAnimation();
	void sMovement();
	void sEnemySpawner();
	void sCollusion();
	void sRender();
	void sDoAction(Action& action);
	void sDebug();
};
