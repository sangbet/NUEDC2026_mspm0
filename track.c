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

// void Track_Process(int32_t baseSpeed, int32_t trackDir) {
//     // 1. 将 trackDir 作为误差传入 PID 
//     // 注意：如果加上 PID 后小车剧烈偏离赛道，请在此处给 trackDir 加负号：-trackDir
//     float turn_output = PID_Calculate((float)trackDir);
    
//     // 2. 将 PID 输出转化为左右轮速度 (直接调用底层 SetSpeed)
//     // 左轮加速则右轮减速，实现差速转向
//     int32_t left_speed  = baseSpeed + (int32_t)turn_output;
//     int32_t right_speed = baseSpeed - (int32_t)turn_output;
    
//     // 3. 驱动电机 (SetSpeed 内部已做 4000 限幅和方向处理)
//     SetSpeed(MOTOR_L, left_speed);
//     SetSpeed(MOTOR_R, right_speed);
// }
void Track_Process(int32_t baseSpeed, uint32_t *trackData) {
    // 静态变量，用于记录上一次有效的偏差方向
    // 这样在丢线的瞬间，能“记住”刚才应该往哪边转
    static int32_t last_valid_error = 0; 
    
    int32_t trackWeight[8] = {-10,-6,-4,-2,2,4,6,10};
    int32_t trackDir = 0;
    uint8_t sensor_count = 0; // 用于统计检测到线的传感器数量
    
    // 1. 遍历计算偏差值并统计有效传感器数量
    for(uint8_t i = 0; i < 8; i++) {
        if(trackData[i] == 1) { // 假设 1 代表检测到黑线
            trackDir += trackWeight[i];
            sensor_count++;
        }
    }

    // 2. 防丢线逻辑核心
    if (sensor_count == 0) {
        // --- 丢线状态 ---
        // 所有传感器都未检测到黑线，此时 PID 计算出的 trackDir 为 0
        // 如果不处理，小车会误以为在正中间而直行，导致彻底冲出赛道
        
        if (last_valid_error < 0) {
            // 最后一次偏差为负，说明线在左边，车偏右了 -> 原地左转找线
            // 这里使用差速转向，甚至可以反转电机以获得更小的转弯半径
            SetSpeed(MOTOR_L, -500); // 左轮反转或停止
            SetSpeed(MOTOR_R, baseSpeed); // 右轮正转
        } 
        else if (last_valid_error > 0) {
            // 最后一次偏差为正，说明线在右边，车偏左了 -> 原地右转找线
            SetSpeed(MOTOR_L, baseSpeed); // 左轮正转
            SetSpeed(MOTOR_R, -500); // 右轮反转或停止
        } 
        else {
            // 特殊情况：刚启动就是全白，或恰好在正中间丢线
            // 默认直行或缓慢旋转，等待找到线
            SetSpeed(MOTOR_L, baseSpeed);
            SetSpeed(MOTOR_R, baseSpeed);
        }
    } 
    else {
        // --- 正常循迹状态 ---
        // 更新记忆的偏差方向（只有正常循迹时才更新，防止丢线时记录被清零）
        last_valid_error = trackDir;

        // 正常 PID 计算
        float turn_output = PID_Calculate((float)trackDir);
        
        int32_t left_speed  = baseSpeed + (int32_t)turn_output;
        int32_t right_speed = baseSpeed - (int32_t)turn_output;
        
        SetSpeed(MOTOR_L, left_speed);
        SetSpeed(MOTOR_R, right_speed);
    }
}