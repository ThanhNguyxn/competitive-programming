object Solution {
    def maxProfitAssignment(difficulty: Array[Int], profit: Array[Int], worker: Array[Int]): Int = {
        // Combine difficulty and profit into a list of pairs (difficulty, profit)
        val jobs = difficulty.zip(profit).sortBy(_._1)
        
        // Sort workers by their ability
        val sortedWorkers = worker.sorted
        
        var totalProfit = 0
        var maxProfitSoFar = 0
        var jobIndex = 0
        val n = jobs.length
        
        for (ability <- sortedWorkers) {
            // For the current worker, find the max profit among all jobs they can handle
            // Since workers and jobs are sorted, we can continue from where we left off
            while (jobIndex < n && jobs(jobIndex)._1 <= ability) {
                maxProfitSoFar = math.max(maxProfitSoFar, jobs(jobIndex)._2)
                jobIndex += 1
            }
            
            // Add the best profit this worker can earn
            totalProfit += maxProfitSoFar
        }
        
        totalProfit
    }
}
