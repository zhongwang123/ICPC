package main

import (
	"fmt"
)

const maxn = 100

var w, p, c [maxn + 5]int
var dp [50005]int64

func max(a int64, b int64) int64 {
	if a > b {
		return a
	}
	return b
}

func trans(x int, value, weight *[]int) {
	k := 1
	for {
		if k >= c[x] {
			break
		}
		*value = append(*value, k*p[x])
		*weight = append(*weight, k*w[x])
		c[x] -= k
		k *= 2
	}
	*value = append(*value, c[x]*p[x])
	*weight = append(*weight, c[x]*w[x])
}

func main() {
	var N, W int
	fmt.Scanf("%d%d\n", &N, &W)

	value := make([]int, 0, 20000)
	weight := make([]int, 0, 20000)

	for i := 1; i <= N; i++ {
		fmt.Scanf("%d%d%d\n", &w[i], &p[i], &c[i])
		trans(i, &value, &weight)
		//fmt.Printf("%d %d\n", w[i], p[i])
	}

	for i := 0; i < len(value); i++ {
		for j := W; j >= weight[i]; j-- {
			dp[j] = max(dp[j], dp[j-weight[i]]+int64(value[i]))
			//fmt.Printf("%d %d\n", i, j)
		}
	}
	fmt.Printf("%d\n", dp[W])
}
