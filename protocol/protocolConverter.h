#pragma once
#include "protocol.h"
#include "protocolOption.h"



class ProtocolConverter {
public:
	ProtocolConverter();
	// ����Ҫ���������
	void convert(unsigned char* data);

	// ����Э�����
	void load(std::shared_ptr<ProtocolOption> option);

	template<class value>
	value get_head(unsigned int index) {
		_Option& option = _option->_optionList[index];

		// ��ȡ��ǰ��ǿ�ʼ��λ��
		int start = _sum[index];
		switch (option._type) {
		case INT: {
			int res = 0;
			for (int i = option._length - 1; i >= 0; i--) {
				res = (res << 8) + ((_data[start + i]) & 0xff);
			}
			return res;
		} 
		case SIZE:
		case UINT: {
			unsigned int res = 0;
			for (int i = option._length - 1; i >= 0; i--) {
				res = (res << 8) + ((_data[start + i]) & 0xff);
			}
			return res;
		}
		}
	}

	void get_data(void* destination);
	unsigned int get_data_size();

private:
	// ���ݵ�ԭ��ַ
	unsigned char* _data;
	// Э���ʽ
	std::shared_ptr<ProtocolOption> _option;
	// ͷ��ǵĸ���
	unsigned int _length;
	// ͷ��ǵ���ʼλ��
	std::deque<unsigned int> _sum;
	
};
