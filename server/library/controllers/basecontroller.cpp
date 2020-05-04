#include <library/controllers/basecontroller.hpp>

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

namespace controllers
{

BaseController::BaseController() : _callbacks()
{
}

BaseController::~BaseController() {}

BaseController::map_type::iterator BaseController::find(method method)
{
    return _callbacks.find(method);
}

bool BaseController::exists(method method)
{
    return find(method) != _callbacks.end();
}

void BaseController::request_handle(http_request request)
{
    auto item = find(request.method());

    if (item != _callbacks.end())
        item->second(request);
    else
        request.reply(status_codes::NotImplemented);
}

}