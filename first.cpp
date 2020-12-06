//
// Created by 任艺伟 on 2020/9/20.
//

#include "first.h"
#include <iostream>
#include <stack>
using namespace std;
stack<string> transfer();
double result(stack<string>);

int main(){
    cout<<result(transfer());
    return 0;
}

stack<string> transfer(){
    stack<char> operation;
    stack<string> final;
    string data;
    cin>>data;
    stack<string> result;

    for(int i=0;i<data.length();i++){
        switch (data[i]) {
            case '-' : case '+' :
                if(data[i]=='-'){
                    if(i==0) final.push("0");
                    else if(!isdigit(data[i-1])){
                        if(data[i-1]!=')') final.push("0");
                    }
                }
                if(operation.empty()) operation.push(data[i]);
                else{
                    while(!operation.empty()){
                        string temp = "";
                        temp.push_back(operation.top());
                        final.push(temp);
                        operation.pop();
                    }
                    operation.push(data[i]);
                }
                break;
            case '*' : case '/' :
                if(operation.empty()||operation.top()=='+'||operation.top()=='-')operation.push(data[i]);
                else{
                    while(operation.top()=='*'||operation.top()=='/'){
                        final.push(to_string(operation.top()));
                        operation.pop();
                    }
                    operation.push(data[i]);
                }
                break;
            default:
                string s;
                while(i<data.length()&&(isdigit(data[i])||data[i]=='.')){
                    s = s+data[i];
                    i++;
                }
                i--;
                final.push(s);
//                cout<<final.size()<<" "<<final.top()<<endl;
        }
    }

//    cout<<operation.size()<<endl;
    while(!operation.empty()){
        string temp = "";
        temp.push_back(operation.top());
        final.push(temp);
//        cout<<final.top()<<endl;
        operation.pop();
    }

//    cout<<final.size()<<endl;
    while(!final.empty()){
//        cout<<final.top();
        result.push(final.top());
        cout<<final.top()<<" ";
        final.pop();
    }
    cout<<endl;

    return result;
}

double result(stack<string> transfer){
    stack<double> calculate;
    bool judge;
    double number1,number2;
    while(!transfer.empty()){
        if(transfer.top()=="+"){
            number1 = calculate.top();
            calculate.pop();
            number2 = calculate.top();
            calculate.pop();
            calculate.push(number1+number2);
        }else if(transfer.top()=="-"){
            number1 = calculate.top();
            calculate.pop();
            number2 = calculate.top();
            calculate.pop();
            calculate.push(number2-number1);
        }else if(transfer.top()=="*"){
            number1 = calculate.top();
            calculate.pop();
            number2 = calculate.top();
            calculate.pop();
            calculate.push(number2*number1);
        }else if(transfer.top()=="/"){
            number1 = calculate.top();
            calculate.pop();
            number2 = calculate.top();
            calculate.pop();
//            cout<<number2<<"  "<<number1<<endl;
//            cout<<2*1.0/4<<endl;
            calculate.push(number2*1.0/number1);
        }else{
            calculate.push(stod(transfer.top()));
        }

        transfer.pop();
    }

    return calculate.top();
}

