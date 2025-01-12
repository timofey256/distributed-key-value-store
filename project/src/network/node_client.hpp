// node_client.hpp
#ifndef NODE_CLIENT_HPP
#define NODE_CLIENT_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class NodeClient {
public:
    NodeClient(const std::string& host, unsigned short port);
    
    // Send GET request to another node
    std::string get(const std::string& key);
    
    // Send PUT request to another node
    void put(const std::string& key, const std::string& value);

private:
    std::string host_;
    unsigned short port_;
    net::io_context ioc_;
    tcp::resolver resolver_;
};

#endif