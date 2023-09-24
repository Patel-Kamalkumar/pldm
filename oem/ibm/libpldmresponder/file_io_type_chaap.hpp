#pragma once

#include "file_io_by_type.hpp"

#include <phosphor-logging/lg2.hpp>

#include <iostream>

PHOSPHOR_LOG2_USING;

namespace pldm
{
namespace responder
{

/** @class ChapHandler
 *
 *  @brief Inherits and implements FileHandler. This class is used
 *  to read/write chaap secret file
 */
class ChapHandler : public FileHandler
{
  public:
    /** @brief CertHandler constructor
     */
    ChapHandler(uint32_t fileHandle, uint16_t fileType) :
        FileHandler(fileHandle), chaapType(fileType)
    {}

    virtual int writeFromMemory(uint32_t /*offset*/, uint32_t /*length*/,
                                uint64_t /*address*/,
                                oem_platform::Handler* /*oemPlatformHandle*/)
    {
        return PLDM_ERROR_UNSUPPORTED_PLDM_CMD;
    }

    virtual int readIntoMemory(uint32_t offset, uint32_t& length,
                               uint64_t address,
                               oem_platform::Handler* /*oemPlatformHandler*/);

    virtual int read(uint32_t /*offset*/, uint32_t& /*length*/,
                     Response& /*response*/,
                     oem_platform::Handler* /*oemPlatformHandler*/)
    {
        return PLDM_ERROR_UNSUPPORTED_PLDM_CMD;
    }

    virtual int write(const char* /*buffer*/, uint32_t /*offset*/,
                      uint32_t& /*length*/,
                      oem_platform::Handler* /*oemPlatformHandler*/)
    {
        return PLDM_ERROR_UNSUPPORTED_PLDM_CMD;
    }

    virtual int fileAck(uint8_t /*fileStatus*/)
    {
        return PLDM_ERROR_UNSUPPORTED_PLDM_CMD;
    }

    virtual int newFileAvailable(uint64_t /*length*/)
    {
        return PLDM_ERROR_UNSUPPORTED_PLDM_CMD;
    }

    virtual int fileAckWithMetaData(uint8_t /*fileStatus*/
                                    ,
                                    uint32_t /*metaDataValue1*/,
                                    uint32_t /*metaDataValue2*/,
                                    uint32_t /*metaDataValue3*/,
                                    uint32_t /*metaDataValue4*/)
    {
        return PLDM_ERROR_UNSUPPORTED_PLDM_CMD;
    }

    virtual int newFileAvailableWithMetaData(uint64_t /*length*/,
                                             uint32_t /*metaDataValue1*/,
                                             uint32_t /*metaDataValue2*/,
                                             uint32_t /*metaDataValue3*/,
                                             uint32_t /*metaDataValue4*/)
    {
        return PLDM_ERROR_UNSUPPORTED_PLDM_CMD;
    }

    /** @brief ChapHandler destructor
     */
    ~ChapHandler() {}

  private:
    uint16_t chaapType; //!< type of the chaap secret file
};
} // namespace responder
} // namespace pldm
