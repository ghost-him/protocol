#pragma once
#include <string>
#include <deque>
#include <bitset>
#include <variant>

enum protocolType {
	INT,
	STR,
	SIZE
};

class _Option {
public:
	protocolType _type;
	int _length = 0;
	std::string _description;
};


using OptionValue = std::variant<int, unsigned int, std::string>;

class ProtocolOption {
	friend class ProtocolConverter;
	friend class ProtocolBuilder;
public:
	ProtocolOption();
	// 获取单次发送的最大长度
	unsigned int maxSize();
	// 添加，
	// 占用的字节长度，信息类型，描述
	bool append(unsigned int length, protocolType type, std::string description = "");

private:
	// 控制信息
	std::bitset<1> _control;

	std::deque<_Option> _optionList;
	// 表明指定消息长度的下标
	unsigned int _size_index;
	// 表明单个消息的最大长度:由SIZE字段的位数控制
	unsigned int _maxSize;
};
