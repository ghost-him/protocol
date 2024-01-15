//
// Created by ghost-him on 24-1-15.
//
#include <iostream>
#include "protocol.h"
#include "protocolBuilder.h"
#include "protocolConverter.h"

std::shared_ptr<ProtocolOption> option = std::make_shared<ProtocolOption>();

void init() {
    option->append(1, INT, "版本号");
    option->append(1, INT, "消息类型");
    option->append(4, INT, "总长度");
    option->append(2, INT, "消息组");
    option->append(4, INT, "偏移量");
    option->append(8, STR, "说明信息");
    option->append(3, SIZE, "消息长度");
}

int main() {
    init();

    // 初始化生成器
    ProtocolBuilder builder;
    // 加载协议的格式
    builder.setProtocolOption(option);
    // 设置头标记
    builder.setHeaderField(0, 1);     // 版本号          1
    builder.setHeaderField(1, 1);     // 消息类型        1
    builder.setHeaderField(2, 20);    // 总长度          20
    builder.setHeaderField(3, 0);     // 消息组          0
    builder.setHeaderField(4, 0);     // 当前消息的偏移量 0
    builder.setHeaderField(5, "12345678");     // 说明信息 0


    // 发送a数组
    char a[3] = "10";
    // 生成可用于发送的协议
    auto proto = builder.buildWithData(a, 2);

    /////////////////////////////////
    // 发送
    //////////////////

    // 传递的过程是字符流
    unsigned char* data = static_cast<unsigned char*>(proto->data());

    std::bitset<8> bit;
    for (int i = 0; i < 50; i++) {
        bit = data[i];
        std::cout << bit << " ";
    }
    std::cout << std::endl;

    //////////////////////////////////////////////
    //
    // 接收方
    // //////////////////////////////////


    // 解码器
    ProtocolConverter converter;
    // 加载相同的协议格式
    converter.setProtocolOption(option);
    // 解码
    converter.parseData(data);
    // 输出传递的原始数据
    // std::cout.write(static_cast<char *>(proto->data()), proto->size());
    // 输出首部信息
    std::cout << "0 " << std::get<long long>(converter.getHeaderField(0)) << std::endl;
    std::cout << "1 " << std::get<long long>(converter.getHeaderField(1)) << std::endl;
    std::cout << "2 " << std::get<long long>(converter.getHeaderField(2)) << std::endl;
    std::cout << "3 " << std::get<long long>(converter.getHeaderField(3)) << std::endl;
    std::cout << "4 " << std::get<long long>(converter.getHeaderField(4)) << std::endl;

    std::cout << "5 " << std::get<std::string>(converter.getHeaderField(5)) << std::endl;
    std::cout << "6 " << std::get<unsigned int>(converter.getHeaderField(6)) << std::endl;
    // 开一个空间，用于存放数据部分
    char b[5] = {};
    // 将数据部分放到b数组中
    converter.copyParsedData(b);
    std::cout << "解析出数据内容为 ";
    // 输出b的内容
    std::cout << b << std::endl;

    return 0;
}