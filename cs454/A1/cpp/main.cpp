#include<iostream>
#include<string>
using namespace std;

void dfs(int level, int n, string ans)
{
    if(n == 0){
        cout << '(' << (ans + string(level, ')')) << ')' << endl;
    }
    else if(level == 0){
        dfs(level+1, n-1, ans + string(1, '('));
    }else{
        dfs(level+1, n-1, ans + string(1, '(') );
        dfs(level-1, n, ans + string(1, ')') );
    }
}

void trees(int n)
{
    dfs(0, n-1, "");
}

int main(int argc, char** argv)
{
    int n;
    cout<< "\nHow many points do you have?" << endl;
    cin >> n;
    trees(n);
    return 0;
}

