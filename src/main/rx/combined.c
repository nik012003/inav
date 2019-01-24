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
#include "rx/sbus.h"

rxRuntimeConfig_t *combinedRxRuntimeConf;
rxConfig_t *combinedRxConfig;

static uint16_t mspFrame[MAX_SUPPORTED_RC_CHANNEL_COUNT] = {1000,1000,1000,1000,1000,1000};


static uint8_t combinedRxFrameStatus(rxRuntimeConfig_t *rxRuntimeConfig)
{
    return RX_FRAME_PENDING;
}

static uint16_t errorFunc(const rxRuntimeConfig_t *rxRuntimeConfig, uint8_t chan) 
{
    return mspFrame;
}

static uint16_t combinedRxReadRawRC(const rxRuntimeConfig_t *rxRuntimeConfig, uint8_t chan) 
{
    //u_int16_t sample;
    //return (5 * combinedRxRuntimeConf->channelData[chan] / 8) + 880;
    return (*combinedRxRuntimeConf->rcReadRawFn)(&combinedRxRuntimeConf, chan); //If I do it here, it does not
    //UNUSED(sample);
    //return mspFrame;
}

void combinedRxInit(const rxConfig_t *rxConfig, rxRuntimeConfig_t *rxRuntimeConfig)
{
    combinedRxConfig = rxConfig;
    combinedRxConfig->receiverType = RX_TYPE_SERIAL;
    combinedRxConfig->serialrx_provider = SERIALRX_SBUS;
    
    rxRuntimeConfig->channelCount = MAX_SUPPORTED_RC_CHANNEL_COUNT;
    rxRuntimeConfig->rxRefreshRate = 20000;
    rxRuntimeConfig->rxSignalTimeout = DELAY_5_HZ;
    rxRuntimeConfig->rcReadRawFn = combinedRxReadRawRC;
    rxRuntimeConfig->rcFrameStatusFn = combinedRxFrameStatus;
    
    combinedRxRuntimeConf = rxRuntimeConfig;
    combinedRxRuntimeConf->rcReadRawFn = errorFunc;

    //combinedRxRuntimeConf->rxSignalTimeout = DELAY_10_HZ;
    //combinedRxRuntimeConf->requireFiltering = false;
    
    
    sbusInit(combinedRxConfig , combinedRxRuntimeConf);

}
#endif