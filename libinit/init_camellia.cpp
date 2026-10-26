/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <libinit_dalvik_heap.h>
#include <libinit_variant.h>

#include "vendor_init.h"

static const variant_info_t camelliain_info = {
    .hwc_value = "",
    .sku_value = "",
    .vendor_sku_value = "camellia",

    .brand = "Redmi",
    .device = "camellia",
    .marketname = "Redmi Note 10T 5G",
    .model = "M2103K19I",
    .build_fingerprint = "Redmi/camellia_in/camellia:12/SP1A.210812.016/V14.0.6.0.TKSINXM:user/release-keys",

    .nfc = false,
};

static const variant_info_t camelliap_info = {
    .hwc_value = "",
    .sku_value = "",
    .vendor_sku_value = "camelliap",

    .brand = "POCO",
    .device = "camellia",
    .marketname = "POCO M3 Pro 5G",
    .model = "M2103K19PI",
    .build_fingerprint = "POCO/camellia_p_in/camellia:12/SP1A.210812.016/V14.0.6.0.TKSINXM:user/release-keys",

    .nfc = false,
};

static const std::vector<variant_info_t> variants = {
    camelliain_info,
    camelliap_info,
};

void vendor_load_properties() {
    search_variant(variants);
    set_dalvik_heap();
}
