#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class HttpSession;

class HttpServer : public std::enable_shared_from_this<HttpServer> {
public:
    explicit HttpServer(const std::string& address, unsigned short port);
    void start();

private:
    void accept();
    void on_accept(beast::error_code ec);

    net::io_context ioc_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

class HttpSession : public std::enable_shared_from_this<HttpSession> {
public:
    explicit HttpSession(tcp::socket&& socket);
    void run();

private:
    void do_read();
    void on_read(beast::error_code ec, std::size_t bytes_transferred);
    void handle_request();
    void handle_get();
    void handle_put();
    void do_write();
    void on_write(beast::error_code ec, std::size_t bytes_transferred);

    beast::tcp_stream tcp_stream_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> request_;
    http::response<http::string_body> response_;
};

#endif