#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <vector>
#include"obj.h"
#include <memory>
#include "json.h"
class SystemData
{
public:
	Json::Value jsonVal;//������
	Json::CharReaderBuilder jsreader;//��ȡ��
	Json::StreamWriterBuilder  builder;//д����
	JSONCPP_STRING  jsonErr;//�쳣��
	SystemData(std::string jsonData)
	{
		//std::unique_ptr<Json::CharReader> const reader(jsreader.newCharReader());
		//if (!reader->parse(jsonData.c_str(), jsonData.c_str() + jsonData.length(), &jsonVal, &jsonErr))
		//{
		//	std::cerr << "json��������" << std::endl;
		//	return;
		//}
		readSDcard();
		saveData();
	}
	std::vector<std::vector<double>> _recoderData;
	std::vector<Obj*> _objData;
	SystemData() { std::cout << "sysData create successful" << std::endl; }
	~SystemData() = default;
	void addObj(Obj* obj)
	{
		_objData.push_back(obj);
	}
	void addRecoderData(std::vector<double> data)
	{
		_recoderData.push_back(data);
	}
	void showRecoderData()
	{
		for (auto& it1 : _recoderData)
		{
			for (auto& it2 : it1)
				std::cout << it2 << ";";
			std::cout << std::endl;
		}
	}
	bool readSDcard()
	{
		FILE* file = fopen("demo.json", "r");
		if (file == nullptr)
		{
			std::cerr << "�ļ��򿪴���" << std::endl;
			return false;
		}
		char buf[1024];
		std::string line;
		while (fgets(buf, 1024, file) != nullptr) //��ȡһ��
			line += buf;
		//std::cout << line << std::endl;

		std::unique_ptr<Json::CharReader> const reader(jsreader.newCharReader());
		if (!reader->parse(line.c_str(), line.c_str() + line.length(), &jsonVal, &jsonErr))
		{
			std::cerr << "json��������!" << std::endl;
			return false;
		}
		fclose(file);
		return true;
	}
	//void rebuildSDcard(const DataConfigList &tempData, std::string name)
	//{
	//	if (name == "����")
	//		pathData.insert({ name ,{"chassis.txt" } }); //try_emplace ���Բ��� ���KEY ���ھͲ������˲����ھͲ���
	//	else if (name == "��̨")
	//		pathData.insert({ name, {"head.txt"} });
	//	else if (name == "����")
	//		pathData.insert({ name, {"intake.txt"} });
	//	else if (name == "��ת��")
	//		pathData.insert({ name, {"rotateIntake.txt" } });
	//	else if (name == "����")
	//		pathData.insert({ name, {"capIntake.txt"} });
	//	else if (name == "����")
	//		pathData.insert({ name, {"lift.txt" }		});
	//	else if (name == "����")
	//		pathData.insert({ name, {"shoot.txt"} });
	//	else if (name == "ǰ��pid")
	//		pathData.insert({ name,{ "frpid.txt"} });
	//	else if (name == "����pid")
	//		pathData.insert({ name, {"rotatepid.txt" }
	//			});
	//	else
	//	{
	//		std::cerr << "��ȡ�������ִ���,�������" << std::endl;
	//		return; //�����ú���
	//	}
	//	configData.try_emplace(name, tempData);
	//	bool flag = readSDcard(configData[name], name); //�ж��ļ��Ƿ��Ѿ�����
	//	if (!flag)
	//	{
	//		std::cerr << name << "û��������" << name << "config�ļ�.���´���!��ע���������������Ϣ" << std::endl;
	//		bool flag = saveData(tempData, name);
	//		if (!flag)
	//			std::cerr << name << " config�ļ����α���ʧ��!,����SD���Ƿ�������SD���Ƿ���!" << std::endl;
	//		else
	//			std::cout << name << " config�ļ������ɹ�" << std::endl;
	//	}
	//}
	std::string UTF8ToGBK(const std::string& strUTF8)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, nullptr, 0);
		WCHAR* wszGBK = new WCHAR[len + 1];
		memset(wszGBK, 0, len * 2 + 2);
		MultiByteToWideChar(CP_UTF8, 0, (LPCCH)strUTF8.c_str(), -1, wszGBK, len);
		len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, nullptr, 0, nullptr, nullptr);
		char* szGBK = new char[len + 1];
		memset(szGBK, 0, len + 1);
		WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, nullptr, nullptr);
		std::string strTemp(szGBK);
		delete[]szGBK;
		delete[]wszGBK;
		return strTemp;
	}
	std::string GBKToUTF8(const std::string& strGBK)
	{
		std::string strOutUTF8 = "";
		WCHAR* str1;
		int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, nullptr, 0);
		str1 = new WCHAR[n];
		MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
		n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, nullptr, 0, nullptr, nullptr);
		char* str2 = new char[n];
		WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, nullptr, nullptr);
		strOutUTF8 = str2;
		delete[]str1;
		delete[]str2;
		return strOutUTF8;
	}
	bool saveData()
	{
		FILE* file = fopen("save.json", "w");
		if (file == nullptr)
		{
			std::cerr << " ����ʧ��" << std::endl;
			return false;
		}
		std::ostringstream os;
		std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
		writer->write(jsonVal, &os);
		//std::string tempStr= UTF8ToGBK(jsonVal.toStyledString());
		std::cout << os.str() << std::endl;
		fprintf(file, "%s", os.str().c_str()); //����¼��
		fclose(file);
		return true;
	}
private:
};
extern SystemData* sysData;
