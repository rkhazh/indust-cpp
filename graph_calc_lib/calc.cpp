#include "graph_calc.h"

void GraphCalc::calculate(const SetGraph &graph, std::map<int, GraphCalc::Node> &nodes) {
    std::stack<int> stack;
    std::stack<int> stack_rev;
    for (int edg = 0; edg < graph.vertices_count(); ++edg) {
        stack.push(edg);
        while (!stack.empty()) {
            int cur = stack.top();
            stack.pop();
            switch (nodes[cur].color) {
                case 0:
                    nodes[cur].color = 1;
                    break;
                case 3:
                    continue;
                case 1:
                    continue;
            }
            auto const &children = graph.get_next_vertices(cur);
            if (children.empty()) { 
                nodes[cur].color = 2;
                continue;
            }
            bool has_white_child = false; // #WhiteVertexMatter
            for (auto const &child: children) {
                switch (nodes[child].color) {
                    case 1: // gray
                        //cycle
                        nodes[cur].color = 3;
                        while (!stack_rev.empty()) {
                            int cur_rev = stack_rev.top();
                            stack_rev.pop();
                            nodes[cur_rev].color = 3;
                        }
                        break;
                    case 0: // white
                        has_white_child = true;
                        stack.push(child);
                        break;
                    case 3:
                        nodes[cur].color = 3;
                        while (!stack_rev.empty()) {
                            int cur_rev = stack_rev.top();
                            stack_rev.pop();
                            nodes[cur_rev].color = 3;
                        }
                        break;
                };
            }
            if (nodes[cur].color == 1) {
                if (!has_white_child) {
                    for (auto const &child: children) {
                        if (!nodes[child].defined) {
                            nodes[cur].defined = false;
                            break;
                        }
                        nodes[cur].val += nodes[child].val;
                    }
                    nodes[cur].color = 2;
                } else {
                    // check this node later, when it will not have any white children
                    stack_rev.push(cur);

                }
            }
        }
        while (!stack_rev.empty()) {
            int cur = stack_rev.top();
            stack_rev.pop();
            assert(nodes[cur].color == 1);
            auto const &children = graph.get_next_vertices(cur);
            for (auto const &child: children) {
                assert(nodes[child].color == 2);
                if (!nodes[child].defined) {
                    nodes[cur].defined = false;
                    break;
                }
                nodes[cur].val += nodes[child].val;
            }
            nodes[cur].color = 2;
        }
    }
}

void test() {
    using namespace GraphCalc;

    int size = 10;
    SetGraph graph = SetGraph(size);
    std::map<int, Node> nodes_map = std::map<int, Node>();
    nodes_map[0] = Node("0", 0);
    nodes_map[1] = Node("1", 1000, false);
    nodes_map[2] = Node("2", 2000);
    nodes_map[3] = Node("3", 10000);
    nodes_map[4] = Node("4", 1);
    nodes_map[5] = Node("5", 10);
    nodes_map[6] = Node("6", 100);
    nodes_map[7] = Node("7", 200);
    nodes_map[8] = Node("8", 1);
    nodes_map[9] = Node("9", 10, false);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(2, 1);
    graph.add_edge(1, 3);
    graph.add_edge(3, 4);
    //graph.add_edge(4, 1);
    graph.add_edge(4, 5);
    graph.add_edge(4, 6);
    graph.add_edge(6, 7);
    graph.add_edge(8, 9);
    nodes_map[10] = Node("10",5000);
    graph.add_vertex();
    graph.add_edge(10,3);
    calculate(graph, nodes_map);
    std::cout << "DONE" << std::endl;
}

int main() {

    test();
    return 0;
}
