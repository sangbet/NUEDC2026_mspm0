#include "track.h"

void ReadTrack(uint32_t *trackData){
    trackData[0] = !(DL_GPIO_readPins(TRACK_TRACK0_PORT, TRACK_TRACK0_PIN) & TRACK_TRACK0_PIN);
    trackData[1] = !(DL_GPIO_readPins(TRACK_TRACK1_PORT, TRACK_TRACK1_PIN) & TRACK_TRACK1_PIN);
    trackData[2] = !(DL_GPIO_readPins(TRACK_TRACK2_PORT, TRACK_TRACK2_PIN) & TRACK_TRACK2_PIN);
    trackData[3] = !(DL_GPIO_readPins(TRACK_TRACK3_PORT, TRACK_TRACK3_PIN) & TRACK_TRACK3_PIN);
    trackData[4] = !(DL_GPIO_readPins(TRACK_TRACK4_PORT, TRACK_TRACK4_PIN) & TRACK_TRACK4_PIN);
    trackData[5] = !(DL_GPIO_readPins(TRACK_TRACK5_PORT, TRACK_TRACK5_PIN) & TRACK_TRACK5_PIN);
    trackData[6] = !(DL_GPIO_readPins(TRACK_TRACK6_PORT, TRACK_TRACK6_PIN) & TRACK_TRACK6_PIN);
    trackData[7] = !(DL_GPIO_readPins(TRACK_TRACK7_PORT, TRACK_TRACK7_PIN) & TRACK_TRACK7_PIN);
}

int32_t CalTrackDir(uint32_t *trackData){
    int32_t trackWeight[8] = {-5,-4,-2,-1,1,2,4,5};
    int32_t trackDir = 0;
    for(uint8_t i = 0;i<8;i++){
        trackDir = trackDir + trackWeight[i] * trackData[i]; 
    }
    return trackDir;
}