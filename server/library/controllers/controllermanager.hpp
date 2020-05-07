#pragma once

#include <library/controllers/basecontroller.hpp>
#include <stdafx.h>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace controllers
{

class ControllerManager
{
public:
	using item_type = BaseController;
	using item_ptr = std::unique_ptr<item_type>;
	using pair_type = std::pair<string_t, item_ptr>;
	using map_type = std::map<string_t, item_ptr>;
	using listener_type = web::http::experimental::listener::http_listener;
	using listener_ptr = std::shared_ptr<listener_type>;

	using request_type = web::http::http_request;

private:
	map_type _data;
	listener_ptr _listener;

private:
	map_type::iterator find(const string_t& absolute_uri);
	void request_handle(request_type request);

public:
	ControllerManager(const listener_ptr& listener);
	virtual ~ControllerManager();

	bool exists(const string_t& absolute_uri);
	void start();
	void stop();

	template <class T>
	void reg(const std::string& absolute_uri);
};

template <class T>
inline void ControllerManager::reg(const std::string& absolute_uri)
{
	string_t result_uri = "";

	if (not absolute_uri.empty()) {
		if (absolute_uri[0] != '/')
			result_uri = "/";
	}

	result_uri.append(absolute_uri);

	if (not exists(result_uri)) {
		_data.insert(pair_type(result_uri, std::make_unique<T>()));

		ucout << "Add controller for " << result_uri << endl;
	}
}
}  // namespace controllers

inline std::ostream& operator<<(std::ostream& stream, const controllers::ControllerManager::request_type& request)
{
	auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

	stream << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << " " << request.method() << " "
	       << request.http_version().to_utf8string() << " "
	       << request.absolute_uri().to_string();

	return stream;
}