class Solution {
public:
    struct Fenwick {
        int n;
        vector<int> bit;

        Fenwick(int n) : n(n), bit(n + 1, 0) {}

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

        int offset = n + 2;
        Fenwick ft(2 * n + 5);

        long long ans = 0;
        int pref = 0;
        ft.add(pref + offset, 1);

        for (int x : nums) {
            pref += (x == target ? 1 : -1);

            ans += ft.query(pref + offset - 1);

            ft.add(pref + offset, 1);
        }

        return ans;
    }
};