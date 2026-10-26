/*
 * Copyright (C) 2022,2025 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "fingerprint.h"

class UdfpsHandler {
  public:
    virtual ~UdfpsHandler() = default;

    virtual void init(fingerprint_device_t*) {};
    virtual void onFingerDown(uint32_t, uint32_t, float, float) {};
    virtual void onFingerUp() {};

    virtual void onAcquired(int32_t, int32_t) {};
    virtual void onAuthenticationSucceeded() {};
    virtual void onAuthenticationFailed() {};
    virtual void cancel() {};
};

struct UdfpsHandlerFactory {
    UdfpsHandler* (*create)();
    void (*destroy)(UdfpsHandler* handler);
};

UdfpsHandlerFactory* getUdfpsHandlerFactory();
