#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

int total=0;
string ans="(";

void do_dfs(int level, int n)
{
    if(n == 0){
        cout << ans;
        cout << string((2*total)-ans.length(), ')') <<endl;
        return;
    }
    if(level == 0){
        ans+="(";
        do_dfs(level+1, n-1);
        ans.pop_back();
    } else{
        ans+="(";
        do_dfs(level+1, n-1);
        ans.pop_back();
        ans+=")";
        do_dfs(level-1, n);
        ans.pop_back();
    }
}

void dfs(int n)
{
    total = n;
    do_dfs(0, n-1);
}

int main(int argc, char** argv)
{
    int n;
    cout<< "\nHow many points do you have?" << endl;
    cin >>  n;
    dfs(n);
    return 0;
}

