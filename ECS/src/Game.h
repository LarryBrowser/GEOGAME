//#include "Assets.h"
#include "EntityManager.h"
#include <cmath>
#include <fstream>
#include <random>
#include <sstream>
#include <string>

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game {
	sf::RenderWindow m_Window;
	sf::Font		 m_font;
	sf::Text		 m_text;
	EntityManager    m_entities;
	PlayerConfig	 m_playerConfig;
	EnemyConfig		 m_enemyConfig;
	BulletConfig	 m_bulletConfig;
	int				 m_score{};
	bool             m_paused{};
	bool             m_running{true};
	int				 m_currentFrame{};
	int				 m_lastEnemySpawnTime{};
	int				 m_lastSpecialSpawnTime{};
	bool			 m_specialWeaponReady{true};

	std::shared_ptr<Entity> m_player;

public:
	void init();
	void update();
	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies();
	void sMovement();
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& target);
	void spawnSpecialWeapon();
	void sUserInput();
	void sRender();
	void sEnemySpawner();
	void sCollusion();
	void sLifespan();
	void run();
	int RNG(int min, int max);
};