#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include"util.h"
namespace ncrapi {
	class Poten
	{
	public:
		Poten(const size_t &port, const size_t &maxDataNum, const int &maxFlag = 5) :_port(port), _maxDataNums(maxDataNum), _MaxFlag(maxFlag)
		{
			std::cout << "poten[" << _port << "]create successful" << std::endl;
			_maxDataNums = std::clamp(_maxDataNums, static_cast<size_t>(2), static_cast <size_t>(50));
			std::cout << "MaxData is : " << _maxDataNums << std::endl;

		}

		int get(int num, int state = 2) //ģ�����num ʵ��û��
		{
			int tempVal = num;
			int temp = tempVal - _lastData;//�仯ֵ
			if (state == 2)//������Զ���ȡģʽ
			{
				if (abs(temp) >= _threshold + 20 && _count > _maxDataNums)//����仯���� �Ҽ�¼����������¼��
				{
					std::cerr << "��ֵ�仯����! ģ��ֵ:";
					tempVal = (_lastData + _threshold * _state);
				}
				else//�仯û�г���
				{
					_threshold = (_threshold + abs(temp)) / 2;//����ƽ����ֵ
					if (temp > 0)
						_flag++;
					else if (temp < 0)
						_flag--;
					else
						_flag = 0;
					_flag = std::clamp(_flag, -_MaxFlag, _MaxFlag);
				}
				_state = copySign(_flag);
			}
			else//�����趨ģʽ
			{
				_state = state;
				if ((abs(temp) >= _threshold + 20 && _count > _maxDataNums ) || (copySign(temp) != state && abs(temp) >= 3))//����仯���� �Ҽ�¼����������¼��
				{
					tempVal = (_lastData + _threshold * state);
					std::cerr << "��ֵ�仯����!����ֵ:"<< num<<" ģ��ֵ:tempVal" << std::endl;
				
				}
				else//�仯û�г���
				{
					_threshold = (_threshold + abs(temp)) / 2;//����ƽ����ֵ
				}
			}
			_count++;
			if (abs(tempVal - num) <= 100)
				_lastData = tempVal;
			else
				_lastData = num;
			return tempVal;
		}
		void print()
		{
			std::cout << "ƽ���仯ֵ:" << _threshold << " �ϴ�ֵ:" << _lastData;
			if (_state == 1)
				std::cout << " ����" << std::endl;
			else if (_state == -1)
				std::cout << " �½�" << std::endl;
			else
				std::cout << " ��ֹ" << std::endl;
		}
	private:
		const size_t _port;
		const int _MaxFlag;//flag�����ֵ
		int _lastData = 0;//�ϴε�ֵ
		int _threshold = 0;//ƽ���仯ֵ
		size_t _count = 0;//��ȡ����������
		int _flag = 0;//����FLAG
		int _state = 0;//-1 �½� 0��ֹ 1����
		size_t _maxDataNums = 0;//������ݼ�¼
	};
}