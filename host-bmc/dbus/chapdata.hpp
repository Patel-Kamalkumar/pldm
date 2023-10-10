#pragma once

#include "common/utils.hpp"
#ifdef OEM_IBM
#include "oem/ibm/requester/dbus_to_file_handler.hpp"
#endif
#include <com/ibm/PLDM/ChapData/server.hpp>
#include <sdbusplus/bus.hpp>
#include <sdbusplus/server.hpp>
#include <sdbusplus/server/object.hpp>

#include <string>
#include <utility>

namespace pldm
{
namespace dbus
{
using ChapDataObj = sdbusplus::server::object::object<
    sdbusplus::com::ibm::PLDM::server::ChapData>;

class ChapDatas : public ChapDataObj
{
  public:
    ChapDatas() = delete;
    ~ChapDatas() = default;
    ChapDatas(const ChapDatas&) = delete;
    ChapDatas& operator=(const ChapDatas&) = delete;
    ChapDatas(ChapDatas&&) = default;
    ChapDatas& operator=(ChapDatas&&) = default;

    ChapDatas(
        sdbusplus::bus::bus& bus, const std::string& objPath,
        pldm::requester::oem_ibm::DbusToFileHandler* dbusToFilehandlerObj) :
        ChapDataObj(bus, objPath.c_str()),
        dbusToFilehandler(dbusToFilehandlerObj)
    {}

    std::string chapName(std::string value) override;

    std::string chapName() const override;

    std::string chapPassword(std::string value) override;

    std::string chapPassword() const override;

  private:
    /** @brief Pointer to host effecter parser */
    pldm::requester::oem_ibm::DbusToFileHandler* dbusToFilehandler;
};

} // namespace dbus
} // namespace pldm
