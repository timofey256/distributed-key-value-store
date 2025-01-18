#include "network/http_server.hpp"
#include "network/node_client.hpp"
#include <iostream>

int run_a_basic_http_server(int& argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <address> <port>\n";
        std::cerr << "Example: " << argv[0] << " 0.0.0.0 8080\n";
        return 1;
    }

    auto const address = argv[1];
    auto const port = static_cast<unsigned short>(std::atoi(argv[2]));

    try {
        std::cout << "Starting server at " << address << ":" << port << std::endl;
        auto server = std::make_shared<HttpServer>(address, port);
        server->start();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    int exit_code = run_a_basic_http_server(argc, argv);
    return exit_code;
}