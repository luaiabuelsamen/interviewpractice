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
};