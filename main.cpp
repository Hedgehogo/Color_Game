#include "src/program/program.hpp"
#include "lib/modules/appendix/yaml-cpp/yamlBuilder/shortcut/shortcut.hpp"

int main() {
	srand(time(NULL));
	ui::yamlBuilderInit();
	ui::inherit<ui::IScalable, cg::GameCustomizer>();
	ui::inherit<ui::IScalable, cg::PointsDisplay>();
	ui::inherit<ui::IScalable, cg::VictoryCatcher>();
	ui::inherit<ui::Layer, cg::LayerWithConstCenter>();
	cg::Program program{sf::VideoMode(400, 200), "IE works!", "../example-resources/test.yaml"};
	program.run();
}
