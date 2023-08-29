#include <iostream>
#include "protocol/protocol.h"
#include "protocol/protocolBuilder.h"
#include "protocol/protocolConverter.h"



std::shared_ptr<ProtocolOption> option = std::make_shared<ProtocolOption>();

void init() {
    option->append(1, UINT, "版本号");
    option->append(1, UINT, "消息类型");
    option->append(4, UINT, "总长度");
    option->append(2, UINT, "消息组");
    option->append(4, UINT, "偏移量");
    option->append(3, SIZE, "消息长度");
}

int main() {
    init();

    // 初始化生成器
    ProtocolBuilder builder;
    // 加载协议的格式
    builder.load(option);
    // 设置头标记
    builder.set_head(0, 1);     // 版本号          1
    builder.set_head(1, 1);     // 消息类型        1
    builder.set_head(2, 20);    // 总长度          20
    builder.set_head(3, 0);     // 消息组          0
    builder.set_head(4, 0);     // 当前消息的偏移量 0


    // 发送a数组
    char a[3] = "10";
    // 生成可用于发送的协议 
    auto proto = builder.set_data(a, 2);
    
    /////////////////////////////////
    // 发送
    //////////////////

    // 传递的过程是字符流
    unsigned char* data = static_cast<unsigned char*>(proto->data());

    //////////////////////////////////////////////
    // 
    // 接收方
    // ////////////////////////////////// 


    // 解码器
    ProtocolConverter converter;
    // 加载相同的协议格式
    converter.load(option);
    // 解码
    converter.convert(data);
    // 输出传递的原始数据
    std::cout.write(static_cast<char *>(proto->data()), proto->size());
    // 输出首部信息
    std::cout << "0 " << converter.get_head<unsigned int>(0) << std::endl;
    std::cout << "1 " << converter.get_head<unsigned int>(1) << std::endl;
    std::cout << "2 " << converter.get_head<unsigned int>(2) << std::endl;
    std::cout << "3 " << converter.get_head<unsigned int>(3) << std::endl;
    std::cout << "4 " << converter.get_head<unsigned int>(4) << std::endl;
    std::cout << "5 " << converter.get_head<unsigned int>(5) << std::endl;
    // 开一个空间，用于存放数据部分
    char b[5] = {};
    // 将数据部分放到b数组中
    converter.get_data(b);
    // 输出b的内容
    std::cout << b << std::endl;

     return 0;
}
