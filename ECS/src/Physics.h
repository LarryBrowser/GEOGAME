#include "Entity.h"
class Physics {
	bool isCollusion(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);
	Vec2& getOverlap(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);
	Vec2& getPreviousOverlap(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);
};
