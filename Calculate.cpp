//
// Created by 任艺伟 on 2020/9/21.
//

#include <iostream>
#include <cmath>

using namespace std;
string makeArray(string,string,string);
bool judge_consist(string ,char);
string inverse(string);
string bigPlus(int*,int*,int,int);
string bigMinus(int*,int*,int,int);
string bigMultiple(int*,int*,int,int);

//int main(){
//    string a;
//    string b;
//    string c;
//    cin>>a>>b>>c;
//    cout<<makeArray(a,b,c);
//
//    return 0;
//}
string makeArray(string number1,string number2,string operation){
    string number1_digit;
    string number2_digit;
    string number1_decimals;
    string number2_decimals;

    char first_signal = number1[0]=='-'?'-':'+';
    char second_signal= number2[0]=='-'?'-':'+';
    number1 = number1[0]=='-'?number1.substr(1):number1;
    number2 = number2[0]=='-'?number2.substr(1):number2;


    if(judge_consist(number1,'.')){
        number1_digit = inverse(number1.substr(0,number1.find('.')));
        number1_decimals = inverse(number1.substr(number1.find('.')+1));
    }else{
        number1_digit=inverse(number1);
    }
    if(judge_consist(number2,'.')){
        number2_digit = inverse(number2.substr(0,number2.find('.')));
        number2_decimals = inverse(number2.substr(number2.find('.')+1));
    }else{
        number2_digit=inverse(number2);
    }

//    cout<<"第一个数 "<<number1_digit<<"  "<<number1_decimals<<endl;
//    cout<<"第二个数 "<<number2_digit<<"  "<<number2_decimals<<endl;


    int  maxLength= max(number1_decimals.length(),number2_decimals.length())
                         +max(number1_digit.length(),number2_digit.length());

//    cout<<maxLength<<endl;
    int *firnum = new int [maxLength]();
    int *secnum  = new int [maxLength]();

    for(int i=0;i<max(number1_decimals.length(),number2_decimals.length());i++){
        if(number1_decimals.length()<number2_decimals.length()){
            if(i<number2_decimals.length()-number1_decimals.length()) firnum[i]=0;
            else firnum[i]=stoi(number1_decimals.substr(i-number2_decimals.length()+number1_decimals.length(),1));

            secnum[i] = stoi(number2_decimals.substr(i, 1));
        }else {
            if (i < number1_decimals.length() - number2_decimals.length()) secnum[i] = 0;
            else secnum[i] = stoi(number2_decimals.substr(i-number1_decimals.length()+number2_decimals.length(),1));

            firnum[i] = stoi(number1_decimals.substr(i, 1));
        }

    }


    for(int i=max(number1_decimals.length(),number2_decimals.length());i<maxLength;i++){
        if(number1_digit.length()<number2_digit.length()) {
//            cout<<maxLength<<"  "<<i<<endl;
            if(i>max(number1_decimals.length(),number2_decimals.length())+number1_digit.length()-1) firnum[i]=0;
            else firnum[i] = stoi(number1_digit.substr(i-max(number1_decimals.length(),number2_decimals.length()),1));

            secnum[i] = stoi(number2_digit.substr(i-max(number1_decimals.length(),number2_decimals.length()),1));
        }else{
//            cout<<maxLength<<"  "<<i<<"   "<<maxLength-number2_digit.length()-2<<endl;
            if(i>max(number1_decimals.length(),number2_decimals.length())+number2_digit.length()-1)secnum[i]=0;
            else secnum[i] = stoi(number2_digit.substr(i-max(number1_decimals.length(),number2_decimals.length()),1));

            firnum[i] = stoi(number1_digit.substr(i-max(number1_decimals.length(),number2_decimals.length()),1));
        }
    }


//    for(int i=0;i<maxLength;i++){
//        cout<<"此时i= "<<i<<" "<<firnum[i]<<" "<<endl;
//    }
//    cout<<endl;
//    for(int i=0;i<maxLength;i++){
//        cout<<"此时i= "<<i<<" "<<secnum[i]<<" "<<endl;
//    }
    string calculateResult = "";

    if(operation=="*") {
        if(first_signal==second_signal)calculateResult = bigMultiple(firnum,secnum,maxLength,max(number1_decimals.length(), number2_decimals.length()));
        else calculateResult = "-"+bigMultiple(firnum,secnum,maxLength,max(number1_decimals.length(), number2_decimals.length()));
    }else{
//        cout << first_signal << "  " << second_signal << endl;
//    cout<<(first_signal=='-')<<" "<<(second_signal=='-')<<" "<<(first_signal=='-'&&second_signal=='-'&&operation=="+")<< endl;
        if ((first_signal == '+' && second_signal == '+' && operation == "+") ||
            (first_signal == '+' && second_signal == '-' && operation == "-"))
            calculateResult = bigPlus(firnum, secnum, maxLength,max(number1_decimals.length(), number2_decimals.length()));
        else if ((first_signal == '-' && second_signal == '-' && operation == "+") ||
                 (first_signal == '-' && second_signal == '+' && operation == "-"))
            calculateResult ="-" + bigPlus(firnum, secnum, maxLength, max(number1_decimals.length(), number2_decimals.length()));
        else if ((first_signal == '+' && second_signal == '-' && operation == "+") ||
                 (first_signal == '+' && second_signal == '+' && operation == "-")) {
            for (int i = maxLength - 1; i >= 0; i--) {
                if (firnum[i] < secnum[i]) {
                    calculateResult = "-" + bigMinus(secnum, firnum, maxLength,max(number1_decimals.length(), number2_decimals.length()));
                    break;
                } else if (firnum[i] > secnum[i]) {
                    calculateResult = bigMinus(firnum, secnum, maxLength,max(number1_decimals.length(), number2_decimals.length()));
                    break;
                }
            }
            if (calculateResult == "")
                calculateResult = bigMinus(firnum, secnum, maxLength,max(number1_decimals.length(),number2_decimals.length()));
        } else {
            for (int i = maxLength - 1; i > 0; i--) {
                if (firnum[i] < secnum[i]) {
                    calculateResult = bigMinus(secnum, firnum, maxLength,max(number1_decimals.length(), number2_decimals.length()));
                    break;
                } else if (firnum[i] > secnum[i]) {
                    calculateResult = "-" + bigMinus(firnum, secnum, maxLength,max(number1_decimals.length(), number2_decimals.length()));
                    break;
                }
            }
            if (calculateResult == "")
                calculateResult = "-" + bigMinus(firnum, secnum, maxLength,max(number1_decimals.length(),number2_decimals.length()));
        }
    }

    calculateResult = calculateResult[calculateResult.length()-1]=='.'?calculateResult.substr(0,calculateResult.length()-1):calculateResult;

    return calculateResult;
}

string bigPlus(int *num1,int *num2,int maxLength,int decimal_digit){
    int* result = new int [maxLength+1]();
    for(int i=0;i<maxLength;i++) {
        result[i] += num1[i] + num2[i];
//        cout<<result[i]<<"  ";
        if (result[i] > 9) {
            result[i + 1] += result[i] / 10;
            result[i] = result[i] % 10;
        }
//        cout<<result[i]<<endl;
    }
//    cout<<result[maxLength]<<endl;

    int max = result[maxLength]==0?maxLength:maxLength+1;
    string finalResult="";

    for(int i=max-1;i>=0;i--){
        if(i == decimal_digit ) {
            finalResult += to_string(result[i]);
                finalResult.push_back('.');
        }

        else finalResult += to_string(result[i]);
    }

    return finalResult;
}


string bigMinus(int *num1,int *num2,int maxLength,int decimal_digit) {
//    cout<<num1[0]<< "  "<<num2[0]<<endl;
    int* result = new int[maxLength]();
    for(int i=0;i<maxLength;i++){
        result[i] += num1[i] - num2[i];
        if(result[i]<0){
            result[i+1] -= 1;
            result[i] += 10;
        }
    }
//    cout<<result[maxLength-1]<<endl;


    string finalResult="";
    for(int i=maxLength-1;i>=0;i--){
        if(i == decimal_digit ) {
            finalResult += to_string(result[i]);
                finalResult.push_back('.');
        }
        else finalResult += to_string(result[i]);
    }
    return finalResult;
}

string bigMultiple(int* num1,int* num2,int maxLength , int decimal_digit){
    int* result = new int[2*maxLength]();
    for(int i=0;i < maxLength;i++){
        for(int j=0;j<maxLength;j++){
            result[i+j] += num1[i]*num2[j];
        }
    }
    for(int i=0 ;i<2*maxLength-1;i++){
        if(result[i]>9) {
            result[i+1] = result[i+1] +result[i]/10;
            result[i] = result[i]%10;
        }
    }

    int max_position=0;
    for(int i=2*maxLength-1;i>=0;i--){
//        cout<<"此时的i: "<<i<<"对应"<<result[i]<<endl;
        if(result[i]!=0) {max_position=i;break;}
    }
//    for(int i=0;i<2*maxLength-1;i++){
//        if(result[i]!=0) {min_position=i;break;}
//    }

    string finalResult;
    for(int i=max_position;i>=0;i--){
        if(i == 2*decimal_digit ) {
            finalResult += to_string(result[i]);
                finalResult.push_back('.');
        }
        else finalResult += to_string(result[i]);
    }

    return finalResult;

}


string inverse(string str){
    string final="";
    for(int i=str.length()-1;i>=0;i--){
        final.push_back(str[i]);
    }
    return final;
}

bool judge_consist(string str,char a){
    int number = str.find(a);
    if(number>=0&&number<str.length()) return true;
    else return false;
}