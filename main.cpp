#include <iostream>
#include "protocol/protocol.h"
#include "protocol/protocolBuilder.h"
#include "protocol/protocolConverter.h"



std::shared_ptr<ProtocolOption> option = std::make_shared<ProtocolOption>();

void init() {
    option->append(1, UINT, "�汾��");
    option->append(1, UINT, "��Ϣ����");
    option->append(4, UINT, "�ܳ���");
    option->append(2, UINT, "��Ϣ��");
    option->append(4, UINT, "ƫ����");
    option->append(3, SIZE, "��Ϣ����");
}

int main() {
    init();

    // ��ʼ��������
    ProtocolBuilder builder;
    // ����Э��ĸ�ʽ
    builder.load(option);
    // ����ͷ���
    builder.set_head(0, 1);     // �汾��          1
    builder.set_head(1, 1);     // ��Ϣ����        1
    builder.set_head(2, 20);    // �ܳ���          20
    builder.set_head(3, 0);     // ��Ϣ��          0
    builder.set_head(4, 0);     // ��ǰ��Ϣ��ƫ���� 0


    // ����a����
    char a[3] = "10";
    // ���ɿ����ڷ��͵�Э�� 
    auto proto = builder.set_data(a, 2);
    
    /////////////////////////////////
    // ����
    //////////////////

    // ���ݵĹ������ַ���
    unsigned char* data = static_cast<unsigned char*>(proto->data());

    //////////////////////////////////////////////
    // 
    // ���շ�
    // ////////////////////////////////// 


    // ������
    ProtocolConverter converter;
    // ������ͬ��Э���ʽ
    converter.load(option);
    // ����
    converter.convert(data);
    // ������ݵ�ԭʼ����
    std::cout.write(static_cast<char *>(proto->data()), proto->size());
    // ����ײ���Ϣ
    std::cout << "0 " << converter.get_head<unsigned int>(0) << std::endl;
    std::cout << "1 " << converter.get_head<unsigned int>(1) << std::endl;
    std::cout << "2 " << converter.get_head<unsigned int>(2) << std::endl;
    std::cout << "3 " << converter.get_head<unsigned int>(3) << std::endl;
    std::cout << "4 " << converter.get_head<unsigned int>(4) << std::endl;
    std::cout << "5 " << converter.get_head<unsigned int>(5) << std::endl;
    // ��һ���ռ䣬���ڴ�����ݲ���
    char b[5] = {};
    // �����ݲ��ַŵ�b������
    converter.get_data(b);
    // ���b������
    std::cout << b << std::endl;

     return 0;
}
