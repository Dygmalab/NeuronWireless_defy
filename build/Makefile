#-------------------------------------------------------------------------------
# Application name (project name)
#-------------------------------------------------------------------------------

APP_NAME = NeuronWireless_defy

#-------------------------------------------------------------------------------
# Common, platform and project root directories
#-------------------------------------------------------------------------------

# Common root directory
COMMON_ROOT_DIR = ../

# Application root directory
APP_ROOT_DIR = $(COMMON_ROOT_DIR)/

# Application build directory
APP_BUILD_DIR = $(APP_ROOT_DIR)/build/

# Libraries root directory
LIB_ROOT_DIR = $(APP_ROOT_DIR)/libraries/

# Platform build directory
PLATFORM_BUILD_DIR = $(APP_BUILD_DIR)/platform/

# SDK root directories
NRF5_SDK = nRF5_SDK_17.1.0_ddde560

SDK_ROOT_DIR = $(LIB_ROOT_DIR)/SDK/
SDK_NRF5_SDK_ROOT_DIR = $(SDK_ROOT_DIR)/$(NRF5_SDK)/

# Kaleidoscope root directory
KALEIDOSCOPE_ADAPTER_ROOT_DIR = $(LIB_ROOT_DIR)/kaleidoscope_adapter/
KALEIDOSCOPE_ROOT_DIR = $(KALEIDOSCOPE_ADAPTER_ROOT_DIR)/kaleidoscope/

KEYBOARD_API_ROOT_DIR = $(KALEIDOSCOPE_ADAPTER_ROOT_DIR)/keyboard_api/

KEYBOARDIO_HID_ROOT_DIR = $(LIB_ROOT_DIR)/KeyboardioHID/

# Tools root directory
TOOLS_ROOT_DIR = $(LIB_ROOT_DIR)/tools/

#-------------------------------------------------------------------------------
# Include common definitions
#-------------------------------------------------------------------------------

# Common definitions
include $(PLATFORM_BUILD_DIR)/MakeDefsCommon.mk

#-------------------------------------------------------------------------------
# BSP Target board variant
#-------------------------------------------------------------------------------

# Hardware board name
#BSP_TARGET_BOARD = BSP_DEFY_N2_DEBUG
BSP_TARGET_BOARD = BSP_DEFY_N2

#-------------------------------------------------------------------------------
# Include target MCU specific definitions
#-------------------------------------------------------------------------------

# Target specific MCU definitions
include $(APP_BUILD_DIR)/MakeDefsBsp.mk


#-------------------------------------------------------------------------------
# Include target MCU specific definitions
#-------------------------------------------------------------------------------

# Target specific MCU definitions
ARDUINO_BUILD_DIR = $(LIB_ROOT_DIR)/Arduino/build
include $(ARDUINO_BUILD_DIR)/MakeArduinoNRF52833.mk

#-------------------------------------------------------------------------------
# Path and toolchain executable prefix to run particular build process tools
#-------------------------------------------------------------------------------

CROSS_FW = $(CS_CROSS_DIR_PATH)$(CS_CROSS_PREFIX_ARM_NONE_EABI)

#-------------------------------------------------------------------------------
# Flags for compiler, assembler and linker
#-------------------------------------------------------------------------------

# Flags common to compiler, assembler and linker
COMMONFLAGS += -mcpu=cortex-m4
COMMONFLAGS += -mfpu=fpv4-sp-d16
COMMONFLAGS += -mthumb -mabi=aapcs -fmessage-length=0 -fsigned-char -fno-builtin -fno-strict-aliasing
COMMONFLAGS += -fsingle-precision-constant
COMMONFLAGS += -ffunction-sections
COMMONFLAGS += -fdata-sections
COMMONFLAGS += -Wall
COMMONFLAGS += -mbe32

# Compiler flags
CFLAGS += $(COMMONFLAGS)
CFLAGS += -Wno-switch -std=c11

CXXFLAGS += $(COMMONFLAGS)
CXXFLAGS += -Wno-switch -std=c++11 -fno-exceptions -fno-rtti
# Handling the Kaleidoscope warnings
CXXFLAGS += -Wno-write-strings

# Assembler flags
ASFLAGS += $(COMMONFLAGS)

# Linker flags
LFLAGS += $(COMMONFLAGS) -L$(LIBDIR) -Wl,--gc-sections
LFLAGS += -specs=nano.specs -specs=nosys.specs -lc -lnosys -lm
LFLAGS += -Wl,-T./init/device/$(TARGET_MCU_DIR_NAME)/flash.ld

#-------------------------------------------------------------------------------
# Base defines
#-------------------------------------------------------------------------------

# Memory
DEFINES += -D__STACK_SIZE=2048
DEFINES += -D__HEAP_SIZE=2048

# GCC toolchain is used for building process
DEFINES += -Dgcc

# THUMB mode
DEFINES += -D_THUMB

#-------------------------------------------------------------------------------
# SDK defines
#-------------------------------------------------------------------------------

# MCU
DEFINES += -DFLOAT_ABI_HARD
DEFINES += -DINITIALIZE_USER_SECTIONS
DEFINES += -DMCU_ALIGNMENT_SIZE=4

# Softdevice
DEFINES += -DSOFTDEVICE_PRESENT
DEFINES += -DS140

# BLE
DEFINES += -DNRF_SD_BLE_API_VERSION=7

# HAL
#DEFINES += -DCONFIG_GPIO_AS_PINRESET
DEFINES += -DCONFIG_NFCT_PINS_AS_GPIOS

# System timer
DEFINES += -DAPP_TIMER_V2
DEFINES += -DAPP_TIMER_V2_RTC1_ENABLED

# Others
DEFINES += -DNRFX_PPI_ENABLED=1
DEFINES += -DNRF52_ARCH

#-------------------------------------------------------------------------------
# RF Host Device
#-------------------------------------------------------------------------------

RF_HOST_DEVICE_HEX = $(LIB_ROOT_DIR)/rf_host_device/rf_host_device/bin/rf_host_device.hex

#-------------------------------------------------------------------------------
# Library search directiories
#-------------------------------------------------------------------------------

LIBDIR += -L./init/device/$(TARGET_MCU_DIR_NAME)

#-------------------------------------------------------------------------------
# Include search directories
#-------------------------------------------------------------------------------

# Application project
INCDIR += -I$(APP_ROOT_DIR)/
INCDIR += -I$(APP_ROOT_DIR)/src/
INCDIR += -I$(APP_ROOT_DIR)/src/version/

INCDIR += -I$(LIB_ROOT_DIR)/
INCDIR += -I$(LIB_ROOT_DIR)/Ble_composite_dev/
INCDIR += -I$(LIB_ROOT_DIR)/Communications/src/
INCDIR += -I$(LIB_ROOT_DIR)/Communications/src/device/neuron/common/
INCDIR += -I$(LIB_ROOT_DIR)/Communications/src/device/neuron/defyN2/
INCDIR += -I$(LIB_ROOT_DIR)/Communications/src/device/neuron/defyN2/com_models/
INCDIR += -I$(LIB_ROOT_DIR)/Fifo_buffer/
INCDIR += -I$(LIB_ROOT_DIR)/EEPROM/
INCDIR += -I$(LIB_ROOT_DIR)/NeuronLedLibrary/
INCDIR += -I$(LIB_ROOT_DIR)/NeuronLedLibrary/LedModeSerializable/
INCDIR += -I$(LIB_ROOT_DIR)/NeuronLedLibrary/LedModeSerializable/src/
INCDIR += -I$(LIB_ROOT_DIR)/NeuronLedLibrary/palette/
INCDIR += -I$(LIB_ROOT_DIR)/rf_host_device/
INCDIR += -I$(LIB_ROOT_DIR)/rf_host_device/rf_host_device/includes/
INCDIR += -I$(LIB_ROOT_DIR)/rf_host_device/rf_host_device/includes/middleware/
INCDIR += -I$(LIB_ROOT_DIR)/rf_host_device/rf_host_device/includes/rf_gateway/
INCDIR += -I$(LIB_ROOT_DIR)/rf_host_device/rf_host_device/includes/rf_protocol/
INCDIR += -I$(LIB_ROOT_DIR)/Spi_slave/
INCDIR += -I$(LIB_ROOT_DIR)/Spi_slave/link/
INCDIR += -I$(LIB_ROOT_DIR)/Status_leds/
INCDIR += -I$(LIB_ROOT_DIR)/Time_counter/
INCDIR += -I$(LIB_ROOT_DIR)/Watchdog_timer/
INCDIR += -I$(LIB_ROOT_DIR)/Wire/
INCDIR += -I$(LIB_ROOT_DIR)/Twi_master/
INCDIR += -I$(LIB_ROOT_DIR)/UpgradeKeyscanner/include/
INCDIR += -I$(LIB_ROOT_DIR)/UpgradeKeyscanner/src/
INCDIR += -I$(LIB_ROOT_DIR)/CRC/
INCDIR += -I$(LIB_ROOT_DIR)/Battery_manager/
INCDIR += -I$(LIB_ROOT_DIR)/Ble_manager/
INCDIR += -I$(LIB_ROOT_DIR)/RF_manager/
INCDIR += -I$(LIB_ROOT_DIR)/utils/Do_once/
INCDIR += -I$(LIB_ROOT_DIR)/utils/Run_task_once/
INCDIR += -I$(LIB_ROOT_DIR)/utils/Timer/

INCDIR += -I$(LIB_ROOT_DIR)/NRf_platform/
INCDIR += -I$(LIB_ROOT_DIR)/NRf_platform/hal/
INCDIR += -I$(LIB_ROOT_DIR)/NRf_platform/hal/mcu/
INCDIR += -I$(LIB_ROOT_DIR)/NRf_platform/hal/mcu/nrf52/
INCDIR += -I$(LIB_ROOT_DIR)/NRf_platform/middleware/
INCDIR += -I$(LIB_ROOT_DIR)/NRf_platform/middleware/halsep/
INCDIR += -I$(LIB_ROOT_DIR)/NRf_platform/middleware/memory/

# Kaleidoscope Adapter
INCDIR += -I$(KEYBOARD_API_ROOT_DIR)/
INCDIR += -I$(KEYBOARD_API_ROOT_DIR)/core/
INCDIR += -I$(KEYBOARD_API_ROOT_DIR)/falsep/
INCDIR += -I$(KEYBOARD_API_ROOT_DIR)/interfaces/
INCDIR += -I$(KEYBOARD_API_ROOT_DIR)/modules/

INCDIR += -I$(KALEIDOSCOPE_ADAPTER_ROOT_DIR)/
INCDIR += -I$(KALEIDOSCOPE_ADAPTER_ROOT_DIR)/fal/
INCDIR += -I$(KALEIDOSCOPE_ADAPTER_ROOT_DIR)/fal/ll/
INCDIR += -I$(KALEIDOSCOPE_ADAPTER_ROOT_DIR)/fal/public/
INCDIR += -I$(KALEIDOSCOPE_ADAPTER_ROOT_DIR)/plugins/

INCDIR += -I$(KALEIDOSCOPE_ROOT_DIR)/src/
INCDIR += -I$(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/device/dygma/
INCDIR += -I$(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/device/dygma/keyboardManager
INCDIR += -I$(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/device/dygma/keyboardManager/universalModules
INCDIR += -I$(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/

# SDK
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/ble/ble_advertising/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/ble/ble_dtm/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/ble/ble_link_ctx_manager/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/ble/ble_services/ble_bas/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/ble/ble_services/ble_dis/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/ble/ble_services/ble_hids/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/ble/common/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/ble/nrf_ble_gatt/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/ble/nrf_ble_qwr/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/ble/peer_manager/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/atomic/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/atomic_fifo/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/atomic_flags/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/balloc/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/bootloader/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/bootloader/dfu/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/delay/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/experimental_section_vars/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/fds/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/fstorage/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/log/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/log/src/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/memobj/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/mutex/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/pwr_mgmt/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/ringbuf/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/scheduler/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/sortlist/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/strerror/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/timer/

INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/util/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/softdevice/common/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/softdevice/s140/headers/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/softdevice/s140/headers/nrf52
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/components/toolchain/cmsis/include/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/external/fprintf/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/integration/nrfx/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/integration/nrfx/legacy/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/src
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/include/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/hal/
INCDIR += -I$(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/mdk/

#-------------------------------------------------------------------------------
# C/C++ sources
#-------------------------------------------------------------------------------

# Application project
SRCSC += $(wildcard $(APP_ROOT_DIR)/*.c)
SRCSC += $(wildcard $(APP_ROOT_DIR)/src/*.c)

SRCSCXX += $(wildcard $(APP_ROOT_DIR)/*.cpp)
SRCSCXX += $(wildcard $(APP_ROOT_DIR)/src/*.cpp)

SRCSCXX += $(wildcard $(APP_ROOT_DIR)/src/version/FirmwareVersion.cpp)

SRCSC += $(LIB_ROOT_DIR)/Ble_composite_dev/Ble_composite_dev.c
SRCSC += $(LIB_ROOT_DIR)/Ble_composite_dev/ble_hid_service.c
SRCSC += $(LIB_ROOT_DIR)/rf_host_device/rf_host_device_api.c
SRCSC += $(LIB_ROOT_DIR)/Spi_slave/link/spi_link_slave.c
SRCSC += $(LIB_ROOT_DIR)/Time_counter/Time_counter.c

SRCSC += $(LIB_ROOT_DIR)/NRf_platform/hal/mcu/nrf52/hal_ll_nrf528xx_mutex.c
SRCSC += $(LIB_ROOT_DIR)/NRf_platform/hal/mcu/nrf52/hal_ll_nrf528xx_spi.c

SRCSC += $(LIB_ROOT_DIR)/NRf_platform/middleware/halsep/hal_mcu_mutex.c
SRCSC += $(LIB_ROOT_DIR)/NRf_platform/middleware/halsep/hal_mcu_spi.c
SRCSC += $(LIB_ROOT_DIR)/NRf_platform/middleware/memory/heap.c
SRCSC += $(LIB_ROOT_DIR)/NRf_platform/middleware/memory/link_list.c
SRCSC += $(LIB_ROOT_DIR)/NRf_platform/middleware/utils/dl_crc32.c
#SRCSC += $(LIB_ROOT_DIR)/NRf_platform/middleware/drivers/spi/link/spi_link_slave.c

SRCSCXX += $(LIB_ROOT_DIR)/Fifo_buffer/Fifo_buffer.cpp
SRCSCXX += $(LIB_ROOT_DIR)/EEPROM/EEPROM.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/LEDDevice.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/LEDDevice-Remote.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/LEDEffect.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/LEDEffect-BatteryStatus.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/LEDEffect-Bluetooth-Pairing-Defy.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/LEDEffect-Rainbow-Defy.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/LEDEffect-SolidColor-Defy.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/LEDEffect-Stalker-Defy.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/LEDLayers.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/LEDManager.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/palette/LEDPalette.cpp
SRCSCXX += $(LIB_ROOT_DIR)/NeuronLedLibrary/palette/LEDPaletteRGBW.cpp

SRCSCXX += $(LIB_ROOT_DIR)/Spi_slave/Spi_slave.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Spi_slave/SpiPort.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Status_leds/Status_leds.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Watchdog_timer/Watchdog_timer.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Twi_master/Twi_master.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Wire/Wire.cpp
SRCSCXX += $(LIB_ROOT_DIR)/UpgradeKeyscanner/src/KeyScannerFlasher.cpp
SRCSCXX += $(LIB_ROOT_DIR)/UpgradeKeyscanner/src/Upgrade.cpp
SRCSCXX += $(LIB_ROOT_DIR)/CRC/CRC_wrapper.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Battery_manager/Battery.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Ble_manager/Ble_manager.cpp
SRCSCXX += $(LIB_ROOT_DIR)/RF_manager/Radio_manager.cpp
SRCSCXX += $(LIB_ROOT_DIR)/utils/Timer/Timer.cpp

# SDK
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/ble/ble_advertising/ble_advertising.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/ble/ble_link_ctx_manager/ble_link_ctx_manager.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/ble/ble_services/ble_bas/ble_bas.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/ble/ble_services/ble_dis/ble_dis.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/ble/ble_services/ble_hids/ble_hids.c
SRCSC += $(wildcard $(SDK_NRF5_SDK_ROOT_DIR)/components/ble/common/*.c)
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/ble/nrf_ble_gatt/nrf_ble_gatt.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/ble/nrf_ble_qwr/nrf_ble_qwr.c
SRCSC += $(wildcard $(SDK_NRF5_SDK_ROOT_DIR)/components/ble/peer_manager/*.c)

SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/atomic/nrf_atomic.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/atomic_fifo/nrf_atfifo.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/atomic_flags/nrf_atflags.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/balloc/nrf_balloc.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/experimental_section_vars/nrf_section_iter.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/fds/fds.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/fstorage/nrf_fstorage.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/fstorage/nrf_fstorage_nvmc.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/fstorage/nrf_fstorage_sd.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/memobj/nrf_memobj.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/pwr_mgmt/nrf_pwr_mgmt.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/strerror/nrf_strerror.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/scheduler/app_scheduler.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/timer/app_timer2.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/timer/drv_rtc.c

SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/sortlist/nrf_sortlist.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/util/app_error.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/util/app_error_handler_gcc.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/util/app_error_weak.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/util/app_util_platform.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/util/nrf_assert.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/softdevice/common/nrf_sdh.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/softdevice/common/nrf_sdh_ble.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/softdevice/common/nrf_sdh_soc.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/external/fprintf/nrf_fprintf.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/external/fprintf/nrf_fprintf_format.c

SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/integration/nrfx/legacy/nrf_drv_clock.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/integration/nrfx/legacy/nrf_drv_power.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/integration/nrfx/legacy/nrf_drv_spis.c

SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/src/nrfx_clock.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/src/nrfx_power.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/src/nrfx_ppi.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/src/nrfx_spis.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/src/nrfx_timer.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/src/nrfx_twim.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/src/prs/nrfx_prs.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/src/nrfx_pwm.c

SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/hal/nrf_nvmc.c

# UART communication and NRF_LOG.
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/ringbuf/nrf_ringbuf.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/integration/nrfx/legacy/nrf_drv_uart.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/src/nrfx_uart.c
SRCSC += $(SDK_NRF5_SDK_ROOT_DIR)/modules/nrfx/drivers/src/nrfx_uarte.c
SRCSC += $(wildcard $(SDK_NRF5_SDK_ROOT_DIR)/components/libraries/log/src/*.c)

# Keyboard API
SRCSC += $(KEYBOARD_API_ROOT_DIR)/falsep/kbd_base.c
SRCSC += $(KEYBOARD_API_ROOT_DIR)/interfaces/kbd_if.c
SRCSC += $(KEYBOARD_API_ROOT_DIR)/modules/kbd_if_manager.c
SRCSC += $(KEYBOARD_API_ROOT_DIR)/keyboard_api.c

# Kaleidoscope FAL (Framework Abstraction Layer)
SRCSCXX += $(KALEIDOSCOPE_ADAPTER_ROOT_DIR)/fal/ll/kbdfal_ll_base.cpp
SRCSCXX += $(KALEIDOSCOPE_ADAPTER_ROOT_DIR)/plugins/KbdInterface.cpp
SRCSCXX += $(KALEIDOSCOPE_ADAPTER_ROOT_DIR)/plugins/LEDControlDygma.cpp

# Kaleidoscope
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/device/dygma/keyboardManager/universalModules/bootloader_util.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/device/dygma/keyboardManager/universalModules/Hand.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/device/dygma/keyboardManager/universalModules/Focus.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/device/dygma/keyboardManager/KeyboardManager.cpp

SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/key_events.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/layers.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/DynamicMacros.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/DynamicSuperKeys.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/EEPROM-Keymap.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/EEPROM-Settings.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/EEPROM-Settings/crc.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/FocusSerial.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/HostPowerManagement.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/IdleLEDsDefy.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/LayerFocus.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/LEDControl/LEDUtils.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/MouseKeys.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/MouseKeys/MouseWrapper.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/OneShot.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/plugin/Qukeys.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope/Runtime.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope_internal/device.cpp
SRCSCXX += $(KALEIDOSCOPE_ROOT_DIR)/src/kaleidoscope_internal/LEDModeManager.cpp

SRCSCXX += $(LIB_ROOT_DIR)/Communications/src/device/neuron/common/Communication_model.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Communications/src/device/neuron/common/Communications_side.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Communications/src/device/neuron/defyN2/com_models/Communication_model_ble.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Communications/src/device/neuron/defyN2/com_models/Communication_model_rf.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Communications/src/device/neuron/defyN2/com_models/Communication_model_wired.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Communications/src/device/neuron/defyN2/Communications_rf_pipe.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Communications/src/device/neuron/defyN2/CommunicationsN2.cpp
SRCSCXX += $(LIB_ROOT_DIR)/Communications/src/device/neuron/defyN2/CommunicationsN2_side.cpp

SRCSCXX += $(LIB_ROOT_DIR)/Communications/src/Communications_protocol_rf.cpp

# Keyboardio HID
INCDIR += -I$(KEYBOARDIO_HID_ROOT_DIR)/src/
SRCSCXX += $(KEYBOARDIO_HID_ROOT_DIR)/src/MultiReport/ConsumerControl.cpp
SRCSCXX += $(KEYBOARDIO_HID_ROOT_DIR)/src/MultiReport/Keyboard.cpp
SRCSCXX += $(KEYBOARDIO_HID_ROOT_DIR)/src/MultiReport/Mouse.cpp
SRCSCXX += $(KEYBOARDIO_HID_ROOT_DIR)/src/MultiReport/RawHID.cpp
SRCSCXX += $(KEYBOARDIO_HID_ROOT_DIR)/src/MultiReport/SystemControl.cpp
SRCSCXX += $(KEYBOARDIO_HID_ROOT_DIR)/src/hidDefy.cpp
SRCSCXX += $(KEYBOARDIO_HID_ROOT_DIR)/src/HIDReportObserver.cpp

#-------------------------------------------------------------------------------
# Main firmware defines
#-------------------------------------------------------------------------------

DEFINES += -DCOMPILE_DEFY_KEYBOARD=1

# Defy Neuron version
DEFINES += -DDEFY_NEURON_FW_VERSION=\"v2.1.1-beta.2\"

# Defy firmware package version - Neuron + Keyscanner + RFGW
ifdef DEFY_FW_VERSION
    DEFINES += -DDEFY_FW_VERSION=\"${DEFY_FW_VERSION}\"
else
    DEFINES += -DDEFY_FW_VERSION=\"v2.1.1-alpha\"			# Fixed "alpha" value to recognize local builds
endif

DEFINES += -DBOARD_VENDORID=0x35EF
DEFINES += -DBOARD_MANUFACTURER=\"DYGMA\"

DEFINES += -DBOARD_PRODUCTID=0x0012
DEFINES += -DBOARD_PRODUCT=\"DEFY\"
DEFINES += -DUSB_PRODUCT=\"DEFY\"
DEFINES += -DKALEIDOSCOPE_HARDWARE_H=\"kaleidoscope/device/dygma/keyboardManager/KeyboardManager.h\"

DEFINES += -DKALEIDOSCOPE_LED_CONTROL_H=\"LEDControlDygma.h\"

DEFINES += -DEEPROM_EMULATION_SIZE=8192

DEFINES += -DBLE_DEVICE_NAME=\"Defy-BLE\"

DEFINES += -DHARDWARE_VERSION_NAME=\"Defy-wireless\"

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------

.PHONY: all release debug print_build_start print_build_end $(BINARY_OUTPUT) clean progr progd

all: release

release: COMMONFLAGS += -Os -s
#release: COMMONFLAGS += -O0 -g
release: print_build_start $(BINARY_OUTPUT) print_build_end

debug: COMMONFLAGS += -O1 -g
#debug: COMMONFLAGS += -O0 -g
debug: DEFINES += -DDEBUG -DDEBUG_NRF
debug: print_build_start $(BINARY_OUTPUT) print_build_end

print_build_start:
	@echo "Build process for $(APP_NAME) project in $(MODE) mode started ..."
	@echo "Compiling ..."

print_build_end:
	@echo "Build process for $(APP_NAME) project in $(MODE) mode finished."

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),progr)
ifneq ($(MAKECMDGOALS),progd)

include $(PLATFORM_BUILD_DIR)/MakeRulesCommon.mk

endif
endif
endif


$(BINARY_OUTPUT): $(OBJSC) $(OBJSCXX) $(OBJSA) $(OBJSa)
	@echo "Compiling done."
	@echo "Linking ..."
	$(CXX) -Xlinker -Map -Xlinker $@.map $(LFLAGS) -o $@.elf $(OBJSC) $(OBJSCXX) $(OBJSA) $(OBJSa) $(LIBS)
#	$(OBJDUMP) -D -S $@.elf > $@.lst
	@echo "Linking done."
	$(SIZE) -A $@.elf
	@echo "Creating application binaries ..."
	$(OBJCOPY) -O binary $@.elf $@.bin
	$(OBJCOPY) -O ihex $@.elf $@.hex
	@echo "Creating final application binary ..."
	python $(TOOLS_ROOT_DIR)/fw_package_builder.py $(RF_HOST_DEVICE_HEX) $@.hex $@_final.hex
	@echo "Creating application binaries done."

clean:
	@echo "Cleaning $(APP_NAME) ..."
	$(RM) $(MODE_DEBUG_DIR_NAME)
	$(RM) $(MODE_DEBUG_DIR_NAME)/$(APP_NAME).*
	$(RM) $(MODE_RELEASE_DIR_NAME)
	$(RM) $(MODE_RELEASE_DIR_NAME)/$(APP_NAME).*
	@echo "Cleaning done."
	

list: $(MODE_DEBUG_DIR_NAME)/$(APP_NAME).elf
	$(OBJDUMP) -D -S ./$(MODE_DEBUG_DIR_NAME)/$(APP_NAME).elf > ./$(MODE_DEBUG_DIR_NAME)/$(APP_NAME).lst

ddd:
	$(DDD) --debugger $(GDB) -x $(DDD_INIT_FILENAME) ./$(MODE_DEBUG_DIR_NAME)/$(APP_NAME).elf


#-------------------------------------------------------------------------------
# End of file
#-------------------------------------------------------------------------------
