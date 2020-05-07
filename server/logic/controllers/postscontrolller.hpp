#pragma once

#include <library/controllers/basecontroller.hpp>

namespace controllers
{
class PostsController : public BaseController
{
public:
    PostsController();
    virtual ~PostsController();

protected:
    void get_handle(web::http::http_request request);

private:
    //void test_database();
};
}