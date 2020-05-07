#include <logic/controllers/postscontrolller.hpp>
#include <thread>
#include <chrono>
#include <jwt/jwt.hpp>
//#include <sqlite_modern_cpp.h>
#include <logic/utils/isauthorized.hpp>

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

namespace controllers
{
PostsController::PostsController() : BaseController() 
{
    using namespace std;
    using namespace std::placeholders;

    _callbacks.insert(BaseController::pair_type(methods::GET, bind(&PostsController::get_handle, this, _1)));
}

PostsController::~PostsController() {}

void PostsController::get_handle(http_request request) 
{
    using namespace jwt::params;

    utils::is_authorized(request);

    static string_t secret_key = "secret_key";

    jwt::jwt_object obj{algorithm("HS256"), payload({{"some", "payload"}}), secret(secret_key.c_str())};

    auto enc_str = obj.signature();

    auto uri_query = request.relative_uri().query();

    auto paths = http::uri::split_query(http::uri::decode(uri_query));

    http_response response(status_codes::OK);

    response.headers().add("set-cookie", "token=" + obj.signature());

	//pplx::task<void> db_task([this]() { this->test_database(); });

	request.reply(response);
}

/*
void PostsController::test_database()
{
    using namespace sqlite;

    try {
        database db("dbfile.db");

        db <<
        "create table if not exists user ("
        "   _id char(36) primary key not null,"
        "   age int,"
        "   name text"
        ");";

        string_t table_name;

        db << "SELECT name FROM sqlite_master WHERE type='table' AND name='user';" >> table_name;

        ucout << "table_name: " << table_name << endl;

        db << "insert into user (_id,age,name) values (?,?,?);"
        << "test"
        << 20
        << u"bob";

    } catch (const std::exception& err) {
        ucout << "Database error: " << err.what() << endl;
    }
}
*/
}