#include"main.h"
#include "poten.h"
#include "configRead.h"
#include "json.h"
void opcontrol()
{
	//Json::Value  CHASSIS_PRAGMA = { {"���ҽ�������", "1.1"},
	//								   {"���������ٶ�", "15"},
	//								   {"ң��������", "10"},
	//								   {"�����ת�ٶ�", "127"} };
	//std::cout << CHASSIS_PRAGMA.toStyledString() << std::endl;

	std::string stu= R"(  {
"����" : 22,
"height" : 1.78,
"����" : "Denny",
"����" : [1,2,3,4],
"object" : 
{
"someone" : "Kelly",
"sometime" : 2018,
"somewhere" : "city"
},
"object_array" : 
[
{
"string1" : "1-1",
"string2" : "1-2"
},
{
"string1" : "2-1",
"string2" : "2-2"
},
{
"string1" : "3-1",
"string2" : "3-2"
}
],
"play_football" : true,
"string_array" : 
[
"string01",
"string02",
"string03"
]
})";
	Json::Value root;
	Json::CharReaderBuilder jsreader;
	std::unique_ptr<Json::CharReader> const reader(jsreader.newCharReader());
	JSONCPP_STRING  err;

	//ʧ��

	if (!reader->parse(stu.c_str(), stu.c_str()+stu.length(), &root, &err))
		return;

	std::string strName = root["����"].asString();
	int strAge = root["����"].asInt();
	std::vector<int>v;
	//for (size_t i = 0; i < root["����"].size(); i++)
	//	v.push_back(root["����"].asInt());
	for (auto &it : v)
		std::cout << it << std::endl;


	std::cout << strName <<" "<< strAge << std::endl;
	//Json::Reader reader;
	//std::fstream fs("");
	//if (reader.parse(stu, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��  
	//{
	//	std::cout <<root<< std::endl;

	//

	//}

	//Json::Value root;
	//Json::Reader reader;
	//std::ifstream ifs("example.json");//open file example.json

	//if (!reader.parse(ifs, root)) {
	//	// fail to parse
	//}
	//else {
	//	// success
	//	std::cout << root["���"].asString() << std::endl;
	//	std::cout << root["indent"]["length"].asInt() << std::endl;
	//}

	//ncrapi::Poten poten(1, 5);
	//std::fstream fs("Text1.txt");
	//if (!fs.is_open())
	//	std::cerr << "file open error" << std::endl;
	//std::string temp;
	//while (std::getline(fs, temp))
	//{
	//	std::istringstream iss(temp);
	//	int val;
	//	iss >> val;
	//	poten.get(val, 1);
	//	poten.print();
	//	Sleep(10);
	//}
	//fs.close();

	//size_t i = 0;

	//while (i<=100)
	//{
	//	chassis->forward(127);
	//	lift->set(50);
	//	intake->set(-10);
	//	shoot->set(20);
	//	for (auto &it : sysData->_objData)
	//		it->addRecoderData();
	//	i++;
	//	Sleep(100);
	//}
	//sysData->showRecoderData();
	delete sysData;
	delete chassis;
}