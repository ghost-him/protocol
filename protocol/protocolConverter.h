#pragma once
#include "protocol.h"
#include "protocolOption.h"



class ProtocolConverter {
public:
	ProtocolConverter();
	// 加载要解码的数据
	void convert(unsigned char* data);

	// 加载协议规则
	void load(std::shared_ptr<ProtocolOption> option);

	template<class Value>
	Value get_head(unsigned int index) {
		_Option& option = _option->_optionList[index];

		// 获取当前标记开始的位置
		int start = _sum[index];
		switch (option._type) {
		case INT: {
			int res = 0;
			for (int i = option._length; i >= 0; i--) {
				res = (res << 8) + (_data[start + i] << (8 * i)) & 0xff;
			}
			return res;
		} 
		case SIZE:
		case UINT: {
			unsigned int res = 0;
			for (int i = option._length; i >= 0; i--) {
				res = (res << 8) + (_data[start + i] << (8 * i)) & 0xff;
			}
			return res;
		} case STR: {
			std::string res;
			for (int i = 0; i < option._length; i++) {
				res.push_back(static_cast<char>(_data[start + i]));
			}
		}
		}
	}

	void get_data(void* destination);

private:
	// 数据的原地址
	unsigned char* _data;
	// 协议格式
	std::shared_ptr<ProtocolOption> _option;
	// 头标记的个数
	unsigned int _length;
	// 头标记的启始位置
	std::deque<unsigned int> _sum;
	
};
