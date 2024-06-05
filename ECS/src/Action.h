#include <string>
class Action {
	std::string m_name;
	std::string m_type;
public:
	std::string& name();
	std::string& type();
};
