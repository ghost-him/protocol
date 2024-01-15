#pragma once
#include "protocol.h"
#include "protocolOption.h"

class ProtocolConverter {
public:
	ProtocolConverter();
	// 加载要解析的协议数据
	void parseData(unsigned char * data);

	// 设置协议解析规则
	void setProtocolOption(std::shared_ptr<ProtocolOption> option);
	
	// 获取特定索引的首部字段值
	OptionValue getHeaderField(unsigned int index);

	// 将解析的协议数据复制到目标缓冲区
	void copyParsedData(void* destination);

	// 获取解析的协议数据大小
	unsigned int getParsedDataSize();


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
