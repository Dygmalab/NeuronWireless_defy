/*
 * kaleidoscope::plugin::FirmwareVersion -- Tell the firmware version via Focus
 *
 * Copyright (C) 2020  Dygma Lab S.L.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "FirmwareVersion.h"
#include "Communications.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope.h"
#include "nrf_log.h"
#include <Kaleidoscope-EEPROM-Settings.h>
#include <Kaleidoscope-Ranges.h>
#include <cstdio>

#ifndef DEFY_FW_VERSION
#error "Firmware package version is not specified."
    #define DEFY_FW_VERSION "N/A"
#endif

#define RP2040_ID_END_PACKAGE 28
#define RP2040_ID_START_PACKAGE 12

# define base16char(i) ("0123456789ABCDEF"[i])

namespace kaleidoscope
{
namespace plugin
{

    uint16_t FirmwareVersion::settings_base_ = 0;

//At the end of the function we need to know if the specifications are different from the ones stored in memory.
//Also we need to act differently depending if the configuration stored in memory is empty or not.
// If it's empty we store the data and don't reset the neuron. If it's not empty we store the data and we DON'T reset the neuron.
    bool left_side_spec_changes = false;
    bool right_side_spec_changes = false;

    FirmwareVersion::Specifications specifications_right_side;
    FirmwareVersion::Specifications specifications_left_side;

    char FirmwareVersion::device_name[16] = {0};
    bool conf_set = false;

    struct Configuration{
        bool configuration_receive_left;
        bool configuration_receive_right;
        bool configuration_left_empty;
        bool configuration_right_empty;
    };
    Configuration configuration;

bool inline filterHand(Communications_protocol::Devices incomingDevice, bool right_or_left)
{
    if (right_or_left == 1)
    {
        return incomingDevice == Communications_protocol::KEYSCANNER_DEFY_RIGHT || incomingDevice == Communications_protocol::BLE_DEFY_RIGHT ||
               incomingDevice == Communications_protocol::RF_DEFY_RIGHT;
    }
    else
    {
        return incomingDevice == Communications_protocol::KEYSCANNER_DEFY_LEFT || incomingDevice == Communications_protocol::BLE_DEFY_LEFT ||
               incomingDevice == Communications_protocol::RF_DEFY_LEFT;
    }
}


EventHandlerResult FirmwareVersion::onSetup()
{
    settings_base_ = kaleidoscope::plugin::EEPROMSettings::requestSlice((sizeof(specifications_left_side)*2)); //multiply by 2
    // because we have two specification structures.
    Communications.callbacks.bind(CONFIGURATION, (
            [this](Packet const &packet)
            {
                //NRF_LOG_DEBUG("Configuration command receive");
                if (filterHand(packet.header.device, false))
                {
                    if (are_specifications_diferences(packet ,true))
                    {
                        //NRF_LOG_DEBUG("saving specifications LEFT side due to differences");
                        configuration.configuration_receive_left = false;
                    }

                    specifications_left_side.configuration = packet.data[0];
                    //NRF_LOG_DEBUG("configuration left_side: %i", specifications_left_side.configuration);

                    specifications_left_side.device_name = packet.data[1];
                    //NRF_LOG_DEBUG("device_name left_side: %i",specifications_left_side.device_name);

                    specifications_left_side.connection = packet.data[2];
                    //NRF_LOG_DEBUG("connection left_side: %i", specifications_left_side.connection);


                    //Save the configuration in memory just one time.
                    if ( !configuration.configuration_receive_left )
                    {
                        //NRF_LOG_DEBUG("saving specifications left side");
                        Runtime.storage().put(settings_base_, specifications_left_side);
                        Runtime.storage().commit();
                        configuration.configuration_receive_left = true;
                        left_side_spec_changes = true;
                    }
                }
                if (filterHand(packet.header.device, true))
                {
                    if (are_specifications_diferences(packet ,false))
                    {
                        //NRF_LOG_DEBUG("saving specifications right side due to differences");
                        //NRF_LOG_DEBUG("configuration right_side: %i", specifications_right_side.configuration);
                        configuration.configuration_receive_right = false;
                    }

                    specifications_right_side.configuration = packet.data[0];
                    //NRF_LOG_DEBUG("configuration right_side: %i", specifications_right_side.configuration);

                    specifications_right_side.device_name = packet.data[1];
                    //NRF_LOG_DEBUG("device_name right_side: %i",specifications_right_side.device_name);

                    specifications_right_side.connection = packet.data[2];
                    //NRF_LOG_DEBUG("conection right_side: %i", specifications_right_side.connection);

                    //Save the configuration in memory just once.
                    if (!configuration.configuration_receive_right )
                    {
                        //NRF_LOG_DEBUG("saving specifications right side");
                        Runtime.storage().put(settings_base_ + sizeof(specifications_left_side), specifications_right_side);
                        Runtime.storage().commit();
                        configuration.configuration_receive_right = true;
                        right_side_spec_changes = true;
                    }
                }
            }));

    Runtime.storage().get(settings_base_, specifications_left_side);

    Runtime.storage().get(settings_base_ + sizeof (specifications_left_side), specifications_right_side);

    /*Left side*/
    if (specifications_left_side.configuration == 0xFF || specifications_left_side.configuration == 0 )
    {
        configuration.configuration_receive_left = false;
        configuration.configuration_left_empty = true;
    }
    else if (specifications_left_side.configuration != 0)
    {
        configuration.configuration_receive_left = true;
        configuration.configuration_left_empty  = false;
    }

    /*Right side*/
    if (specifications_right_side.configuration == 0xFF || specifications_right_side.configuration == 0 )
    {
        configuration.configuration_receive_right = false;
        configuration.configuration_right_empty = true;
    }
    else if (specifications_right_side.configuration != 0)
    {
        configuration.configuration_receive_right = true;
        configuration.configuration_right_empty = false;
    }

    //NRF_LOG_DEBUG("Getting configurations right %i", specifications_right_side.configuration);
    //NRF_LOG_DEBUG("Getting configurations left %i", specifications_left_side.configuration);

    return EventHandlerResult::OK;
}

EventHandlerResult FirmwareVersion::onFocusEvent(const char *command)
{
    const char *cmd = "version";
    if (::Focus.handleHelp(command, cmd)) return EventHandlerResult::OK;

    if (strcmp(command, cmd) != 0) return EventHandlerResult::OK;

    //NRF_LOG_DEBUG("read request: version");

    char cstr[70];
    strcpy(cstr, DEFY_FW_VERSION);
    ::Focus.sendRaw<char *>(cstr);

    return EventHandlerResult::EVENT_CONSUMED;
}

EventHandlerResult FirmwareVersion::beforeEachCycle()
{
    return EventHandlerResult::OK;
}

bool FirmwareVersion::are_specifications_diferences( Communications_protocol::Packet  const &packet_check , bool side)
{
    uint8_t configuration = packet_check.data[0];
    uint8_t connection = packet_check.data[2];
    bool chip_id_diferences = false;

    FirmwareVersion::Specifications mem_spec{};

    if (side)
    {
        mem_spec = specifications_left_side;
    } else
    {
        mem_spec =  specifications_right_side;
    }

    for (uint8_t i = RP2040_ID_START_PACKAGE; i < RP2040_ID_END_PACKAGE ; ++i) {
        if (mem_spec.chip_id_rp2040[i - RP2040_ID_START_PACKAGE] == static_cast<char>(packet_check.data[i]))
        {
            continue;
        }
        else
        {
            chip_id_diferences = true;
        }
    }
    if (chip_id_diferences)
    {
        //NRF_LOG_DEBUG("Chip id is not the same" );
    }

    //NRF_LOG_DEBUG(" connection Memory: %i , Receive: %i ", mem_spec.connection, connection );
    //NRF_LOG_DEBUG(" configuration Memory: %i , Receive: %i ", mem_spec.configuration, configuration);

    if (   connection != mem_spec.connection
           || configuration != mem_spec.configuration || chip_id_diferences){
        //NRF_LOG_DEBUG("Specifications are different from stored in memory");
        return true;
    }
    //NRF_LOG_DEBUG("Same specifications");
    return false;
}

bool FirmwareVersion::keyboard_is_wireless()
{
    bool resp = false;

    if(!configuration.configuration_receive_right || !configuration.configuration_receive_left)
    {
        //NRF_LOG_DEBUG("Configuration not received");
        return false;
    }

    if (static_cast<Device>(specifications_left_side.connection) == Device::Wireless
        && static_cast<Device>(specifications_right_side.connection) == Device::Wireless)
    {
        resp = true;
    }
    else
    {
        resp = false;
    }
    return resp;
}

} // namespace plugin
} // namespace kaleidoscope

kaleidoscope::plugin::FirmwareVersion FirmwareVersion;
