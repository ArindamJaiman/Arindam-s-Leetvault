class Solution {
public:
    static constexpr int MOD = 1000000007;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> pos;
        vector<int> digits;
        pos.reserve(n);
        digits.reserve(n);
        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                pos.push_back(i);
                digits.push_back(s[i] - '0');
            }
        }

        int k = digits.size();
        if (k == 0) {
            return vector<int>(queries.size(), 0);
        }
        vector<int> nextIdx(n, k);

        int ptr = k - 1;
        for (int i = n - 1; i >= 0; i--) {
            while (ptr >= 0 && pos[ptr] > i)
                ptr--;

            if (ptr >= 0 && pos[ptr] == i)
                nextIdx[i] = ptr;
            else if (ptr + 1 < k)
                nextIdx[i] = ptr + 1;
        }
        vector<int> prevIdx(n, -1);

        ptr = 0;
        for (int i = 0; i < n; i++) {
            while (ptr < k && pos[ptr] < i)
                ptr++;

            if (ptr < k && pos[ptr] == i)
                prevIdx[i] = ptr;
            else if (ptr > 0)
                prevIdx[i] = ptr - 1;
        }

        vector<long long> pow10(k + 1, 1);
        for (int i = 1; i <= k; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        vector<long long> prefVal(k + 1, 0);

        vector<int> prefSum(k + 1, 0);

        for (int i = 0; i < k; i++) {
            prefVal[i + 1] = (prefVal[i] * 10 + digits[i]) % MOD;
            prefSum[i + 1] = prefSum[i] + digits[i];
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int L = nextIdx[l];
            int R = prevIdx[r];

            if (L > R || L == k || R == -1) {
                ans.push_back(0);
                continue;
            }

            int len = R - L + 1;

            long long x =
                (prefVal[R + 1] -
                 prefVal[L] * pow10[len] % MOD +
                 MOD) % MOD;

            long long sum = prefSum[R + 1] - prefSum[L];

            ans.push_back((x * sum) % MOD);
        }
        return ans;
    }
};