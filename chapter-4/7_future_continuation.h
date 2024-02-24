#ifndef INC_7_FUTURE_CONTINUATION_H
#define INC_7_FUTURE_CONTINUATION_H

#include <utility>
/*
 * Увы, но нет в msvc
 */
#include <experimental/future>

namespace chapter_4
{

template<typename Func>
std::experimental::future<decltype(std::declval<Func>()())>
spawn_async(Func &&func)
{
	std::experimental::promise<
		decltype(std::declval<Func>()())> p;
	auto res = p.get_future();
	std::thread t(
		[p = std::move(p), f = std::decay_t<Func>(func)]()
			mutable
		{
			try {
				p.set_value_at_thread_exit(f());
			}
			catch (...) {
				p.set_exception_at_thread_exit(std::current_exception());
			}
		});
	t.detach();
	return res;
}

std::experimental::future<void> process_login(
	std::string const &username, std::string const &password)
{
	return backend.async_authenticate_user(username, password).then(
		[](std::experimental::future<user_id> id)
		{
			return backend.async_request_current_info(id.get());
		}).then([](std::experimental::future<user_data> info_to_display)
				{
					try {
						update_display(info_to_display.get());
					}
					catch (std::exception &e) {
						display_error(e);
					}
				});
}

}

#endif //INC_7_FUTURE_CONTINUATION_H
