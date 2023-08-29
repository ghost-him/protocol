#pragma once
#include <bitset>
#include "protocolOption.h"
#include <memory>


class Protocol {
    friend class ProtocolConverter;
    friend class ProtocolBuilder;
public:
    Protocol();
    Protocol(const Protocol& pro);

    const Protocol& operator=(const Protocol& pro);

    // ��ȡ����ָ��
    void* data();
    // ��ȡ����ĳ���
    unsigned int size();

private:
    // ���ڴ洢��ǰ������
    std::unique_ptr<unsigned char[]> _data;
    // ��ǰ�ĳ���
    unsigned int _size;

    void init(const Protocol& pro);
};