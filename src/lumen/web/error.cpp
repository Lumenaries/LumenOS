#include "lumen/web/error.hpp"

#include "esp_log.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace lumen::web {
namespace {

constexpr auto tag = "web/error";

/** Convert a status code integer into a string.
 *
 * \param status_code The HTTP status code to respond with.
 */
std::string status_to_string(uint status_code);

} // namespace

esp_err_t
send_error(httpd_req_t* request, uint status_code, std::string const& message)
{
    auto status = status_to_string(status_code);

    httpd_resp_set_type(request, "application/json");
    httpd_resp_set_status(request, status.c_str());

    auto detail = json{{"detail", message}};

    ESP_LOGW(tag, "%s - %s", status.c_str(), detail.dump().c_str());

    return httpd_resp_send(
        request, detail.dump().c_str(), HTTPD_RESP_USE_STRLEN
    );
}

namespace {

std::string status_to_string(uint status_code)
{
    switch (status_code) {
    case 400:
        return {"400 Bad Request"};

    case 404:
        return {"400 Not Found"};

    case 500:
        return {"500 Internal Server Error"};

    case 503:
        return {"503 Service Unavailable"};

    default:
        return {"500 Internal Server Error"};
    }
}

} // namespace

} // namespace lumen::web
