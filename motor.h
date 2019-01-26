#pragma once
#include <iostream>
#include "json.h"
class Motor
{
public:

	 Motor(const Json::Value& pragma) :
		_port(pragma["�˿�"].asUInt()), _isRevase(pragma["����"].asBool()),_gear(pragma["����"].asUInt()),_name(pragma["����"].asString())
	{
		init();
	}
	void set(int pwm)
	{

		std::cout <<"���["<< _port <<"] pwm:"<<pwm << std::endl;
	}

	/**
	 *��ȡ��������
	 * @return std::string ������������
	 */
	std::string getName()
	{
		return _name;
	}
	/**
	 *��ȡ���Ķ˿ں�
	 * @return std::string ������������
	 */
	size_t getPort()
	{
		return _port;
	}
	/**
	 *�����������
	 * @return std::string �����������
	 */
	bool  getRevase()
	{
		return _gear;
	}

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
		if (_gear == 0)
		{
			_speed = 100;
		}
		else if (_gear == 1)
		{
			_speed = 200;
		}
		else if (_gear == 2)
		{
			_speed = 600;
		}
		else
		{
			_speed = 100;
			std::cerr << "�������ô���,�Ѿ��������ΪĬ���̳���" << std::endl;
		}
		std::cout << "��� "<<_name<< "[" <<_port<<"]"<< ":" << _isRevase << " " << _gear << " " << " ����ɹ�" << std::endl;
	}
private:
	const size_t _port;
	const bool _isRevase;
	const size_t _gear;
	const std::string _name;
	int _speed = 0;
};