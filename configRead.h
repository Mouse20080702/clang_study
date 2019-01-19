#pragma once
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <type_traits>
#define MAX_BUF_LEN 1024


//  Helper����������ַ�����ȡ�����ַ���ת��Ϊbool
//  true������true�����򷵻�false
bool to_bool(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	if (str.compare("true") == 0) return true;
	else if (str.compare("false") == 0) return false;
	else throw std::invalid_argument("Boolean can only be false or true, impartial to case.");
}

class ConfigReader
{
	// Default Constructor�����ڲ����ݽṹ
	ConfigReader()
	{
		if (!parse_file()) throw ConfigReaderException();
	}

	// /�����������ʹ�õ��쳣��
// /  - ���캯��ʧ��
	class ConfigReaderException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "A ConfigReaderException happened";
		}
	};

	//����������ɸ��ĵĴ����볢�Խ��������ļ�
	//���Ƿ���fasel����������Ǹ�ʽ����������У�����
	// ����true
	bool parse_file()
	{
		size_t curr_line = 0;//������

		FILE* file = fopen("chassis.txt", "r");
		if (file == nullptr)
			return false;
		char buf[MAX_BUF_LEN];
		while (fgets(buf, MAX_BUF_LEN, file) != nullptr)//��ȡһ��
		{
			std::string line = buf;
			std::string key, val;
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
			std::cout << "key:" << key << " val:" << val << std::endl;
			//��������
		/*	m_cfg_data[key] = val;*/

			curr_line++;
		}
		return true;
	}

	static ConfigReader* s_instance;

	// / Datastruct���ڲ����������ļ�
	std::unordered_map<std::string, std::string> m_cfg_data;

public:

	//������key��Ӧ��ֵ��Ϊstd :: string
	std::string get(std::string key)
	{
		auto search = m_cfg_data.find(key);

		if (search == m_cfg_data.end())
		{
			std::cerr << "Can't find key: " << key << std::endl;
			return "";
		}

		return search->second;
	}

	/**
	* SFINAE���ڲ�������ԭʼ�������͡�
	*����������������ͣ����Ǽ���һ�����캯��
	��ʽΪfoo��std::string����*���á�
	*/
	// / INTEGRAL TYPES
	template<class T, typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value>::type* = nullptr>
	T get_as(std::string key)
	{
		auto found_val = this->get(key);
		T ret_val = 0;
		try
		{
			ret_val = std::stoi(found_val);
		}
		catch (const std::invalid_argument& ia)
		{
			std::cerr << "Key: " << key << " throws Invalid Argument" << std::endl;
			std::cerr << ia.what() << std::endl;
			return T();
		}
		return ret_val;
	}

	// /��������
	template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
	T get_as(std::string key)
	{
		auto found_val = this->get(key);
		T ret_val = 0.0f;
		try
		{
			ret_val = std::stod(found_val);
		}
		catch (const std::invalid_argument& ia)
		{
			std::cerr << "Key: " << key << " throws Invalid Argument" << std::endl;
			std::cerr << ia.what() << std::endl;
			return T();
		}
		return ret_val;
	}

	// / BOOL
	template<class T, typename std::enable_if<std::is_same<bool, T>::value>::type* = nullptr>
	T get_as(std::string key)
	{
		auto found_val = this->get(key);
		T ret_val = to_bool(found_val);
		return ret_val;
	}
	// / COMPLEX TYPE
	template<class T, typename std::enable_if<std::is_class<T>::value>::type* = nullptr>
	T get_as(std::string key)
	{
		auto found_val = this->get(key);
		return T(found_val);
	}

	//ʵ�ֵ���
	static ConfigReader* instance()
	{
		if (ConfigReader::s_instance == nullptr) ConfigReader::s_instance = new ConfigReader();
		return s_instance;
	}
};