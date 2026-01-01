#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty()) return {};
        
        int m = heights.size();
        int n = heights[0].size();
        
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));
        
        // DFS from top and bottom borders
        for (int j = 0; j < n; ++j) {
            dfs(heights, pacific, 0, j, m, n);       // Top row (Pacific)
            dfs(heights, atlantic, m - 1, j, m, n);   // Bottom row (Atlantic)
        }
        
        // DFS from left and right borders
        for (int i = 0; i < m; ++i) {
            dfs(heights, pacific, i, 0, m, n);       // Left col (Pacific)
            dfs(heights, atlantic, i, n - 1, m, n);   // Right col (Atlantic)
        }
        
        vector<vector<int>> result;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }
        
        return result;
    }
    
private:
    void dfs(vector<vector<int>>& heights, vector<vector<bool>>& visited, int i, int j, int m, int n) {
        visited[i][j] = true;
        
        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        for (auto& d : dirs) {
            int ni = i + d[0];
            int nj = j + d[1];
            
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && !visited[ni][nj]) {
                // Water flows from higher/equal to lower, so we go reverse: lower/equal to higher
                if (heights[ni][nj] >= heights[i][j]) {
                    dfs(heights, visited, ni, nj, m, n);
                }
            }
        }
    }
};
