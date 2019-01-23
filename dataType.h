#pragma once
#include <any>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using DataConfig = std::vector<std::string>;                           //����һ��CONFIG������
using DataConfigList = std::vector<DataConfig>;                        //����� �������� ���������
using DataUnorderedList = std::unordered_map<std::string, DataConfig>; //����Ĺ�ϣ��
using DataConfigListSet = std::unordered_map<std::string, DataConfigList>; //config�б������ �����ϣ
using PidDebugTuple = std::tuple<uint32_t, double, double, double, double, double>; //PIDDATA������
