#include <bits/stdc++.h>
using namespace std;

int main()
{
    // 不断读入字符, 如果遇到", 则输出s的一个
    // 如果不是, 则原封不动输出
    // freopen("in.txt", "r", stdin);
    char s[2][3] = {"``", "''"};
    bool flag = 0;
    char ch;
    while ((ch = getchar()) != EOF)
    {
        if (ch == '"')
        {
            printf("%s", s[flag]);
            flag = not flag;
        }
        else
        {
            printf("%c", ch);
        }
    }
    return 0;
}