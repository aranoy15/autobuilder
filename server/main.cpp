#include <iostream>
#include <stdafx.h>
#include <memory>
#include <logic/controllers/usercontroller.hpp>
#include <logic/controllers/postscontrolller.hpp>
#include <library/controllers/controllermanager.hpp>
#include <kaguya/kaguya.hpp>

#include <boost/process.hpp>

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace controllers;

struct ServerSettings
{
    std::string address;
    std::string port;
    std::string version;

	ServerSettings() : address("http://localhost"), port("8000"), version("1.0")
	{
	}

	ServerSettings(const std::string& address, const std::string& port,
	               const std::string version)
	    : address(address), port(port), version(version)
	{
	}
};

ServerSettings get_settings()
{
    kaguya::State state;

    if (state.dofile("config/serversetting.lua")) {
        auto settings = state["settings"];

        std::string address = settings["address"].get<std::string>();
        std::string port = settings["port"].get<std::string>();
        std::string version = settings["version"].get<std::string>();

        return ServerSettings(address, port, version);
    }

    return ServerSettings();
}

void test_func()
{
    using namespace boost::process;

    ipstream pipe_stream;
    child c("gcc --version", std_out > pipe_stream);

    std::string line;

    while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
        std::cerr << line << std::endl;

    c.wait();
}

int main()
{
	ServerSettings settings = get_settings();

    utility::string_t port = settings.port;
    utility::string_t address = settings.address;
    utility::string_t version = settings.version;

    uri_builder uri(address + ":" + port);

    ucout << "Complete address: " << uri.to_string() << std::endl;

    ControllerManager manager(std::make_shared<http_listener>(uri.to_string()));

    manager.reg<UserController>("/user");
    manager.reg<PostsController>("/posts");

    manager.start();

    ucout << "Press enter to exit ..." << endl;

    std::string line;
    std::getline(std::cin, line);

    manager.stop();

    return 0;
}