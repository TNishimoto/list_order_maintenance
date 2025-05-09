#pragma once
#include "./list_order_map.hpp"
#include "stool/include/light_stool.hpp"
#include <cassert>

namespace stool
{
    namespace lom
    {
        template <typename T>
        struct OnlineBackwardSuffixSortComparer
        {
            static inline std::vector<T> *characters = nullptr;
            static inline std::vector<stool::lom::LOPointer> *pointers = nullptr;

            bool operator()(const uint64_t &a, const uint64_t &b) const
            {
                const T c1 = (*OnlineBackwardSuffixSortComparer::characters)[a];
                const T c2 = (*OnlineBackwardSuffixSortComparer::characters)[b];

                if (c1 != c2)
                {
                    return c1 < c2;
                }
                else
                {

                    if (a == 0 || b == 0)
                        return a < b;
                    const stool::lom::LOPointer p1 = (*OnlineBackwardSuffixSortComparer::pointers)[a - 1];
                    const stool::lom::LOPointer p2 = (*OnlineBackwardSuffixSortComparer::pointers)[b - 1];
                    return *p1 < *p2;
                }
            }
        };

        template <typename T>
        class OnlineBackwardSuffixSort
        {
        private:
            std::vector<T> characters;
            std::vector<stool::lom::LOPointer> pointers;
            std::set<uint64_t, OnlineBackwardSuffixSortComparer<T>> sortedSuffixes;
            ListOrderMaintenance list;
            void set_comparer_pointers()
            {
                OnlineBackwardSuffixSortComparer<T>::characters = &this->characters;
                OnlineBackwardSuffixSortComparer<T>::pointers = &this->pointers;
            }

        public:
            std::set<uint64_t>::iterator begin()
            {
                return this->sortedSuffixes.begin();
            }
            std::set<uint64_t>::iterator end()
            {
                return this->sortedSuffixes.end();
            }
            void clear()
            {
                this->characters.clear();
                this->pointers.clear();
                this->sortedSuffixes.clear();
                this->list.clear();
            }

            void push(T item)
            {
                uint64_t pos = this->characters.size();
                this->characters.push_back(item);
                this->sortedSuffixes.insert(pos);
                auto it = sortedSuffixes.find(pos);

                assert(it != sortedSuffixes.end());

                if (*it == *sortedSuffixes.begin())
                {

                    auto p = list.insertAfter();
                    this->pointers.push_back(p);
                }
                else
                {
                    --it;
                    auto p = list.insertAfter(this->pointers[*it]);
                    this->pointers.push_back(p);
                }
            }
            OnlineBackwardSuffixSort()
            {
                this->set_comparer_pointers();
            }
            OnlineBackwardSuffixSort(const std::vector<T> &text)
            {
                this->set_comparer_pointers();

                // stool::Counter counter;
                uint64_t counterMax = (text.size() / 100) + 1;
                uint64_t counter = counterMax;
                uint64_t counterID = 0;
                uint64_t counter_sum = 0;

                if (text.size() > 1000000)
                {
                    std::cout << std::endl;
                }
                for (auto it = text.rbegin(); it != text.rend(); ++it)
                {
                    counter--;
                    if (counter == 0)
                    {
                        counter_sum += counterMax;
                        if (text.size() > 1000000)
                        {
                            std::cout << "\r Processing(" << counterID << "/" << "100" << "): [" << counter_sum << "/" << text.size() << "]" << std::flush;
                        }
                        counter = counterMax;
                        counterID++;
                    }
                    // counter.increment();
                    this->push(*it);
                }
                if (text.size() > 1000000)
                {
                    std::cout << std::endl;
                }
            }

            uint64_t size()
            {
                return this->characters.size();
            }

            template <typename X>
            inline std::vector<X> to_suffix_array()
            {
                uint64_t size = this->size();

                std::vector<X> sa;
                sa.resize(size);
                uint64_t x = 0;

                auto it = this->sortedSuffixes.begin();
                while (it != this->sortedSuffixes.end())
                {
                    sa[x++] = (X)(size - (*it) - 1);
                    ++it;
                }
                return sa;
            }

            /*
            static std::vector<uint64_t> construct_suffix_array(const std::vector<T> &text)
            {
                stool::lom::OnlineBackwardSuffixSort<T> ss;
                for (int64_t i = text.size() - 1; i >= 0; i--)
                {
                    ss.push(text[i]);
                }

                return ss.to_suffix_array();
            }
            */
            void print()
            {
                uint64_t size = this->size() + 1;
                std::cout << "---------" << std::endl;
                for (auto &it : this->sortedSuffixes)
                {
                    uint64_t p = size - it - 1;
                    std::vector<int64_t> vec;
                    int64_t x = it;
                    while (x >= 0)
                    {
                        vec.push_back(this->characters[x--]);
                    }
                    std::string s;
                    stool::Printer::toIntegerString(vec, s);
                    std::cout << p << ": " << s << "/" << *this->pointers[it] << std::endl;
                }
                std::cout << "---------" << std::endl;
            }
        };

    } // namespace LO
} // namespace stool