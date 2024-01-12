#include "protocolConverter.h"

#include <cstring>

ProtocolConverter::ProtocolConverter() {
	_length = 0;
	_option = nullptr;
	_data = nullptr;
}

// 加载要解码的数据
void ProtocolConverter::parseData(unsigned char * data) {
	_data = data;
}

// 加载协议规则
void ProtocolConverter::setProtocolOption(std::shared_ptr<ProtocolOption> option) {
	_option = option;
	// 初始化前缀和数组
	_length = _option->_optionList.size();

	_sum.resize(_length + 1);
	// 计算前缀和数组
	for (int i = 1; i <= _length; i++) {
		_sum[i] = _sum[i - 1] + _option->_optionList[i - 1]._length;
	}
}
OptionValue ProtocolConverter::getHeaderField(unsigned int index) {
	_Option& option = _option->_optionList[index];

	// 获取当前标记开始的位置
	int start = _sum[index];
	switch (option._type) {
	case INT: {
		int res = 0;
		for (int i = 0; i < option._length; i++) {
			res = (res << 8) + ((_data[start + i]) & 0xff);
		}
		return res;
	}
	case SIZE: {
		unsigned int res = 0;
		for (int i = 0; i < option._length; i++) {
			res = (res << 8) + ((_data[start + i]) & 0xff);
		}
		return (int)res;
	}
	case STR: {
		std::string res;
		for (int i = 0; i < option._length; i++) {
			res.push_back(_data[start + i]);
		}
		return res;
	}
	}
}

void ProtocolConverter::copyParsedData(void* destination) {
	// 计算数据部分的长度：总长度 - 首部的长度
	int data_size = std::get<int>(getHeaderField(_option->_size_index)) - _sum[_length];
	// 将内容复制出去
	memcpy(destination,  _data + _sum[_length], data_size);
}

unsigned int ProtocolConverter::getParsedDataSize() {
	// 计算数据部分的长度：总长度 - 首部的长度
	unsigned int data_size = (unsigned int)std::get<int>(getHeaderField(_option->_size_index)) - _sum[_length];
	return data_size;
}
