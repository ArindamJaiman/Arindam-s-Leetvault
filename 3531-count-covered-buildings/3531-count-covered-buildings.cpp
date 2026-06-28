class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        unordered_map<int, int> rowMin, rowMax;
        unordered_map<int, int> colMin, colMax;

        for (auto &b : buildings) {
            int x = b[0], y = b[1];

            if (rowMin.count(x)) {
                rowMin[x] = min(rowMin[x], y);
                rowMax[x] = max(rowMax[x], y);
            } else {
                rowMin[x] = rowMax[x] = y;
            }

            if (colMin.count(y)) {
                colMin[y] = min(colMin[y], x);
                colMax[y] = max(colMax[y], x);
            } else {
                colMin[y] = colMax[y] = x;
            }
        }

        int covered = 0;

        for (auto &b : buildings) {
            int x = b[0], y = b[1];

            if (rowMin[x] < y && y < rowMax[x] &&
                colMin[y] < x && x < colMax[y]) {
                covered++;
            }
        }

        return covered;
    }
};