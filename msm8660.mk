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

# Overlay
DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.bluetooth_le.xml:system/etc/permissions/android.hardware.bluetooth_le.xml \
    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
    frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
    frameworks/native/data/etc/android.hardware.ethernet.xml:system/etc/permissions/android.hardware.ethernet.xml \
    frameworks/native/data/etc/android.hardware.nfc.xml:system/etc/permissions/android.hardware.nfc.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/android.software.sip.voip.xml:system/etc/permissions/android.software.sip.voip.xml \
    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:system/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.compass.xml:system/etc/permissions/android.hardware.sensor.compass.xml \
    frameworks/native/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
    frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/native/data/etc/android.hardware.usb.host.xml:system/etc/permissions/android.hardware.usb.host.xml \
    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml \
    frameworks/native/data/etc/com.android.nfc_extras.xml:system/etc/permissions/com.android.nfc_extras.xml \
    frameworks/native/data/etc/com.nxp.mifare.xml:system/etc/permissions/com.nxp.mifare.xml \
    frameworks/native/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml

# System properties
PRODUCT_PROPERTY_OVERRIDES += \
    wifi.interface=wlan0

PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    persist.sys.usb.config=mtp

PRODUCT_PROPERTY_OVERRIDES += \
    ro.vendor.extension_library=/system/lib/libqc-opt.so

PRODUCT_PROPERTY_OVERRIDES += \
    debug.mdpcomp.maxlayer=3 \
    debug.hwc.dynThreshold=1.9 \
    ro.opengles.version=131072

PRODUCT_PROPERTY_OVERRIDES += \
    lpa.decode=false \
    qcom.hw.aac.encoder=true \
    camera2.portability.force_api=1

PRODUCT_PROPERTY_OVERRIDES += \
    persist.rild.nitz_plmn="" \
    persist.rild.nitz_long_ons_0="" \
    persist.rild.nitz_long_ons_1="" \
    persist.rild.nitz_long_ons_2="" \
    persist.rild.nitz_long_ons_3="" \
    persist.rild.nitz_short_ons_0="" \
    persist.rild.nitz_short_ons_1="" \
    persist.rild.nitz_short_ons_2="" \
    persist.rild.nitz_short_ons_3=""

# RIL Class
PRODUCT_PROPERTY_OVERRIDES += \
    ro.telephony.ril_class=SamsungMSM8660RIL

# Ramdisk
PRODUCT_PACKAGES += \
    fstab.qcom \
    init.qcom.efs.sync.sh \
    init.qcom.mdm_links.sh \
    init.qcom.modem_links.sh \
    init.qcom.rc \
    init.qcom.syspart_fixup.sh \
    lpm.rc \
    ueventd.qcom.rc

# Audio
PRODUCT_PACKAGES += \
    audio.a2dp.default \
    audio.usb.default \
    audio_policy.conf \
    audio_policy.msm8660 \
    audio.primary.msm8660 \
    libaudio-resampler \
    libaudioutils

# Camera
PRODUCT_PACKAGES += \
    camera.msm8660

# Chromecast
PRODUCT_PROPERTY_OVERRIDES += \
    ro.enable.chromecast.mirror=true

# Display
PRODUCT_PACKAGES += \
    copybit.msm8660 \
    gralloc.msm8660 \
    hwcomposer.msm8660 \
    libgenlock \
    memtrack.msm8660

# ES File Explorer
PRODUCT_COPY_FILES += \
    device/samsung/msm8660-common/es.apk:system/app/ES/es.apk

# GalaxyS2Settings
PRODUCT_PACKAGES += \
    GalaxyS2Settings \
    SamsungServiceMode

# GPS
PRODUCT_PACKAGES += \
    gps.msm8660

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/gps/gps.conf:system/etc/gps.conf

# Keylayouts
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/keylayout/8660_handset.kl:system/usr/keylayout/8660_handset.kl\
    $(LOCAL_PATH)/keylayout/ffa-keypad.kl:system/usr/keylayout/ffa-keypad.kl \
    $(LOCAL_PATH)/keylayout/fluid-keypad.kl:system/usr/keylayout/fluid-keypad.kl \
    $(LOCAL_PATH)/keylayout/sec_touchkey.kl:system/usr/keylayout/sec_touchkey.kl \
    $(LOCAL_PATH)/keylayout/Vendor_04e8_Product_7021.kl:system/usr/keylayout/Vendor_04e8_Product_7021.kl \
    $(LOCAL_PATH)/configs/excluded-input-devices.xml:system/etc/excluded-input-devices.xml

# Lights
PRODUCT_PACKAGES += \
    lights.msm8660

# Media
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/media_codecs.xml:system/etc/media_codecs.xml \
    $(LOCAL_PATH)/configs/media_profiles.xml:system/etc/media_profiles.xml

PRODUCT_COPY_FILES += \
    frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:system/etc/media_codecs_google_audio.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_telephony.xml:system/etc/media_codecs_google_telephony.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_video.xml:system/etc/media_codecs_google_video.xml

# NFC
PRODUCT_PACKAGES += \
    libnfc \
    libnfc_jni \
    Nfc \
    Tag \
    com.android.nfc_extras

ifeq ($(TARGET_BUILD_VARIANT),user)
    NFCEE_ACCESS_PATH := $(LOCAL_PATH)/configs/nfcee_access.xml
else
    NFCEE_ACCESS_PATH := $(LOCAL_PATH)/configs/nfcee_access_debug.xml
endif
PRODUCT_COPY_FILES += \
    $(NFCEE_ACCESS_PATH):system/etc/nfcee_access.xml

# OMX
PRODUCT_PACKAGES += \
    libdashplayer \
    libOmxVdec \
    libOmxVenc \
    libOmxAacEnc \
    libOmxAmrEnc \
    libOmxEvrcEnc \
    libOmxQcelp13Enc \
    libstagefrighthw \
    qcmediaplayer

PRODUCT_BOOT_JARS += \
    qcmediaplayer

# Package generation
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/test_radio_version.sh:/system/etc/test_radio_version.sh

# Power HAL
PRODUCT_PACKAGES += \
    power.msm8660

# Torch
PRODUCT_PACKAGES += \
    Torch

# USB
PRODUCT_PACKAGES += \
    com.android.future.usb.accessory

# Wifi
PRODUCT_PACKAGES += \
    dhcpcd.conf \
    hostapd \
    hostapd_default.conf \
    libnetcmdiface \
    libwpa_client \
    wpa_supplicant \
    wpa_supplicant.conf

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/p2p_supplicant_overlay.conf:system/etc/wifi/p2p_supplicant_overlay.conf \
    $(LOCAL_PATH)/configs/wpa_supplicant_overlay.conf:system/etc/wifi/wpa_supplicant_overlay.conf

# Doze
PRODUCT_PACKAGES += \
    SamsungDoze

# TWRP
PRODUCT_COPY_FILES += \
    device/samsung/msm8660-common/recovery/root/etc/twrp.fstab:recovery/root/etc/twrp.fstab 

#HW Hack
PRODUCT_PROPERTY_OVERRIDES += \
    persist.hwc.mdpcomp.enable=false

# Common Qualcomm hardware
$(call inherit-product, device/samsung/qcom-common/qcom-common.mk)
