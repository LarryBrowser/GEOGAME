#include "Game.h"
#include <map>
#include "Action.h"

class Scene {
	std::shared_ptr<Game>		m_game;
	EntityManager				m_entities;
	int							m_currentFrame{};
	std::map<int, std::string>	m_actionMap;
	bool						m_paused{};
	bool						m_hasEnded{};
public:
	virtual void update() = 0;
	virtual void sDoAction(Action& action) = 0;
	virtual void sRender() = 0;

	void simulate(int i);
	void doAction(Action& action);
	void registerAction(Action& action);
};
