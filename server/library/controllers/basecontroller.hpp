#pragma once

#include <stdafx.h>

namespace controllers
{
using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

enum class AuthorizedType
{
    NoAuthorized,
    Authorized
};

struct CallbackType
{
    AuthorizedType type;
    
};

class BaseController
{
public:
    using callback_type = std::function<void(http_request)>;
    using map_type = std::map<method, callback_type>;
    using pair_type = std::pair<method, callback_type>;

protected:
    map_type _callbacks;

public:
	BaseController();
	virtual ~BaseController();

private:
    map_type::iterator find(method method);

public:
    bool exists(method method);
    void request_handle(http_request request);
};
}//controllers