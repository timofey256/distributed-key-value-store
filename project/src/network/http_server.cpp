#include "http_server.hpp"
#include <iostream>
#include <boost/asio/strand.hpp>
#include <boost/beast/core/tcp_stream.hpp>

// ----- HttpServer implementation -----

HttpServer::HttpServer(const std::string& address, unsigned short port)
    : ioc_(1)
    , acceptor_(ioc_)
    , socket_(ioc_) {
    
    tcp::endpoint endpoint{net::ip::make_address(address), port};
    
    beast::error_code ec;
    acceptor_.open(endpoint.protocol(), ec);
    if(ec) {
        throw std::runtime_error("Failed to open acceptor: " + ec.message());
    }

    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if(ec) {
        throw std::runtime_error("Failed to set reuse address: " + ec.message());
    }

    acceptor_.bind(endpoint, ec);
    if(ec) {
        throw std::runtime_error("Failed to bind acceptor: " + ec.message());
    }

    acceptor_.listen(net::socket_base::max_listen_connections, ec);
    if(ec) {
        throw std::runtime_error("Failed to start listening: " + ec.message());
    }
}

void HttpServer::start() {
    accept();
    ioc_.run();
}

void HttpServer::accept() {
    acceptor_.async_accept(
        socket_,
        beast::bind_front_handler(&HttpServer::on_accept, shared_from_this()));
}

void HttpServer::on_accept(beast::error_code ec) {
    if (ec) {
        std::cerr << "Accept error: " << ec.message() << std::endl;
    } else {
        std::make_shared<HttpSession>(std::move(socket_))->run();
    }
    accept();
}

// ----- HttpSession implementation -----

HttpSession::HttpSession(tcp::socket&& socket)
    : tcp_stream_(std::move(socket))
    , buffer_(8192) {
}

void HttpSession::run() {
    do_read();
}

void HttpSession::do_read() {
    tcp_stream_.expires_after(std::chrono::seconds(30));

    http::async_read(
        tcp_stream_,
        buffer_,
        request_,
        beast::bind_front_handler(&HttpSession::on_read, shared_from_this()));
}

void HttpSession::on_read(beast::error_code ec, std::size_t bytes_transferred) {
    if (ec) {
        std::cerr << "Read error: " << ec.message() << std::endl;
        return;
    }

    handle_request();
}

void HttpSession::handle_request() {
    response_.version(request_.version());
    response_.keep_alive(false);

    switch (request_.method()) {
        case http::verb::get:
            handle_get();
            break;
        case http::verb::put:
            handle_put();
            break;
        default:
            response_.result(http::status::bad_request);
            response_.set(http::field::content_type, "text/plain");
            response_.body() = "Unknown HTTP method";
            break;
    }

    do_write();
}

void HttpSession::handle_get() {
    std::string key = std::string(request_.target()).substr(1);
    response_.result(http::status::ok);
    response_.set(http::field::content_type, "application/json");
    response_.body() = "{\"key\":\"" + key + "\",\"value\":\"dummy\"}";
}

void HttpSession::handle_put() {
    std::string key = std::string(request_.target()).substr(1);
    std::string value = request_.body();

    response_.result(http::status::ok);
    response_.set(http::field::content_type, "application/json");
    response_.body() = "{\"status\":\"ok\"}";
}

void HttpSession::do_write() {
    response_.set(http::field::content_length, std::to_string(response_.body().size()));

    http::async_write(
        tcp_stream_,
        response_,
        beast::bind_front_handler(&HttpSession::on_write, shared_from_this()));
}

void HttpSession::on_write(beast::error_code ec, std::size_t bytes_transferred) {
    if (ec) {
        std::cerr << "Write error: " << ec.message() << std::endl;
        return;
    }

    
    if (response_.keep_alive()) { // persistent connection
        do_read();
    } else { // one connection = one request-response cycle
        beast::error_code ec_shutdown;
        tcp_stream_.socket().shutdown(tcp::socket::shutdown_send, ec_shutdown);
    }
}