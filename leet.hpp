#ifndef LEET_HPP
#define LEET_HPP

namespace Leet {
    // -------------------------------------------------------------------------------------------------
    class lengthOfLongestSubstring {
    public:
        static int solution1(std::string s);
        static int solution2(std::string s);
        static int solution3(std::string s);
    };

    // -------------------------------------------------------------------------------------------------
    class longestValidParentheses {
    public:
        static int solution1(std::string s);
        static int solution2(std::string s);
        static int solution3(std::string s);
    };

    // -------------------------------------------------------------------------------------------------
    class findMatrix {
    public:
        static std::vector< std::vector<int> > solution1(std::vector<int>& nums);
        static std::vector<std::vector<int> > solution2(std::vector<int>& nums);
    };
}
#endif