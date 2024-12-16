#include <string>
#include <array>
#include <algorithm>
#include <iostream>



class A
{
public:
    A(std::string value) :
        _value(value)
    {}

    std::string getValue() const 
    {
        return _value;
    }

private:
    std::string _value;
};



int main()
{
    // array of objects of class A
    std::array arr =
    {
        A("min"),
        A("and"),
        A("max"),
        A("elements"),
        A("by"),
        A("size")
    };

    // function to compare objects of class A by the size of their value
    auto fnComp = [](const A& l, const A& r) -> bool
        {
            return l.getValue().size() < r.getValue().size();
        };

    // get iterator to minimum element
    auto minElem1 = std::min_element(arr.begin(), arr.end(), fnComp);
    std::cout << "min element: " << minElem1->getValue() << std::endl;

    // get iterator to maximum element
    auto maxElem1 = std::max_element(arr.begin(), arr.end(), fnComp);
    std::cout << "max element: " << maxElem1->getValue() << std::endl;

    // get pair of iterators to min and max elements
    auto [minElem2, maxElem2] = std::minmax_element(arr.begin(), arr.end(), fnComp);
    std::cout << "min element (minmax): " << minElem2->getValue() << std::endl;
    std::cout << "max element (minmax): " << maxElem2->getValue() << std::endl;

    return 0;
}
