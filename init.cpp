#include "main.h"
#include "userConfig.h"
#include "json.h"
#include <iostream>
//SystemData* sysData;
//Chassis *chassis;
//Generic* lift;
//Generic* intake;
//Generic* shoot;
void f(void* pragma)
{
	int* a = (int*)pragma;
	int b = *a;
	std::cout<<"val:"<<b<< std::endl;
}
void init()
{
std::string stu = R"({
  "����������": "ȫ�ܻ�",
  "������": "8982B",
  "�û�": "sheep",
  "����": {
    "���": {
      "��ǰ": {
        "�˿�": 1,
        "����": 0,
        "����": 1
      },
      "���": {
        "�˿�": 2,
        "����": 1,
        "����": 1
      },
      "��ǰ": {
        "�˿�": 3,
        "����": 1,
        "����": 1
      },
      "�Һ�": {
        "�˿�": 4,
        "����": 0,
        "����": 1
      }
    },
    "ADI": 2018,
    "����": "city"
  },
  "Skills": [ "Basketball", "Sing", "Play Games", "Program" ]
})";
	Json::Value val;
	Json::CharReaderBuilder jsreader;
	std::unique_ptr<Json::CharReader> const reader(jsreader.newCharReader());
	JSONCPP_STRING  err;
	if (!reader->parse(stu.c_str(), stu.c_str() + stu.length(), &val, &err))
		return;
	//on::Value::Members key = val["����"]["���"]["��ǰ"].getMemberNames();
	std::cout << val["����"]["���"].size() << std::endl;
	std::cout << val["Skills"][0].asString() << std::endl;
	size_t count = 0;
	for (auto& it : val["����"]["���"]["�Һ�"])
	{
		auto key =val["����"]["���"]["�Һ�"].getMemberNames();
		std::cout << key[count] << " : " << it.asInt() << std::endl;
		count++;
	}
	int b = 9000;
	int c = 1900;
	f(&b);
	f(&c);
	//for (auto &it:key) //����json��Ա
	//{
	//	std::string name = it;
	//	int flag = val[it].asInt();
	//	std::cout << name << ":" << flag << std::endl;
	//}
	//sysData = new SystemData();
	//chassis = new Chassis( CHASSIS_PRAGMA);
	//lift = new Generic({ Motor{5,-1} }, "����");
	//intake = new Generic({ Motor{6,-1} }, "����");
	//shoot = new Generic({ Motor{7,-1}, Motor{8,1} }, "����");

}