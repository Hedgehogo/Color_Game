#pragma once
#include "../../lib/ui/UI.hpp"

namespace ui {
	template<>
	bool convert(const YAML::Node &node, sf::Time &game);
}

namespace cg {
	using STime = ui::SValue<sf::Time>;
	using PSTime = std::shared_ptr<STime>;
}
