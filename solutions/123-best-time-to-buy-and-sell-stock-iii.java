class Solution {
    public int maxProfit(int[] prices) {
        // Initialize variables for first and second transactions
        // buy1: Max profit after buying 1st stock (will be negative)
        // sell1: Max profit after selling 1st stock
        // buy2: Max profit after buying 2nd stock
        // sell2: Max profit after selling 2nd stock
        int buy1 = Integer.MIN_VALUE;
        int sell1 = 0;
        int buy2 = Integer.MIN_VALUE;
        int sell2 = 0;

        for (int price : prices) {
            // Update states in order
            // We want to maximize the profit for each state
            
            // 1. First Buy: Either keep previous buy1 or buy now (-price)
            buy1 = Math.max(buy1, -price);
            
            // 2. First Sell: Either keep previous sell1 or sell now (buy1 + price)
            sell1 = Math.max(sell1, buy1 + price);
            
            // 3. Second Buy: Either keep previous buy2 or buy now using profit from sell1 (sell1 - price)
            buy2 = Math.max(buy2, sell1 - price);
            
            // 4. Second Sell: Either keep previous sell2 or sell now (buy2 + price)
            sell2 = Math.max(sell2, buy2 + price);
        }

        return sell2;
    }
}
