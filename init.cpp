#include "main.h"
#include "userConfig.h"
#include <iostream>
SystemData* sysData;
Chassis* chassis;
//Generic* lift;
//Generic* intake;
//Generic* shoot;

void init()
{



	Json::Value val;
	Json::CharReaderBuilder jsreader;
	std::unique_ptr<Json::CharReader> const reader(jsreader.newCharReader());
	JSONCPP_STRING  err;
	if (!reader->parse(stu.c_str(), stu.c_str() + stu.length(), &val, &err))
	{
		std::cerr << "������ȡ����,��ע���ʽ" << std::endl;
		return;
	}

	//Motor a(val["����"]["���"][3]);
	//ADI gyro(val["����"]["ADI"][0]);
	//on::Value::Members key = val["����"]["���"]["��ǰ"].getMemberNames();
	//std::cout << val["����"]["���"].size() << std::endl;
	//std::cout << val["Skills"][0].asString() << std::endl;
	//size_t count = 0;
	//for (auto& it : val["����"]["���"]["�Һ�"])
	//{
	//	auto key = val["����"]["���"]["�Һ�"].getMemberNames();
	//	std::cout << key[count] << " : " << it.asInt() << std::endl;
	//	count++;
	//}
		//for (auto &it:key) //����json��Ա
		//{
		//	std::string name = it;
		//	int flag = val[it].asInt();
		//	std::cout << name << ":" << flag << std::endl;
		//}
	sysData = new SystemData();
	chassis = new Chassis(val["����"]);
	//lift = new Generic({ Motor{5,-1} }, "����");
	//intake = new Generic({ Motor{6,-1} }, "����");
	//shoot = new Generic({ Motor{7,-1}, Motor{8,1} }, "����");

}