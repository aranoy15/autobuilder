#pragma once

#include <stdafx.h>
#include <tuple>

namespace utils
{
    bool is_authorized(web::http::http_request& request);
}