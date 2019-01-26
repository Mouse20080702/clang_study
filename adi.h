#pragma once
#include <iostream>
#include "json.h"
class ADI
{
public:

	explicit ADI(const Json::Value& pragma) :
		_port(pragma["�˿�"].asUInt()), _name(pragma["����"].asString())
	{
		init();
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
private:
	void init()
	{
		std::cout << "ADI " << _name << "[" << _port << "]" << " ����ɹ�" << std::endl;
	}
private:
	const size_t _port;
	const std::string _name;
};