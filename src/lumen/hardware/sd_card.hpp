#pragma once

#include "nlohmann/json.hpp"

#include <string>

namespace lumen::hardware {

/// Initialize the SD card.
void init_sd_card();

/** Read a file stream into a JSON object.
 *
 * \param filepath The path to the file to read from.
 *
 * \returns The file as a JSON object.
 *
 * \note `filepath` must be prepended by '/'
 */
nlohmann::json read_json(std::string const& filepath);

/** Write a JSON object to a file.
 *
 * \param filepath The path to the file to write to.
 *
 * \param data The JSON object to write.
 *
 * \note `filepath` must be prepended by '/'
 */
void write_json(std::string const& filepath, nlohmann::json data);

/** Delete a file.
 *
 * \param filepath The path to the file to write to.
 *
 * \note `filepath` must be prepended by '/'
 */
void delete_file(std::string const& filepath);

} // namespace lumen::hardware
