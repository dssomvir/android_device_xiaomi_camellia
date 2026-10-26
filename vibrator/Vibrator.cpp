/*
 * Copyright (C) 2019 The Android Open Source Project
 * Copyright (C) 2021 StatiX
 * SPDX-License-Identifer: Apache-2.0
 */

#define LOG_TAG "vibrator.camellia"

#include "vibrator-impl/Vibrator.h"

#include <android-base/logging.h>
#include <cerrno>
#include <fstream>

namespace aidl {
namespace android {
namespace hardware {
namespace vibrator {

template <typename T>
static bool write_haptic_node(const std::string& path, const T& value) {
    std::ofstream file(path);
    if (!file.is_open()) {
        PLOG(ERROR) << "Failed to open vibrator sysfs node " << path;
        return false;
    }
    file << value;
    file.flush();
    if (!file.good()) {
        PLOG(ERROR) << "Failed to write vibrator sysfs node " << path;
        return false;
    }
    return true;
}

ndk::ScopedAStatus Vibrator::getCapabilities(int32_t* _aidl_return) {
    LOG(INFO) << "Vibrator reporting capabilities";
    *_aidl_return = 0;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::off() {
    LOG(INFO) << "Vibrator off";
    if (!write_haptic_node(activate_node, 0)) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::on(int32_t timeoutMs,
                                const std::shared_ptr<IVibratorCallback>& callback) {
    LOG(INFO) << "Vibrator on for timeoutMs: " << timeoutMs;
    if (timeoutMs <= 0) {
        return off();
    }
    if (!write_haptic_node(duration_node, timeoutMs) ||
        !write_haptic_node(activate_node, 1)) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::perform(Effect effect, EffectStrength strength,
                                     const std::shared_ptr<IVibratorCallback>& callback,
                                     int32_t* _aidl_return) {
    ndk::ScopedAStatus status;
    uint32_t timeMs = 0;

    LOG(INFO) << "Vibrator perform";

    switch (effect) {
        case Effect::TICK:
            LOG(INFO) << "Vibrator effect set to TICK";
            timeMs = WAVEFORM_TICK_EFFECT_MS;
            break;
        case Effect::TEXTURE_TICK:
            LOG(INFO) << "Vibrator effect set to TEXTURE_TICK";
            timeMs = WAVEFORM_TEXTURE_TICK_EFFECT_MS;
            break;
        case Effect::CLICK:
            LOG(INFO) << "Vibrator effect set to CLICK";
            timeMs = WAVEFORM_CLICK_EFFECT_MS;
            break;
        case Effect::HEAVY_CLICK:
            LOG(INFO) << "Vibrator effect set to HEAVY_CLICK";
            timeMs = WAVEFORM_HEAVY_CLICK_EFFECT_MS;
            break;
        case Effect::DOUBLE_CLICK:
            LOG(INFO) << "Vibrator effect set to DOUBLE_CLICK";
            timeMs = WAVEFORM_DOUBLE_CLICK_EFFECT_MS;
            break;
        case Effect::THUD:
            LOG(INFO) << "Vibrator effect set to THUD";
            timeMs = WAVEFORM_THUD_EFFECT_MS;
            break;
        case Effect::POP:
            LOG(INFO) << "Vibrator effect set to POP";
            timeMs = WAVEFORM_POP_EFFECT_MS;
            break;
        default:
            return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    status = on(timeMs, nullptr);
    if (!status.isOk()) {
        return status;
    } else {
        *_aidl_return = timeMs;
    }
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::getSupportedEffects(std::vector<Effect> *_aidl_return) {

    *_aidl_return = {
        Effect::TICK,
        Effect::TEXTURE_TICK,
        Effect::CLICK,
        Effect::HEAVY_CLICK,
        Effect::DOUBLE_CLICK,
        Effect::THUD,
        Effect::POP
    };

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::setAmplitude(float amplitude) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::setExternalControl(bool enabled) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getCompositionDelayMax(int32_t* maxDelayMs) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getCompositionSizeMax(int32_t* maxSize) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getSupportedPrimitives(std::vector<CompositePrimitive>* supported) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getPrimitiveDuration(CompositePrimitive primitive,
                                                  int32_t* durationMs) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::compose(const std::vector<CompositeEffect>& composite,
                                     const std::shared_ptr<IVibratorCallback>& callback) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getSupportedAlwaysOnEffects(std::vector<Effect>* _aidl_return) {
    return getSupportedEffects(_aidl_return);
}

ndk::ScopedAStatus Vibrator::alwaysOnEnable(int32_t id, Effect effect, EffectStrength strength) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::alwaysOnDisable(int32_t id) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getResonantFrequency(float *resonantFreqHz) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getQFactor(float *qFactor) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getFrequencyResolution(float *freqResolutionHz) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getFrequencyMinimum(float *freqMinimumHz) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getBandwidthAmplitudeMap(std::vector<float> *_aidl_return) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getPwlePrimitiveDurationMax(int32_t *durationMs) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getPwleCompositionSizeMax(int32_t *maxSize) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::getSupportedBraking(std::vector<Braking>* supported) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Vibrator::composePwle(const std::vector<PrimitivePwle> &composite,
                                         const std::shared_ptr<IVibratorCallback> &callback) {
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

}  // namespace vibrator
}  // namespace hardware
}  // namespace android
}  // namespace aidl
