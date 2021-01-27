#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
} ;

class Solution {
public:
    /// 两数之和，思路：双层数组遍历，两数相加判断是否相等
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        for(int firstIndex = 0; firstIndex < nums.size(); firstIndex++) {
            for(int nextIndex = firstIndex + 1; nextIndex < nums.size(); nextIndex++) {
//                cout << "size:" << nums.size() << "," << firstIndex << ":" << nextIndex << endl;
                if (target - nums[firstIndex] == nums[nextIndex]) {
                    result.clear();
                    result.push_back(firstIndex);
                    result.push_back(nextIndex);
                    // continue;
                    //return result;
                }
            }
        }
        return result;
    }

    /// 两数相加，双指针偏移，临时变量存储进位，下一个和+进位1
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        int raiseVal = 0;
        ListNode *head = nullptr, *tail = nullptr;
        while (l1 != nullptr || l2 != nullptr) {
            int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + raiseVal;
            int value = sum % 10;
            if (head == nullptr) {
                head = new ListNode(value);
                tail = head;
            } else {
                tail->next = new ListNode(value);
                tail = tail->next;
            }
            raiseVal = sum / 10;
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }

        }
        if (raiseVal > 0) {
            tail->next = new ListNode(raiseVal);
        }
        return head;
    }

    /// 无重复字符的最长子串
    /// 思路：遍历字符串，使用unordered_set存储，没有就插入，有就清空再从下一个字符重新遍历
    int lengthOfLongestSubstr(string s) {
        if (s.length() == 1) {
            return 1;
        }
        unordered_set<string> set = unordered_set<string>();
        int maxCount = 0;
        for (int i = 0; i < s.length(); ++i) {
            string subS = s.substr(i,1);
            set.clear();
            set.insert(subS);
            for (int j = i + 1; j < s.length(); ++j) {
                string subNextS = s.substr(j,1);
                if (set.find(subNextS) == set.end()) {
                    /// 不存在，继续叠加
                    set.insert(subNextS);
                    if (set.size() > maxCount) {
                        maxCount = set.size();
                    }
                } else {
                    /// 存在，返回上层循环
                    if (set.size() > maxCount) {
                        maxCount = set.size();
                    }
                    break;
                }
            }
        }
        return maxCount;
    }

    /// 寻找两个正序数组的中位数
    /// 思路：合并两个有序数组后，取中间值（遍历数为两个数组的和就能覆盖所有元素，分别用两个下标控制）
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        if (nums1.size() == 0 && nums2.size() == 0) {
            return 0;
        }
        // 遍历两个数组，排序
        vector<int> sortVector;
        if (nums1.size() == 0 && nums2.size() != 0) {
            sortVector.insert(sortVector.end(), nums2.begin(), nums2.end());
        } else if (nums2.size() == 0 && nums1.size() != 0) {
            sortVector.insert(sortVector.end(), nums1.begin(), nums1.end());
        } else if (nums1[0] > nums2[nums2.size() - 1]) {
            sortVector.insert(sortVector.end(), nums2.begin(), nums2.end());
            sortVector.insert(sortVector.end(), nums1.begin(), nums1.end());
        } else if (nums2[0] > nums1[nums1.size() - 1]) {
            sortVector.insert(sortVector.end(), nums1.begin(), nums1.end());
            sortVector.insert(sortVector.end(), nums2.begin(), nums2.end());
        } else {
            int maxCount = nums1.size() + nums2.size();
            int num1Index = 0 , num2Index = 0;
            for (int i = 0; i < maxCount; ++i) {

                if (num1Index < nums1.size() && num2Index < nums2.size()) {
                    int n1 = nums1[num1Index];
                    int n2 = nums2[num2Index];
                    if (n1 < n2) {
                        sortVector.push_back(n1);
                        num1Index++;
                    } else if (n1 > n2) {
                        sortVector.push_back(n2);
                        num2Index++;
                    } else {
                        sortVector.push_back(n1);
                        sortVector.push_back(n2);
                        num1Index++;
                        num2Index++;
                    }
                } else if (num1Index < nums1.size()) {
                    sortVector.push_back(nums1[num1Index]);
                    num1Index++;
                } else if (num2Index < nums2.size()) {
                    sortVector.push_back(nums2[num2Index]);
                    num2Index++;
                }
            }
        }

        if (sortVector.size() == 0) {
            return 0;
        }
        if (sortVector.size() % 2 == 0) {
            int index = sortVector.size() / 2;
            return (sortVector[index - 1] + sortVector[index]) * 1.0 / 2.0;
        } else {
            int index = (sortVector.size() - 1) / 2;
            return sortVector[index];
        }
    }

    /// 最长回文字符串
    /// 思路：中心拓展，获取奇数、偶数的回文串对应下标，判断长度，然后返回子串
    pair<int, int> expandPalindromeCenter(const string &s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }
        return {left + 1, right - 1};
    }

    string longestPalindrome(string s) {
        if (s.length() <= 1) {
            return s;
        }
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); ++i) {
            /// 获取奇数、偶数的回文串对应下标
            auto [left1, right1] = expandPalindromeCenter(s, i, i);
            auto [left2, right2] = expandPalindromeCenter(s, i, i+1);
            if (right1 - left1 > end - start) {
                start = left1;
                end = right1;
            }
            if (right2 - left2 > end - start) {
                start = left2;
                end = right2;
            }
        }
        return s.substr(start, end - start + 1);
    }

    /// 6.Z字形变换，思路：多个vector保存，然后依次读取。。。很暴力
    string convert(const string &s, int numRows) {
        if (numRows == 0 || numRows == 1) {
            return s;
        }
        unordered_map<int, vector<string>> map;
        for (int i = 0; i < numRows; ++i) {
            //pair<int, vector<string>>
            unordered_map<int, vector<string>>::iterator iter = map.find(i);
            if (iter == map.end()) {
                /// 不存在，生成
                vector<string> list;
                map.insert({i,list});
            }
        }
        int index = 0;
        bool isIncre = true;
        for (int i = 0; i < s.length(); ++i) {
            string tmp = s.substr(i, 1);

            unordered_map<int, vector<string>>::iterator iter = map.find(index);
            iter->second.push_back(tmp);

            if (isIncre) {
                index++;
            } else {
                index--;
            }
            if (index == numRows - 1) {
                isIncre = false;
            } else if (index == 0) {
                isIncre = true;
            }
        }

        string result;
        for (int i = 0; i < numRows; ++i) {
            unordered_map<int, vector<string>>::iterator iter = map.find(i);
            for (int i = 0; i < iter->second.size(); ++i) {
                result.append(iter->second[i]);
            }
        }
        return result;
    }
};

int main() {
    Solution object = Solution();
//    vector<int> nums = {2,7,1,8};
//    nums = object.twoSum(nums, 9);

//    ListNode *l1 = new ListNode(2,new ListNode(4, new ListNode(3)));
//    ListNode *l2 = new ListNode(5,new ListNode(6, new ListNode(4)));
//    ListNode *result = object.addTwoNumbers(l1, l2);
//    while (result != nullptr) {
//        cout << result->val << endl;
//        result = result->next;
//    }

//    int count = object.lengthOfLongestSubstr("   ");

//    vector<int> nums1 = {1,1,1,1,1,1,1,1,1,1,4,4};
//    vector<int> nums2 = {1,3,4,4,4,4,4,4,4,4,4};
//    double count = object.findMedianSortedArrays(nums1,nums2);
//    cout << count;

//    string s = object.longestPalindrome("ccc");
    string s = object.convert("AB", 1);
    cout << s;
    return 0;
}
