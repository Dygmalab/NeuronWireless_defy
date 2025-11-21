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

#include "Ble_manager.h"
#include "configuration.h"
#include "Config_manager.h"
#include "FirmwareVersion.h"
#include "LEDManager.h"
#include "MouseKeysDygma.h"
#include "QukeysDygma.h"
#include "Radio_manager.h"

typedef struct PACK
{
    uint8_t legacy_settings[4];     /* addr. 0. A placeholder for the legacy settings header of size 4 */
    uint8_t fade_enabled;           /* addr. 0x0004 */

    /* Idle LEDs */                              /* addr. 0x0005 */
    LEDManager::idleleds_conf_t idleleds;

//    Qukeys qukeys;                /* addr. 0x0015 */
    kaleidoscope::plugin::Qukeys::Qukeys_config_t Qukeys;

//    MouseKeys_ mouseKeys;         /* addr. 0x001A */
    kaleidoscope::plugin::MouseKeys_::MouseKeys_config_t MouseKeys;

    uint8_t legacy_keyscan_interval;/* addr. 0x0024 A placeholder for the legacy keyscan_interval which is not used throughout the system */

//    Brightness brightness;        /* addr. 0x0025 */
    LEDManager::brightness_conf_t brightness;

//    Specification specification;  /* addr. 0x002A */  // settings_base_ = kaleidoscope::plugin::EEPROMSettings::requestSlice((sizeof(specifications_left_side)*2)); //multiply by 2
    FirmwareVersion::device_spec_t device_spec;

    uint8_t bat_saving_mode;        /* addr. 0x007A */  // settings_saving_ = ::EEPROMSettings.requestSlice(sizeof(saving_mode));

//    Ble_flash_data ble_flash_data;/* addr. 0x007B */  // flash_base_addr = kaleidoscope::plugin::EEPROMSettings::requestSlice(sizeof(ble_flash_data));
    BleManager::connections_config_t ble_connections;

//    uint8_t power_rf;             /* addr. 0x0165 */  // settings_base_ = kaleidoscope::plugin::EEPROMSettings::requestSlice(sizeof(power_rf));
    RadioManager::rf_config_t rf;


//    Keymap keymap;                /* addr. 0x0166 */  // keymap_base_ = ::EEPROMSettings.requestSlice(max_layers_ * Runtime.device().numKeys() * 2);
//
//    Palette palette;              /* addr. 0x07A6 */  // palette_memory_pos = ::EEPROMSettings.requestSlice( palette_color_cnt * color_size );
//
//    Colormap colormap;            /* addr. 0x07E6 */  //colormap_memory_pos = ::EEPROMSettings.requestSlice( colormap_memory_size );
//
//    Superkeys superkeys;          /* addr. 0x0B60 */  // storage_base_ = ::EEPROMSettings.requestSlice(size + 8);
//
//    Macros macros;                /* addr. 0x0F68 */  // storage_base_ = ::EEPROMSettings.requestSlice(size);

#warning "Test"
    uint8_t last_item;
} config_cache_t;

static config_cache_t config_cache;

static result_t _cfg_item_request_cb( ConfigManager::cfg_item_type_t item_type, const void ** pp_item )
{
    switch( item_type )
    {
        case ConfigManager::CFG_ITEM_TYPE_DEVICE_SPEC:

            *pp_item = &config_cache.device_spec;

            break;

        case ConfigManager::CFG_ITEM_TYPE_LEDS_FADE_EFFECT:

            *pp_item = &config_cache.fade_enabled;

            break;

        case ConfigManager::CFG_ITEM_TYPE_LEDS_IDLELEDS:

            *pp_item = &config_cache.idleleds;

            break;

        case ConfigManager::CFG_ITEM_TYPE_LEDS_BRIGHTNESS:

            *pp_item = &config_cache.brightness;

            break;

        case ConfigManager::CFG_ITEM_TYPE_BAT_SAVING_MODE:

            *pp_item = &config_cache.bat_saving_mode;

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

#warning "Test"
#define GET_OFFSET( item_ptr )  ( (uint32_t)item_ptr - (uint32_t)&config_cache )

static result_t _cfg_item_request_kbdmem_cb( kbdmem_item_type_t item_type, const void ** pp_item )
{
    volatile uint32_t legacy_settings = GET_OFFSET( config_cache.legacy_settings );
    volatile uint32_t fade_enabled = GET_OFFSET( &config_cache.fade_enabled );
    volatile uint32_t idleleds = GET_OFFSET( &config_cache.idleleds );
    volatile uint32_t qukeys = GET_OFFSET( &config_cache.Qukeys );
    volatile uint32_t mousekeys = GET_OFFSET( &config_cache.MouseKeys );
    volatile uint32_t brightness = GET_OFFSET( &config_cache.brightness );
    volatile uint32_t device_spec = GET_OFFSET( &config_cache.device_spec );
    volatile uint32_t bat_saving_mode = GET_OFFSET( &config_cache.bat_saving_mode );
    volatile uint32_t ble_connections = GET_OFFSET( &config_cache.ble_connections );
    volatile uint32_t rf = GET_OFFSET( &config_cache.rf );

    volatile uint32_t last_item = GET_OFFSET( &config_cache.last_item );

    switch( item_type )
    {
        case KBDMEM_ITEM_TYPE_QUKEYS:

            *pp_item = &config_cache.Qukeys;

            break;

        case KBDMEM_ITEM_TYPE_MOUSEKEYS:

            *pp_item = &config_cache.MouseKeys;

            break;

        default:

            ASSERT_DYGMA( false, "Invalid KBDMEM item requested" );

            return RESULT_ERR;
    }

    return RESULT_OK;
}

result_t configuration_init( void )
{
    ConfigManager::ConfigManager_config_t config;

    config.p_config_cache = (uint8_t *)&config_cache;
    config.config_cache_size = sizeof( config_cache );

    /* Callbacks */
    config.item_request_cb = _cfg_item_request_cb;
    config.item_request_kbdmem_cb = _cfg_item_request_kbdmem_cb;

    ConfigManager.init( &config );

    return RESULT_OK;
}

void configuration_save( void )
{
    ConfigManager.config_save_now();
}

void configuration_run()
{
    ConfigManager.run();
}
