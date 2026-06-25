class Solution {
public:
    using ll = long long;

    struct BIT {
        int n;
        vector<int> bit;

        BIT(int n) : n(n), bit(n + 1, 0) {}

        void add(int idx, int val) {
            while (idx <= n) {
                bit[idx] += val;
                idx += idx & -idx;
            }
        }

        int query(int idx) {
            int res = 0;
            while (idx > 0) {
                res += bit[idx];
                idx -= idx & -idx;
            }
            return res;
        }
    };

    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        vector<int> pref(n + 1);
        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + (nums[i] == target ? 1 : -1);

        vector<int> vals = pref;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        BIT bit(vals.size());

        long long ans = 0;

        for (int x : pref) {
            int id = lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
            ans += bit.query(id - 1);
            bit.add(id, 1);
        }

        return ans;
    }
};