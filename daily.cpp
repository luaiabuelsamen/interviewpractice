#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> two_sum(vector<int>& nums, int target) {
        unordered_map<int, int> hash_table = {};
        vector<int> ret = {-1, -1};
        for (int i = 0; i < nums.size(); i ++) {
            if (hash_table.count(target - nums[i])) {
                ret[0] = hash_table[target - nums[i]];
                ret[1] = i;
                return ret;
            }
            hash_table[nums[i]] = i;
        }
        return ret;
    }

    bool contains_dup(vector<int>& nums) {
        unordered_set <int> hashset;
        for (int i: nums) {
            if(hashset.count(i)){
                return true;
            }
            hashset.insert(i);
        }
        return false;
    }

    int longest_unique_substring(string s){
        int left = 0;
        int max_len = 0;
        unordered_map <char, int> hash_map;

        for (int right = 0; right < s.length(); ++right){
            if (hash_map.count(s[right]) && hash_map[s[right]] >= left){
                left =  hash_map[s[right]] + 1;
            }
            max_len = max(max_len, right - left + 1);
            hash_map[s[right]] = right;
        }
        return max_len;

    }

    bool checkSorted(vector<int>& list){
        if (!list.size()){
            return true;
        }
        int prev_num = list[0];
        for (int i = 1; i < list.size(); i++) {
            if (list[i] < prev_num) {
                return false;
            }
            prev_num = list[i];
        }
        return true;
    }

    struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy = ListNode(0);
        ListNode* cur = &dummy;
        int carry = 0;
        int l1_val, l2_val;
        while(l1 || l2 || carry) {
            l1_val = l1? l1->val : 0;
            l2_val = l2? l2->val : 0;
            cur->next = new ListNode((l1_val + l2_val + carry)%10);
            carry = (l1_val + l2_val + carry) / 10;
            cur = cur->next;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }
        return dummy.next;
    }

    bool isPalindrome(int x) {
        
        if (x < 0 ){
            return false;
        }
        if (x < 10 ){
            return true;
        }

        int biggest = x / (x / 10);
        int smallest = x % 10;
    }

    void inverse_string(vector<char>& s){
        for(int i = 0; i < s.size()/ 2; i ++){
            swap(s[i], s[s.size() -i - 1]);
        }
    }

    int count_blocks(vector<vector<int>>& mat){
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> heights(m, vector<int>(0, n));
        
        for (int row = 0; row < m; row++){
            for (int col = 0; col < n; col++) {
                if(mat[row][col] == 1){
                    heights[row][col] = (row == 0) ? 1 : heights[row - 1][col] + 1;
                }
            }
        }

        int result = 0;
        for(int i = 0; i < m; i ++){
            vector<int> stack;
            int count = 0;
            for( int j = 0; j < n; j ++){
                while(!stack.empty() && heights[i][stack.back()] >= heights[i][j]){
                    int idx = stack.back();
                    stack.pop_back();
                    count -= heights[i][idx] * (stack.empty() ? 1 + idx : idx - heights[i][stack.back()]);
                }

                count += heights[i][j] * (stack.empty() ? 1 + j : j - heights[i][stack.back()]);
                result += count;
                stack.push_back(j);
            }
        }
        return result;
    }
};