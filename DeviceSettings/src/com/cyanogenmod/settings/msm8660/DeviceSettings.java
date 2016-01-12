/*
 * Copyright (C) 2012 The CyanogenMod Project
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

package com.cyanogenmod.settings.msm8660;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.preference.CheckBoxPreference;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceCategory;

public class DeviceSettings extends PreferenceActivity  {

    public static final String KEY_SWEEP2WAKE = "s2w";
    public static final String KEY_DT2W = "dt2w";
    public static final String KEY_DT2S = "dt2s";
    public static final String KEY_BLN_TIMEOUT = "bln_timeout";
    public static final String KEY_PANEL_UV = "panel_uv";
    public static final String KEY_LP_FLASH = "lp_flash";

    public static final String KEY_KEYS_CATEGORY = "category_touchkey";
    public static final String KEY_DISPLAY_CATEGORY = "category_display";
    public static final String KEY_MISC_CATEGORY = "category_misc";

    private CheckBoxPreference mSweep2Wake;
    private ListPreference mDoubleTap2Wake;
    private ListPreference mDoubleTap2Sleep;
    private ListPreference mBLNTimeout;

    private ListPreference mPanelUV;

    private CheckBoxPreference mLPFlash;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        addPreferencesFromResource(R.xml.main);

        mSweep2Wake = (CheckBoxPreference) findPreference(KEY_SWEEP2WAKE);
        mSweep2Wake.setEnabled(Sweep2Wake.isSupported());
        mSweep2Wake.setOnPreferenceChangeListener(new Sweep2Wake());

        mDoubleTap2Wake = (ListPreference) findPreference(KEY_DT2W);
        mDoubleTap2Wake.setEnabled(DoubleTap2Wake.isSupported());
        mDoubleTap2Wake.setOnPreferenceChangeListener(new DoubleTap2Wake());

        mDoubleTap2Sleep = (ListPreference) findPreference(KEY_DT2S);
        mDoubleTap2Sleep.setEnabled(DoubleTap2Sleep.isSupported());
        mDoubleTap2Sleep.setOnPreferenceChangeListener(new DoubleTap2Sleep());

        mBLNTimeout = (ListPreference) findPreference(KEY_BLN_TIMEOUT);
        mBLNTimeout.setEnabled(BLNTimeout.isSupported());
        mBLNTimeout.setOnPreferenceChangeListener(new BLNTimeout());

        mPanelUV = (ListPreference) findPreference(KEY_PANEL_UV);
        mPanelUV.setEnabled(PanelUV.isSupported());
        mPanelUV.setOnPreferenceChangeListener(new PanelUV());

        mLPFlash = (CheckBoxPreference) findPreference(KEY_LP_FLASH);
        mLPFlash.setEnabled(LPFlash.isSupported());
        mLPFlash.setOnPreferenceChangeListener(new LPFlash());

    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
}
