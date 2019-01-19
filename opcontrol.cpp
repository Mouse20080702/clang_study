#include"main.h"
#include "poten.h"
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
using DataTypeMotorList = std::vector<DataTypeMotor>;                         //�����
void opcontrol()
{
	DataTypeMotorList data;
	FILE* file = fopen("chassis.txt", "r");
	if (file == nullptr)
		std::cerr << "�ļ��򿪴���" << std::endl;
	char buf[MAX_BUF_LEN];
	std::string line;

	while (fgets(buf, MAX_BUF_LEN, file) != nullptr)//��ȡһ��
	{
		line = buf;
		DataTypeMotor tempData;
		delAllMark(line, " ");//ɾ������Ŀո�
		size_t del_idx = line.find("=");//��¼�Ⱥŵ�λ��
		//������Կ��ֵ
		tempData.push_back(line.substr(0, del_idx));//���KEY��ֵ
		std::string val = line.substr(del_idx + 1, line.length());//���VAL��ֵ
		size_t val_idx = val.find(",");//����VAL��ֵ��ס�ҵ� "," ��λ��
		if (val_idx != std::string::npos)//����ѵ��˶���
			while (1)
			{
				tempData.push_back(val.substr(0, val_idx));//��Ӵ�0�����ŵ�����
				val.erase(0, val_idx + 1);//ɾ�����źͶ���ǰ��ֵ
				val_idx = val.find(",");//���� ������,�� m
				if (val_idx == std::string::npos)//������û�ҵ�������
				{
					tempData.push_back(val);//ʣ�µ�����ֵȫ�ӽ�ȥ
					break;
				}

			}
		else//û�ҵ����ž�һ��ֵ��
			tempData.push_back(val);
		//��������
		data.push_back({ tempData });
	}
	fclose(file);
	for (auto &it : data)
	{
		for (auto &it1 : it)
			std::cout << it1 << " ";
		//std::cout << std::endl;
	}
	FILE *outFile = fopen("chassisFilter", "w");
	if (outFile == nullptr)
		std::cerr << "�ļ�����ʧ��" << std::endl;
	for (auto &it : data)
	{
		std::string tempStr;//��ʱ����
		for (auto &it1 : it)
		{
			if (it1 == it.front())//����ǵ�һ��Ԫ�� KEY
			{
				tempStr = it1;
				tempStr += "=";
			}
			else //VAL
			{
				tempStr += it1;
				if (it1 != it.back())//���һ��ֵ���治�Ӷ���
					tempStr += ",";
			}
		}
		fprintf(outFile, "%s", tempStr.c_str());//����¼��
	}
	fclose(file);
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