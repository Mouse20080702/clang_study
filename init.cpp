#include "main.h"
#include "userConfig.h"
SystemData* sysData;
Chassis *chassis;
Generic* lift;
Generic* intake;
Generic* shoot;
void init()
{
	sysData = new SystemData();
	chassis = new Chassis( CHASSIS_PRAGMA);
	//lift = new Generic({ Motor{5,-1} }, "����");
	//intake = new Generic({ Motor{6,-1} }, "����");
	//shoot = new Generic({ Motor{7,-1}, Motor{8,1} }, "����");

}