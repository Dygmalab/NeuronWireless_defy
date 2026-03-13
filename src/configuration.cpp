/*
 * configuration.cpp -- Application-specific configuration handling
 *
 * Copyright (C) 2025  Dygma Lab S.L.
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

#include "Battery.h"
#include "Ble_manager.h"
#include "configuration.h"
#include "Config_manager.h"
#include "DynamicMacrosDygma.h"
#include "EEPROMKeymapDygma.h"
#include "FirmwareVersion.h"
#include "KeyRoleManager.h"
#include "LEDLayers.h"
#include "LEDManager.h"
#include "LEDPaletteRGBW.h"
#include "MouseKeysDygma.h"
#include "QukeysDygma.h"
#include "Radio_manager.h"
#include "SuperkeysHandler.h"

typedef struct PACK __attribute__((aligned(4)))
{
    LEDManager::ledmanager_conf_t ledmanager;
    kaleidoscope::plugin::Qukeys::Qukeys_config_t Qukeys;
    kaleidoscope::plugin::MouseKeys_::MouseKeys_config_t MouseKeys;
    FirmwareVersion::device_spec_t device_spec;
    Battery::battery_conf_t battery;
    BleManager::connections_config_t ble_connections;
    RadioManager::rf_config_t rf;
    kaleidoscope::plugin::EEPROMKeymap::keymap_config_t keymap;
    LEDPaletteRGBW::palette_config_t palette;
    LEDLayers::colormap_config_t colormap;
    kaleidoscope::plugin::KeyRoleManager::keyrole_config_t keyrole;
    kaleidoscope::plugin::SuperkeysHandler::superkey_config_t superkey;
    kaleidoscope::plugin::DynamicMacros::macros_config_t macros;
} config_cache_t;

static config_cache_t config_cache;

static result_t _cfg_item_request_cb( ConfigManager::cfg_item_type_t item_type, const void ** pp_item )
{
    switch( item_type )
    {
        case ConfigManager::CFG_ITEM_TYPE_DEVICE_SPEC:

            *pp_item = &config_cache.device_spec;

            break;

        case ConfigManager::CFG_ITEM_TYPE_LEDS_LEDMANAGER:

            *pp_item = &config_cache.ledmanager;

            break;

        case ConfigManager::CFG_ITEM_TYPE_LEDS_PALETTE:

            *pp_item = &config_cache.palette;

            break;

        case ConfigManager::CFG_ITEM_TYPE_LEDS_COLORMAP:

            *pp_item = &config_cache.colormap;

            break;

        case ConfigManager::CFG_ITEM_TYPE_BATTERY:

            *pp_item = &config_cache.battery;

            break;

        case ConfigManager::CFG_ITEM_TYPE_BLE_CONNECTIONS:

            *pp_item = &config_cache.ble_connections;

            break;

        case ConfigManager::CFG_ITEM_TYPE_RF:

            *pp_item = &config_cache.rf;

            break;

        default:

            ASSERT_DYGMA( false, "Invalid KBDMEM item requested" );

            return RESULT_ERR;
    }

    return RESULT_OK;
}

static result_t _cfg_item_request_kbdmem_cb( kbdmem_item_type_t item_type, const void ** pp_item )
{
    switch( item_type )
    {
        case KBDMEM_ITEM_TYPE_QUKEYS:

            *pp_item = &config_cache.Qukeys;

            break;

        case KBDMEM_ITEM_TYPE_MOUSEKEYS:

            *pp_item = &config_cache.MouseKeys;

            break;

        case KBDMEM_ITEM_TYPE_KEYMAP:

            *pp_item = &config_cache.keymap;

            break;

        case KBDMEM_ITEM_TYPE_KEYROLE:

            *pp_item = &config_cache.keyrole;

            break;

        case KBDMEM_ITEM_TYPE_SUPERKEY:

            *pp_item = &config_cache.superkey;

            break;

        case KBDMEM_ITEM_TYPE_MACROS:

            *pp_item = &config_cache.macros;

            break;

        default:

            ASSERT_DYGMA( false, "Invalid KBDMEM item requested" );

            return RESULT_ERR;
    }

    return RESULT_OK;
}

result_t configuration_init( void )
{
    result_t result = RESULT_ERR;

    ConfigManager::ConfigManager_config_t config;

    config.p_config_cache = (uint8_t *)&config_cache;
    config.config_cache_size = sizeof( config_cache );

    /* Callbacks */
    config.item_request_cb = _cfg_item_request_cb;
    config.item_request_kbdmem_cb = _cfg_item_request_kbdmem_cb;

    result = ConfigManager.init( &config );
    EXIT_IF_ERR( result, "ConfigManager.init failed" );

_EXIT:
    return result;
}

void configuration_save( void )
{
    ConfigManager.config_save_now();
}

void configuration_run()
{
    ConfigManager.run();
}
