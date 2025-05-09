#pragma once
#include "./online_suffix_sort.hpp"

namespace stool
{
    namespace lom
    {
        template <typename T, typename INDEX = uint64_t>
        std::vector<INDEX> construct_suffix_array(const std::vector<T> &text)
        {
            stool::lom::OnlineBackwardSuffixSort<T> ss(text);
            return ss.template to_suffix_array<INDEX>();
        };

        template <typename T>
        std::vector<T> construct_bwt(const std::vector<T> &text)
        {

            stool::lom::OnlineBackwardSuffixSort<T> ss(text);
            std::vector<T> r;
            for (auto &it : ss)
            {
                uint64_t sa_value = ss.size() - 1 - it;
                T bwtChar = sa_value == 0 ? text[text.size() - 1] : text[sa_value - 1];
                r.push_back(bwtChar);
            }
            return r;
        };

        template <typename T>
        std::vector<std::pair<T, uint64_t>> construct_rlbwt(const std::vector<T> &text)
        {

            stool::lom::OnlineBackwardSuffixSort<T> ss(text);
            std::vector<std::pair<T, uint64_t>> r;

            T character;
            uint64_t pow = 0;

            for (auto &it : ss)
            {
                uint64_t sa_value = ss.size() - 1 - it;
                T bwtChar = sa_value == 0 ? text[text.size() - 1] : text[sa_value - 1];
                if (bwtChar == character)
                {
                    pow++;
                }
                else
                {
                    if (pow > 0)
                    {
                        r.push_back(std::pair<T, uint64_t>(character, pow));
                    }
                    character = bwtChar;
                    pow = 1;
                }
            }
            if (pow > 0)
            {
                r.push_back(std::pair<T, uint64_t>(character, pow));
            }

            return r;
        };

        template <typename T>
        std::vector<int64_t> construct_differential_suffix_array(const std::vector<T> &text)
        {

            stool::lom::OnlineBackwardSuffixSort<T> ss(text);
            std::vector<int64_t> sa = ss.template to_suffix_array<int64_t>();
            int64_t tmp = sa[0];
            for (uint64_t i = 1; i < sa.size(); i++)
            {
                int64_t newValue = sa[i] - tmp;
                tmp = sa[i];
                sa[i] = newValue;
            }

            return sa;
        };

    }
}