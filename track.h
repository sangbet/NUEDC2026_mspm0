#ifndef TRACK_H
#define TRACK_H

#include "ti_msp_dl_config.c"
#include "motor.h"

void ReadTrack(uint32_t *trackData);
int32_t CalTrackDir(uint32_t *trackData);

#endif