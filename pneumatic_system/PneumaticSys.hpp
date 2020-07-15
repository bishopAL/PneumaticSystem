
 #include "Arduino.h"

class PneumaticSys
{
public:
	PneumaticSys();
	~PneumaticSys();
	uint8_t SV[4][4];  //Solenoid valves电磁阀
	//int EPV; //electric proportion valve电气比例阀
	void enableNormalPneumatic(int i);
	void enablePositivePneumatic(int i);
	void enableNegtivePneumatic(int i);
	void holdPressure(int i);
};
