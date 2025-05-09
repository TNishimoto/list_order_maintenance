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
            std::vector<uint64_t> sa;

            {
                stool::lom::OnlineBackwardSuffixSort<T> ss(text);
                std::vector<uint64_t> tmp = ss.template to_suffix_array<uint64_t>();
                sa.swap(tmp);

                std::cout << "Destructing OnlineBackwardSuffixSort..." << std::flush;
            }
                std::cout << "[END]" << std::endl;


            return stool::construct_DSA(sa);
        };

    }
}