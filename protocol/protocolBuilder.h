#pragma once
#include "protocolOption.h"
#include "protocol.h"

class ProtocolBuilder {
public:
	ProtocolBuilder();
	// ����Э���ʽ
	void load(std::shared_ptr<ProtocolOption> option);
	// ����ͷ���
	// �±��0��ʼ
	template<class Data>
	void set_head(unsigned int index, Data data) {
		_Option& option = _option->_optionList[index];

		// ��ȡ��ǰ��ǿ�ʼ��λ��
		unsigned int start = _sum[index];
		for (int i = 0; i < option._length; i++) {
			_head[start + i] = (data >> (8 * i)) & 0xff;
		}
	}
	// ������������
	std::shared_ptr<Protocol> set_data(void* data, unsigned int size);


private:
	std::shared_ptr<ProtocolOption> _option;

	// ͷ��ǵĸ���
	unsigned int _length;
	// ͷ��ǵ���ʼλ��
	std::deque<unsigned int> _sum;
	// ͷ��ǻ�����
	std::unique_ptr<unsigned char[]> _head;
};