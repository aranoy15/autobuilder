#include <library/controllers/controllermanager.hpp>
#include <logic/controllers/usercontroller.hpp>

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;



namespace controllers
{
ControllerManager::ControllerManager(const ControllerManager::listener_ptr& listener) : _listener(listener)
{
    assert(_listener != nullptr);

    auto bind = std::bind(&ControllerManager::request_handle, this, std::placeholders::_1);

    _listener->support(methods::GET, bind);
    _listener->support(methods::GET, bind);
    _listener->support(methods::PUT, bind);
    _listener->support(methods::POST, bind);
    _listener->support(methods::DEL, bind);
    _listener->support(methods::CONNECT, bind);
    _listener->support(methods::HEAD, bind);
    _listener->support(methods::MERGE, bind);
    _listener->support(methods::OPTIONS, bind);
    _listener->support(methods::PATCH, bind);
    _listener->support(methods::TRCE, bind);
}

ControllerManager::~ControllerManager() {}

void ControllerManager::request_handle(request_type request)
{
    ucout << request << std::endl;

	auto iterator = find(request.absolute_uri().to_string());

    if (iterator == _data.end()) {
        request.reply(status_codes::BadGateway);
        return;
    }

    iterator->second->request_handle(request);
}

ControllerManager::map_type::iterator ControllerManager::find(const string_t& absolute_uri)
{
    return _data.find(absolute_uri);
}

bool ControllerManager::exists(const string_t& absolute_uri)
{
    return find(absolute_uri) != _data.end();
}

void ControllerManager::start()
{
    try {
        _listener->open().wait();
    } catch (const std::exception& err) {
		ucout << "Exception while start listener: " << err.what() << std::endl;
	}
}

void ControllerManager::stop()
{
    try {
        _listener->close().wait();
    } catch (const std::exception& err) {
        ucout << "Exception while stop listener: " << err.what() << std::endl;
    }
}

}