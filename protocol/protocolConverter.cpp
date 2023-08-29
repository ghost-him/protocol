#include "protocolConverter.h"

ProtocolConverter::ProtocolConverter() {
	_length = 0;
	_option = nullptr;
	_data = nullptr;
}

// ����Ҫ���������
void ProtocolConverter::convert(unsigned char* data) {
	_data = data;
}

// ����Э�����
void ProtocolConverter::load(std::shared_ptr<ProtocolOption> option) {
	_option = option;
	// ��ʼ��ǰ׺������
	_length = _option->_optionList.size();

	_sum.resize(_length + 1);
	// ����ǰ׺������
	for (int i = 1; i <= _length; i++) {
		_sum[i] = _sum[i - 1] + _option->_optionList[i - 1]._length;
	}
}


void ProtocolConverter::get_data(void* destination) {
	// �������ݲ��ֵĳ��ȣ��ܳ��� - �ײ��ĳ���
	unsigned int data_size = get_head<unsigned int>(_option->_size_index) - _sum[_length];
	// �����ݸ��Ƴ�ȥ
	memcpy(destination,  _data + _sum[_length], data_size);
}

unsigned int ProtocolConverter::get_data_size() {
	// �������ݲ��ֵĳ��ȣ��ܳ��� - �ײ��ĳ���
	unsigned int data_size = get_head<unsigned int>(_option->_size_index) - _sum[_length];
	return data_size;
}