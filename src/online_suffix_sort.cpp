#include "../src/online_suffix_sort.hpp"

namespace stool
{
namespace LO
{

template<> std::vector<uint64_t> *OnlineBackwardSuffixSortComparer<uint64_t>::characters = nullptr;
template<> std::vector<uint32_t> *OnlineBackwardSuffixSortComparer<uint32_t>::characters = nullptr;
template<> std::vector<uint16_t> *OnlineBackwardSuffixSortComparer<uint16_t>::characters = nullptr;
template<> std::vector<uint8_t> *OnlineBackwardSuffixSortComparer<uint8_t>::characters = nullptr;
template<> std::vector<int64_t> *OnlineBackwardSuffixSortComparer<int64_t>::characters = nullptr;
template<> std::vector<int32_t> *OnlineBackwardSuffixSortComparer<int32_t>::characters = nullptr;
template<> std::vector<int8_t> *OnlineBackwardSuffixSortComparer<int8_t>::characters = nullptr;
template<> std::vector<char> *OnlineBackwardSuffixSortComparer<char>::characters = nullptr;


template<> std::vector<stool::LO::LOPointer> *OnlineBackwardSuffixSortComparer<uint64_t>::pointers = nullptr;
template<> std::vector<stool::LO::LOPointer> *OnlineBackwardSuffixSortComparer<uint32_t>::pointers = nullptr;
template<> std::vector<stool::LO::LOPointer> *OnlineBackwardSuffixSortComparer<uint16_t>::pointers = nullptr;
template<> std::vector<stool::LO::LOPointer> *OnlineBackwardSuffixSortComparer<uint8_t>::pointers = nullptr;
template<> std::vector<stool::LO::LOPointer> *OnlineBackwardSuffixSortComparer<int64_t>::pointers = nullptr;
template<> std::vector<stool::LO::LOPointer> *OnlineBackwardSuffixSortComparer<int32_t>::pointers = nullptr;
template<> std::vector<stool::LO::LOPointer> *OnlineBackwardSuffixSortComparer<int8_t>::pointers = nullptr;
template<> std::vector<stool::LO::LOPointer> *OnlineBackwardSuffixSortComparer<char>::pointers = nullptr;

template <typename T>
bool OnlineBackwardSuffixSortComparer<T>::operator()(const uint64_t &a, const uint64_t &b) const
{    
    const T c1 = (*OnlineBackwardSuffixSortComparer::characters)[a];
    const T c2 = (*OnlineBackwardSuffixSortComparer::characters)[b];

    if (c1 != c2)
    {
        return c1 < c2;
    }
    else
    {

        if(a == 0 || b == 0) return a < b;
        const stool::LO::LOPointer p1 = (*OnlineBackwardSuffixSortComparer::pointers)[a - 1];
        const stool::LO::LOPointer p2 = (*OnlineBackwardSuffixSortComparer::pointers)[b - 1];
        return *p1 < *p2;
    }
}

template struct OnlineBackwardSuffixSortComparer<uint64_t>;
template struct OnlineBackwardSuffixSortComparer<uint32_t>;
template struct OnlineBackwardSuffixSortComparer<uint16_t>;
template struct OnlineBackwardSuffixSortComparer<uint8_t>;
template struct OnlineBackwardSuffixSortComparer<int64_t>;
template struct OnlineBackwardSuffixSortComparer<int32_t>;
template struct OnlineBackwardSuffixSortComparer<int8_t>;
template struct OnlineBackwardSuffixSortComparer<char>;






template <typename T>
void OnlineBackwardSuffixSort<T>::set_comparer_pointers()
{
    OnlineBackwardSuffixSortComparer<T>::characters = &this->characters;
    OnlineBackwardSuffixSortComparer<T>::pointers = &this->pointers;
}
template class OnlineBackwardSuffixSort<uint64_t>;
template class OnlineBackwardSuffixSort<uint32_t>;
template class OnlineBackwardSuffixSort<uint16_t>;
template class OnlineBackwardSuffixSort<uint8_t>;
template class OnlineBackwardSuffixSort<int64_t>;
template class OnlineBackwardSuffixSort<int32_t>;
template class OnlineBackwardSuffixSort<int8_t>;
template class OnlineBackwardSuffixSort<char>;



} // namespace LO
} // namespace stool