class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        vector<vector<long long>> rowSum(m + 1, vector<long long>(n + 1, 0));
        vector<vector<long long>> colSum(m + 1, vector<long long>(n + 1, 0));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rowSum[i][j + 1] = rowSum[i][j] + grid[i][j];
                colSum[i + 1][j] = colSum[i][j] + grid[i][j];
            }
        }
        
        int maxK = min(m, n);
        for (int k = maxK; k >= 1; k--) {
            for (int r = 0; r <= m - k; r++) {
                for (int c = 0; c <= n - k; c++) {
                    if (isMagic(grid, rowSum, colSum, r, c, k)) {
                        return k;
                    }
                }
            }
        }
        return 1;
    }
    
private:
    bool isMagic(vector<vector<int>>& grid, 
                 vector<vector<long long>>& rowSum,
                 vector<vector<long long>>& colSum,
                 int r, int c, int k) {
        long long target = rowSum[r][c + k] - rowSum[r][c];
        
        for (int i = 0; i < k; i++) {
            if (rowSum[r + i][c + k] - rowSum[r + i][c] != target) return false;
            if (colSum[r + k][c + i] - colSum[r][c + i] != target) return false;
        }
        
        long long diag1 = 0, diag2 = 0;
        for (int i = 0; i < k; i++) {
            diag1 += grid[r + i][c + i];
            diag2 += grid[r + i][c + k - 1 - i];
        }
        
        return diag1 == target && diag2 == target;
    }
};
