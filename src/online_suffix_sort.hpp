#include "../src/list_order_map.hpp"
#include "stool/src/print.hpp"
#include <cassert>

namespace stool
{
namespace LO
{
template <typename T>
struct OnlineBackwardSuffixSortComparer
{
    static std::vector<T> *characters;
    static std::vector<stool::LO::LOPointer> *pointers;

    bool operator()(const uint64_t &a, const uint64_t &b) const;
};

template <typename T>
class OnlineBackwardSuffixSort
{
private:
    std::vector<T> characters;
    std::vector<stool::LO::LOPointer> pointers;
    std::set<uint64_t, OnlineBackwardSuffixSortComparer<T>> sortedSuffixes;
    ListOrderMaintenance list;
    void set_comparer_pointers();

public:
    std::set<uint64_t>::iterator begin()
    {
        return this->sortedSuffixes.begin();
    }
    std::set<uint64_t>::iterator end()
    {
        return this->sortedSuffixes.end();
    }
    void clear(){        
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

        //stool::Counter counter;
        uint64_t counterMax = (text.size() / 100) + 1;
        uint64_t counter = counterMax;
        uint64_t counterID = 0;
        uint64_t counter_sum = 0;
        for (auto it = text.rbegin();it!=text.rend();++it)
        {
            counter--;
            if(counter == 0){
                counter_sum += counterMax;
                std::cout << "Processing(" << counterID << "/" << "100" << "): [" << counter_sum << "/" << text.size() << "]" << std::endl;
                counter = counterMax;
                counterID++;
            }
            //counter.increment();
            this->push(*it);
        }
        std::cout << std::endl;
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
        stool::LO::OnlineBackwardSuffixSort<T> ss;
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

template <typename T, typename INDEX = uint64_t>
std::vector<INDEX> construct_suffix_array(const std::vector<T> &text)
{
    stool::LO::OnlineBackwardSuffixSort<T> ss(text);
    return ss.template to_suffix_array<INDEX>();
};

template <typename T>
std::vector<T> construct_bwt(const std::vector<T> &text)
{

    stool::LO::OnlineBackwardSuffixSort<T> ss(text);
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

    stool::LO::OnlineBackwardSuffixSort<T> ss(text);
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
    
    stool::LO::OnlineBackwardSuffixSort<T> ss(text);
    std::vector<int64_t> sa = ss.template to_suffix_array<int64_t>();
    int64_t tmp = sa[0];
    for(uint64_t i=1;i<sa.size();i++){
        int64_t newValue = sa[i] - tmp;
        tmp = sa[i];
        sa[i] = newValue;
    }

    return sa;
    
};


} // namespace LO
} // namespace stool