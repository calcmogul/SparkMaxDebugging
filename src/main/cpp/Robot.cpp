// Copyright (c) 2020 FRC Team 3512. All Rights Reserved.

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

TEST(RobotTest, Init) { Robot robot; }
#endif
