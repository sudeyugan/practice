#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INF 100000
#define MAX_N 105
#define MAX_M 105
#define Max_Item 105

int main()
{
    int A[MAX_N][MAX_M];
    int Item[MAX_N][MAX_M];
    int Trap[MAX_N][MAX_M];
    int dp[Max_Item][MAX_N][MAX_M];
    int n, m;
    scanf(" %d %d", &n, &m);
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            scanf(" %d", &A[i][j]);
        }
    }
    int k;
    scanf("%d", &k);
    int tx, ty;
    for (int i = 0; i < k; i++)
    {
        scanf(" %d %d", &tx, &ty);
        Trap[tx][ty] = 1;
    }
    int p;
    scanf("%d", &p);
    int ix, iy;
    for (int i = 0; i < p; i++)
    {
        scanf(" %d %d", &ix, &iy);
        Item[ix][iy] = 1;
    }
    for (int i = 0; i < Max_Item; i++)
    {
        for (int j = 0; j < MAX_N; j++)
        {
            for (int k = 0; k < MAX_M; k++)
            {
                dp[i][j][k] = INF;
            }
        }
    }
    dp[0][1][1] = A[1][1];

    for (int item = 0; item < p; item++)
    {
        for (int i = 1; i < n+1; i++)
        {
            for (int j = 1; j < m+1; j++)
            {
                if(dp[item][i][j]>INF/2){
                    continue;
                }
                int dr[] = {0, 1};
                int dc[] = {1, 0};
                for (int c = 0; c < 2; c++)
                {
                    int ni = i + dr[c];
                    int nj = j + dc[c];
                    if (Item[ni][nj] == 1)
                    {
                        if (dp[item + 1][ni][nj] > dp[item][ni][nj])
                        {
                            dp[item + 1][ni][nj] = dp[item][ni][nj];
                        }
                    }
                    else if (Trap[ni][nj] == 1)
                    {
                        if (item > 0)
                        {
                            if (dp[item - 1][ni][nj] > dp[item][ni][nj])
                            {
                                dp[item - 1][ni][nj] = dp[item][ni][nj];
                            }
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        if (dp[item][i][j] + A[i][j] < dp[item][ni][nj]){
                            dp[item][ni][nj] = dp[item][i][j] + A[i][j];
                        }
                    }
                }
            }
        }
    }
    int min = INF;

    for (int item = 0; item < p; item++){
        if(min <dp[item][m][n]){
            min =dp[item][m][n];
        }
    }

    if(min > INF/2){
        printf("failed");
    }else{
        printf("%d", min);
    }

    return 0;
}   
