// Copyright (c) 2020-2021 FRC Team 3512. All Rights Reserved.

#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>

#ifdef RUNNING_FRC_TESTS
#include <gtest/gtest.h>
#include <hal/HAL.h>
#endif

class Robot : public frc::TimedRobot {
private:
    rev::CANSparkMax m_leftGrbx{9, rev::CANSparkMax::MotorType::kBrushless};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#else
int main(int argc, char** argv) {
    HAL_Initialize(500, 0);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(RobotTest, Init) {
    uint64_t kThreadRate = 25000;
    int32_t status = 0;
    uint64_t currTime;
    uint64_t startTime = HAL_GetFPGATime(&status);

    HAL_NotifierHandle m_setNotifier = HAL_InitializeNotifier(&status);

    for (int i = 0; i < 1000; i++) {
        currTime = HAL_GetFPGATime(&status);
        uint64_t nextTime = static_cast<uint64_t>(
            currTime + (kThreadRate - (currTime - startTime)));
        HAL_UpdateNotifierAlarm(m_setNotifier, nextTime, &status);
        if (HAL_WaitForNotifierAlarm(m_setNotifier, &status) == 0) {
            break;
        }
        startTime = HAL_GetFPGATime(&status);
    }
    HAL_StopNotifier(m_setNotifier, &status);
    HAL_CleanNotifier(m_setNotifier, &status);
}
#endif
