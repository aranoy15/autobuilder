#include <logic/controllers/usercontroller.hpp>

#include <rttr/registration>

using namespace web::http::details;

namespace controllers
{
UserController::UserController() : BaseController() 
{
    using namespace std;
    using namespace std::placeholders;

    _callbacks.insert(BaseController::pair_type(methods::GET, bind(&UserController::get_handle, this, _1)));
}

UserController::~UserController() {}

void UserController::get_handle(http_request request) 
{
    request.headers().add(header_names::content_type, mime_types::text_plain_utf8);
    request.reply(status_codes::OK, "Hello from cpprestsdk");
}
}