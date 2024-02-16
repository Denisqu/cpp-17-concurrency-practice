#ifndef INC_8_SHARED_MUTEX_DNS_CACHE_H
#define INC_8_SHARED_MUTEX_DNS_CACHE_H

#include <map>
#include <string>
#include <shared_mutex>

namespace chapter_3
{

class dns_entry;

/*!
 * @brief Читаем сразу несколькими потоками,
 * но писать можем только одним (если сейчас его никто
 * не читает)
 */
class dns_cache
{
	std::map<std::string, dns_entry> entries;
	mutable std::shared_mutex entry_mutex;

public:
	dns_entry find_entry(const std::string &domain) const
	{
		std::shared_lock<std::shared_mutex> lock(entry_mutex);
		const auto it = entries.find(domain);
		return (it == entries.end()) ? dns_entry() : it->second;
	}

	void update_or_add_entry(const std::string &domain, const dns_entry &dns_details)
	{
		std::lock_guard<std::shared_mutex> lock(entry_mutex);
		entries[domain] = dns_details;
	}
};

}
#endif //INC_8_SHARED_MUTEX_DNS_CACHE_H
