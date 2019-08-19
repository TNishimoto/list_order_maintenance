#include "../src/suffix_sort.hpp"

namespace stool
{
namespace LO
{

template <>
std::vector<uint64_t> *OnlineBackwardSuffixSortComparer<uint64_t>::characters = nullptr;
template <>
std::vector<stool::LO::LOPointer> *OnlineBackwardSuffixSortComparer<uint64_t>::pointers = nullptr;

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
        const stool::LO::LOPointer p1 = (*OnlineBackwardSuffixSortComparer::pointers)[a - 1];
        const stool::LO::LOPointer p2 = (*OnlineBackwardSuffixSortComparer::pointers)[b - 1];
        /*
    const T b1 = (*OnlineBackwardSuffixSortComparer::characters)[a-1];
    const T b2 = (*OnlineBackwardSuffixSortComparer::characters)[b-1];
        if(b1 < b2){
            std::cout << b1 << "<" << b2<< std::endl;
            if(*p1 > *p2){
                std::cout << a << "/" << b << std::endl;
            }
            assert(*p1 < *p2);
        }else if(b2 < b1){
            std::cout << b1 << ">" << b2 << std::endl;
            assert(*p1 > *p2);
        }
        */

        return *p1 < *p2;
    }
}
template struct OnlineBackwardSuffixSortComparer<uint64_t>;

template <typename T>
void OnlineBackwardSuffixSort<T>::set_comparer_pointers()
{
    OnlineBackwardSuffixSortComparer<T>::characters = &this->characters;
    OnlineBackwardSuffixSortComparer<T>::pointers = &this->pointers;
}

template class OnlineBackwardSuffixSort<uint64_t>;


} // namespace LO
} // namespace stool