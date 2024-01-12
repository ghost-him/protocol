#include <iostream>
#include "protocol/protocol.h"
#include "protocol/protocolBuilder.h"
#include "protocol/protocolConverter.h"

std::shared_ptr<ProtocolOption> option = std::make_shared<ProtocolOption>();

void init() {
    option->append(1, INT, "�汾��");
    option->append(1, INT, "��Ϣ����");
    option->append(4, INT, "�ܳ���");
    option->append(2, INT, "��Ϣ��");
    option->append(4, INT, "ƫ����");
    option->append(8, STR, "˵����Ϣ");
    option->append(3, SIZE, "��Ϣ����");
}

int main() {
    init();

    // ��ʼ��������
    ProtocolBuilder builder;
    // ����Э��ĸ�ʽ
    builder.setProtocolOption(option);
    // ����ͷ���
    builder.setHeaderField(0, 1);     // �汾��          1
    builder.setHeaderField(1, 1);     // ��Ϣ����        1
    builder.setHeaderField(2, 20);    // �ܳ���          20
    builder.setHeaderField(3, 0);     // ��Ϣ��          0
    builder.setHeaderField(4, 0);     // ��ǰ��Ϣ��ƫ���� 0
    builder.setHeaderField(5, "12345678");     // ˵����Ϣ 0


    // ����a����
    char a[3] = "10";
    // ���ɿ����ڷ��͵�Э�� 
    auto proto = builder.buildWithData(a, 2);
    
    /////////////////////////////////
    // ����
    //////////////////

    // ���ݵĹ������ַ���
    unsigned char* data = static_cast<unsigned char*>(proto->data());

    std::bitset<8> bit;
    for (int i = 0; i < 50; i++) {
        bit = data[i];
        std::cout << bit << " ";
    }
    std::cout << std::endl;

    //////////////////////////////////////////////
    // 
    // ���շ�
    // ////////////////////////////////// 


    // ������
    ProtocolConverter converter;
    // ������ͬ��Э���ʽ
    converter.setProtocolOption(option);
    // ����
    converter.parseData(data);
    // ������ݵ�ԭʼ����
   // std::cout.write(static_cast<char *>(proto->data()), proto->size());
    // ����ײ���Ϣ
    std::cout << "0 " << std::get<int>(converter.getHeaderField(0)) << std::endl;
    std::cout << "1 " << std::get<int>(converter.getHeaderField(1)) << std::endl;
    std::cout << "2 " << std::get<int>(converter.getHeaderField(2)) << std::endl;
    std::cout << "3 " << std::get<int>(converter.getHeaderField(3)) << std::endl;
    std::cout << "4 " << std::get<int>(converter.getHeaderField(4)) << std::endl;

    std::cout << "5 " << std::get<std::string>(converter.getHeaderField(5)) << std::endl;
    std::cout << "6 " << std::get<int>(converter.getHeaderField(6)) << std::endl;
    // ��һ���ռ䣬���ڴ�����ݲ���
    char b[5] = {};
    // �����ݲ��ַŵ�b������
    converter.copyParsedData(b);
    std::cout << "��������������Ϊ ";
    // ���b������
    std::cout << b << std::endl;
    
     return 0;
}
