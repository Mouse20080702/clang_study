#pragma once
#include <iostream>
class Motor
{
public:
	explicit Motor(const std::string &name, const std::string &port, const std::string &isRevase, const std::string &gearset = "�̳���") : _pragma({ name, port, isRevase })
	{
		init();
	}
	explicit Motor(const DataConfig &pragma) : _pragma(pragma)
	{
		init();
	}
	void set(int pwm)
	{
		std::cout << _pragma[0] <<" pwm:"<<pwm << std::endl;
	}

	/**
	 *��ȡ��������
	 * @return std::string ������������
	 */
	std::string getName()
	{
		return _pragma.at(0);
	}
	/**
	 *��ȡ���Ķ˿ں�
	 * @return std::string ������������
	 */
	std::string getPort()
	{
		return _pragma.at(1);
	}
	/**
	 *�����������
	 * @return std::string �����������
	 */
	std::string getRevase()
	{
		return _pragma.at(2);
	}
	/**
	 * @��ȡ������������
	 *
	 * @return std::string ���س��ֵ���������
	 */
	std::string getGearName()
	{
		return _pragma.at(3);
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
		if (_pragma.at(3) == "�����")
		{
			_speed = 100;
		}
		else if (_pragma.at(3) == "�̳���")
		{
			_speed = 200;
		}
		else if (_pragma.at(3) == "������")
		{
			_speed = 600;
		}
		else
		{
			_speed = 100;
			std::cerr << "�������ô���,�Ѿ��������ΪĬ���̳���" << std::endl;
		}
		std::cout << _pragma.at(0) << ":" << _pragma.at(1) << " " << _pragma.at(2) << " " << _pragma.at(3) << " ����ɹ�" << std::endl;
	}
	const DataConfig _pragma;
	int _speed = 0;
};