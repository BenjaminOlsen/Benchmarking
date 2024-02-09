#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include "leet.hpp"

#define MAX(X,Y)  (((X)>(Y))?(X):(Y))
// -------------------------------------------------------------------------------------------------
int Leet::lengthOfLongestSubstring::solution1(std::string s) {
    std::vector<int> chars(128);

    int left = 0;
    int right = 0;

    int cnt = 0; //length of current longest valid string

    while (right < s.length()) {
        char r = s[right];
        chars[r]++;

        while (chars[r] > 1) {
            char l = s[left];
            chars[l]--;
            left++;
        }

        cnt = MAX(cnt, right - left + 1);

        right++;
    }

    return cnt;
}


// -------------------------------------------------------------------------------------------------
int Leet::lengthOfLongestSubstring::solution2(std::string s) {
    int i = 0; //left index
    int j = 0; //right index
    int cnt = 0; // count of the current max valid string length
    char curChar; // holds the letter

    // maps char to its last seen index in s
    std::unordered_map<char, int> map;

    //scan through the string once
    while (j < s.size()) {
        curChar = s[j];
        
        // if the current char at the right index is already in the string
        if (map.count(curChar)){
        // then advance the left index just beyond that index
            i = map[curChar]+1;
        }
        
        //the length of the string is j-1+1
        cnt = std::max(j-i+1, cnt); //j-i+1 > cnt ? j-i+1 : cnt;

        //set the position of the current char
        map[curChar]=j;
        /*printf("i: %d, j: %d, s[%d]: %c, cnt: %d, len: %d", i, j, j, curChar, cnt, j-i+1);
        for (unordered_map<char, int>::const_iterator it = map.begin(); it != map.end(); it++){
        printf(", map[%c] = %d", it->first, it->second);
        }
        printf("\n");*/
        ++j;
    }

    return cnt;
}


// -------------------------------------------------------------------------------------------------
int Leet::lengthOfLongestSubstring::solution3(std::string s) {
    std::vector<int> chars(128);
    //this vector is really a map between the ascii value of the char and its last index in the string


    //if it has never been seen before, its value is negative
    for (auto &k : chars) {
        k = -1;
    }

    int left = 0;
    int right = 0;

    int cnt = 0; //length of current longest valid string
    while (right < s.length()) {
        char r = s[right];
        
        // if r is already in the string, then move the left index just beyond its previous position
        if (chars[r] > 0) {
            left = chars[r] + 1;
        }

        //and set its index to the current one
        chars[r] = right;

        //update the longest string length
        cnt = MAX(cnt, right - left + 1);

        right++;
    }

    return cnt;
}

template<typename T>
void printStack(std::stack<T> s) {
    while (!s.empty()) {
        T el = s.top();
        s.pop();
        std::cout << el << ',';
    }
    std::cout << std::endl;
}
// -------------------------------------------------------------------------------------------------
int Leet::longestValidParentheses::solution1(std::string s) {
    //"((((((()()()()()()()()()()())))))))))))()()()()((((())()()()()()()()()()()()()()()()()()()()
    
    size_t n = s.size();
    //std::cout << s << std::endl;
    int longest = 0;
    std::stack<size_t> stack;

    for (size_t k = 0; k < s.size(); k++) {
        char c = s[k];
        //printf("s[%lu] = %c\n", k, c);
        if (c == '(') {
            stack.push(k);
            //printStack(stack);
        }
        else { // c==')'
            if (!stack.empty()) { 
                //printf("s[stack.top()]: %c\n", s[stack.top()]);
                if (s[stack.top()] == '(') {
                    stack.pop();
                }
                else {
                    stack.push(k);
                }
            }
            else {
                //printf("push %d\n",int(k));
                stack.push(k);
            }
            //printStack(stack);
            
        }
    }
    //now, the stack only contains the indices that do NOT correspond to a valid parenthesis string, 
    //so we can calculate the biggest gap between the indices by scanning through 
    if (stack.empty()) {
        longest = n;
    }
    else {
        int begin = 0;
        int end = n;

        while (!stack.empty()) {
            begin = stack.top();
            stack.pop();
            longest = std::max((end-begin-1), longest);
            //for (int k = begin; k < end; k++) { std::cout << s[k]; }
            //std::cout << ", end: " << end << ", begin: " << begin << ", longest: " << longest << ", stack.size(): " << stack.size() << std::endl;
            end = begin; //the end for the next iter is the beginning of this one
        }
        // for the 0 index case
        longest = std::max(longest, end);
    }
    //printf("str: \"%s\" (len %lu) - longest:  %d\n", s.c_str(), s.size(), longest);
    return longest;

}

// -------------------------------------------------------------------------------------------------
int Leet::longestValidParentheses::solution2(std::string s) {
    std::stack<int> st;
    st.push(-1);
    int len_max = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '('){
            st.push(i);
        }
        else{
            st.pop();
            if(st.empty()){
                st.push(i);
            }
            else {
                int len = i - st.top();
                len_max = std::max(len, len_max);
            }
        }
        
    }
    return len_max;
}

// -------------------------------------------------------------------------------------------------
int Leet::longestValidParentheses::solution3(std::string s){
    if (s.size() < 2) {
        return 0;
    }

    int maxValid = 0;
    int* layerMaxLength = new int[s.size()]{};  //stores the longest valid substring ending at each position 
    int curLayer = -1;

    // keep track of the current "layer", or "depth" of the open parentheses
    for (char& c : s) {
        if (c == '(') {
            curLayer++; //increase current layer
        } 
        else if (curLayer >= 0) { // if we're inside an open parenthesis,
            //increase the current max length by 2, including the length of any sequence
            //contained within, i.e. in one layer deeper.
            layerMaxLength[curLayer] += layerMaxLength[curLayer + 1] + 2; 
            // as the current layer is now closed, the contained layer is counted in curLayer
            layerMaxLength[curLayer + 1] = 0;

            maxValid = std::max(layerMaxLength[curLayer], maxValid); // update max

            curLayer--; // go up one layer
        } 
        else { // curLayer never increased, there has been no valid substring
            layerMaxLength[0] = 0;
        }
    }
    return maxValid;
}

// -------------------------------------------------------------------------------------------------
std::vector< std::vector<int> > Leet::findMatrix::solution1(std::vector<int>& nums) { 
    std::cout << "solution1; input length: "<< nums.size() << std::endl;
    
    if (nums.size() == 0) {
        return std::vector<std::vector<int>>();
    }

    
    std::vector<std::unordered_set<int>> rowSets(nums.size());
    std::vector<std::vector<int>> resVec(1);

    // for each number in nums, put it in the lowest row such that it doesn't repeat
    for (int n : nums) {
        for (int rowIdx = 0; rowIdx < rowSets.size(); ++rowIdx){
            //put it in the first row that you find that does not contain it
            //printf("---------\nrowIdx: %d; n: %d\n", rowIdx, n);
            if (rowSets[rowIdx].find(n) == rowSets[rowIdx].end()) {
                //printf("inserting %d in row %d\n", n, rowIdx);
                rowSets[rowIdx].insert(n);
                resVec[rowIdx].push_back(n);
                break;
            }
            else if (rowIdx == resVec.size()-1) { //if it's the last row in the vec already, make a new row
                //printf("making a new row beyond %d for %d\n", rowIdx, n);
                resVec.push_back(std::vector<int>());
                //rowSets[rowIdx].insert(n);
            }
            else {
                //printf("%d already in row %d\n", n, rowIdx);
            }
        }
    }
    return resVec;
}


// -------------------------------------------------------------------------------------------------
std::vector< std::vector<int> > Leet::findMatrix::solution2(std::vector<int>& nums) { 
    std::vector<int> freq(nums.size()+1);
    std::vector<std::vector<int>> res;

    std::cout << "solution2; input length: "<< nums.size() << std::endl;

    for (auto i : nums)
    {
        if (freq[i] >= res.size()) res.push_back({});
        res[freq[i]].push_back(i);
        freq[i]++;
    }
    return res; 
}