#include "file_io_type_chap.hpp"

#include <iostream>

namespace pldm
{
using namespace utils;

namespace responder
{

static constexpr auto chapDataFilePath = "/var/lib/pldm/ChapData/";
static constexpr auto chapDataFilename = "chapsecret";

int ChapHandler::read(uint32_t offset, uint32_t& length, Response& response,
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

    auto rc = readFile(filePath.c_str(), offset, length, response);
    fs::remove(filePath);
    if (rc)
    {
        return PLDM_ERROR;
    }
    return PLDM_SUCCESS;
}

int ChapHandler::fileAckWithMetaData(uint8_t /*fileStatus*/,
                                     uint32_t /*metaDataValue1*/,
                                     uint32_t /*metaDataValue2*/,
                                     uint32_t /*metaDataValue3*/,
                                     uint32_t /*metaDataValue4*/)
{
    /// just returning success without any operation
    return PLDM_SUCCESS;
}
} // namespace responder
} // namespace pldm
