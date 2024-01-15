#include "protocolBuilder.h"

#include <cstring>

ProtocolBuilder::ProtocolBuilder() {
	_length = 0;
	_option = nullptr;
}

void ProtocolBuilder::setProtocolOption(std::shared_ptr<ProtocolOption> option) {
	_option = option;

	// 初始化前缀和数组
	_length = _option->_optionList.size();
	_sum.resize(_length + 1);
	// 计算前缀和数组
	for (int i = 1; i <= _length; i++) {
		_sum[i] = _sum[i - 1] + _option->_optionList[i - 1]._length;
	}
	// 开辟一个头标记长度的空间，给头标记缓冲区
	// _sum[_length]表示头标记的长度
	_head.reset(new unsigned char[_sum[_length]]);
}

void ProtocolBuilder::setHeaderField(unsigned int index, const OptionValue& value) {
	_Option& option = _option->_optionList[index];
	// 获取当前标记开始的位置
	unsigned int start = _sum[index];

	switch (option._type) {
	case STR: {
		std::string str = std::get<std::string>(value);
		for (unsigned int i = 0; i < option._length && i < str.size(); i++) {
			_head[start + i] = str[i];
		}
		break;
	}
    case SIZE:
	case INT: {
		long long data;
        data = std::get<long long>(value);
		for (int i = 0; i < option._length; i++) {
			_head[start + (option._length - 1) - i] = (data >> (8 * i)) & 0xff;
		}
		break;
	}
	}
}


// 设置数据内容
std::shared_ptr<Protocol> ProtocolBuilder::buildWithData(void* data, unsigned int size) {
	// 计算总长度 总长度 = 首部长度 + 数据长度
	unsigned int total_size = _sum[_length] + size;
	// 判断数据大小是否合法
	if (total_size > _option->maxSize()) {
		return nullptr;
	}
	// 如果满足
	std::shared_ptr<Protocol> res = std::make_shared<Protocol>();
	// 初始化协议对象，赋予长度和空间
	res->_size = total_size;
	res->_data.reset(new unsigned char[total_size]);
	// 设置数据部分的长度
	setHeaderField(_option->_size_index, (int)total_size);
	// 复制头标记的内容
	memcpy(res->_data.get(), _head.get(), _sum[_length]);
	// 复制数据部分的内容
	memcpy(res->_data.get() + _sum[_length], data, size);
    return res;
}

std::shared_ptr<Protocol> ProtocolBuilder::buildWithPlainBuffer(void *data, unsigned int size)
{
    std::shared_ptr<Protocol> res = std::make_shared<Protocol>();
    res->_data.reset(new unsigned char[size]);
    memcpy(res->_data.get(), data, size);
    return res;
}

