#include "Game.h"
#include <cassert>
void Game::init()
{
	std::ifstream fin{ "src/Config.txt" };
	std::string type{};
	int windowW, windowH, windowStyle, FPS{};
	std::string FontFilename{};
	int fontSize, fontR, fontG, fontB{};
	int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, VMIN, VMAX, L, SI{};
	float S, SMIN, SMAX{};
	while (fin >> type)
	{
		if (type == "Window")
		{
			fin >> windowW >> windowH >> FPS >> windowStyle;
			m_Window.create(sf::VideoMode(windowW, windowH), "GEO HELL", windowStyle);
			m_Window.setFramerateLimit(FPS);
		}

		if (type == "Font")
		{
			fin >> FontFilename >> fontSize >> fontR >> fontG >> fontB;
			if (!m_font.loadFromFile(FontFilename))
			{
				std::cout << "Failed loading font!" << '\n';
			}
			m_text.setFont(m_font);
			m_text.setCharacterSize(fontSize);
			m_text.setFillColor(sf::Color(fontR, fontG, fontB));
		}

		if (type == "Player")
		{
			fin >> SR >> CR >> S >> FR >> FG >> FB >> OR >> OG >> OB >> OT >> V;
			m_playerConfig.SR = SR;
			m_playerConfig.CR = CR;
			m_playerConfig.S = S;
			m_playerConfig.FR = FR;
			m_playerConfig.FG = FG;
			m_playerConfig.FB = FB;
			m_playerConfig.OR = OR;
			m_playerConfig.OG = OG;
			m_playerConfig.OB = OB;
			m_playerConfig.OT = OT;
			m_playerConfig.V = V;
			//std::cout << "Player specifications: " << SR << CR << FR << FG << FB << OR << OG << OB << OT << V << S;
		}

		if (type == "Enemy")
		{
			fin >> SR >> CR >> SMIN >> SMAX >> OR >> OG >> OB >> OT >> VMIN >> VMAX >> L >> SI;
			m_enemyConfig.SR = SR;
			m_enemyConfig.CR = CR;
			m_enemyConfig.SMIN = SMIN;
			m_enemyConfig.SMAX = SMAX;
			m_enemyConfig.OR = OR;
			m_enemyConfig.OG = OG;
			m_enemyConfig.OB = OB;
			m_enemyConfig.OT = OT;
			m_enemyConfig.VMIN = VMIN;
			m_enemyConfig.VMAX = VMAX;
			m_enemyConfig.L = L;
			m_enemyConfig.SI = SI;
		}

		if (type == "Bullet")
		{
			fin >> SR >> CR >> S >> FR >> FG >> FB >> OR >> OG >> OB >> OT >> V >> L;
			m_bulletConfig.SR = SR;
			m_bulletConfig.CR = CR;
			m_bulletConfig.S = S;
			m_bulletConfig.FR = FR;
			m_bulletConfig.FG = FG;
			m_bulletConfig.FB = FB;
			m_bulletConfig.OR = OR;
			m_bulletConfig.OG = OG;
			m_bulletConfig.OB = OB;
			m_bulletConfig.OT = OT;
			m_bulletConfig.V = V;
			m_bulletConfig.L = L;
		}
	}
}

void Game::update()
{
	m_entities.update();
}

void Game::spawnPlayer()
{
	auto entity = m_entities.addEntity("player");
	float mx = m_Window.getSize().x / 2.0f;
	float my = m_Window.getSize().y / 2.0f;
	entity->addComponent<CTransform>(Vec2(mx, my),
		Vec2(0.0f, 0.0f), 0.0f);
	entity->hasComponent<CCollusion>();
	entity->addComponent<CShape>(m_playerConfig.SR, m_playerConfig.V, 
		sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB),
		sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);
	entity->addComponent<CInput>();
	entity->addComponent<CCollusion>(m_playerConfig.CR);
	m_player = entity;
}

void Game::spawnEnemy()
{
	auto entity = m_entities.addEntity("enemy");
	float ex, ey{};
	while (true)
	{
		ex = static_cast<float>(RNG(m_enemyConfig.CR, m_Window.getSize().x - m_enemyConfig.CR));
		ey = static_cast<float>(RNG(m_enemyConfig.CR, m_Window.getSize().y - m_enemyConfig.CR));
		Vec2 vec(ex, ey);
		if (sqrt(vec.length(m_player->getComponent<CTransform>().pos) >= m_player->getComponent<CCollusion>().radius * 5))
		{
			break;
		}
		std::cout << "AMOGUS: \n";
	}
	int verticeVal = RNG(m_enemyConfig.VMIN, m_enemyConfig.VMAX);
	float speedVal = RNG(m_enemyConfig.SMIN,m_enemyConfig.SMAX);
	int FR = RNG(1, 255);
	int FG = RNG(1, 255);
	int FB = RNG(1, 255);
	float xDir = RNG(0, 1) ? true : -1;
	float yDir = RNG(0, 1) ? true : -1;

	entity->addComponent<CTransform>((Vec2(ex, ey)),
		Vec2(speedVal * xDir, speedVal * yDir), 0.0f);
	entity->addComponent<CShape>(m_enemyConfig.SR, verticeVal, sf::Color(FR, FG, FB),
		sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);
	entity->addComponent<CCollusion>(m_enemyConfig.CR);
	entity->addComponent<CLifeSpan>(20*60);
	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies()
{
	auto entity = m_entities.addEntity("enemy");
	entity->addComponent<CLifeSpan>(m_enemyConfig.L);
}

void Game::sMovement()
{
	for (auto e : m_entities.getEntities())
	{
		auto& e_transform = e->getComponent<CTransform>();
		e_transform.pos.x += e_transform.velocity.x;
		e_transform.pos.y += e_transform.velocity.y;
	}
	auto& m_player_transform = m_player->getComponent<CTransform>();
	auto& m_player_input = m_player->getComponent<CInput>();
	m_player_transform.velocity = { 0, 0 };
	if (m_player_input.up)
	{
		m_player_transform.velocity.y = -1 * m_playerConfig.S;
	}

	if (m_player_input.left)
	{
		m_player_transform.velocity.x = -1 * m_playerConfig.S;
	}

	if (m_player_input.down)
	{
		m_player_transform.velocity.y = m_playerConfig.S;
	}
	
	if (m_player_input.right)
	{
		m_player_transform.velocity.x = m_playerConfig.S;
	}
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& target)
{
	auto bullet = m_entities.addEntity("bullet");

	Vec2 BDir = target - entity->getComponent<CTransform>().pos; // bullet direction
	BDir.normalize();

	Vec2 SPos = entity->getComponent<CTransform>().pos + BDir; // spawn position

	bullet->addComponent<CTransform>(Vec2(SPos), 
		Vec2(BDir.x*m_bulletConfig.S, BDir.y*m_bulletConfig.S), 0.0f);
	bullet->addComponent<CShape>(m_bulletConfig.SR, m_bulletConfig.V,
		sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB), 
		sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);
	bullet->addComponent<CCollusion>(m_bulletConfig.CR);
	bullet->addComponent<CLifeSpan>(m_bulletConfig.L);
}

void Game::spawnSpecialWeapon()
{
	int timePassed = m_currentFrame - m_lastSpecialSpawnTime;
	if (timePassed > 10 * 60 || m_specialWeaponReady)
	{
		m_paused = true;
		m_lastSpecialSpawnTime = m_currentFrame;
	}
	m_specialWeaponReady = false;
}

void Game::sUserInput()
{
	sf::Event e;
	auto& player_inputs = m_player->getComponent<CInput>();
	while (m_Window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			m_running = false;
		}

		if (e.type == sf::Event::KeyPressed)
		{
			switch (e.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W key Pressed\n";
				player_inputs.up = true;
				break;
			case sf::Keyboard::A:
				std::cout << "A key Pressed\n";
				player_inputs.left = true;
				break;
			case sf::Keyboard::S:
				std::cout << "S key Pressed\n";
				player_inputs.down = true;
				break;
			case sf::Keyboard::D:
				std::cout << "D key Pressed\n";
				player_inputs.right = true;
				break;
			case sf::Keyboard::Escape:
				m_running = false;
				break;
			case sf::Keyboard::Space:
				std::cout << "Space key Pressed\n";
				spawnSpecialWeapon();
				break;
			default: break;
			}
		}

		if (e.type == sf::Event::KeyReleased)
		{
			switch (e.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W key Released\n";
				player_inputs.up = false;
				break;
			case sf::Keyboard::A:
				std::cout << "A key Released\n";
				player_inputs.left = false;
				break;
			case sf::Keyboard::S:
				std::cout << "S key Released\n";
				player_inputs.down = false;
				break;
			case sf::Keyboard::D:
				std::cout << "D key Released\n";
				player_inputs.right = false;
				break;
			default: break;
			}
		}

		if (e.type == sf::Event::MouseButtonPressed)
		{
			switch (e.mouseButton.button)
			{
			case sf::Mouse::Left: std::cout << "Left mouse button clicked at: ("
				<< e.mouseButton.x << ',' << e.mouseButton.y << ")\n";
				spawnBullet(m_player, Vec2(e.mouseButton.x, e.mouseButton.y));
				break;
			case sf::Mouse::Right: std::cout << "Right mouse button clicked at: ("
				<< e.mouseButton.x << ',' << e.mouseButton.y << ")\n";
				break;
			default: break;
			}
		}
	}
}

void Game::sRender()
{
	m_Window.clear(sf::Color(101.0f, 89.0f, 248.0f));
	std::stringstream ss;
	ss << m_score;
	std::string score{ ss.str() };
	m_text.setString("SCORE: " + score);
	m_Window.draw(m_text);
	for (auto& e : m_entities.getEntities())
	{
		auto& e_shape = e->getComponent<CShape>();
		auto& e_transform = e->getComponent<CTransform>();
		e_shape.circle.setPosition(e_transform.pos.x, e_transform.pos.y);
		e_shape.circle.setRotation(e_transform.angle);
		m_Window.draw(e_shape.circle);
		e_transform.angle += 1.0f;
	}
	m_Window.display();
}

void Game::sEnemySpawner()
{
	int timePassed = m_currentFrame - m_lastEnemySpawnTime;
	const int second{ 60 };
	if(timePassed > m_enemyConfig.SI)
	{ 
		spawnEnemy();
	}
}

void Game::sCollusion()
{
	//3 is the amount of pixels decided for padding so that player doesn't look glitchy when pushing against the wall
	for (auto e : m_entities.getEntities("enemy"))
	{
		auto& e_transform = e->getComponent<CTransform>();
		auto& e_shape = e->getComponent<CShape>();
		if (e_transform.pos.x - e_shape.circle.getRadius() <= 3 && e_transform.velocity.x < 0)
		{
			e_transform.velocity.x *= -1;
		}
		if (e_transform.pos.y - e_shape.circle.getRadius() <= 3 && e_transform.velocity.y < 0)
		{
			e_transform.velocity.y *= -1;
		}
		if (e_transform.pos.x + e_shape.circle.getRadius() >= 
			m_Window.getSize().x - 3 && e_transform.velocity.x > 0)
		{
			e_transform.velocity.x *= -1;
		}
		if (e_transform.pos.y + e_shape.circle.getRadius() >= 
			m_Window.getSize().y - 3 && e_transform.velocity.y > 0)
		{
			e_transform.velocity.y *= -1;
		}
	}

	for (auto e : m_entities.getEntities("player"))
	{
		auto& e_transform = e->getComponent<CTransform>();
		auto& e_shape = e->getComponent<CShape>();
		if (e_transform.pos.x - e_shape.circle.getRadius() <= 3 && e_transform.velocity.x < 0)
		{
			e_transform.velocity.x *= -1;
		}
		if (e_transform.pos.y - e_shape.circle.getRadius() <= 3 && e_transform.velocity.y < 0)
		{
			e_transform.velocity.y *= -1;
		}
		if (e_transform.pos.x + e_shape.circle.getRadius() >=
			m_Window.getSize().x - 3 && e_transform.velocity.x > 0)
		{
			e_transform.velocity.x *= -1;
		}
		if (e_transform.pos.y + e_shape.circle.getRadius() >=
			m_Window.getSize().y - 3 && e_transform.velocity.y > 0)
		{
			e_transform.velocity.y *= -1;
		}
	}
	float rd{}; //radius distance
	float vl{}; // vector length

	for (auto p : m_entities.getEntities("player"))
	{
		auto& p_transform = p->getComponent<CTransform>();
		auto& p_collusion = p->getComponent<CCollusion>();
		for (auto& e : m_entities.getEntities("enemy"))
		{
			auto& e_transform = e->getComponent<CTransform>();
			auto& e_collusion = e->getComponent<CCollusion>();
			rd = p_collusion.radius + e_collusion.radius;
			vl = p_transform.pos.length(e_transform.pos);

			if (rd * rd > vl)
			{
				e->kill();
				p->kill();
				m_paused = true;
				break;
			}
		}
	}

	for (auto& b : m_entities.getEntities("bullet"))
	{
		auto& b_transform = b->getComponent<CTransform>();
		auto& b_collusion = b->getComponent<CCollusion>();
		for (auto& e : m_entities.getEntities("enemy"))
		{
			auto& e_transform = e->getComponent<CTransform>();
			auto& e_collusion = e->getComponent<CCollusion>();
			rd = b_collusion.radius + e_collusion.radius; 
			vl = b_transform.pos.length(e_transform.pos);

			if (rd * rd > vl)
			{
				e->kill();
				b->kill();
				m_score += 1000*m_entities.getEntities().size();
				break;
			}
		}
	}
}

void Game::sLifespan()
{
	float lsr{}; // Total-remaining lifespan ratio
	for (auto& e : m_entities.getEntities("enemy"))
	{
		auto& e_lifespan = e->getComponent<CLifeSpan>();
		auto& e_shape = e->getComponent<CShape>();
		e_lifespan.remaining--;
		lsr = static_cast<float>(e_lifespan.remaining) / e_lifespan.total;
		//std::cout << "LSR: " << lsr << '\n';
		sf::Color color = e->getComponent<CShape>().circle.getFillColor();
		color.a = lsr * 255.0f;
		e_shape.circle.setFillColor(color);
	}

	for (auto& e : m_entities.getEntities("bullet"))
	{
		auto& e_lifespan = e->getComponent<CLifeSpan>();
		auto& e_shape = e->getComponent<CShape>();
		e_lifespan.remaining--;
		lsr = static_cast<float>(e_lifespan.remaining) / e_lifespan.total;
		std::cout << "LSR: " << lsr << '\n';
		sf::Color color = e_shape.circle.getFillColor();
		color.a = lsr * 255.0f;
		e_shape.circle.setFillColor(color);
	}

	for (auto& e : m_entities.getEntities("enemy"))
	{
		if (e->getComponent<CLifeSpan>().remaining <= 0)
		{
			e->kill();
		}
	}
	for (auto& e : m_entities.getEntities("bullet"))
	{
		if (e->getComponent<CLifeSpan>().remaining <= 0)
		{
			e->kill();
		}
	}
}

void Game::run()
{
	init();
	spawnPlayer();
	while(m_running)
	{ 
		sUserInput();

		if (!m_specialWeaponReady && m_currentFrame - m_lastSpecialSpawnTime > 2*60)
		{
			m_paused = false;
		}

		if (!m_paused)
		{
			sLifespan();
			sEnemySpawner();
			sCollusion();
			sMovement();
		}
		update();
		sRender();

		if (m_player->active() == false)
		{
			for (auto e : m_entities.getEntities())
			{
				e->kill();
			}
			m_score = 0;
			spawnPlayer();
			m_paused = false;
			m_specialWeaponReady = true;
		}
		++m_currentFrame;
	}
}

int Game::RNG(int min, int max)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution rand{ min, max };
	return rand(mt);
}
