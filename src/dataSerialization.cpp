//
// Created by zheming on 15/11/15.
//


#include <iostream>
#include <string>
#include <sstream>
#include "../include/dataSerialization.h"


/* redos protocol
*<number of arguments> CR LF
$<number of bytes of argument 1> CR LF
<argument data> CR LF
...
$<number of bytes of argument N> CR LF
<argument data> CR LF

例子如下：
*3
$3
SET
$5
mykey
$7
myvalue

上面的命令看上去像是单引号字符串，所以可以在查询中看到每个字节的准确值：
"*3\r\n$3\r\nSET\r\n$5\r\nmykey\r\n$7\r\nmyvalue\r\n"

*/


std::string dataSerilize(std::string command, std::string key, std::string value) {
    std::string numOfArugments = "3";
    std::string byteSizeOfFirstArgument = std::to_string(command.length());
    std::string byteSizeOfSecondArgument = std::to_string(key.length());
    std::string byteSizeOfThirdArgument = std::to_string(value.length());
    std::string data = "*" + numOfArugments + "\r\n" +
                       "$" + byteSizeOfFirstArgument + "\r\n" +
                       command + "\r\n" +
                       "$" + byteSizeOfSecondArgument + "\r\n" +
                       key + "\r\n" +
                       "$" + byteSizeOfThirdArgument + "\r\n" +
                       value + "\r\n";


    return data;
}


std::string dataSerilize(std::string command, std::string key) {
    std::string numOfArugments = "2";
    std::string byteSizeOfFirstArgument = std::to_string(command.length());
    std::string byteSizeOfSecondArgument = std::to_string(key.length());
    std::string data = "*" + numOfArugments + "\r\n" +
                       "$" + byteSizeOfFirstArgument + "\r\n" +
                       command + "\r\n" +
                       "$" + byteSizeOfSecondArgument + "\r\n" +
                       key + "\r\n";
    return data;
}


std::string dataSerilize(std::string command, std::string key, std::string field, std::string value) {
    std::string numOfArugments = "4";
    std::string byteSizeOfFirstArgument = std::to_string(command.length());
    std::string byteSizeOfSecondArgument = std::to_string(key.length());
    std::string byteSizeOfThirdArgument = std::to_string(field.length());
    std::string byteSizeOfFourthArgument = std::to_string(value.length());
    std::string data = "*" + numOfArugments + "\r\n" +
                       "$" + byteSizeOfFirstArgument + "\r\n" +
                       command + "\r\n" +
                       "$" + byteSizeOfSecondArgument + "\r\n" +
                       key + "\r\n" +
                       "$" + byteSizeOfThirdArgument + "\r\n" +
                       field + "\r\n" +
                       "$" + byteSizeOfFourthArgument + "\r\n" +
                       value + "\r\n";
    return data;
}


std::string deserilizeGetData(char responseData[]) {
    std::string str(responseData);
    std::istringstream is(str);
    std::string dataLen;
    std::string dataValue;
    is >> dataLen >> dataValue;
    int dataRealLen = std::stoi(dataLen.substr(1));
    if (dataRealLen == -1) {
        return "(nil)";
    }
    else {
        return dataValue;
    }
}

std::string deserilizeHgetData(char responseData[]) {
    std::string str(responseData);
    std::istringstream is(str);
    std::string dataLen;
    std::string dataValue;
    is >> dataLen >> dataValue;
    int dataRealLen = std::stoi(dataLen.substr(1));
    if (dataRealLen == -1) {
        return "(nil)";
    }
    else {
        return dataValue;
    }
}

/*
*10
$3
age
$2
20
$6
school
$5
fudan
$3
sex
$4
male
$4
from
$8
zhejiang
$2
to
$8
shanghai
 */

/*
127.0.0.1:6379> HGETALL wangzheming
 1) "age"
 2) "20"
 3) "school"
 4) "fudan"
 5) "sex"
 6) "male"
 7) "from"
 8) "zhejiang"
 9) "to"
10) "shanghai"
 */
void deserilizeHgetallData(char responseData[]) {
    std::string str(responseData);
    std::istringstream is(str);
    std::string dataLen;
    std::string dataValue;
    is >> dataLen;
    int dataRealLen = std::stoi(dataLen.substr(1));
    if (dataRealLen == 0) {
        std::cout << "empty list or set" << std::endl;
    }
    else {
        for (int i = 1; i <= dataRealLen; ++i) {
            std::string bytesize;
            std::string realdata;
            is >> bytesize >> realdata;
            std::cout << std::to_string(i) << ") \"" << realdata << "\"" << std::endl;
        }
    }
}