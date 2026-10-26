#!/usr/bin/env -S PYTHONPATH=../../../tools/extract-utils python3
#
# SPDX-FileCopyrightText: 2024 The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

from extract_utils.fixups_blob import (
    blob_fixup,
    blob_fixups_user_type,
)
from extract_utils.fixups_lib import (
    lib_fixup_remove,
    lib_fixups,
    lib_fixups_user_type,
)
from extract_utils.main import (
    ExtractUtils,
    ExtractUtilsModule,
)

namespace_imports = [
    'hardware/mediatek',
    'hardware/xiaomi',
    'vendor/xiaomi/camellia',
    'hardware/mediatek/libmtkperf_client'
]


def lib_fixup_vendor_suffix(lib: str, partition: str, *args, **kwargs):
    return f'{lib}_{partition}' if partition == 'vendor' else None


lib_fixups: lib_fixups_user_type = {
    **lib_fixups,
    ('vendor.mediatek.hardware.videotelephony@1.0',): lib_fixup_vendor_suffix,
    ('libsink',): lib_fixup_remove,
}

blob_fixups: blob_fixups_user_type = {
    'system/lib64/libsink.so': blob_fixup()
        .add_needed('libaudioclient_shim.so'),
    'system/lib64/libsource.so': blob_fixup()
        .add_needed('libui_shim.so'),
    'system/priv-app/ImsService/ImsService.apk': blob_fixup()
        .apktool_patch('blob-patches/ImsService.patch', '-r'),
    'vendor/lib/hw/vendor.mediatek.hardware.pq@2.13-impl.so': blob_fixup()
        .replace_needed('libutils.so', 'libutils-v32.so'),
    ('vendor/bin/mnld', 'vendor/lib64/libaalservice.so', 'vendor/lib64/libcam.utils.sensorprovider.so', 'vendor/lib64/librgbwlightsensor.so'): blob_fixup()
        .replace_needed('libsensorndkbridge.so', 'android.hardware.sensors@1.0-convert-shared.so'),
    'vendor/lib64/hw/vendor.mediatek.hardware.pq@2.13-impl.so': blob_fixup()
        .replace_needed('libutils.so', 'libutils-v32.so'),
    ('vendor/lib64/libteei_daemon_vfs.so',
     'vendor/lib64/lib3a.flash.so',
     'vendor/lib64/libSQLiteModule_VER_ALL.so',
     'vendor/lib64/lib3a.sensors.color.so',
     'vendor/lib64/lib3a.sensors.flicker.so',
     'vendor/lib64/libaaa_ltm.so',
     'vendor/lib64/libaaa_ltmx.so',
     'vendor/lib64/lib3a.ae.stat.so'): blob_fixup()
        .add_needed('liblog.so'),
     'vendor/etc/vintf/manifest/manifest_media_c2_V1_2_default.xml': blob_fixup()
        .regex_replace('1.1', '1.2'),
     'vendor/lib64/libmnl.so' : blob_fixup()
        .add_needed('libcutils.so'),
    ('vendor/bin/hw/android.hardware.gnss-service.mediatek', 'vendor/lib64/hw/android.hardware.gnss-impl-mediatek.so'): blob_fixup()
        .replace_needed('android.hardware.gnss-V1-ndk_platform.so', 'android.hardware.gnss-V1-ndk.so'),
     'vendor/lib64/libmtkcam_stdutils.so': blob_fixup()
        .replace_needed('libutils.so', 'libutils-v32.so'),
    ('vendor/lib/libnvram.so', 'vendor/lib64/libnvram.so', 'vendor/lib64/libsysenv.so', 'vendor/bin/hw/android.hardware.neuralnetworks@1.3-service-mtk-neuron') : blob_fixup()
         .add_needed('libbase_shim.so'),
     'vendor/lib64/libvendor.goodix.hardware.biometrics.fingerprint@2.1.so': blob_fixup()
         .add_needed('libhidlbase-v32.so'),
     'vendor/bin/hw/android.hardware.media.c2@1.2-mediatek-64b': blob_fixup()
         .replace_needed('libavservices_minijail_vendor.so', 'libavservices_minijail.so')
         .add_needed('libstagefright_foundation-v33.so'),
     'vendor/lib64/hw/hwcomposer.mt6833.so' : blob_fixup()
         .add_needed('libprocessgroup_shim.so'),
     'vendor/lib64/hw/audio.primary.mt6833.so' : blob_fixup()
        .replace_needed('libalsautils.so', 'libalsautils-v31.so'),
    ('vendor/lib64/libmtkcam_stdutils.so', 'vendor/lib64/hw/android.hardware.camera.provider@2.6-impl-mediatek.so'): blob_fixup()
        .replace_needed('libutils.so', 'libutils-v32.so'),
     'vendor/lib64/libgoodixhwfingerprint.so': blob_fixup()
        .replace_needed('libvendor.goodix.hardware.biometrics.fingerprint@2.1.so', 'vendor.goodix.hardware.biometrics.fingerprint@2.1.so')

}  # fmt: skip
module = ExtractUtilsModule(
    "camellia",
    "xiaomi",
    blob_fixups=blob_fixups,
    lib_fixups=lib_fixups,
    namespace_imports=namespace_imports,
)

if __name__ == '__main__':
    utils = ExtractUtils.device(module)
    utils.run()
