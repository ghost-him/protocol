#pragma once
#include "protocolOption.h"
#include "protocol.h"

class ProtocolBuilder {
public:
	ProtocolBuilder();
	// 设置协议格式
	void setProtocolOption(std::shared_ptr<ProtocolOption> option);

	// 设置特定索引的首部字段的值
	void setHeaderField(unsigned int index, const OptionValue& value);

	// 设置协议数据内容
	std::shared_ptr<Protocol> buildWithData(void* data, unsigned int size);


private:
	std::shared_ptr<ProtocolOption> _option;

	// 头标记的个数
	unsigned int _length;
	// 头标记的启始位置
	std::deque<unsigned int> _sum;
	// 头标记缓冲区
	std::unique_ptr<unsigned char[]> _head;
};
