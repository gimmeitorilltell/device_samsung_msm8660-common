/*
 * Copyright (C) 2015 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "PowerHAL"

#include <hardware/hardware.h>
#include <hardware/power.h>

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <utils/Log.h>

#include "power.h"

#define CPUFREQ_PATH "/sys/devices/system/cpu/cpu0/cpufreq/"
#define SCALING_GOVERNOR_PATH "/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"
#define INTERACTIVE_PATH "/sys/devices/system/cpu/cpufreq/interactive/"
#define ONDEMAND_PATH "/sys/devices/system/cpu/cpufreq/ondemand/"

#define GPU_GOVERNOR_PATH "/sys/class/kgsl/kgsl-3d0/pwrscale/trustzone/governor"
#define INPUT_BOOST_PATH "/sys/kernel/cpu_input_boost/"

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static int boostpulse_fd = -1;

static int current_power_profile = -1;
static int requested_power_profile = -1;

static char governor[20];

static int sysfs_read(char *path, char *s, int num_bytes)
{
    char buf[80];
    int count;
    int ret = 0;
    int fd = open(path, O_RDONLY);

    if (fd < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);

        return -1;
    }

    if ((count = read(fd, s, num_bytes - 1)) < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error writing to %s: %s\n", path, buf);

        ret = -1;
    } else {
        s[count] = '\0';
    }

    close(fd);

    return ret;
}

static int sysfs_write_str(char *path, char *s)
{
    char buf[80];
    int len;
    int ret = 0;
    int fd;

    fd = open(path, O_WRONLY);
    if (fd < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);
        return -1 ;
    }

    len = write(fd, s, strlen(s));
    if (len < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error writing to %s: %s\n", path, buf);
        ret = -1;
    }

    close(fd);

    return ret;
}

static int sysfs_write_int(char *path, int value)
{
    char buf[80];
    snprintf(buf, 80, "%d", value);
    return sysfs_write_str(path, buf);
}

static int get_scaling_governor() {
    if (sysfs_read(SCALING_GOVERNOR_PATH, governor,
                sizeof(governor)) == -1) {
        return -1;
    } else {
        // Strip newline at the end.
        int len = strlen(governor);

        len--;

        while (len >= 0 && (governor[len] == '\n' || governor[len] == '\r'))
            governor[len--] = '\0';
    }

    return 0;
}

static int is_profile_valid(int profile)
{
    return profile >= 0 && profile < PROFILE_MAX;
}

static void power_init(__attribute__((unused)) struct power_module *module)
{
    ALOGI("%s", __func__);
}

static int boostpulse_open()
{
    pthread_mutex_lock(&lock);
    if (boostpulse_fd < 0) {
        boostpulse_fd = open(INTERACTIVE_PATH "boostpulse", O_WRONLY);
    }
    pthread_mutex_unlock(&lock);

    return boostpulse_fd;
}

static void power_set_interactive(__attribute__((unused)) struct power_module *module, int on)
{
    if (!is_profile_valid(current_power_profile)) {
        ALOGD("%s: no power profile selected yet", __func__);
        return;
    }

    sysfs_write_int(INTERACTIVE_PATH "hispeed_freq",
                    interactive_profiles[current_power_profile].hispeed_freq);
    sysfs_write_int(INTERACTIVE_PATH "go_hispeed_load",
                    interactive_profiles[current_power_profile].go_hispeed_load);
    sysfs_write_str(INTERACTIVE_PATH "target_loads",
                    interactive_profiles[current_power_profile].target_loads);
}

static void set_power_profile(int profile)
{
    if (!is_profile_valid(profile)) {
        ALOGE("%s: unknown profile: %d", __func__, profile);
        return;
    }

    if (profile == current_power_profile)
        return;

    ALOGD("%s: setting profile %d", __func__, profile);

    if (get_scaling_governor() < 0) {
        ALOGE("Can't read scaling governor.");
    } else {
        if (strncmp(governor, "ondemand", 8) == 0) {
                sysfs_write_int(INPUT_BOOST_PATH "enabled",
                                ondemand_profiles[profile].input_boost_on);
                sysfs_write_int(ONDEMAND_PATH "up_threshold",
                                ondemand_profiles[profile].up_threshold);
                sysfs_write_int(ONDEMAND_PATH "io_is_busy",
                                ondemand_profiles[profile].io_is_busy);
                sysfs_write_int(ONDEMAND_PATH "sampling_down_factor",
                                ondemand_profiles[profile].sampling_down_factor);
                sysfs_write_int(ONDEMAND_PATH "down_differential",
                                ondemand_profiles[profile].down_differential);
                sysfs_write_int(ONDEMAND_PATH "up_threshold_multi_core",
                                ondemand_profiles[profile].up_threshold_multi_core);
                sysfs_write_int(ONDEMAND_PATH "down_differential_multi_core",
                                ondemand_profiles[profile].down_differential_multi_core);
                sysfs_write_int(ONDEMAND_PATH "optimal_freq",
                                ondemand_profiles[profile].optimal_freq);
                sysfs_write_int(ONDEMAND_PATH "sync_freq",
                                ondemand_profiles[profile].sync_freq);
                sysfs_write_int(ONDEMAND_PATH "up_threshold_any_cpu_load",
                                ondemand_profiles[profile].up_threshold_any_cpu_load);
                sysfs_write_int(ONDEMAND_PATH "sampling_rate",
                                ondemand_profiles[profile].sampling_rate);
                sysfs_write_int(CPUFREQ_PATH "scaling_max_freq",
                                ondemand_profiles[profile].scaling_max_freq);
                sysfs_write_int(CPUFREQ_PATH "scaling_min_freq",
                                ondemand_profiles[profile].scaling_min_freq);
                sysfs_write_str(INPUT_BOOST_PATH "ib_freqs",
                                ondemand_profiles[profile].input_boost_freqs);
                sysfs_write_str(GPU_GOVERNOR_PATH,
                                ondemand_profiles[profile].gpu_governor);
        } else if (strncmp(governor, "interactive", 11) == 0) {
                sysfs_write_int(INPUT_BOOST_PATH,
                                interactive_profiles[profile].input_boost_on);
                sysfs_write_int(INTERACTIVE_PATH "boost",
                                interactive_profiles[profile].boost);
                sysfs_write_int(INTERACTIVE_PATH "boostpulse_duration",
                                interactive_profiles[profile].boostpulse_duration);
                sysfs_write_int(INTERACTIVE_PATH "go_hispeed_load",
                                interactive_profiles[profile].go_hispeed_load);
                sysfs_write_int(INTERACTIVE_PATH "hispeed_freq",
                                interactive_profiles[profile].hispeed_freq);
                sysfs_write_int(INTERACTIVE_PATH "io_is_busy",
                                interactive_profiles[profile].io_is_busy);
                sysfs_write_int(INTERACTIVE_PATH "min_sample_time",
                                interactive_profiles[profile].min_sample_time);
                sysfs_write_int(INTERACTIVE_PATH "sampling_down_factor",
                                interactive_profiles[profile].sampling_down_factor);
                sysfs_write_str(INTERACTIVE_PATH "target_loads",
                                interactive_profiles[profile].target_loads);
                sysfs_write_int(CPUFREQ_PATH "scaling_max_freq",
                                interactive_profiles[profile].scaling_max_freq);
                sysfs_write_int(CPUFREQ_PATH "scaling_min_freq",
                                interactive_profiles[profile].scaling_min_freq);
                sysfs_write_str(INPUT_BOOST_PATH "ib_freqs",
                                interactive_profiles[profile].input_boost_freqs);
                sysfs_write_str(GPU_GOVERNOR_PATH,
                                interactive_profiles[profile].gpu_governor);
        }
    }

    current_power_profile = profile;
}

static void power_hint(__attribute__((unused)) struct power_module *module,
                       power_hint_t hint, void *data)
{
    char buf[80];
    int len;

    switch (hint) {
    case POWER_HINT_INTERACTION:
        if (!is_profile_valid(current_power_profile)) {
            ALOGD("%s: no power profile selected yet", __func__);
            return;
        }

        if (!interactive_profiles[current_power_profile].boostpulse_duration)
            return;

        if (boostpulse_open() >= 0) {
            snprintf(buf, sizeof(buf), "%d", 1);
            len = write(boostpulse_fd, &buf, sizeof(buf));
            if (len < 0) {
                strerror_r(errno, buf, sizeof(buf));
                ALOGE("Error writing to boostpulse: %s\n", buf);

                pthread_mutex_lock(&lock);
                close(boostpulse_fd);
                boostpulse_fd = -1;
                pthread_mutex_unlock(&lock);
            }
        }
        break;
    case POWER_HINT_SET_PROFILE:
        pthread_mutex_lock(&lock);
        set_power_profile(*(int32_t *)data);
        pthread_mutex_unlock(&lock);
        break;
    case POWER_HINT_LOW_POWER:
        /* This hint is handled by the framework */
        break;
    default:
        break;
    }
}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

static int get_feature(__attribute__((unused)) struct power_module *module,
                       feature_t feature)
{
    if (feature == POWER_FEATURE_SUPPORTED_PROFILES) {
        return PROFILE_MAX;
    }
    return -1;
}

struct power_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = POWER_MODULE_API_VERSION_0_2,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = POWER_HARDWARE_MODULE_ID,
        .name = "Samsung MSM8660 Power HAL",
        .author = "The CyanogenMod Project",
        .methods = &power_module_methods,
    },

    .init = power_init,
    .setInteractive = power_set_interactive,
    .powerHint = power_hint,
    .getFeature = get_feature
};
