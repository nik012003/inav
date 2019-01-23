/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "platform.h"

#ifdef USE_RX_MSP

#include "build/build_config.h"

#include "common/utils.h"

#include "rx/rx.h"
#include "rx/combined.h"

static uint16_t mspFrame[MAX_SUPPORTED_RC_CHANNEL_COUNT] = {1000,1000,1000,1000,1000,1000};

static uint16_t rxCombinedReadRawRC()
{
    return mspFrame;
}

static uint8_t rxCombinedFrameStatus(rxRuntimeConfig_t *rxRuntimeConfig)
{
    return RX_FRAME_COMPLETE;
}

void combinedRxInit(const rxConfig_t *rxConfig, rxRuntimeConfig_t *rxRuntimeConfig)
{
    UNUSED(rxConfig);

    rxRuntimeConfig->channelCount = MAX_SUPPORTED_RC_CHANNEL_COUNT;
    rxRuntimeConfig->rxRefreshRate = 20000;
    rxRuntimeConfig->rxSignalTimeout = DELAY_5_HZ;
    rxRuntimeConfig->rcReadRawFn = rxCombinedReadRawRC;
    rxRuntimeConfig->rcFrameStatusFn = rxCombinedFrameStatus;
}
#endif