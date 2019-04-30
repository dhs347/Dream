//
//  dp II.cpp
//  algorithm-exercise
//
//  Created by Hongyan Liu on 2019/4/29.
//  Copyright ? 2019 Hongyan Liu. All rights reserved.
//

#include <bits/stdc++.h>

#define OFFSET 2000

int dp[101][4001];
int weight[101];

//dp[i][j]代表到第i个橘子，左右两筐重量差为j时候的总重量

int max(int x,int y,int z)
{
    int max = x;
    if(max < y)
    {
        max = y;
    }
    if(max < z)
    {
        max = z;
    }
    return max;
}

void init(int n)
{
    for(int i = -2000;i<=2000;i++)
    {
        dp[0][i+OFFSET] = -1e9;
    }
    dp[0][0+OFFSET] = 0;
    for(int i = 1;i<=n;i++)
    {
        for(int j = -2000;j<=2000;j++)
        {
            int temp1 = -1e9;
            int temp2 = -1e9;
            int temp3 = -1e9;
            if(j - weight[i] >= -2000 && dp[i - 1][j-weight[i]+OFFSET] != -1e9)                           //如果可以放在左篮子
            {
                temp1 = dp[i - 1][j-weight[i]+OFFSET] + weight[i];
            }
            if(j + weight[i] <= 2000 && dp[i - 1][j+weight[i]+OFFSET] != -1e9)                           //如果可以放在右篮子
            {
                temp2 = dp[i - 1][j+weight[i]+OFFSET] + weight[i];
            }
            if(dp[i - 1][j+OFFSET] != -1e9)                                     //如果可以不取该橘子
            {
                temp3 = dp[i - 1][j+OFFSET];
            }
            dp[i][j+OFFSET] = max(temp1,temp2,temp3);
        }
    }
}

int main()
{
	freopen("a.in","r",stdin);
    int t;
    int cas = 0;
    scanf("%d",&t);
    while(t--!=0)
    {
        int n;
        scanf("%d",&n);
        int zerosize = 0;
        memset(dp,0,sizeof(dp));
        memset(weight,0,sizeof(weight));
        int cnt = 0;
        for(int i =1;i<=n;i++)
        {
            scanf("%d",&weight[++cnt]);
            if(weight[cnt] == 0)
            {
                cnt--;
                zerosize++;
            }
        }
        n = cnt;
        init(n);
        printf("Case %d: ",++cas);
        if(dp[n][0+OFFSET] == 0)
        {
            if(zerosize > 0)
            {
                printf("0\n");
            }
            else
            {
                printf("-1\n");
            }
        }
        else
        {
            printf("%d\n",dp[n][0+OFFSET] / 2);
        }
    }
    return 0;
}

