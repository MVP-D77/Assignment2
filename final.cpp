//
// Created by 任艺伟 on 2020/9/21.
//

#include <iostream>
#include <stack>
#include "Calculate.cpp"
#include <cmath>

using namespace std;
stack<string> transfer(string);
string result(stack<string>);
string pretreatment(string);
bool judge_consist(string ,char);
string functionRes (string ,string);
string simplify (string);


//int main(){
//    cout<<result(transfer(pretreatment()));
//    return 0;
//}

string pretreatment(string initial){
    stack<string> midterm;
    if (initial!="Final=" ) midterm.push(initial);
    string result;
    while(getline(cin,result)) {
        if(result=="stop") {
            cout<<"感谢您的使用！！"<<endl;
            exit(-1);
        }
        midterm.push(result);
        if (!judge_consist(result,'=') ){
            midterm.pop();
            break;
        }
    }
    while(!midterm.empty()){
        string signal = midterm.top().substr(0,midterm.top().find("="));
        string number = midterm.top().substr(midterm.top().find("=")+1);
        while(result.find(signal)!=-1) {
            result.replace(result.find(signal), signal.length(), number);
        }
        midterm.pop();
    }

    string  function[] = {"sqrt","exp","pow","log10","abs","sin","cos","tan","atan","ceil","floor","rand"};
    for(int i=0;i<12;i++){
        if(result.find(function[i])!=-1){
            while(result.find(function[i])!=-1){
                int first_position = result.find(function[i]);
                int start_position = result.find(function[i])+function[i].length()+1;
                int final_position = result.find(')',result.find(function[i]));
                string value = result.substr(start_position,final_position-start_position);
//                cout<<value<<endl;
                string function_value =simplify(functionRes(function[i],value));
                if(function_value=="") return"";
                result.replace(first_position,final_position-first_position+1,function_value);
            }
        }
    }
    int index=0;
    while(judge_consist(result,' ')) {
        index=result.find(' ');
        result.erase(index,1);
    }
    return result;
}

string simplify(string value){
    string signal = value[0] =='-'?"-":"";
    value = value[0]=='-'?value.substr(1):value;

    if(judge_consist(value,'.')) {
        int j = value.length() - 1;
        while (value[j] == '0' && value[j - 1] == '0') j--;
        if(value[value.length()-1]=='0') {
            if (value[j - 1] == '.') value = value.substr(0, j - 1);
            else value = value.substr(0, j);
        }
    }
    int k=0;
    if(value.length()>1) {
        while (value[k] == '0' && value[k + 1] == '0') k++;
        if (value[0] == '0'&&value[1]!='.') value = value.substr(k + 1);
    }
    return signal+value;
}

string functionRes (string name,string value){

    if(name=="sqrt") {
        if(stod(value)>=0) {
            return to_string(sqrt(stod(value)));
        }else {
            cout<<"sqrt函数中的值小于0，请检查运算表达式"<<endl;
            return "";
        }
    }
    else if (name=="exp") return to_string(sqrt(stod(value)));
    else if (name=="log") {
        if(stod(value)>=0) {
            return to_string(log(stod(value)));
        }else {
            cout<<"log函数中的值小于0，请检查运算表达式"<<endl;
            return "";
        }
    }
    else if (name=="log10") {
        if(stod(value)>=0) {
            return to_string(log10(stod(value)));
        }else {
            cout<<"log10函数中的值小于0，请检查运算表达式"<<endl;
            return "";
        }
    }
    else if (name=="sin") return to_string(sin(stod(value)));
    else if (name=="abs") return to_string(abs(stod(value)));
    else if (name=="cos") return to_string(cos(stod(value)));
    else if (name=="tan") return to_string(tan(stod(value)));
    else if (name=="atan") return to_string(atan(stod(value)));
    else if (name=="ceil") return to_string(ceil(stod(value)));
    else if (name=="floor") return to_string(floor(stod(value)));
    else if (name=="rand") return to_string(rand());
    else{
        int position = value.find(',');
        string value1 = value.substr(0,position);
//        cout<<value1<<endl;
        string value2 = value.substr(position+1);
        return  to_string(pow(stod(value1),stod(value2)));
    }
}

stack<string> transfer(string data){
    stack<char> operation;
    stack<string> final;
    stack<string> result;
    stack<string> sign;

    if(data.length()==0) return sign;
    else{
        for(int i=0;i<data.length();i++){
            if(data[i]-'0'>10&&data[i]-'0'>=0){
                if(data[i]!='+'&&data[i]!='-'&&data[i]!='*'&&data[i]!='/'&&data[i]!=')'&&data[i]!='('){
                    cout<<"输入的运算表达式中除可调用的函数之外，有其他字母或者非法字符，请检查表达式输入"<<endl;
                    return sign;
                }
            }
        }
    }

    for(int i=0;i<data.length();i++){
        switch (data[i]) {
            case '(':
                operation.push('(');
                break;
            case ')': {
                while (operation.top()!='('){
                        string temp = "";
                        temp.push_back(operation.top());
                        final.push(temp);
                        operation.pop();
                        if(operation.empty()) {
                            cout << "运算表达式中左括号与右括号不匹配" << endl;
                            return sign;
                        }
                }
                operation.pop();
                break;
            }
            case '-' : case '+' :
                if(i==data.length()-1){
                    cout<<"末尾运算符"<<data[i]<<"后面缺少数字"<<endl;
                    return sign;
                }else if(!isdigit(data[i+1])&&data[i+1]!='('&&data[i+1]!=')'){
                    cout<<"出现连续运算符"<<data[i]<<data[i+1]<<"请检查输入的运算表达式"<<endl;
                    return sign;
                }
                if(data[i]=='+'){
                    if(i==0||data[i-1]=='(') break;
                }
                if(data[i]=='-'){
                    if(i==0) final.push("0");
                    else if(!isdigit(data[i-1])){
                        if(data[i-1]!=')'&&data[i-1]!='!') final.push("0");
                    }
                }
                if(operation.empty()||operation.top()=='(') operation.push(data[i]);
                else{
                    while(!operation.empty()&&operation.top()!='('){
                        string temp = "";
                        temp.push_back(operation.top());
                        final.push(temp);
                        operation.pop();
                    }
                    operation.push(data[i]);
                }
                break;
            case '*' : case '/' :
                if(i==data.length()-1){
                    cout<<"末尾运算符"<<data[i]<<"后面缺少数字"<<endl;
                    return sign;
                }else if(!isdigit(data[i+1])&&data[i+1]!='('&&data[i+1]!=')'){
                    cout<<"出现连续运算符"<<data[i]<<data[i+1]<<"请检查输入的运算表达式"<<endl;
                    return sign;
                }
                if(i==0) {
                    cout<<"表达式不能以"<<data[i]<<"开始，请检查表达式正确与否"<<endl;
                    return sign;
                }
                if(operation.empty()||operation.top()=='+'||operation.top()=='-'||operation.top()=='(')operation.push(data[i]);
                else{
                    while(!operation.empty()&&(operation.top()=='*'||operation.top()=='/')){
                        string temp="";
                        temp.push_back(operation.top());
                        final.push(temp);
                        operation.pop();
                    }
                    operation.push(data[i]);
                }
                break;
            case'!':    final.push("!");
                        break;
            default:
                    string s;
                    while (i < data.length() && (isdigit(data[i]) || data[i] == '.')) {
                        s = s + data[i];
                        i++;
                    }
                    i--;
                    final.push(s);
        }
    }

    while(!operation.empty()){
        string temp = "";
        temp.push_back(operation.top());
        if(temp=="("){
            cout<<"左括号缺少对应的右括号，请检查运算表达式"<<endl;
            return sign;
        }

        final.push(temp);
        operation.pop();
    }

    while(!final.empty()){
        result.push(final.top());
//        cout<<result.top()<<" ";
        final.pop();
    }

//    cout<<endl;
    return result;
}

string result(stack<string> transfer){
    stack<string> calculate;
    bool judge;
    string number1,number2;
    while(!transfer.empty()){
        if(transfer.top()=="+"||transfer.top()=="-"||transfer.top()=="*"){
            number1 = calculate.top();
            calculate.pop();
            number2 = calculate.top();
            calculate.pop();
            calculate.push(simplify(makeArray(number2,number1,transfer.top())));
        }else if(transfer.top()=="/"){
            number1 = calculate.top();
            calculate.pop();
            number2 = calculate.top();
            if(number2=="0"){
                cout<<"请检查除号后面的除数，出现除数为0的情况";
                return "";
            }
            calculate.pop();
            calculate.push(simplify(to_string(stod(number2)*1.0/stod(number1))));
//            cout<<calculate.top()<<endl;

        }else if(transfer.top()=="!"){
            number1 = calculate.top();
            calculate.pop();
            if(judge_consist(number1,'.')){
                cout<<"抱歉，计算器仅支持整数阶乘"<<endl;
                return "";
            }else{
                int result =1;
                for(int i=stoi(number1);i>0;i--){
                    result*=i;
                }
                calculate.push(to_string(result));
            }
        }
        else{
//            stod double stod转化成double 会损失一位精度。
            calculate.push(simplify(transfer.top()));
        }
        transfer.pop();
    }

    if(calculate.empty()){
        return "";
    }
    else return calculate.top();
}

