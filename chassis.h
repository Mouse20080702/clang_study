#pragma once
#include"system.h"
#include"motor.h"
#include <string>
#include "util.h"
class Chassis :public Obj
{
public:
	Chassis(const Json::Value &pragma) : _name("����")
	{
		
		sysData->rebuildSDcard(pragma, _name);
		_sideNums = _motorList.size() / 2;
		_gearing = _motorList.begin()->getGearSpeed();
		sysData->addObj(this);
		std::cout << "���̻��๹��ɹ�" << std::endl;

	}
	~Chassis() = default;
	virtual void addRecoderData() override
	{
		//sysData->addRecoderData({ static_cast<double>(_pwm) });
	}
	void set(int left, int right)
	{
		for (size_t i = 0; i < _sideNums; i++)
			_motorList[i].set(left);
		for (size_t i = _sideNums; i < _motorList.size(); i++)
			_motorList[i].set(left);
	}
	//void forward(const int pwm)
	//{
	//	_pwm = pwm;
	//	_pwm = std::clamp(_pwm, -127, 127);
	//	set(_pwm ,_pwm);
	//}
protected:
	const std::string _name;
	std::vector<Motor> _motorList;
	double _shootPosVal = 1.0;
	int _shootSpeed = 10, _joyThreshold = 10, _maxRotateSpd = 127;

	size_t _sideNums = 0; //����������
	int _pwm[2];          //0 ���pwm 1 �ұ�pwm
	size_t _gearing;      //��������ٶ�
};
