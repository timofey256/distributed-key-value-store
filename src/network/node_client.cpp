#include "node_client.hpp"
#include <boost/beast/version.hpp>
#include <stdexcept>

NodeClient::NodeClient(const std::string& host, unsigned short port)
    : host_(host)
    , port_(port)
    , ioc_(1)
    , resolver_(ioc_) {
}

std::string NodeClient::get(const std::string& key) {
    try {
        auto const results = resolver_.resolve(host_, std::to_string(port_));
        
        beast::tcp_stream stream(ioc_);
        stream.connect(results);

        http::request<http::string_body> req{http::verb::get, "/" + key, 11};
        req.set(http::field::host, host_);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(stream, req);

        beast::flat_buffer buffer;
        http::response<http::string_body> res;
        http::read(stream, buffer, res);

        return res.body();
    }
    catch(std::exception const& e) {
        throw std::runtime_error("Failed to send GET request: " + std::string(e.what()));
    }
}

void NodeClient::put(const std::string& key, const std::string& value) {
    try {
        auto const results = resolver_.resolve(host_, std::to_string(port_));
        
        beast::tcp_stream stream(ioc_);
        stream.connect(results);

        http::request<http::string_body> req{http::verb::put, "/" + key, 11};
        req.set(http::field::host, host_);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.body() = value;
        req.prepare_payload();

        http::write(stream, req);

        beast::flat_buffer buffer;
        http::response<http::string_body> res;
        http::read(stream, buffer, res);
    }
    catch(std::exception const& e) {
        throw std::runtime_error("Failed to send PUT request: " + std::string(e.what()));
    }
}