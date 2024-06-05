#ifndef SECOND_LAB_TESTING_H
#define SECOND_LAB_TESTING_H

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../List/List.h"

TEST(List, defaultConstructor) {
    List<int> list;
    ASSERT_TRUE(list.getLength() == 0 && list.begin() == list.end());
}

TEST(List, initializerListConstructor) {
    List<int> list = {52, 78, 1337};
    ASSERT_TRUE(list.getLength() == 3 && list.getElem(0) == 52 && list.getElem(1) == 78 && list.getElem(2) == 1337);
}

TEST(List, copyConstructor) {
    List<int> list1;
    int value = 52;
    list1.add(value);
    List<int> list2(list1);
    ASSERT_EQ(list2.getElem(0), value);
}

TEST(List, moveConstructor) {
    List<int> list1;
    int value = 777;
    list1.add(value);
    List<int> list2(std::move(list1));
    ASSERT_TRUE(list2.getLength() == 1 && list2.getElem(0) == value);
}

TEST(List, destructor) {
    auto* list = new List<int>();
    int value = 7;
    list->add(value);
    delete list;
}

TEST(List, insert) {
    List<int> list;
    int value = 1599;
    list.add(value);
    list.add(value);
    list.add(value);
    list.insert(52, 2);
    ASSERT_TRUE(list.getLength() == 4 && list.getElem(0) == value && list.getElem(1) == value && list.getElem(2) == 52 && list.getElem(3) == value);
}

TEST(List, add) {
    List<int> list;
    int value = 1599;
    list.add(value);
    ASSERT_EQ(list.getElem(0), value);
}

TEST(List, addRange) {
    List<int> list1;
    int value = 9;
    list1.add(value);
    list1.add(value);
    list1.add(value);
    List<int> list2;
    list2.addRange(list1);
    ASSERT_TRUE(list2.getLength() == 3 && list2.getElem(0) == 9 && list2.getElem(1) == 9 && list2.getElem(2) == 9);
}

TEST(List, arrayAddRange) {
    List<int> list;
    int value1 = 5, value2 = 52, value3 = 525;
    int range[] = {value1, value2, value3};
    size_t size = sizeof(range) / sizeof(range[0]);
    list.addRange(range, size);
    ASSERT_TRUE(list.getLength() == size && list.getElem(0) == value1 && list.getElem(1) == value2 && list.getElem(2) == value3);  // Check if the size of the List is correct
}

TEST(List, removeElem) {
    List<int> list;
    int value = 96;
    list.add(value);
    list.removeElem(0);
    ASSERT_EQ(list.getLength(), 0);
}

TEST(List, getLength) {
    List<int> list;
    int value = 66;
    list.add(value);
    ASSERT_EQ(list.getLength(), 1);
}

TEST(List, getElem) {
    List<int> list;
    int value = 1337;
    list.add(value);
    ASSERT_EQ(list.getElem(0), value);
}

TEST(List, operatorBrackets) {
    List<int> list;
    int value = 52;
    list.add(value);
    ASSERT_EQ(list[0], value);
}

TEST(List, getIndex) {
    List<int> list;
    int value = 104;
    list.add(value);
    ASSERT_EQ(list.getIndex(value), 0);
}

TEST(List, setElem) {
    List<int> list;
    int value = 9, new_value = 911;
    list.add(value);
    list.setElem(0, new_value);
    ASSERT_EQ(list.getElem(0), new_value);
}

TEST(List, toArray) {
    List<int> list;
    int value = 9;
    list.add(value);
    int* arr = list.toArray();
    ASSERT_EQ(list[0], arr[0]);
    delete[] arr;
}

TEST(List, combine) {
    List<int> list1;
    int value1 = 52, value2 = 78;
    list1.add(value1);
    list1.add(value2);
    List<int> list2;
    int value3 = 777, value4 = 1337;
    list2.add(value3);
    list2.add(value4);
    List<int> list3 = list1.combine(list2);
    ASSERT_TRUE(list1.getLength() == 2 && list2.getLength() == 2 && list3.getLength() == 4 && list3.getElem(0) == value1 && list3.getElem(1) == value2 && list3.getElem(2) == value3 && list3.getElem(3) == value4);
}

TEST(List, sort) {
    List<int> list;
    int value1 = 78, value2 = 79, value3 = 77;
    list.add(value1);
    list.add(value2);
    list.add(value3);
    list.sort(List<int>::compare);
    ASSERT_TRUE(list[0] == value3 && list[1] == value1 && list[2] == value2);
}

TEST(List, reverse) {
    List<int> list;
    int value1 = 1, value2 = 2, value3 = 3;
    list.add(value1);
    list.add(value2);
    list.add(value3);
    list.reverse();
    ASSERT_TRUE(list.getElem(0) == value3 && list.getElem(1) == value2 && list.getElem(2) == value1);
}

TEST(List, assignmentOperator) {
    List<int> list1;
    int value = 56;
    list1.add(value);
    List<int> list2;
    list2 = list1;
    ASSERT_EQ(list2.getElem(0), value);
}

TEST(List, addOperator) {
    List<int> list1;
    int value = 9;
    list1.add(value);
    list1.add(value);
    list1.add(value);
    List<int> list2;
    list2 = list2 + list1;
    ASSERT_TRUE(list2.getElem(0) == 9 && list2.getElem(1) == 9 && list2.getElem(2) == 9);
}

TEST(List, appPlusOperator) {
    List<int> list1;
    int value = 9;
    list1.add(value);
    list1.add(value);
    list1.add(value);
    List<int> list2;
    list2 += list1;
    ASSERT_TRUE(list2.getLength() == 3 && list2.getElem(0) == 9 && list2.getElem(1) == 9 && list2.getElem(2) == 9);
}


TEST(Iterator, iteratorMethods) {
    List<int> list;
    int value1 = 78, value2 = 79, value3 = 77;
    list.add(value1);
    list.add(value2);
    list.add(value3);
    Iterator<int> it(list);
    size_t index = 0;
    for (it.start(); !it.isEnd() && index < list.getLength() - 1; it.next(), index++)
        ASSERT_EQ(list.getElem(index), it.value());
}

int startTest()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

#endif //SECOND_LAB_TESTING_H
