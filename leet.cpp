#include <string>
#include <vector>
#include <unordered_map>

#include "leet.hpp"

#define MAX(X,Y)  (((X)>(Y))?(X):(Y))
// -------------------------------------------------------------------------------------------------
int Leet::lengthOfLongestSubstring1::solution(std::string s) {
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
int Leet::lengthOfLongestSubstring2::solution(std::string s) {
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
int Leet::lengthOfLongestSubstring3::solution(std::string s) {
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
