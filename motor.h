#pragma once
#include <iostream>
#include "json.h"
class Motor
{
public:

	explicit Motor(const Json::Value& pragma) : _pragma(pragma)
	{
		init();
	}
	void set(int pwm)
	{

		std::cout << _pragma <<" pwm:"<<pwm << std::endl;
	}

	/**
	 *��ȡ��������
	 * @return std::string ������������
	 */
	int getName()
	{
		return _pragma["�˿�"].asInt();
	}
	/**
	 *��ȡ���Ķ˿ں�
	 * @return std::string ������������
	 */
	bool getPort()
	{
		return _pragma["����"].asBool();
	}
	/**
	 *�����������
	 * @return std::string �����������
	 */
	int getRevase()
	{
		return _pragma["����"].asInt();
	}
	/**
	 * @��ȡ������������
	 *
	 * @return std::string ���س��ֵ���������
	 */
	//std::string getGearName()
	//{
	//	return _pragma.at(3);
	//}
	/**
	 *��ȡ��ǰ���ֵ��ٶ�
	 * @return int �������ֵ��ٶ� �����100 �̳���200 ������600
	 */
	int getGearSpeed()
	{
		return _speed;
	}

private:
	void init()
	{
		if (_pragma["����"] == "0")
		{
			_speed = 100;
		}
		else if (_pragma["����"] == "1")
		{
			_speed = 200;
		}
		else if (_pragma["����"] == "2")
		{
			_speed = 600;
		}
		else
		{
			_speed = 100;
			std::cerr << "�������ô���,�Ѿ��������ΪĬ���̳���" << std::endl;
		}
		std::cout << _pragma["�˿�"] << ":" << _pragma["����"] << " " << _pragma["����"] << " "  << " ����ɹ�" << std::endl;
	}
	const Json::Value _pragma;
	int _speed = 0;
};