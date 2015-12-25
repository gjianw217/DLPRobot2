
extern void TestRobotInit();
extern void TestServer();
extern void TestServer1();
extern void TestGPIOOut();
extern void TestRS485Coder(void);
extern void TestModbusNet();
extern void TestServer2();
extern void SolvePTZUnsmoothWay1(void);
extern void SolvePTZUnsmoothWay2(void);

extern void TestStepMotor(void);
extern void TestMotorbyPRUCoder(void);
extern void TestPWMCAN(void);
int main()
{
//    TestGPIOOut();
//    TestRS485Coder();
//    TestRobotInit();
//    TestModbusNet();
    TestServer();
//    SolvePTZUnsmoothWay1();
  //  SolvePTZUnsmoothWay2();
   // TestStepMotor();
//    TestMotorbyPRUCoder();

//    TestPWMCAN();

	return 0;
}
