#pragma once
#include <vector>
#include <iostream>
#include <list>
#include <random>
#include <exception>
#include <memory>
#include <map>
#include <set>
#include <forward_list>
using namespace std;

namespace my
{
//using LOInt = uint64_t;
using LOInt = uint64_t;

class ListOrderLessComparer
{
  public:
	bool operator()(const std::list<LOInt>::iterator &left, const std::list<LOInt>::iterator &right) const
	{
		return *left < *right;
	}
};
class ListOrderLessEqualComparer
{
  public:
	bool operator()(const std::list<LOInt>::iterator &left, const std::list<LOInt>::iterator &right) const
	{
		return *left <= *right;
	}
};

class ListOrderMaintenance
{
  private:
	std::list<LOInt> _list;
	std::list<LOInt>::iterator _B;
	LOInt labelMaxValue;
	LOInt getStarLabel(const std::list<LOInt>::iterator &item);
	bool errorCheck();
	bool errorCheck(const std::list<LOInt>::iterator& x);
	bool errorCheck(const std::list<LOInt>::iterator& start, const std::list<LOInt>::iterator& end);
	void print(const std::list<LOInt>::iterator& x);

	//const std::list<LOInt>::iterator getMinimumIterator();
	//const std::list<LOInt>::iterator getMaximumIterator();
	//LOInt specialMod(LOInt v);

	void relabeling(const std::list<LOInt>::iterator &x);
	LOInt getDistance(const std::list<LOInt>::iterator &x, const std::list<LOInt>::iterator &y);
	LOInt getHalfPosition(const std::list<LOInt>::iterator &x, const std::list<LOInt>::iterator &succ);

  public:
	LOInt getBasicLabel(const std::list<LOInt>::iterator &item);
	bool remove(std::list<LOInt>::iterator &x);
	const std::list<LOInt>::iterator insertAfter(const std::list<LOInt>::iterator &x);
	const std::list<LOInt>::iterator insertAfter();
	ListOrderMaintenance();
	virtual ~ListOrderMaintenance()
	{
	}

	void clear();
};
#ifdef _INT128
string to_string(__int128_t n);
#endif
string to_string(uint64_t n);


}