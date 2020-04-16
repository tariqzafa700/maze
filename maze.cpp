#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <memory>

using namespace std;

template<typename T,
         typename Container = vector<T>,
         typename Comp = less<typename Container::value_type>> : public priority_queue<T, container, Comp>
class SearchablePriorityQueue {
    auto find(const T& element) {
        auto start = this->c.begin();
        auto end = this->c.end();
        for (auto it = start; it != end; ++it) {
            if (*it == element) {
                return it;
            }
        }
        return end;
    }
};

class Node {
    public:
        Node(int _x, int _y, bool _e) : x(_x), y(_y), f(0), g(0), h(0), enabled(_e) { }
        int x, y, f, g, h;
        bool enabled;
        bool operator()() {
            return enabled;
        }
        friend bool operator==(const Node& left, const Node& right) {
            return left.x == right.x && left.y == right.y;
        }
};

auto nodeCompare = [](const Node& a, const Node& b) {
    return a.f > b.f;
};

int findHeuristicDistance(int currX, int currY, int endX, int endY) {
    return abs(currX - endX) + abs(currY - endY);
}

shared_ptr<Node> getEnabledNeighbours(const vector<vector<int>>& matrix, int currX, int currY, const int xSize, const int ySize, 
                                      const Node& curr, const Node& end, vector<Node>& closedList, 
                                      SearchablePriorityQueue<Node, std::vector<Node>, decltype(nodeCompare)>& openList) {
    if(currX >= 0 && currY < xSize && currY >= 0 && currY < ySize && matrix[currX][currY] != 0) {
        auto node = new Node(currX, currY, true);
        node->g = curr.g + 1;
        node->h = findHeuristicDistance(currX, currY, end.x, end.y);
        node->f = node->g + node->h;
        return shared_ptr<Node>(node);
    } else {
        return nullptr;
    }
}

bool isEnabled(const vector<vector<int>>& matrix, int currX, int currY, const int xSize, const int ySize) {
    return currX >= 0 && currY < xSize && currY >= 0 && currY < ySize && matrix[currX][currY] != 0 && ;
}

int leastDistance(const vector<vector<int>>& matrix, const int xSize, const int ySize, const pair<int,int>& start, const pair<int,int>& end) {
    SearchablePriorityQueue<Node, std::vector<Node>, decltype(nodeCompare)> pq(nodeCompare);
    vector<Node> closedList;
    Node currNode(start.first, start.second, true);
    Node endNode(end.first, end.second, true);
    pq.push(currNode);
    closedList.push_back(currNode);

    while(1) {
        Node top = pq.top();
        pq.pop();
        if (isEnabled(matrix, currNode.x + 1, currNode.y)) {
            auto node = Node(currNode.x + 1, currNode.y, true);
            auto cit = find(closedList.begin(), closedList.end(), node);
            auto oit = pq.find(node);
            if (cit != closedList.end() && oit != ) {
                
            }
        }
        
        auto&& p = getEnabledNeighbours(matrix, currNode.x + 1, currNode.y, xSize, ySize, currNode, endNode);
        if (p) {
            pq.push(*p);
        }
        if (*p == endNode) 
            break;
        p = getEnabledNeighbours(matrix, currNode.x, currNode.y + 1, xSize, ySize, currNode, endNode);
        if (p) {
            pq.push(*p);
        }
        if (*p == endNode) 
            break;
        p = getEnabledNeighbours(matrix, currNode.x, currNode.y - 1, xSize, ySize, currNode, endNode);
        if (p) {
            pq.push(*p);
        }
        if (*p == endNode) 
            break;
        p = getEnabledNeighbours(matrix, currNode.x - 1, currNode.y, xSize, ySize, currNode, endNode);
        if (p) {
            pq.push(*p);
        }
        if (pq.empty() || *p == endNode) 
            break;
    }
}

int main() {

}
