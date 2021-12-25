#include "list_order.hpp"

namespace stool {

namespace lom
{
	template <typename T, typename COMPARER>
	class ListOrderMap {
		ListOrderMaintenance list;
	public:

		std::map<T, std::list<LOInt>::iterator, COMPARER> map;


		void add(T item) {
			if (this->contains(item)) throw "error";
			auto ptr = map.upper_bound(item);
			if (map.size() == 0 || ptr == map.begin()) {
				auto ptr2 = list.insertAfter();
				map.insert(std::pair<int, std::list<LOInt>::iterator>(item, ptr2));
			}
			else {
				auto ptr2 = list.insertAfter((--ptr)->second);
				map.insert(std::pair<int, std::list<LOInt>::iterator>(item, ptr2));
			}
		}
		bool erase(T item) {
			auto result = map.find(item);

			if (result != map.end()) {

				auto preItem = (*result).second;

				map.erase(item);
				list.remove(preItem);
				return true;
			}
			else {
				return false;
			}
		}
		bool contains(T item) {
			auto result = map.find(item);

			if (result != map.end()) {
				return true;
			}
			return false;

		}
		LOInt getLabel(std::list<LOInt>::iterator& x) {
			return this->list.getBasicLabel(x);
		}


	};
}
}