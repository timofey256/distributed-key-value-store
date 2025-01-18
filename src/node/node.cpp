#include "node.hpp"

Node::Node(std::string ip, uint port) : ip_(ip), port_(port) {
    server_ = std::make_shared<HttpServer>(ip, port);
    client_ = std::make_unique<NodeClient>(ip, port);
}

void Node::start() {
    server_->start();
}

std::string Node::get_from_node(unsigned short target_port, const std::string& key) {
    NodeClient client(ip_, target_port);
    return client.get(key);
}