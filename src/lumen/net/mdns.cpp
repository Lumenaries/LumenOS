#include "lumen/net/mdns.hpp"

#include "mdns.h"

namespace lumen::net {
namespace {

constexpr auto tag = "net/mdns";

} // namespace

void init_mdns()
{
    mdns_init();
    mdns_hostname_set(CONFIG_NET_MDNS_HOSTNAME);

    mdns_txt_item_t serviceTxtData[] = {{"board", "esp32"}, {"path", "/"}};

    ESP_ERROR_CHECK(mdns_service_add(
        "ESP32-WebServer",
        "_http",
        "_tcp",
        80,
        serviceTxtData,
        sizeof(serviceTxtData) / sizeof(serviceTxtData[0])
    ));
}

} // namespace lumen::net
