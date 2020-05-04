#include <logic/utils/isauthorized.hpp>

bool utils::is_authorized(web::http::http_request& request)
{
    auto& headers = request.headers();

    if (headers.has("Cookie")) {
        auto& cookie = headers["Cookie"];
        ucout << "Cookie result: " << cookie << std::endl;
    }

    return false;
}