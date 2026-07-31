#ifndef TRACK_H
#define TRACK_H

#include "ti_msp_dl_config.h"
#include "motor.h"

void ReadTrack(uint32_t *trackData);
int32_t CalTrackDir(uint32_t *trackData);
void Track_PID_Init(float kp, float ki, float kd, float max_out);
void Track_Process(int32_t baseSpeed, int32_t trackDir);

#endif