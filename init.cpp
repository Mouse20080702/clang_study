#include "main.h"
std::shared_ptr<SystemData> sysData;
std::shared_ptr<Chassis> chassis;
std::shared_ptr<Generic> lift;
std::shared_ptr<Generic> intake;
std::shared_ptr<Generic> shoot;
void init()
{
	sysData = std::make_shared<SystemData>();
	chassis = std::make_shared<Chassis>("����");
	lift = std::make_shared<Generic>("����");
	intake = std::make_shared<Generic>("����");
	shoot = std::make_shared<Generic>("����");

}