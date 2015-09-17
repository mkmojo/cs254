#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

int count=0;
string ans="(";

void do_dfs(int level, int total)
{
    if(total == 0){
        cout << ans;
        cout << string(2*count-ans.length(), ')') <<endl;
        return;
    }
    if(level == 0){
        ans+="(";
        do_dfs(level+1, total-1);
        ans.pop_back();
    } else{
        ans+="(";
        do_dfs(level+1, total-1);
        ans.pop_back();
        ans+=")";
        do_dfs(level-1, total);
        ans.pop_back();
    }
}

void dfs(char* n)
{
    int nn = atoi(n);
    count = nn;
    do_dfs(0, nn-1);
}

int main(int argc, char** argv)
{
    dfs(argv[1]);
    cout << count << endl;
    return 0;
}

