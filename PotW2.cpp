#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>

struct node {
    std::string name;
    std::vector<node*> friends;
    bool visited;
    int qdist;

    node(std::string n) : name(n), friends(), visited(false), qdist(-1) { }

    void add_friend(node* f) { friends.push_back(f); }
};

struct graph {
    node* root;
    std::unordered_map<std::string, node*> nodes;

    graph(std::string n) : nodes() {
        root = new node(n);
        nodes.insert({n, root});
    }

    ~graph() {
        for (auto p : nodes)
            delete p.second;
    }

    node* create_node(std::string name) {
        node* new_node = new node(name);
        nodes.insert({name, new_node});
        return new_node;
    }

    bool in_graph(std::string name) {
        return nodes.find(name) != nodes.end();
    }

    void make_friends(std::string name1, std::string name2) {
        node* node1;
        node* node2;

        if (in_graph(name1)) {
            node1 = nodes[name1];
        } else {
            node1 = create_node(name1);
            nodes.insert({name1, node1});
        }

        if (in_graph(name2)) {
            node2 = nodes[name2];
        } else {
            node2 = create_node(name1);
            nodes.insert({name2, node2});
        }

        node1->add_friend(node2);
        node2->add_friend(node1);
    }
};

int main() {
    graph friends("Quinn");

    unsigned n;
    std::cin >> n;

    std::string s1, s2;
    for (unsigned i = 0; i != n; ++i) {
        std::cin >> s1 >> s2;
        friends.make_friends(s1, s2);
    }

    std::queue<node*> q;
    int qdist = 0;
    int dist_size = 1;
    q.push(friends.root);
    friends.root->visited = true;

    while (!q.empty()) {
        node* cur = q.front();
        cur->qdist = qdist;
        q.pop();

        for (auto n : cur->friends) {
            if (!n->visited) {
                q.push(n);
                n->visited = true;
            }
        }

        --dist_size;
        if (dist_size == 0) {
            ++qdist;
            dist_size = q.size();
        }
    }

    std::vector< std::pair<std::string, node*> > people;

    for (auto p : friends.nodes)
        people.push_back(p);

    std::sort(
        people.begin(),
        people.end()
    );

    for (auto p : people) {
        std::cout << p.first << " ";
        if (p.second->qdist >= 0)
            std::cout << p.second->qdist << std::endl;
        else
            std::cout << "uncool" << std::endl;
    }

    return 0;
}

