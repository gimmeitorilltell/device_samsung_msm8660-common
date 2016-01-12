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

enum {
    PROFILE_POWER_SAVE = 0,
    PROFILE_BALANCED,
    PROFILE_HIGH_PERFORMANCE,
    PROFILE_BIAS_POWER,
    PROFILE_BIAS_PERFORMANCE,
    PROFILE_MAX
};

typedef struct ondemand_governor_settings {
    int input_boost_on;
    int up_threshold;
    int io_is_busy;
    int sampling_down_factor;
    int down_differential;
    int up_threshold_multi_core;
    int down_differential_multi_core;
    int optimal_freq;
    int sync_freq;
    int up_threshold_any_cpu_load;
    int sampling_rate;
    int scaling_max_freq;
    int scaling_min_freq;
    char *input_boost_freqs;
    char *gpu_governor;
} ondemand_power_profile;

static ondemand_power_profile ondemand_profiles[PROFILE_MAX] = {
    [PROFILE_POWER_SAVE] = {
        .input_boost_on = 0,
        .up_threshold = 90,
        .io_is_busy = 0,
        .sampling_down_factor = 2,
        .down_differential = 10,
        .up_threshold_multi_core = 70,
        .down_differential_multi_core = 3,
        .optimal_freq = 486000,
        .sync_freq = 540000,
        .up_threshold_any_cpu_load = 80,
        .sampling_rate = 50000,
        .scaling_max_freq = 1026000,
        .scaling_min_freq = 192000,
        .input_boost_freqs = "756000 540000",
        .gpu_governor = "ondemand",
    },
    [PROFILE_BIAS_POWER] = {
        .input_boost_on = 1,
        .up_threshold = 90,
        .io_is_busy = 1,
        .sampling_down_factor = 2,
        .down_differential = 10,
        .up_threshold_multi_core = 70,
        .down_differential_multi_core = 3,
        .optimal_freq = 918000,
        .sync_freq = 1026000,
        .up_threshold_any_cpu_load = 80,
        .sampling_rate = 50000,
        .scaling_max_freq = 1026000,
        .scaling_min_freq = 192000,
        .input_boost_freqs = "972000 864000",
        .gpu_governor = "ondemand",
    },
    [PROFILE_BALANCED] = {
        .input_boost_on = 1,
        .up_threshold = 90,
        .io_is_busy = 1,
        .sampling_down_factor = 2,
        .down_differential = 10,
        .up_threshold_multi_core = 70,
        .down_differential_multi_core = 3,
        .optimal_freq = 918000,
        .sync_freq = 1026000,
        .up_threshold_any_cpu_load = 80,
        .sampling_rate = 50000,
        .scaling_max_freq = 1512000,
        .scaling_min_freq = 384000,
        .input_boost_freqs = "1242000 1026000",
        .gpu_governor = "ondemand",
    },
    [PROFILE_BIAS_PERFORMANCE] = {
        .input_boost_on = 1,
        .up_threshold = 90,
        .io_is_busy = 1,
        .sampling_down_factor = 2,
        .down_differential = 10,
        .up_threshold_multi_core = 70,
        .down_differential_multi_core = 3,
        .optimal_freq = 918000,
        .sync_freq = 1026000,
        .up_threshold_any_cpu_load = 80,
        .sampling_rate = 50000,
        .scaling_max_freq = 1512000,
        .scaling_min_freq = 756000,
        .input_boost_freqs = "1242000 1026000",
        .gpu_governor = "ondemand",
    },
    [PROFILE_HIGH_PERFORMANCE] = {
        .input_boost_on = 0,
        .up_threshold = 90,
        .io_is_busy = 1,
        .sampling_down_factor = 2,
        .down_differential = 10,
        .up_threshold_multi_core = 70,
        .down_differential_multi_core = 3,
        .optimal_freq = 1512000,
        .sync_freq = 1512000,
        .up_threshold_any_cpu_load = 80,
        .sampling_rate = 50000,
        .scaling_max_freq = 1512000,
        .scaling_min_freq = 1512000,
        .input_boost_freqs = "1512000 1512000",
        .gpu_governor = "performance",
    },
};

typedef struct interactive_governor_settings {
    int input_boost_on;
    int boost;
    int boostpulse_duration;
    int go_hispeed_load;
    int hispeed_freq;
    int io_is_busy;
    int min_sample_time;
    int sampling_down_factor;
    char *target_loads;
    int scaling_max_freq;
    int scaling_min_freq;
    char *input_boost_freqs;
    char *gpu_governor;
} interactive_power_profile;

static interactive_power_profile interactive_profiles[PROFILE_MAX] = {
    [PROFILE_POWER_SAVE] = {
        .input_boost_on = 1,
        .boost = 0,
        .boostpulse_duration = 0,
        .go_hispeed_load = 90,
        .hispeed_freq = 486000,
        .io_is_busy = 0,
        .min_sample_time = 60000,
        .sampling_down_factor = 100000,
        .target_loads = "95",
        .scaling_max_freq = 1026000,
        .scaling_min_freq = 192000,
        .input_boost_freqs = "756000 540000",
        .gpu_governor = "ondemand",
    },
    [PROFILE_BIAS_POWER] = {
        .input_boost_on = 1,
        .boost = 0,
        .boostpulse_duration = 0,
        .go_hispeed_load = 90,
        .hispeed_freq = 486000,
        .io_is_busy = 0,
        .min_sample_time = 60000,
        .sampling_down_factor = 100000,
        .target_loads = "95",
        .scaling_max_freq = 1026000,
        .scaling_min_freq = 192000,
        .input_boost_freqs = "972000 864000",
        .gpu_governor = "ondemand",
    },
    [PROFILE_BALANCED] = {
        .input_boost_on = 1,
        .boost = 0,
        .boostpulse_duration = 80000,
        .go_hispeed_load = 90,
        .hispeed_freq = 918000,
        .io_is_busy = 1,
        .min_sample_time = 80000,
        .sampling_down_factor = 100000,
        .target_loads = "90",
        .scaling_max_freq = 1512000,
        .scaling_min_freq = 384000,
        .input_boost_freqs = "1242000 1026000",
        .gpu_governor = "ondemand",
    },
    [PROFILE_BIAS_PERFORMANCE] = {
        .input_boost_on = 1,
        .boost = 0,
        .boostpulse_duration = 80000,
        .go_hispeed_load = 90,
        .hispeed_freq = 918000,
        .io_is_busy = 1,
        .min_sample_time = 80000,
        .sampling_down_factor = 100000,
        .target_loads = "90",
        .scaling_max_freq = 1512000,
        .scaling_min_freq = 756000,
        .input_boost_freqs = "1242000 1026000",
        .gpu_governor = "ondemand",
    },
    [PROFILE_HIGH_PERFORMANCE] = {
        .input_boost_on = 0,
        .boost = 1,
        .boostpulse_duration = 0, /* prevent unnecessary write */
        .go_hispeed_load = 50,
        .hispeed_freq = 1242000,
        .io_is_busy = 1,
        .min_sample_time = 60000,
        .sampling_down_factor = 100000,
        .target_loads = "80",
        .scaling_max_freq = 1512000,
        .scaling_min_freq = 384000,
        .input_boost_freqs = "1512000 1512000",
        .gpu_governor = "performance",
    },
};
