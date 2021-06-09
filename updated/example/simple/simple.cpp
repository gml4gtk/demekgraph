#include "interface.hpp"
#include "svg.hpp"

std::string usage_string =
R"(usage: ./simple <file>

Draw a graph described in the source code to <file>.
)";

void print_help() {
    std::cout << usage_string;
}

int main(int argc, char** argv) {
	if (argc != 2 || argv[1] == std::string{ "-h" }) {
		print_help();
		return 0;
	}

	// the graph builder should be used carefully (see documentation in include/graph.hpp)
	graph g = graph_builder()
				.add_edge(0, 1).add_edge(0, 2).add_edge(0, 3)
				.add_edge(1, 3).add_edge(3, 3).add_edge(2, 4)
				.build();

	attributes attr;
	sugiyama_layout l(g, attr);

	// draw to svg using the svg writer in example/draw/
	drawing_options opts;
	opts.use_labels = false; // disable custom labels and use node ids instead since we have no labels
	// however some lables could be created like so:
	// opts.labels = { {0, "a"}, {1, "B"}, {2, "AB"}, {3, "abc"}, {4, "ABC"} };
	draw_to_svg(argv[1], l, opts);
}
