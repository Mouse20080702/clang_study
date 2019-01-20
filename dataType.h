#pragma once
#include <any>
#include <string>
#include <tuple>
#include <vector>

	using DataConfig = std::vector<std::string>;           //����һ��CONFIG������
	using DataConfigList = std::vector<DataConfig>;        //�����
	using DataConfigListSet = std::vector<DataConfigList>; //config�б������

	using PidDebugTuple = std::tuple<uint32_t, double, double, double, double, double>; //PIDDATA������