#include "time.hpp"

namespace ui {
	template<>
	bool convert(const YAML::Node &node, sf::Time &game) { return true; }
}