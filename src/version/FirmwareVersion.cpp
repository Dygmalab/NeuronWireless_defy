/*
 * FirmwareVersion -- Provide the version and system hardware configuration
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
#include "Config_manager.h"
#include "Communications.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope.h"
//#include "nrf_log.h"

#include "kbd_if_manager.h"

#ifndef DEFY_FW_VERSION
#error "Firmware package version is not specified."
    #define DEFY_FW_VERSION "N/A"
#endif

#define RP2040_ID_END_PACKAGE 28
#define RP2040_ID_START_PACKAGE 12

# define base16char(i) ("0123456789ABCDEF"[i])

    uint16_t FirmwareVersion::settings_base_ = 0;
    const FirmwareVersion::device_spec_t * FirmwareVersion::p_device_spec = nullptr;

//At the end of the function we need to know if the specifications are different from the ones stored in memory.
//Also we need to act differently depending if the configuration stored in memory is empty or not.
// If it's empty we store the data and don't reset the neuron. If it's not empty we store the data and we DON'T reset the neuron.
    bool left_side_spec_changes = false;
    bool right_side_spec_changes = false;

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


result_t FirmwareVersion::init()
{
    result_t result = RESULT_ERR;

    result = kbdif_initialize();
    EXIT_IF_ERR( result, "kbdif_initialize failed" );

    result = ConfigManager.config_item_request( ConfigManager::CFG_ITEM_TYPE_DEVICE_SPEC, (const void **)&p_device_spec );
    EXIT_IF_ERR( result, "ConfigManager.config_item_request failed" );

    settings_base_ = kaleidoscope::plugin::EEPROMSettings::requestSlice((sizeof(struct Specifications)*2)); //multiply by 2

    // because we have two specification structures.
    Communications.callbacks.bind(CONFIGURATION, (
            [this](Packet const &packet)
            {
                //NRF_LOG_DEBUG("Configuration command receive");
                if (filterHand(packet.header.device, false))
                {
                    keyscanner_spec_t keyscanner_spec = p_device_spec->ks_left;

                    if (are_specifications_diferences(packet ,true))
                    {
                        //NRF_LOG_DEBUG("saving specifications LEFT side due to differences");
                        configuration.configuration_receive_left = false;
                    }

                    keyscanner_spec.configuration = packet.data[0];
                    //NRF_LOG_DEBUG("configuration left_side: %i", keyscanner_spec.configuration);

                    keyscanner_spec.device_name = packet.data[1];
                    //NRF_LOG_DEBUG("device_name left_side: %i",keyscanner_spec.device_name);

                    keyscanner_spec.connection = packet.data[2];
                    //NRF_LOG_DEBUG("connection left_side: %i", keyscanner_spec.connection);


                    //Save the configuration in memory just one time.
                    if ( !configuration.configuration_receive_left )
                    {
                        //NRF_LOG_DEBUG("saving specifications left side");
                        cfgmem_keyscanner_spec_left_save( &keyscanner_spec );
                        configuration.configuration_receive_left = true;
                        left_side_spec_changes = true;
                    }
                }
                if (filterHand(packet.header.device, true))
                {
                    keyscanner_spec_t keyscanner_spec = p_device_spec->ks_right;

                    if (are_specifications_diferences(packet ,false))
                    {
                        //NRF_LOG_DEBUG("saving specifications right side due to differences");
                        //NRF_LOG_DEBUG("configuration right_side: %i", keyscanner_spec.configuration);
                        configuration.configuration_receive_right = false;
                    }

                    keyscanner_spec.configuration = packet.data[0];
                    //NRF_LOG_DEBUG("configuration right_side: %i", keyscanner_spec.configuration);

                    keyscanner_spec.device_name = packet.data[1];
                    //NRF_LOG_DEBUG("device_name right_side: %i",keyscanner_spec.device_name);

                    keyscanner_spec.connection = packet.data[2];
                    //NRF_LOG_DEBUG("conection right_side: %i", keyscanner_spec.connection);

                    //Save the configuration in memory just once.
                    if (!configuration.configuration_receive_right )
                    {
                        //NRF_LOG_DEBUG("saving specifications right side");
                        cfgmem_keyscanner_spec_right_save( &keyscanner_spec );
                        configuration.configuration_receive_right = true;
                        right_side_spec_changes = true;
                    }
                }
            }));

    /*Left side*/
    if (p_device_spec->ks_left.configuration == 0xFF || p_device_spec->ks_left.configuration == 0 )
    {
        configuration.configuration_receive_left = false;
        configuration.configuration_left_empty = true;
    }
    else if (p_device_spec->ks_left.configuration != 0)
    {
        configuration.configuration_receive_left = true;
        configuration.configuration_left_empty  = false;
    }

    /*Right side*/
    if (p_device_spec->ks_right.configuration == 0xFF || p_device_spec->ks_right.configuration == 0 )
    {
        configuration.configuration_receive_right = false;
        configuration.configuration_right_empty = true;
    }
    else if (p_device_spec->ks_right.configuration != 0)
    {
        configuration.configuration_receive_right = true;
        configuration.configuration_right_empty = false;
    }

    //NRF_LOG_DEBUG("Getting configurations right %i", p_device_spec->ks_right.configuration);
    //NRF_LOG_DEBUG("Getting configurations left %i", p_device_spec->ks_left.configuration);

_EXIT:
    return result;
}

bool FirmwareVersion::are_specifications_diferences( Communications_protocol::Packet  const &packet_check , bool side)
{
    uint8_t configuration = packet_check.data[0];
    uint8_t connection = packet_check.data[2];
    bool chip_id_diferences = false;

    const keyscanner_spec_t * p_keyscanner_spec;

    if (side)
    {
        p_keyscanner_spec = &p_device_spec->ks_left;
    } else
    {
        p_keyscanner_spec = &p_device_spec->ks_right;
    }

    for (uint8_t i = RP2040_ID_START_PACKAGE; i < RP2040_ID_END_PACKAGE ; ++i) {
        if (p_keyscanner_spec->chip_id_rp2040[i - RP2040_ID_START_PACKAGE] == static_cast<char>(packet_check.data[i]))
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

    //NRF_LOG_DEBUG(" connection Memory: %i , Receive: %i ", p_keyscanner_spec->connection, connection );
    //NRF_LOG_DEBUG(" configuration Memory: %i , Receive: %i ", p_keyscanner_spec->configuration, configuration);

    if (   connection != p_keyscanner_spec->connection
           || configuration != p_keyscanner_spec->configuration || chip_id_diferences){
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

    if (static_cast<Device>(p_device_spec->ks_left.connection) == Device::Wireless
        && static_cast<Device>(p_device_spec->ks_right.connection) == Device::Wireless)
    {
        resp = true;
    }
    else
    {
        resp = false;
    }
    return resp;
}

result_t FirmwareVersion::kbdif_initialize()
{
    result_t result = RESULT_ERR;
    kbdif_conf_t config;

    /* Prepare the kbdif configuration */
    config.p_instance = this;
    config.handlers = &kbdif_handlers;

    /* Initialize the kbdif */
    result = kbdif_init( &p_kbdif, &config );
    EXIT_IF_ERR( result, "kbdif_init failed" );

    /* Add the kbdif into the kbdif manager */
    result = kbdifmgr_add( p_kbdif );
    EXIT_IF_ERR( result, "kbdifmgr_add failed" );

_EXIT:
    return result;
}

kbdapi_event_result_t FirmwareVersion::kbdif_command_event_cb( void * p_instance, const char * p_command )
{
    const char *cmd = "version";
    if (::Focus.handleHelp(p_command, cmd)) return KBDAPI_EVENT_RESULT_IGNORED;

    if (strcmp(p_command, cmd) != 0) return KBDAPI_EVENT_RESULT_IGNORED;

    //NRF_LOG_DEBUG("read request: version");

    char cstr[70];
    strcpy(cstr, DEFY_FW_VERSION);
    ::Focus.sendRaw<char *>(cstr);

    return KBDAPI_EVENT_RESULT_CONSUMED;
}

const kbdif_handlers_t FirmwareVersion::kbdif_handlers =
{
    .key_event_cb = NULL,
    .command_event_cb = kbdif_command_event_cb,
};

void FirmwareVersion::cfgmem_keyscanner_spec_left_save( const keyscanner_spec_t * p_spec )
{
    result_t result = RESULT_ERR;

    result = ConfigManager.config_item_update( &p_device_spec->ks_left, p_spec, sizeof( p_device_spec->ks_left) );
    ASSERT_DYGMA( result == RESULT_OK, "ConfigManager.config_item_update failed" );

    UNUSED( result );
}

void FirmwareVersion::cfgmem_keyscanner_spec_right_save( const keyscanner_spec_t * p_spec )
{
    result_t result = RESULT_ERR;

    result = ConfigManager.config_item_update( &p_device_spec->ks_right, p_spec, sizeof( p_device_spec->ks_right) );
    ASSERT_DYGMA( result == RESULT_OK, "ConfigManager.config_item_update failed" );

    UNUSED( result );
}

class FirmwareVersion FirmwareVersion;
