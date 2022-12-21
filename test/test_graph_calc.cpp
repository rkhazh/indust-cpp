#include <gtest/gtest.h>
#include <graph_calc.h>
#include <vector>
#include <string>

TEST(SetGraph, setGraphConstructor)
{
    SetGraph graph = SetGraph(3);
    EXPECT_EQ(graph.vertices_count(), 3);
    SetGraph graph1 = graph;
    EXPECT_EQ(graph1.vertices_count(), 3);
}

TEST(SetGraph, addEdge)
{
    SetGraph graph = SetGraph(3);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    auto next_vert = graph.get_next_vertices(0);
    ASSERT_EQ(next_vert.size(), 2);
    EXPECT_EQ(next_vert[0], 1);
    EXPECT_EQ(next_vert[1], 2);
    next_vert = graph.get_prev_vertices(1);
    EXPECT_EQ(next_vert.size(), 1);
    next_vert = graph.get_prev_vertices(2);
    EXPECT_EQ(next_vert.size(), 1);
    next_vert = graph.get_next_vertices(1);
    EXPECT_EQ(next_vert.size(), 0);
}

TEST(SetGraph, addVertex)
{
    SetGraph graph = SetGraph(3);
    EXPECT_EQ(graph.vertices_count(), 3);
    graph.add_vertex();
    EXPECT_EQ(graph.vertices_count(), 4);
}

TEST(GraphCalc, parseGraph)
{
    std::string str_in = "A1=2\nA2=A1+2+5\nA3=A4\nA4=A1+3";
    std::stringstream in_stream(str_in);
    std::map<int, GraphCalc::Node> nodes = std::map<int, GraphCalc::Node>();
    SetGraph graph = GraphCalc::parse_graph(in_stream, nodes);
    ASSERT_EQ(graph.vertices_count(), 4);
    EXPECT_EQ(graph.get_next_vertices(2), std::vector<int>({3}));
}

TEST(GraphCalc, cycleTest)
{
    std::string str_in = "A1=2\nA2=A1+2+5\nA3=A4\nA4=A1+A5\nA5=A3+5";
    std::stringstream in_stream(str_in);
    std::map<int, GraphCalc::Node> nodes = std::map<int, GraphCalc::Node>();
    SetGraph graph = GraphCalc::parse_graph(in_stream, nodes);
    GraphCalc::calculate(graph, nodes);
    EXPECT_EQ(nodes[0].defined, true);
    EXPECT_EQ(nodes[0].color, 2);
    EXPECT_EQ(nodes[0].val, 2);
    EXPECT_EQ(nodes[1].defined, true);
    EXPECT_EQ(nodes[1].color, 2);
    EXPECT_EQ(nodes[1].val, 9);
    EXPECT_EQ(nodes[2].color, 3);
    EXPECT_EQ(nodes[3].color, 3);
    EXPECT_EQ(nodes[4].color, 3);
}

TEST(GraphCalc, undefTest)
{
    std::string str_in = "A1=2\nA2=A1+2+5\nA3=A4\nA4=A1+A5";
    std::stringstream in_stream(str_in);
    std::map<int, GraphCalc::Node> nodes = std::map<int, GraphCalc::Node>();
    SetGraph graph = GraphCalc::parse_graph(in_stream, nodes);
    GraphCalc::calculate(graph, nodes);
    EXPECT_EQ(nodes[0].defined, true);
    EXPECT_EQ(nodes[0].color, 2);
    EXPECT_EQ(nodes[0].val, 2);
    EXPECT_EQ(nodes[1].defined, true);
    EXPECT_EQ(nodes[1].color, 2);
    EXPECT_EQ(nodes[1].val, 9);
    EXPECT_EQ(nodes[2].color, 2);
    EXPECT_EQ(nodes[2].defined, false);
    EXPECT_EQ(nodes[3].color, 2);
    EXPECT_EQ(nodes[3].defined, false);
    EXPECT_EQ(nodes[4].color, 2);
    EXPECT_EQ(nodes[4].defined, false);
}

TEST(GraphCalc, multibranchTest)
{
    std::string str_in = "A1=2\nA2=A1+2+5\nA3=A4\nA4=A1+A5\nA6=3+3+A8+A7\nA8=A7+2\nA7=3";
    std::stringstream in_stream(str_in);
    std::map<int, GraphCalc::Node> nodes = std::map<int, GraphCalc::Node>();
    SetGraph graph = GraphCalc::parse_graph(in_stream, nodes);
    GraphCalc::calculate(graph, nodes);
    EXPECT_EQ(nodes[0].defined, true);
    EXPECT_EQ(nodes[0].color, 2);
    EXPECT_EQ(nodes[0].val, 2);
    EXPECT_EQ(nodes[1].defined, true);
    EXPECT_EQ(nodes[1].color, 2);
    EXPECT_EQ(nodes[1].val, 9);
    EXPECT_EQ(nodes[2].color, 2);
    EXPECT_EQ(nodes[2].defined, false);
    EXPECT_EQ(nodes[3].color, 2);
    EXPECT_EQ(nodes[3].defined, false);
    EXPECT_EQ(nodes[4].color, 2);
    EXPECT_EQ(nodes[4].defined, false);
    EXPECT_EQ(nodes[5].defined, true);
    EXPECT_EQ(nodes[5].color, 2);
    EXPECT_EQ(nodes[5].val, 14);
    EXPECT_EQ(nodes[6].defined, true);
    EXPECT_EQ(nodes[6].color, 2);
    EXPECT_EQ(nodes[6].val, 5);
    EXPECT_EQ(nodes[7].defined, true);
    EXPECT_EQ(nodes[7].color, 2);
    EXPECT_EQ(nodes[7].val, 3);
}

TEST(GraphCalc, allInTest)
{
    std::string str_in = "A0=0+B2+A1\nB2=A1+2000\nA1=A3+1000\nA3=10000+A4\nA4=A1+A5+1+A6\nA6=100\nA7=200+A8\nA5=10\nA8=2\nG9=G10+1";
    std::stringstream in_stream(str_in);
    std::map<int, GraphCalc::Node> nodes = std::map<int, GraphCalc::Node>();
    SetGraph graph = GraphCalc::parse_graph(in_stream, nodes);
    GraphCalc::calculate(graph, nodes);
    EXPECT_EQ(nodes[0].color, 3);
    EXPECT_EQ(nodes[1].color, 3);
    EXPECT_EQ(nodes[2].color, 3);
    EXPECT_EQ(nodes[3].color, 3);
    EXPECT_EQ(nodes[4].color, 3);

    EXPECT_EQ(nodes[5].defined, true);
    EXPECT_EQ(nodes[5].color, 2);
    EXPECT_EQ(nodes[5].val, 10);

    EXPECT_EQ(nodes[6].defined, true);
    EXPECT_EQ(nodes[6].color, 2);
    EXPECT_EQ(nodes[6].val, 100);

    EXPECT_EQ(nodes[7].defined, true);
    EXPECT_EQ(nodes[7].color, 2);
    EXPECT_EQ(nodes[7].val, 202);

    EXPECT_EQ(nodes[8].defined, true);
    EXPECT_EQ(nodes[8].color, 2);
    EXPECT_EQ(nodes[8].val, 2);

    EXPECT_EQ(nodes[9].defined, false);
    EXPECT_EQ(nodes[9].color, 2);

    EXPECT_EQ(nodes[10].defined, false);
    EXPECT_EQ(nodes[10].color, 2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
