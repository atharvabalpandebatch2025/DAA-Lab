#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
    int n;
    scanf("%d", &n);

    int cost[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    if (n == 1) {
        printf("0\n");
        return 0;
    }

    int totalMasks = 1 << n;
    long long INF = LLONG_MAX / 4;

    long long **dp = malloc(totalMasks * sizeof(long long *));

    for (int i = 0; i < totalMasks; i++) {
        dp[i] = malloc(n * sizeof(long long));
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }

    // Start from city 0
    dp[1][0] = 0;

    for (int mask = 1; mask < totalMasks; mask++) {
        for (int u = 0; u < n; u++) {
            if (dp[mask][u] == INF)
                continue;

            if (!(mask & (1 << u)))
                continue;

            for (int v = 0; v < n; v++) {
                if (mask & (1 << v))
                    continue;

                if (cost[u][v] == -1)
                    continue;

                int newMask = mask | (1 << v);
                long long newCost = dp[mask][u] + cost[u][v];

                if (newCost < dp[newMask][v]) {
                    dp[newMask][v] = newCost;
                }
            }
        }
    }

    long long ans = INF;
    int fullMask = totalMasks - 1;

    // Return to the starting city
    for (int u = 1; u < n; u++) {
        if (dp[fullMask][u] == INF)
            continue;

        if (cost[u][0] == -1)
            continue;

        long long tourCost = dp[fullMask][u] + cost[u][0];

        if (tourCost < ans) {
            ans = tourCost;
        }
    }

    if (ans == INF)
        printf("-1\n");
    else
        printf("%lld\n", ans);

    for (int i = 0; i < totalMasks; i++) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}