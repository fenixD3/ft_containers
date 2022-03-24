#include "vector.h"
#include "stack.h"
#include "map.h"
#include "set.h"

#include <vector>
#include <stack>
#include <map>
#include <set>

#include <chrono>
#include <functional>
#include <iostream>

void test_set_ft()
{
    ft::set<size_t> st;
    for (auto i = 0; i < 1'000'000; ++i)
    {
        st.insert(i);
    }

    st.erase(st.find(33), st.find(999'999));
    std::cout << __FUNCTION__ << ": ";
}

void test_set_std()
{
    std::set<size_t> st;
    for (auto i = 0; i < 1'000'000; ++i)
    {
        st.insert(i);
    }

    st.erase(st.find(33), st.find(999'999));
    std::cout << __FUNCTION__ << ": ";
}

void test_map_ft()
{
    ft::map<std::string, size_t> m;
    for (auto i = 0; i < 1'000'000; ++i)
    {
        m[std::string(1000, i)] = i;
    }

    m.erase(m.find(std::string(1000, 'a')), m.find(std::string(1000, 'z')));
    std::cout << __FUNCTION__ << ": ";
}

void test_map_std()
{
    std::map<std::string, size_t> m;
    for (auto i = 0; i < 1'000'000; ++i)
    {
        m[std::string(1000, i)] = i;
    }

    m.erase(m.find(std::string(1000, 'a')), m.find(std::string(1000, 'z')));
    std::cout << __FUNCTION__ << ": ";
}

void test_stack_ft()
{
    ft::stack<std::string> s;
    for (auto i = 0; i < 1'000'000; ++i)
    {
        s.push(std::string(1000, 'f'));
    }

    s.pop();
    std::cout << __FUNCTION__ << ": ";
}

void test_stack_std()
{
    std::stack<std::string> s;
    for (auto i = 0; i < 1'000'000; ++i)
    {
        s.push(std::string(1000, 'f'));
    }

    s.pop();
    std::cout << __FUNCTION__ << ": ";
}

void test_vector_ft()
{
    ft::vector<size_t> v;
    for (auto i = 0; i < 1'000'000; ++i)
    {
        v.push_back(i);
    }

    v.erase(v.begin() + 3, v.end() - 5);
    std::cout << __FUNCTION__ << ": ";
}

void test_vector_std()
{
    std::vector<size_t> v;
    for (auto i = 0; i < 1'000'000; ++i)
    {
        v.push_back(i);
    }

    v.erase(v.begin() + 3, v.end() - 5);
    std::cout << __FUNCTION__ << ": ";
}

void measure_func(const std::function<void()>& func)
{
    auto start = std::chrono::steady_clock::now();
    func();
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " seconds" << std::endl;
}

int main()
{
    measure_func(test_vector_ft);
    measure_func(test_vector_std);

    measure_func(test_stack_ft);
    measure_func(test_stack_std);

    measure_func(test_map_ft);
    measure_func(test_map_std);

    measure_func(test_set_ft);
    measure_func(test_set_std);
    return 0;
}
