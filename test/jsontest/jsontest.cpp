#include"json.hpp"
using json=nlohmann::json;

#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

string fun1()
{
    json js;
    js["msg_type"]=2;
    js["from"]="zhang san";
    js["to"]="li si";
    js["msg"]="hello world!";

    string sendBuf=js.dump();
    return sendBuf;
}

void test1()
{
    json js;
    js["msg_type"]=2;
    js["from"]="zhang san";
    js["to"]="li si";
    js["msg"]="hello world!";
    cout<<js<<endl;

    string sendBuf = js.dump();
    cout << sendBuf << endl;
}
void test2()
{
    json js;
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    js["shuzu"]=v;
    cout<<js<<endl;
}
int main()
{
    test2();
    // string rcevBuf=fun1();
    // cout<<rcevBuf<<endl;
    // json jsbuf=json::parse(rcevBuf);
    // cout<<jsbuf["msg_type"]<<endl;
    // cout<<jsbuf["from"]<<endl;
    // cout<<jsbuf["to"]<<endl;
    // cout<<jsbuf["msg"]<<endl;

}