/**
 * @param {number} k
 * @param {number[]} prices
 * @return {number}
 */
var maxProfit = function(k, prices) {
    const n = prices.length;
    if (n <= 1) return 0;

    // Optimization: If k is large enough (k >= n/2), we can make every profitable transaction.
    // This reduces the problem to "Best Time to Buy and Sell Stock II".
    if (k >= Math.floor(n / 2)) {
        let maxPro = 0;
        for (let i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                maxPro += prices[i] - prices[i - 1];
            }
        }
        return maxPro;
    }

    // DP arrays to store the state of each transaction
    // buy[i]: Max profit after buying the i-th stock
    // sell[i]: Max profit after selling the i-th stock
    const buy = new Array(k + 1).fill(-Infinity);
    const sell = new Array(k + 1).fill(0);

    for (const price of prices) {
        for (let i = 1; i <= k; i++) {
            // Update buy[i]: either keep previous buy state or buy now using profit from previous sell
            buy[i] = Math.max(buy[i], sell[i - 1] - price);
            
            // Update sell[i]: either keep previous sell state or sell now
            sell[i] = Math.max(sell[i], buy[i] + price);
        }
    }

    return sell[k];
};
