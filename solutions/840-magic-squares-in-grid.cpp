class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        if (rows < 3 || cols < 3) return 0;
        
        int count = 0;
        for (int r = 0; r <= rows - 3; r++) {
            for (int c = 0; c <= cols - 3; c++) {
                if (isMagic(grid, r, c)) count++;
            }
        }
        return count;
    }
    
private:
    bool isMagic(vector<vector<int>>& grid, int r, int c) {
        vector<int> nums;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int val = grid[r + i][c + j];
                if (val < 1 || val > 9) return false;
                nums.push_back(val);
            }
        }
        
        sort(nums.begin(), nums.end());
        for (int i = 0; i < 9; i++) {
            if (nums[i] != i + 1) return false;
        }
        
        int s1 = grid[r][c] + grid[r][c+1] + grid[r][c+2];
        int s2 = grid[r+1][c] + grid[r+1][c+1] + grid[r+1][c+2];
        int s3 = grid[r+2][c] + grid[r+2][c+1] + grid[r+2][c+2];
        int s4 = grid[r][c] + grid[r+1][c] + grid[r+2][c];
        int s5 = grid[r][c+1] + grid[r+1][c+1] + grid[r+2][c+1];
        int s6 = grid[r][c+2] + grid[r+1][c+2] + grid[r+2][c+2];
        int s7 = grid[r][c] + grid[r+1][c+1] + grid[r+2][c+2];
        int s8 = grid[r][c+2] + grid[r+1][c+1] + grid[r+2][c];
        
        return s1 == 15 && s2 == 15 && s3 == 15 && s4 == 15 &&
               s5 == 15 && s6 == 15 && s7 == 15 && s8 == 15;
    }
};
