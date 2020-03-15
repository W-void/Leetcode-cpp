#include<stdio.h>
#include<vector>

using namespace std;

int main(){
    vector<int> v1(10, 1);
    vector<int> v2 = v1;
    v2[0] = 0;
    printf("%d", v1[0]);
}