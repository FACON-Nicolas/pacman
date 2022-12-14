#include "../includes/Grid.hpp"
using namespace std;

Grid::Grid() {
    initializeGrids();
    m_predecessorMap = vector<PVertexDescriptor>(num_vertices(m_graph));
    m_distanceMap = vector<int>(num_vertices(m_graph));
    initializeVertices();
}

Grid::~Grid() {

}

void Grid::initializeVertices() {
    for (auto n : getNodesValues())
        m_vertices.push_back(vertex(n, m_graph));
}

vector<boost::graph_traits<PGraph>::vertex_descriptor> Grid::dijkstraShortestPaths(int start, int end) {
    auto startNode = getVertex(start);
    auto endNode = getVertex(end);

    boost::dijkstra_shortest_paths(m_graph, startNode, boost::predecessor_map(&m_predecessorMap[0]).distance_map(&m_distanceMap[0]));

    std::vector<boost::graph_traits<PGraph>::vertex_descriptor> path;
    boost::graph_traits<PGraph>::vertex_descriptor current = endNode;

    while (current !=  start) {
        path.push_back(current);
        current = m_predecessorMap[current];
    } path.push_back(start);
    
    return path;
}

bool Grid::isNode(int node) {
    return find(m_nodes.begin(), m_nodes.end(), node) != m_nodes.end();
}

PVertexDescriptor Grid::getVertex(int node) {
    PVertexDescriptor v;
    for (vector<int>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
        if (*it == node)
            return m_vertices[it - m_nodes.begin()];
    throw invalid_argument("node not in graph.");
}

void Grid::initializeGrids() {
    initializeMainGrid();
    initializePacGumGrid();
    initializeGraph();
}

int Grid::get(PVector2Grid position) const {
    int row = position.first, col = position.second;
    if (row < 0 || row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH)
        throw invalid_argument("row or column out of range");
    return m_grid[row][col].get();
}

void Grid::set(PVector2Grid position, int value) {
    int row = position.first, col = position.second;
    if (row < 0 || row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH)
        throw invalid_argument("row or column out of range");
    m_grid[row][col].set(value);
}

PacGum Grid::getPacGum(PVector2Grid position) {
    int row = position.first, col = position.second;
    if (row < 0 || row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH)
        throw invalid_argument("row or column out of range");
    return m_pacGumGrid[row][col];
}

void Grid::setPacGum(PVector2Grid position, PacGum pacGumValue) {
    int row = position.first, col = position.second;
    if (row < 0 || row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH)
        throw invalid_argument("row or column out of range");
    m_pacGumGrid[row][col] = pacGumValue;
}

vector<int> Grid::wallToBin(PVector2Grid position) {
    int row = position.first, col = position.second;
    if (row < 0 || row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH)
        throw invalid_argument("row or column out of range");
    return m_grid[row][col].wallToBin();
}

bool Grid::isWallPresent(PVector2Grid position, Wall wall) {
    int row = position.first, col = position.second;
    if (row < 0 || row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH) {
        throw invalid_argument("row or column out of range");
    }
    return m_grid[row][col].isWallPresent(wall);
}

void Grid::initializeMainGrid() {

    // grid with tiles' wall values.
    int grid[GRID_HEIGHT][GRID_WIDTH] = {
        {9, 5, 5, 5, 1, 5, 5, 5, 5, 3, 10, 9, 5, 5, 5, 5, 1, 5, 5, 5, 3},
        {10, 9, 1, 3, 10, 9, 1, 1, 3, 10, 10, 10, 9, 1, 1, 3, 10, 9, 1, 3, 10},
        {10, 12, 4, 6, 10, 12, 4, 4, 6, 10, 14, 10, 12, 4, 4, 6, 10, 12, 4, 6, 10},
        {8, 5, 5, 5, 0, 5, 1, 5, 5, 4, 5, 4, 5, 5, 1, 5, 0, 5, 5, 5, 2},
        {10, 13, 5, 7, 10, 11, 10, 13, 5, 5, 1, 5, 5, 7, 10, 11, 10, 13, 5, 7, 10},
        {12, 5, 5, 5, 2, 10, 12, 5, 5, 3, 10, 9, 5, 5, 6, 10, 8, 5, 5, 5, 6},
        {1, 1, 1, 3, 10, 8, 5, 5, 7, 10, 14, 10, 13, 5, 5, 2, 10, 9, 1, 1, 1},
        {0, 0, 0, 2, 10, 10, 9, 5, 5, 4, 5, 4, 5, 5, 3, 10, 10, 8, 0, 0, 0},
        {4, 4, 4, 6, 10, 14, 10, 9, 1, 1, 0, 1, 1, 3, 10, 14, 10, 12, 4, 4, 4},
        {5, 5, 5, 5, 0, 5, 2, 8, 0, 0, 0, 0, 0, 2, 8, 5, 0, 5, 5, 5, 5},
        {1, 1, 1, 3, 10, 11, 10, 12, 4, 4, 4, 4, 4, 6, 10, 11, 10, 9, 1, 1, 1},
        {0, 0, 0, 2, 10, 10, 8, 5, 5, 5, 5, 5, 5, 5, 2, 10, 10, 8, 0, 0, 0},
        {4, 4, 4, 6, 10, 14, 10, 13, 5, 5, 1, 5, 5, 7, 10, 14, 10, 12, 4, 4, 4},
        {9, 5, 5, 5, 0, 5, 4, 5, 5, 3, 10, 9, 5, 5, 4, 5, 0, 5, 5, 5, 3},
        {10, 13, 5, 3, 10, 13, 5, 5, 7, 10, 14, 10, 13, 5, 5, 7, 10, 9, 5, 7, 10},
        {12, 5, 3, 10, 8, 5, 1, 5, 5, 4, 5, 4, 5, 5, 1, 5, 2, 10, 9, 5, 6},
        {5, 7, 10, 14, 10, 11, 10, 13, 5, 5, 1, 5, 5, 7, 10, 11, 10, 14, 10, 13, 5},
        {9, 5, 4, 5, 6, 10, 12, 5, 5, 3, 10, 9, 5, 5, 6, 10, 12, 5, 4, 5, 3},
        {10, 13, 5, 5, 5, 4, 5, 5, 7, 10, 14, 10, 13, 5, 5, 4, 5, 5, 5, 7, 10},
        {12, 5, 5, 5, 5, 5, 5, 5, 5, 4, 5, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6},
    };

    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            m_grid[i][j] = Tile(grid[i][j]);
}

void Grid::initializePacGumGrid() {
    int pacGumGrid[GRID_HEIGHT][GRID_WIDTH] = {
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                    {2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 2},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                    {0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0},
                    {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                    {0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0},
                    {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                    {2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2},
                    {0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
                    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    m_pacGumCount = 0;

    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (pacGumGrid[i][j] == 0) m_pacGumGrid[i][j] = PacGum::EMPTY;
            else{
                if (pacGumGrid[i][j] == 1) m_pacGumGrid[i][j] = PacGum::DOT;
                else m_pacGumGrid[i][j] = PacGum::ENERGIZER;
                m_pacGumCount++;
            }
        }
}

int Grid::getWeightBetweenNeighbors(PVector2Grid a, PVector2Grid b) {
    auto neighbors = nodesNeighbors(a);
    if (find(neighbors.begin(), neighbors.end(), b) == neighbors.end())
        throw invalid_argument("a and b are not neighbors.");
    return abs((a.first == b.first) ? a.second - b.second : a.first - b.first);
}

vector<PEdge> Grid::edgesValues() {
    vector<PEdge> edges;
    for (auto n : getNodesValues()) {
        for (auto neighbor : nodesNeighbors(convertNode(n))) {
            if (n < convertPV2(neighbor)) {
                PEdge e(n, convertPV2(neighbor));
                edges.push_back(e);
            }
        }
    }
    return edges;
}

void Grid::initializeGraph() {
    int numberOfNodes = getNumberOfNodesInGrid();
    m_nodes = getNodesValues();

    int nodeValues[numberOfNodes];

    for (int i  = 0; i < numberOfNodes; i++)
        nodeValues[i] = m_nodes[i];

    PEdge edgesValuesArray[edgesValues().size()];
    for (int i = 0; i < edgesValues().size(); i++)
        edgesValuesArray[i] = edgesValues()[i];

    int numArc = sizeof(edgesValuesArray) / sizeof(PEdge);
    int weight[numArc];

    for (int i = 0; i < sizeof(edgesValuesArray) / sizeof(PEdge); i++) {
        int a = edgesValuesArray[i].first, b = edgesValuesArray[i].second;
        weight[i] = getWeightBetweenNeighbors(convertNode(a), convertNode(b)); 
    }

    m_graph = PGraph(edgesValuesArray, edgesValuesArray + numArc, weight, numberOfNodes);

}

int Grid::convertPV2(PVector2Grid position) {
    if (position.first < 0 || position.first >= GRID_HEIGHT || position.second < 0 || position.second >= GRID_WIDTH)
        throw invalid_argument("index out of range");
    return position.first * ROW_VALUE + position.second * COLUMN_VALUE;
}

PVector2Grid Grid::convertNode(int value) {
    PVector2Grid position;
    position.first = value / 1000;
    position.second = value % 1000;
    return position;
}

bool Grid::isNode(PVector2Grid position) {
    int row = position.first, col = position.second;
    if (row < 0 || row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH) {
        throw invalid_argument("row or column out of range");
    } int tileValue = get(position);
    return ((tileValue % 5 != 0 || tileValue == 0) && getPacGum(position) != PacGum::EMPTY);
}

int Grid::getNumberOfNodesInGrid() {
    int nodes = 0;
    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            if (isNode(convertPV2(PVector2Grid(i, j))))
                nodes++;
    return nodes;
}

int Grid::getRandomNode() {
    int index = rand() % m_nodes.size();
    return m_nodes[index];
}

vector<int> Grid::getNodesValues() {
    vector<int> nodes;
    for (int i=0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            if (isNode(PVector2Grid(i, j)))
                nodes.push_back(convertPV2(PVector2Grid(i, j)));
    return nodes;
}

vector<PVector2Grid> Grid::horizontalNodesNeighbors(PVector2Grid position) {
    int row(position.first), column(position.second);
    vector<PVector2Grid> nodesPosition;
    if (!isWallPresent(position, Wall::LEFT)) {
        do {
            column--;
            if (column < 0) column = GRID_WIDTH-1;
        } while(!isNode(PVector2Grid(row%=GRID_HEIGHT, column%=GRID_WIDTH)));
        nodesPosition.push_back(PVector2Grid(row, column));
    }

    column = position.second;

    if (!isWallPresent(position, Wall::RIGHT)) {
        do {
            column++;
            if (column >= GRID_WIDTH) column = 0;
        } while(!isNode(PVector2Grid(row, column)));
        nodesPosition.push_back(PVector2Grid(row, column));
    } return nodesPosition;
}

vector<PVector2Grid> Grid::verticalNodesNeighbors(PVector2Grid position) {
    int row(position.first), column(position.second);
    vector<PVector2Grid> nodesPosition;
    if (!isWallPresent(position, Wall::TOP)) {
        do {
            row--;
            if (row < 0) row = GRID_HEIGHT;
        } while(!isNode(PVector2Grid(row, column)));
        nodesPosition.push_back(PVector2Grid(row, column));
    }

    row = position.first;

    if (!isWallPresent(position, Wall::BOTTOM)) {
        do {
            row++;
            if (row < 0) row = GRID_HEIGHT;
        } while(!isNode(PVector2Grid(row, column)));
        nodesPosition.push_back(PVector2Grid(row, column));
    } return nodesPosition;
}

vector<PVector2Grid> Grid::nodesNeighbors(PVector2Grid position) {
    vector<PVector2Grid> neighbors = horizontalNodesNeighbors(position);
    vector<PVector2Grid> v = verticalNodesNeighbors(position);
    for (vector<PVector2Grid>::iterator it = v.begin(); it != v.end(); it++)
        neighbors.push_back(*it);
    return neighbors;
}