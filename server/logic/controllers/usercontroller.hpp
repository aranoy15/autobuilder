#pragma once

#include <library/controllers/basecontroller.hpp>


namespace controllers
{
class UserController : public BaseController
{
    void get_handle(web::http::http_request request);

public:
    UserController();
    virtual ~UserController();
};
}