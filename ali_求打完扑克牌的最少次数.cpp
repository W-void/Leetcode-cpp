/*
求打完扑克牌的最少次数

      扑克牌的类型有0，1，2，3，4，5，6，7，8，9共10种类型，每种类型的牌的数量记为Ai，0<=Ai<=4，且保证至少有一张牌。扑克牌的打法有以下几种：

     单张牌：把任意一种类型的单张扑克牌打出

     对子：把两张相同类型的扑克牌一起打出

     顺子：把5张连续的扑克牌打出，如01234，34567等

     连对：把3对连续的对子一起打出，如112233，445566等

     输入是10个整数，分别代表每种扑克牌的数量；输出是1个整数，求打完所有的扑克牌所需的最少次数。

     输入样例：1 1 1 2 2 2 2 2 1 1

     输出样例：3

     样例解析：分别打出01234、34567、56789，总共需要3次打完。
————————————————
版权声明：本文为CSDN博主「liemozhu」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/pgs1004151212/article/details/104984841
*/

#include<stdio.h>
#include<vector>
#include<map>
#include <fstream>
#include<math.h>
using namespace std;

bool check(int ans, int i){
    for(int j=0; j<i-4; j++){
        ans /= 10;
    }
    for(int j=0; j<4; j++){
        if(ans % 10 == 0)
            return false;
        ans /=10;
    }
    return true;
}

bool check2(int ans, int i){
    for(int j=0; j<i-2; j++){
        ans /= 10;
    }
    for(int j=0; j<2; j++){
        if(ans % 10 < 2)
            return false;
        ans /=10;
    }
    if(ans % 10 < 1) return false;
    return true;
}

int _min(int a, int b, int c, int d){
    a = min(a, b);
    c = min(c, d);
    return min(a, c);
}
    
map<int, int> mp;
int dfs(int Ans){
    int ans = Ans;
    vector<int> puke(10, 0);
    for(int i=0; i<10; i++){
        puke[i] = ans % 10;
        ans /= 10;
    }
    ans = 0;
    for(int i=0; i<10; i++){
        for(int j=1; j<=puke[i]; j++){      
            int single = mp[ans];
            int pair = ans >= (int)pow(10, i) ? mp[ans - (int)pow(10, i)] : INT_MAX;
            int shunzi = INT_MAX;
            if(i>=4 && check(ans, i)){
                int tmp = (int)pow(10, i-1) + (int)pow(10, i-2) + (int)pow(10, i-3) + (int)pow(10, i-4);
                shunzi = dfs(ans-tmp);
            }
            int liandui = INT_MAX;
            if(i>=2 && check2(ans, i)){
                int tmp = (int)pow(10, i) + 2 * (int)pow(10, i-1) + 2 * (int)pow(10, i-2);
                liandui = dfs(ans-tmp);
            }
            ans += (int)pow(10, i);
            mp[ans] = _min(single, pair, shunzi, liandui) + 1;
        }
    }
    return mp[ans];
}

int main(){
    vector<int> puke(10, 0);
    int tmp = 0, p = 1, ans = 0;
    for(int i=0; i<10; i++){
        scanf("%d", &tmp);
        ans += tmp * p;
        p *= 10;
    }
    mp[0] = 0;
    dfs(ans);
    printf("%d\n", mp[ans]);
    return mp[ans];
}