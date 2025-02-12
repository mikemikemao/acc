/*描述:
对于给定的若干个单词组成的句子，每个单词均由大小写字母混合构成，单词间使用单个空格分隔。输出最后一个单词的长度。
输入描述：
在一行上输入若干个字符串，每个字符串代表一个单词，组成给定的句子。
除此之外，保证每个单词非空，由大小写字母混合构成，且总字符长度不超过。
输出描述：
在一行上输出一个整数，代表最后一个单词的长度。
示例1
输入：
HelloNowcoder
复制
输出：
13
复制
说明：
在这个样例中，最后一个单词是
"HelloNowcoder"
"HelloNowcoder" ，长度为
13
13 。
示例2
输入：
A B C D
复制
输出：
1
*/

#include <iostream>
using namespace std;
#include <iostream>
#include <string>

int main() {
    std::string s;
    std::getline(std::cin, s);//接收带空格的字符串要用getline
    //反向寻找空格
    size_t pos = s.rfind(' ');
    if(pos != string::npos) {
        //有空格
        //这里size表示的是有效字符, -1才是索引
        std::cout << s.size() - pos - 1 << std::endl;
    }
    else {
        //没空格, 说明就是一个单词
        std::cout << s.size() << std::endl;
    }
    return 0;
}

