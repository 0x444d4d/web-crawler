#include "curlfetcher.h"
#include "curl/curl.h"
#include <string>
#include <optional>

std::atomic_int CurlFetcher::curl_instance_counter_ = 0;

CurlFetcher::CurlFetcher()
{
    if (curl_instance_counter_.fetch_add(1, std::memory_order_acquire) == 0)
        curl_global_init(CURL_GLOBAL_ALL);

    ++curl_instance_counter_;

}

CurlFetcher::~CurlFetcher()
{
    if (curl_instance_counter_.fetch_sub(1, std::memory_order_acquire) == 1)
        curl_global_cleanup();

}

std::optional<CurlFetcher::FetchInfo> CurlFetcher::fetchUrl(const std::string &url)
{

    FetchInfo info;

    CURL* curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, curlWrite);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &info);

    auto result = curl_easy_perform(curl_handle);
    if (result != CURLE_OK && result != CURLE_WRITE_ERROR)
        return {};

    char* contentType = nullptr;
    curl_easy_getinfo(curl_handle, CURLINFO_CONTENT_TYPE, &contentType);
    info.ContentType = contentType;

    curl_easy_cleanup(curl_handle);

    return info;
}

size_t CurlFetcher::curlWrite(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    auto info = static_cast<FetchInfo*>(userdata);
    if (nmemb != 0)
        info->content.insert(info->content.end(), ptr, ptr + nmemb);

    return nmemb; //TODO: Return a value smaller than nmemb to limit
    //download size. 12-05-20 2:0:0
}
