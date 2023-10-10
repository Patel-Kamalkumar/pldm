#include "libpldm/entity.h"
#include "libpldm/state_set_oem_ibm.h"

#include "host-bmc/dbus/custom_dbus.hpp"
#include "pcie_topology.hpp"
#include "serialize.hpp"

#include <phosphor-logging/lg2.hpp>

PHOSPHOR_LOG2_USING;

namespace pldm
{
namespace dbus
{

std::string ChapDatas::chapName(std::string value)
{
    pldm::serialize::Serialize::getSerialize().serialize(path, "ChapData",
                                                         "ChapName", value);

    return sdbusplus::com::ibm::PLDM::server::ChapData::chapName(value);
}

std::string ChapDatas::chapName() const
{
    return sdbusplus::com::ibm::PLDM::server::ChapData::chapName();
}

std::string ChapDatas::chapPassword(std::string value)
{
    pldm::serialize::Serialize::getSerialize().serialize(path, "ChapData",
                                                         "ChapPassword", value);
    std::cout << "KK setting chappwd:" << value << "\n";
    dbusToFilehandler->newChapDataFileAvailable(ChapName, value);
    return sdbusplus::com::ibm::PLDM::server::ChapData::chapPassword(value);
}

std::string ChapDatas::chapPassword() const
{
    return sdbusplus::com::ibm::PLDM::server::ChapData::chapPassword();
}

} // namespace dbus
} // namespace pldm
