#include <functional>
#include <vector>

template<typename T>
std::function<void (T)> create_handler(std::vector<T>* memo)
{
    return [memo](T event_data) mutable
    {
        memo->push_back(event_data);
    };
}
