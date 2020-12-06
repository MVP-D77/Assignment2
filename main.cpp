#include "final.cpp"
#include <iostream>

using namespace std;

int main(){
    cout<<"欢迎使用CS205专属计算器！！"<<endl;
    cout<<"本计算器支持正常四则运算，高精度加法，减法，乘法，变量表达式，以及部分函数的使用"<<endl;
    cout<<"支持连续计算，输入stop结束计算器运行"<<endl;
    cout<<"附函数列表：sqrt 开方；exp e的指数；pow(m,n) m的n次幂；log10 取对数；abs 取绝对值；sin 正弦;"<<endl;
    cout<<"cos 余弦；tan 正切；atan 反正切；ceil 向上取整；floor 向下取整；rand 随机数"<<endl;
    cout<<"轻敲回车快来使用叭！！！";
    getchar();
    cout<<"请输入要计算的表达式"<<endl;
    string final ="";
    while(true) {
        string temp = "Final="+final;
        final =simplify(result(transfer(pretreatment(temp))));
        cout<<final<<endl;
        cout<<"请输入要计算的表达式"<<endl;
    }
    return 0;
}