class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> cnt;
        for (int x : nums) cnt[x]++;
        int ans = 1;
        // Special case for 1
        if (cnt.count(1)) {
            ans = max(ans, cnt[1] % 2 ? cnt[1] : cnt[1] - 1);
        }
        for (auto &[start, f] : cnt) {
            if (start == 1) continue;
            long long cur = start;
            int pairs = 0;

            while (cnt[cur] >= 2) {
                if (cur > 31622) break;          // cur*cur would exceed 1e9
                long long nxt = cur * cur;
                if (!cnt.count(nxt)) break;

                pairs += 2;
                cur = nxt;
            }
            ans = max(ans, pairs + 1);
        }

        return ans;
    }
};