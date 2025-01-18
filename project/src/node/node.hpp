#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include "network/http_server.hpp" 
#include "network/node_client.hpp" 

class Node {
private:
    std::shared_ptr<HttpServer> server_;
    std::unique_ptr<NodeClient> client_;
    std::unordered_map<std::string, std::string> data_;
    std::string ip_;
    uint port_;

public:
    Node(std::string ip, uint port) : ip_(ip), port_(port) {
        server_ = std::make_shared<HttpServer>(ip, port);
        client_ = std::make_unique<NodeClient>(ip, port);
    }

    void start() {
        server_->start();
    }

    std::string get_from_node(unsigned short target_port, const std::string& key) {
        NodeClient client(ip_, target_port);
        return client.get(key);
    }
};

#endif