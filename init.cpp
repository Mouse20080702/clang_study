#include "main.h"
SystemData* sysData;
Chassis *chassis;
Generic* lift;
Generic* intake;
Generic* shoot;
void init()
{
	sysData = new SystemData();
	chassis = new Chassis({ Motor{1,1},Motor{2,1},Motor{3,-1},Motor{4,-1} }, "����");
	lift = new Generic({ Motor{5,-1} }, "����");
	intake = new Generic({ Motor{6,-1} }, "����");
	shoot = new Generic({ Motor{7,-1}, Motor{8,1} }, "����");

}