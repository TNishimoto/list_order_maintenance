#include "../src/list_order_map.hpp"

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
public:
    std::vector<T> characters;
    std::vector<stool::LO::LOPointer> pointers;
    std::set<uint64_t, OnlineBackwardSuffixSortComparer<T>> sortedSuffixes;
    ListOrderMaintenance list;
    void push(T item)
    {
        uint64_t pos = this->characters.size();
        this->characters.push_back(item);
        //auto p = list.insertAfter();
        //this->pointers.push_back(p);
        this->sortedSuffixes.insert(pos);

        auto it = lower_bound(sortedSuffixes.begin(), sortedSuffixes.end(), pos);
        --it;
        auto p = list.insertAfter(this->pointers[*it]);
        this->pointers.push_back(p);
    }
    void set_comparer_pointers();
    OnlineBackwardSuffixSort()
    {
        this->set_comparer_pointers();
        this->characters.push_back(0);
        auto p = list.insertAfter();
        this->pointers.push_back(p);
        this->sortedSuffixes.insert(0);
    }
    uint64_t size()
    {
        return this->characters.size();
    }
    std::vector<uint64_t> to_suffix_array()
    {
        uint64_t size = this->size();

        std::vector<uint64_t> sa;
        sa.resize(size);
        uint64_t x = 0;
        for (auto &it : this->sortedSuffixes)
        {
            sa[x++] = size - it - 1;
        }
        return sa;
    }
};
} // namespace LO
} // namespace stool