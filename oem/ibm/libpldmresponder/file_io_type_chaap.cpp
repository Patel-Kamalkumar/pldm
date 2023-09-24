#include "file_io_type_chaap.hpp"

#include <iostream>

namespace pldm
{
using namespace utils;

namespace responder
{

static constexpr auto chapDataFilePath = "/var/lib/pldm/ChapData/";
static constexpr auto chapDataFilename = "chapsecret";

int ChapHandler::readIntoMemory(uint32_t offset, uint32_t& length,
                                uint64_t address,
                                oem_platform::Handler* /*oemPlatformHandler*/)
{
    namespace fs = std::filesystem;
    if (!fs::exists(chapDataFilePath))
    {
        error("chap file directory not present.");
        return PLDM_ERROR;
    }
    std::string filePath = std::string(chapDataFilePath) +
                           std::string(chapDataFilename);
    auto rc = transferFileData(filePath.c_str(), true, offset, length, address);
    fs::remove(filePath);
    if (rc)
    {
        return PLDM_ERROR;
    }
    return PLDM_SUCCESS;
}
} // namespace responder
} // namespace pldm
