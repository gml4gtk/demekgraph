#include "graph.hpp"
#include "parser.hpp"
#include "helper.hpp"

#include <random>
#include <set>

void dfs_preds(const graph& g, vertex_t u, std::vector<std::vector<vertex_t>>& tp) {
	if (!tp[u].empty()) {
		return;
	}

	for (auto v : g.in_neighbours(u)) {
		dfs_preds(g, v, tp);
		for (auto x : tp[v]) {
			tp[u].push_back(x);
		}
		tp[u].push_back(v);
	} 
}

std::vector<std::vector<vertex_t>> dfs_preds(const graph& g) {
	std::vector<std::vector<vertex_t>> tp(g.size());
	for (auto u : g.vertices()) {
		dfs_preds(g, u, tp);
	}
	return tp;
}

void write_dot(const graph& g, const drawing_options& opts, const std::string& file) {
	std::ofstream out { file };

	out << "digraph G{\n";

	for (auto u : g.vertices()) {
		for (auto v : g.out_neighbours(u)) {
			out << opts.labels.at(u) << " -> " << opts.labels.at(v) << "\n";
		}
	}

	out << "}\n";
}

std::string usage_string =
R"(usage: ./cycl [-i] <source_dir>

Loads all files in <source_dir> with .gv extension and adds cycles to the graph.
The output is written to <source_dir> as a new file. All attributes are removed from the file.
The input graphs CANNOT contain any cycles!!!!
    -i Modify each input file instead of saving output as a new file.
)";

void print_help() {
    std::cout << usage_string;
}

int main(int argc, char **argv) {
	std::string in;
	bool inplace = false;
	if (argc == 3 && std::string{ argv[1] } == "-i") {
		inplace = true;
		in = argv[2];
	} else if (argc == 2) {
		if (std::string{ argv[1] } == "-h") {
			print_help();
			return 0;	
		}
		in = argv[1];
	} else {
		print_help();
		return 1;
	}


	std::mt19937 mt;
	auto files = dir_contents(in, ".gv");
	for (auto& f : files) {
		attributes attr;
		drawing_options opts;
		graph g = parse(in + "/" + f, attr, opts);

		auto tp = dfs_preds(g);

		std::uniform_int_distribution<vertex_t> dist(0, g.size() - 1);
		std::set<vertex_t> used;

		int n = 0.3 * g.size();
		while(n) {

			vertex_t u = dist(mt);

			if (used.count(u) > 0 || tp[u].empty()) continue;
			used.insert(u);

			std::uniform_int_distribution<int> pred(0, tp[u].size() - 1);
			vertex_t v = tp[u][ pred(mt) ];

			g.add_edge(u, v);

			--n;
		}

		remove_suffix(f);
		write_dot(g, opts, inplace ? in + "/" + f + ".gv" : in + "/" + f + "_cycles.gv");
	}
}