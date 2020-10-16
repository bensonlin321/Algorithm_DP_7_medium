#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <limits>
#include <utility> // pair
#include <tuple>
#include <algorithm>

/*
7    1    5    3    6    4

i = 1

price = 1


"buy" means the profit of you buy the stock at (i-1)th day
"sell" means the profit of you sell the stock at (i-1)th day
"rest" means the profit of you rest the stock at (i-1)th day

buy[i]  = max(rest[i-1] - price[i], buy[i-1]) 
sell[i] = max(buy[i-1] + price[i], sell[i-1])
rest[i] = max(sell[i-1], buy[i-1], rest[i-1])
*/

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        int buy = INT_MIN, pre_buy = 0, sell = 0, pre_sell = 0;
        for (int price_index = 0 ; price_index < prices.size(); price_index++) {
            pre_buy = buy;
            buy = std::max(pre_sell - prices[price_index], pre_buy);
            pre_sell = sell;
            sell = std::max(pre_buy + prices[price_index], pre_sell);

            printf("buy[%d]: %d, sell[%d]: %d\n", price_index, buy, price_index, sell);
        }
        return sell;
    }

    /*              _
                   | | rest (rest[i-1])
                   | |
                  _|_v__
                 | rest |
             ____|______|<----
       buy  |                 |
     (price)|                 | rest
         ___v__            ___|__
        | hold |   sell   | sold |
        |______|--------->|______|
          | ^
          | | rest (hold[i-1])
          |_|

           *hold[i] = max(hold[i-1], rest[i-1] - prices[i])
            hold means the maximum profit of holding a stock
            hold[i-1] means the maximum profit of yesterday
            rest[i-1] - price[i]: choose the maximum profit of yesterday and buy a stock with today's price
           *sold[i] = hold[i-1] + price[i]
           *rest[i] = max(rest[i-1], sold[i-1])

           init: 
           rest[0] = 0
           sold[0] = 0
           hold[0] = -INF (did not buy anything)

           ans: the last day that the profit you can get
           return max(rest[last], sold[last])

            |      price     |           hold               |      rest     |      sold     |
            |      init      |            N/A               |       0       |       0       |
            |       1        |            -1                |       0       |      N/A+1    |
                             (first day buy, need -1 profit)
            |       2        |            -1                |       0       |       1       |
            |       3        |            -1                |       1       |       2       |
            |       0        |            1                 |       2       |       -1      |
            |       2        |            1                 |       2       |       3       |

    */

    int maxProfit_v2(std::vector<int>& prices) {
        int sold = 0;
        int rest = 0;
        int hold = INT_MIN;
        printf("|\t\tprice\t\t|\t\thold\t\t|\t\trest\t\t|\t\tsold\t\t|\n");
        printf("|\t\tinit\t\t|\t\t%d\t|\t\t%d\t\t|\t\t%d\t\t|\n", hold, rest, sold);
        for (int i = 0 ; i < prices.size(); i++) {
            int prev_sold = sold;
            sold = hold + prices[i];
            hold = std::max(hold, rest - prices[i]);
            rest = std::max(rest, prev_sold);
            printf("|\t\t%d\t\t|\t\t%d\t\t|\t\t%d\t\t|\t\t%d\t\t|\n", prices[i], hold, rest, sold);

        }
        return std::max(rest, sold);
    }
};

int main(int argc, char *argv[]) {
    Solution *s = new Solution();
    std::vector<int> prices{ 1,2,3,0,2 };
    printf("output:%d\n", s -> maxProfit_v2(prices));
}
