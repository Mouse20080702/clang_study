#pragma once
#include <iostream>
#include <vector>
#include "dataType.h"
#include"obj.h"
#include <memory>
class SystemData
{
public:
	DataConfigListSet configData; //configList���͵ļ���
	DataConfig path;              //·��
	std::vector<std::vector<double>> _recoderData;
	std::vector<Obj *> _objData;
	SystemData() { std::cout << "sysData create successful" << std::endl; }
	~SystemData() = default;
	void addObj(Obj * obj)
	{
		_objData.push_back(obj);
	}
	void addRecoderData(std::vector<double> data)
	{
		_recoderData.push_back(data);
	}
	void showRecoderData()
	{
		for (auto &it1 : _recoderData)
		{
			for (auto &it2 : it1)
				std::cout << it2 << ";";
			std::cout << std::endl;
		}
	}
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
	bool readSDcard(DataConfigList &data, const std::string &filePath)
	{
		FILE* file = fopen(filePath.c_str(), "r");
		if (file == nullptr)
		{
			std::cerr <<"·�� "<< filePath << " �򿪴���" << std::endl;
			return false;
		}
		char buf[1024];
		std::string line;
		while (fgets(buf, 1024, file) != nullptr)//��ȡһ��
		{
			line = buf;
			DataConfig tempData;
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
		return true;
	}
	void rebuildSDcard(const DataConfigList &tempData, const std::string &name)
	{
		if (name == "����")
			path.push_back("chassis.txt");
		else if (name == "��̨")
			path.push_back("head.txt");
		else if (name == "����")
			path.push_back("intake.txt");
		else if (name == "��ת��")
			path.push_back("rotateIntake.txt");
		else if (name == "����")
			path.push_back("capIntake.txt");
		else if (name == "����")
			path.push_back("lift.txt");
		else if (name == "����")
			path.push_back("shoot.txt");
		else
			std::cerr<< "��ȡ�������ִ���,�������"<<std::endl;
		configData.push_back(tempData);
		bool flag =readSDcard(configData.back(),path.back());
		if (!flag)
		{
			std::cerr << name << "û��������" << name << "���ļ�.���´���!��ע���������������Ϣ" << std::endl;
			bool flag = saveData(tempData, path.back());
			if (!flag)
				std::cerr << "���α���ʧ��!,����SD���Ƿ�������SD���Ƿ���!" << std::endl;
			else
				std::cout<<"·�� " << path.back() << " �����ɹ�" << std::endl;
		}
	}

	bool saveData(const DataConfigList &data, const std::string &filePath)
	{
		FILE *file = fopen(filePath.c_str(), "w");
		if (file == nullptr)
		{
			std::cerr << "·�� " << filePath << " ����ʧ��" << std::endl;
			return false;
		}
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
			fprintf(file, "%s\n", tempStr.c_str());//����¼��
		}
		fclose(file);
		return true;
	}
private:
};
extern SystemData* sysData;
