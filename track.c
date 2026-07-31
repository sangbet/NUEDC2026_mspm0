#include "track.h"
#include "motor.h"


typedef struct {
    float Kp;           
    float Ki;           
    float Kd;           
    float integral;     // 积分累加项
    float prev_error;   // 上一次的误差
    float out_max;      // 输出最大限幅
} PID_TypeDef;

static PID_TypeDef track_pid;



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
    int32_t trackWeight[8] = {-8,-6,-4,-2,2,4,6,8};
    int32_t trackDir = 0;
    for(uint8_t i = 0;i<8;i++){
        trackDir = trackDir + trackWeight[i] * trackData[i]; 
    }
    return trackDir;
}




// 初始化 PID 参数
void Track_PID_Init(float kp, float ki, float kd, float max_out) {
    track_pid.Kp = kp;
    track_pid.Ki = ki;
    track_pid.Kd = kd;
    track_pid.integral = 0;
    track_pid.prev_error = 0;
    track_pid.out_max = max_out;
}

// PID 计算函数 (位置式)
static float PID_Calculate(float error) {
    // 1. 误差累加 (积分项)
    track_pid.integral += error;
    
    // 积分限幅，防止积分饱和导致失控 (限幅值可按需调整，这里设为 max_out 的 2 倍)
    float int_max = track_pid.out_max * 2.0f;
    if (track_pid.integral > int_max) track_pid.integral = int_max;
    if (track_pid.integral < -int_max) track_pid.integral = -int_max;

    // 2. 计算微分项 (误差变化率)
    float derivative = error - track_pid.prev_error;
    track_pid.prev_error = error; 

    // 3. 计算总输出
    float output = track_pid.Kp * error + track_pid.Ki * track_pid.integral + track_pid.Kd * derivative;

    // 4. 输出限幅，防止差速过大导致一轮骤停或倒转过猛
    if (output > track_pid.out_max) output = track_pid.out_max;
    if (output < -track_pid.out_max) output = -track_pid.out_max;

    return output;
}

// 循迹处理：读取偏差 -> PID计算 -> 驱动电机
void Track_Process(int32_t baseSpeed, int32_t trackDir) {
    // 1. 将 trackDir 作为误差传入 PID 
    // 注意：如果加上 PID 后小车剧烈偏离赛道，请在此处给 trackDir 加负号：-trackDir
    float turn_output = PID_Calculate((float)trackDir);
    
    // 2. 将 PID 输出转化为左右轮速度 (直接调用底层 SetSpeed)
    // 左轮加速则右轮减速，实现差速转向
    int32_t left_speed  = baseSpeed + (int32_t)turn_output;
    int32_t right_speed = baseSpeed - (int32_t)turn_output;
    
    // 3. 驱动电机 (SetSpeed 内部已做 4000 限幅和方向处理)
    SetSpeed(MOTOR_L, left_speed);
    SetSpeed(MOTOR_R, right_speed);
}