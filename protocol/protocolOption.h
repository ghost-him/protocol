#pragma once
#include <string>
#include <deque>
#include <bitset>

#define PROTOCOL_SIZE 4096
#define PROTOCOL_TYPE_SIZE 50


enum protocolType {
	UINT,
	INT,
	STR,
	SIZE
};

class _Option {
public:
	protocolType _type;
	int _length;
	std::string _description;
};


class ProtocolOption {
	friend class ProtocolConverter;
	friend class ProtocolBuilder;
public:
	ProtocolOption();
	// ��ȡ���η��͵���󳤶�
	unsigned int size();

	// ��ӣ�
	// ռ�õ��ֽڳ��ȣ���Ϣ���ͣ�����
	bool append(unsigned int length, protocolType type, std::string description = "");

private:
	// ������Ϣ
	std::bitset<1> _control;

	std::deque<_Option> _optionList;
	// ����ָ����Ϣ���ȵ��±�
	unsigned int _size_index;
	// ����������Ϣ����󳤶�
	unsigned int _size;
};
