#include"main.h"
#include "poten.h"
#include <json.h>
#include <fstream>
#include "configRead.h"
#define MAX_BUF_LEN 1024

void delAllMark(std::string &s, const std::string &mark)
{
	size_t nSize = mark.size();
	while (1)
	{
		size_t pos = s.find(mark);    //  ����������
		if (pos == std::string::npos)
		{
			return;
		}
		s.erase(pos, nSize);
	}

}
using DataTypeMotor = std::vector<std::string>;                                     //ÿһ���������ò���
using DataTypeMotorList =  std::vector<DataTypeMotor>;                         //�����
void opcontrol()
{
	DataTypeMotorList data;
	size_t curr_line = 0;//������

	FILE* file = fopen("chassis.txt", "r");
	if (file == nullptr)
		std::cerr << "�ļ��򿪴���" << std::endl;
	char buf[MAX_BUF_LEN];
	while (fgets(buf, MAX_BUF_LEN, file) != nullptr)//��ȡһ��
	{
		std::string line = buf;
		std::string key, val;
		delAllMark(line, " ");//ɾ������Ŀո�
		size_t del_idx = line.find("=");
		//����ÿ��ֻ����һ��=
		if (line.find('=', del_idx + 1) != std::string::npos)//����ҵ��˵�һ��= �ĺ��л���=
		{
			std::cerr << "�� " << curr_line << " ����һ��=" << std::endl;
			std::cerr << "��ת�� " << curr_line + 1 << " �ж�ȡ" << std::endl;
			curr_line++;
			continue;
		}

		//������Կ��ֵ
		key = line.substr(0, del_idx);
		val = line.substr(del_idx + 1, line.length());
		//��������
		data.push_back({key,val});
		curr_line++;
	}
	for (auto &it : data)
	{
		for (auto &it1 : it)
			std::cout << it1;
		std::cout << std::endl;
	}

	//Json::Value root;
	//Json::Reader reader;
	//std::string test = "{\"name\" : \
			//						\"Tocy\", \"salary\" : 100, \"msg\" : \"work hard\", \
		 //       \"files\" : [\"1.ts\", \"2.txt\"]}";
			//std::vector<std::pair<std::string, std::string>> test2 = ;
			//if (!reader.parse(test2, root)) {
			//	// "parse fail";
			//}
			//else
			//	std::cout << root["���˵�"].asString();//print "UP000000"

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
}