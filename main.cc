#include <iostream>
#include <utility>
#include <string>
#include <unistd.h>
#include <map>
#include "gtest/gtest.h"

using namespace std;

TEST(smart_ptr, unique_ptr)
{
    // std::make_unique can be used in C++14
    auto uptr = std::make_unique<int>(42);
    cout << *uptr << endl;

    // unique_ptr can not be copied
    // auto uptr_cpy = uptr;

    // old construct method
    auto uptr_using_new = new int(43);
    cout << *uptr_using_new << endl;

    auto uptr_not_using_new(new int(44));
    cout << *uptr_not_using_new << endl;

    auto uptr_move = std::move(uptr);
    // uptr should be nullptr
    assert(!uptr);
    EXPECT_EQ(uptr, nullptr);
    cout << *uptr_move << endl;
}

TEST(auto, reference)
{
    class TestBundle
    {
      public:
        int x;
    };

    TestBundle cat;
    cat.x = 100;
    std::map<string, std::map<string, TestBundle>> bundleMaps;
    auto& catMap = bundleMaps["cat"];
    catMap["cat1"] = std::move(cat);

    TestBundle dog;
    dog.x = 101;
    auto dogMap = bundleMaps["dog"];
    dogMap["dog1"] = std::move(dog);

    cout << "bundleMaps size: " << bundleMaps.size() << endl;
    EXPECT_EQ(bundleMaps.size(), 2);
    EXPECT_EQ(bundleMaps["cat"].size(), 1);
    EXPECT_EQ(bundleMaps["dog"].size(), 0);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}