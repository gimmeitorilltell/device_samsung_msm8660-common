# Copyright (C) 2012 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# inherit from qcom-common
-include device/samsung/qcom-common/BoardConfigCommon.mk

TARGET_SPECIFIC_HEADER_PATH := device/samsung/msm8660-common/include

# Platform
TARGET_BOARD_PLATFORM := msm8660
TARGET_BOARD_PLATFORM_GPU := qcom-adreno200
TARGET_BUILD_VARIANT := userdebug

# Architecture
TARGET_CPU_VARIANT := scorpion

# Audio
BOARD_HAVE_SAMSUNG_AUDIO := true
BOARD_USES_LEGACY_ALSA_AUDIO := true
AUDIO_FEATURE_ENABLED_COMPRESS_VOIP := false
AUDIO_FEATURE_ENABLED_INCALL_MUSIC := false
AUDIO_FEATURE_ENABLED_PROXY_DEVICE := false
COMMON_GLOBAL_CFLAGS += -DLEGACY_QCOM_VOICE
USE_LEGACY_AUDIO_POLICY := true

# Bluetooth
BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_BCM := true
BOARD_BLUEDROID_VENDOR_CONF := device/samsung/msm8660-common/bluetooth/vnd_msm8660.txt

# Camera
BOARD_CAMERA_USE_MM_HEAP := true
COMMON_GLOBAL_CFLAGS += -DQCOM_BSP_CAMERA_ABI_HACK
COMMON_GLOBAL_CFLAGS += -DSAMSUNG_CAMERA_HARDWARE

# Charger
BOARD_BATTERY_DEVICE_NAME := "battery"
BOARD_CHARGING_MODE_BOOTING_LPM := /sys/class/power_supply/battery/batt_lp_charging

# CMHW
BOARD_HARDWARE_CLASS += device/samsung/msm8660-common/cmhw

# Dex-preoptimization
ifeq ($(HOST_OS),linux)
  ifeq ($(WITH_DEXPREOPT),)
    WITH_DEXPREOPT := true
    WITH_DEXPREOPT_COMP := false
  endif
endif
DONT_DEXPREOPT_PREBUILTS := true

# Display
BOARD_USES_LEGACY_MMAP := true
NUM_FRAMEBUFFER_SURFACE_BUFFERS := 3
TARGET_BOOTANIMATION_PRELOAD := true
TARGET_DISPLAY_INSECURE_MM_HEAP := true
TARGET_DISPLAY_USE_RETIRE_FENCE := true
TARGET_NO_INITLOGO := true

# Dlmalloc
MALLOC_IMPL := dlmalloc

# External apps on SD
TARGET_EXTERNAL_APPS = sdcard0

# Fonts
EXTENDED_FONT_FOOTPRINT := true

# GPS
BOARD_HAVE_NEW_QC_GPS := true
TARGET_GPS_HAL_PATH := device/samsung/msm8660-common/gps

# Lights
TARGET_PROVIDES_LIBLIGHT := true

# Logging
TARGET_USES_LOGD := false

# Media
TARGET_ENABLE_QC_AV_ENHANCEMENTS := true
TARGET_NO_ADAPTIVE_PLAYBACK := true

# Qualcomm support
COMMON_GLOBAL_CFLAGS += -DQCOM_BSP
TARGET_USES_QCOM_BSP := true

# Recovery
TARGET_RECOVERY_DEVICE_DIRS := device/samsung/msm8660-common
TARGET_RECOVERY_FSTAB := device/samsung/msm8660-common/rootdir/etc/fstab.qcom
TARGET_USERIMAGES_USE_F2FS := true

# Releasetools
TARGET_RELEASETOOLS_EXTENSIONS := device/samsung/msm8660-common

# RIL
BOARD_RIL_CLASS := ../../../device/samsung/msm8660-common/ril
BOARD_PROVIDES_LIBRIL := true

# SELinux
include device/qcom/sepolicy/sepolicy.mk
BOARD_SEPOLICY_DIRS += device/samsung/msm8660-common/sepolicy

# TWRP
DEVICE_RESOLUTION := 480x800
RECOVERY_GRAPHICS_USE_LINELENGTH := true
RECOVERY_SDCARD_ON_DATA := true
TARGET_RECOVERY_PIXEL_FORMAT := "RGBX_8888"
TW_BRIGHTNESS_PATH := "/sys/class/leds/lcd-backlight/brightness"
TW_EXTERNAL_STORAGE_PATH := "/external_sd"
TW_EXTERNAL_STORAGE_MOUNT_POINT := "external_sd"
TW_EXTERNAL_STORAGE_PATH := "/usb-otg"
TW_EXTERNAL_STORAGE_MOUNT_POINT := "usb-otg"
TW_EXCLUDE_SUPERSU := true
TW_HAS_DOWNLOAD_MODE := true
TW_NO_CPU_TEMP := true
TW_NO_REBOOT_BOOTLOADER := true
TW_INCLUDE_CRYPTO := true
TW_CRYPTO_FS_TYPE := "ext4"
TW_CRYPTO_REAL_BLKDEV := "/dev/block/mmcblk0p28"
TW_CRYPTO_MNT_POINT := "/data"
TW_CRYPTO_FS_OPTIONS := "noauto_da_alloc"
TW_CRYPTO_FS_FLAGS := "0x00000006"
TW_CRYPTO_KEY_LOC := "/efs/metadata"
TW_MAX_BRIGHTNESS := 255
TW_THEME := portrait_mdpi

# Wifi related defines
BOARD_HAVE_SAMSUNG_WIFI := true
BOARD_WLAN_DEVICE := bcmdhd
BOARD_HOSTAPD_DRIVER := NL80211
BOARD_HOSTAPD_PRIVATE_LIB := lib_driver_cmd_${BOARD_WLAN_DEVICE}
BOARD_WPA_SUPPLICANT_DRIVER := NL80211
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_${BOARD_WLAN_DEVICE}
WPA_SUPPLICANT_VERSION := VER_0_8_X
WIFI_BAND := 802_11_ABG
WIFI_DRIVER_FW_PATH_PARAM   := "/sys/module/dhd/parameters/firmware_path"
WIFI_DRIVER_FW_PATH_STA     := "/system/etc/wifi/bcmdhd_sta.bin"
WIFI_DRIVER_FW_PATH_AP      := "/system/etc/wifi/bcmdhd_apsta.bin"
WIFI_DRIVER_FW_PATH_P2P     := "/system/etc/wifi/bcmdhd_p2p.bin"
WIFI_DRIVER_MODULE_PATH     := "/system/lib/modules/dhd.ko"
WIFI_DRIVER_MODULE_NAME     := "dhd"
WIFI_DRIVER_MODULE_ARG      := "firmware_path=/system/etc/wifi/bcmdhd_sta.bin nvram_path=/system/etc/wifi/nvram_net.txt"
WIFI_DRIVER_MODULE_AP_ARG   := "firmware_path=/system/etc/wifi/bcmdhd_apsta.bin nvram_path=/system/etc/wifi/nvram_net.txt"

# Vold
BOARD_VOLD_EMMC_SHARES_DEV_MAJOR := true
TARGET_USE_CUSTOM_LUN_FILE_PATH := /sys/devices/platform/msm_hsusb/gadget/lun%d/file
