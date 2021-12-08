#pragma once
#include "common/types.hpp"
#include "common/utils.hpp"
#include "libpldmresponder/pdr_utils.hpp"
#include "pldmd/handler.hpp"

namespace pldm
{

namespace responder
{

namespace oem_platform
{
using namespace pldm::responder::pdr_utils;

using ObjectPath = std::filesystem::path;
using ObjectPathMaps = std::map<ObjectPath, pldm_entity_node*>;

class Handler : public CmdHandler
{
  public:
    Handler(const pldm::utils::DBusHandler* dBusIntf) : dBusIntf(dBusIntf)
    {}

    /** @brief Interface to set the numeric effecter requested by pldm
     *  requester for OEM types. Each individual oem type should implement
     *  it's own handler.
     *
     *  @param[in] entityType - entity type corresponding to the effecter id
     *  @param[in] entityInstance - entity instance
     *  @param[in] effecterSemanticId - effecter semantic id
     *  @param[in] effecterDataSize - effecter value size.
     *  @param[in] effecterValue - effecter value.
     *  @param[in] effecterOffset - offset of the effecter.
     *  @param[in] effecterResolution - resolution of the effecter.
     *  @param[in] effecterId - Effecter ID sent by the requester to act on.
     *
     *  @return - Success or failure in setting the states.Returns failure in
     *            terms of PLDM completion codes if atleast one state fails to
     *            be set
     *
     */
    virtual int oemSetNumericEffecterValueHandler(
        uint16_t entityType, uint16_t entityInstance,
        uint16_t effecterSemanticId, uint8_t effecterDataSize,
        uint8_t* effecterValue, real32_t effecterOffset,
        real32_t effecterResolution, uint16_t effecterId) = 0;

    /** @brief Interface to get the state sensor readings requested by pldm
     *  requester for OEM types. Each specific type should implement a handler
     *  of it's own
     *
     *  @param[in] entityType - entity type corresponding to the sensor
     *  @param[in] entityInstance - entity instance number
     *  @param[in] stateSetId - state set id
     *  @param[in] compSensorCnt - composite sensor count
     *  @param[out] stateField - The state field data for each of the states,
     *                           equal to composite sensor count in number
     *
     *  @return - Success or failure in getting the states. Returns failure in
     *            terms of PLDM completion codes if fetching atleast one state
     *            fails
     */
    virtual int getOemStateSensorReadingsHandler(
        pldm::pdr::EntityType entityType,
        pldm::pdr::EntityInstance entityInstance,
        pldm::pdr::ContainerID entityContainerId,
        pldm::pdr::StateSetId stateSetId,
        pldm::pdr::CompositeCount compSensorCnt, uint16_t sensorId,
        std::vector<get_sensor_state_field>& stateField) = 0;

    /** @brief Interface to set the effecter requested by pldm requester
     *         for OEM types. Each individual oem type should implement
     *         it's own handler.
     *
     *  @param[in] entityType - entity type corresponding to the effecter id
     *  @param[in] entityInstance - entity instance
     *  @param[in] stateSetId - state set id
     *  @param[in] compEffecterCnt - composite effecter count
     *  @param[in] stateField - The state field data for each of the states,
     *                         equal to compEffecterCnt in number
     *  @param[in] effecterId - Effecter id
     *
     *  @return - Success or failure in setting the states.Returns failure in
     *            terms of PLDM completion codes if atleast one state fails to
     *            be set
     */
    virtual int oemSetStateEffecterStatesHandler(
        uint16_t entityType, uint16_t entityInstance, uint16_t stateSetId,
        uint8_t compEffecterCnt,
        std::vector<set_effecter_state_field>& stateField,
        uint16_t effecterId) = 0;

    /** @brief Interface to generate the OEM PDRs
     *
     * @param[in] repo - instance of concrete implementation of Repo
     */
    virtual void buildOEMPDR(pdr_utils::Repo& repo) = 0;

    /** @brief Interface to check if setEventReceiver is sent to host already.
     *         If sent then then disableWatchDogTimer() would be called to
     *         disable the watchdog timer */
    virtual void checkAndDisableWatchDog() = 0;

    /** @brief Interface to check if the watchdog timer is running
     *
     * @return - true if watchdog is running, false otherwise
     * */
    virtual bool watchDogRunning() = 0;

    /** @brief Interface to reset the watchdog timer */
    virtual void resetWatchDogTimer() = 0;

    /** @brief Interface to disable the watchdog timer */
    virtual void disableWatchDogTimer() = 0;

    /* @brief Interface to set the host effecter state */
    virtual void setHostEffecterState(bool status) = 0;

    /** @brief Interface to keep track of how many times setEventReceiver
     *         is sent to host */
    virtual void countSetEventReceiver() = 0;

    /** @brief Interface to check the BMC state */
    virtual int checkBMCState() = 0;

    /** @brief update the dbus object paths */
    virtual void upadteOemDbusPaths(std::string& dbusPath) = 0;
    /** @brief Interface to update container ID */
    virtual void updateContainerID() = 0;
    virtual void modifyPDROemActions(uint16_t entityType,
                                     uint16_t stateSetId) = 0;

    virtual ~Handler() = default;

  protected:
    const pldm::utils::DBusHandler* dBusIntf;
};

} // namespace oem_platform

namespace oem_fru
{

class Handler : public CmdHandler
{
  public:
    Handler(const pldm::utils::DBusHandler* dBusIntf) : dBusIntf(dBusIntf)
    {}

    /** @brief Process OEM FRU record
     *
     * @param[in] fruData - the data of the fru
     */
    virtual int processOEMfruRecord(const std::vector<uint8_t>& fruData) = 0;

    virtual ~Handler() = default;

  protected:
    const pldm::utils::DBusHandler* dBusIntf;
};

} // namespace oem_fru

} // namespace responder

} // namespace pldm
