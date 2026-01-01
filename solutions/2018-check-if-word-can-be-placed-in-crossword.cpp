class Solution {
public:
    bool placeWordInCrossword(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        int len = word.size();
        string rev = word;
        reverse(rev.begin(), rev.end());
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (canPlace(board, word, i, j, 0, 1, m, n) ||
                    canPlace(board, rev, i, j, 0, 1, m, n) ||
                    canPlace(board, word, i, j, 1, 0, m, n) ||
                    canPlace(board, rev, i, j, 1, 0, m, n)) {
                    return true;
                }
            }
        }
        return false;
    }
    
private:
    bool canPlace(vector<vector<char>>& board, string& word, int r, int c, int dr, int dc, int m, int n) {
        int len = word.size();
        int pr = r - dr, pc = c - dc;
        if (pr >= 0 && pr < m && pc >= 0 && pc < n && board[pr][pc] != '#') {
            return false;
        }
        
        int er = r + dr * len, ec = c + dc * len;
        if (er >= 0 && er < m && ec >= 0 && ec < n && board[er][ec] != '#') {
            return false;
        }
        
        for (int i = 0; i < len; i++) {
            int nr = r + dr * i, nc = c + dc * i;
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) return false;
            char cell = board[nr][nc];
            if (cell == '#') return false;
            if (cell != ' ' && cell != word[i]) return false;
        }
        
        return true;
    }
};
