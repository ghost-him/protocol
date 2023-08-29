#include "protocolBuilder.h"

ProtocolBuilder::ProtocolBuilder() {
	_length = 0;
	_option = nullptr;
}

void ProtocolBuilder::load(std::shared_ptr<ProtocolOption> option) {
	_option = option;

	// ��ʼ��ǰ׺������
	_length = _option->_optionList.size();
	_sum.resize(_length + 1);
	// ����ǰ׺������
	for (int i = 1; i <= _length; i++) {
		_sum[i] = _sum[i - 1] + _option->_optionList[i - 1]._length;
	}
	// ����һ��ͷ��ǳ��ȵĿռ䣬��ͷ��ǻ�����
	// _sum[_length]��ʾͷ��ǵĳ���
	_head.reset(new unsigned char[_sum[_length]]);
}
// ������������
std::shared_ptr<Protocol> ProtocolBuilder::set_data(void* data, unsigned int size) {
	std::shared_ptr<Protocol> res = std::make_shared<Protocol>();
	// �����ܳ��� �ܳ��� = �ײ����� + ���ݳ���
	unsigned int total_size = _sum[_length] + size;
	// ��ʼ��Э����󣬸��賤�ȺͿռ�
	res->_size = total_size;
	res->_data.reset(new unsigned char[total_size]);
	// �������ݲ��ֵĳ���
	set_head(_option->_size_index, total_size);
	// ����ͷ��ǵ�����
	memcpy(res->_data.get(), _head.get(), _sum[_length]);
	// �������ݲ��ֵ�����
	memcpy(res->_data.get() + _sum[_length], data, size);
	return res;
}

