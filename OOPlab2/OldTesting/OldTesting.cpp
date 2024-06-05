#include "OldTesting.h"

void startTesting() {
    List<int> testList = {52, 78, 1337, 1488, 777};
    std::cout << "Start List: " << testList << "\n" << "\n";
    try {
        additionTests(testList);
        deletionTests(testList);
        getsTests(testList);
        extraTests(testList);
        iteratorTests(testList);
        std::cout << "\n";
    } catch (std::exception& exception) {
        std::cerr << "Error: " << exception.what() << "\n";
    }
}

template <typename T>
void additionTests(List<T> &lst) {
    std::cout << "Public methods for List:" << "\n";
    int elem = 34;
    std::cout << "\n" << "Test 1: void add(const T& elem); " << "\n" << "elem = " << elem << "\n";
    std::cout << "list = " << lst << "\n";
    lst.add(elem);
    std::cout << lst << "\n" << "\n";

    std::cout << "Test 2: void addRange(const list<T>& lst); " << "\n";
    List<int> lst2 = {6, 7, 8};
    std::cout << "list = " << lst << "\n";
    std::cout << "lst = " << lst2 << "\n";
    lst.addRange(lst2);
    std::cout << lst << "\n" << "\n";

    std::cout << "Test 3: void addRange(T* arr, int size); " << "\n";
    int arr[] = {63, 65};
    int size = 2;
    std::cout << "list = " << lst << "\n";
    std::cout << "arr = ";
    for (int i = 0; i <= size -1; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    std::cout << "size = " << size << "\n";
    lst.addRange(arr, size);
    std::cout << lst << "\n" << "\n";
}

template <typename T>
void deletionTests(List<T> &lst) {
    std::cout << "Test 4: void removeElem(int index); " << "\n";
    std::cout << "list = " << lst << "\n";
    int index = 0;
    std::cout << "index = " << index << "\n";
    lst.removeElem(index);
    std::cout << lst << "\n" << "\n";
}

template <typename T>
void getsTests(List<T> &lst) {
    std::cout << "Test 5: int getLength() const; " << "\n";
    std::cout << "list = " << lst << "\n";
    std::cout << lst.getLength() << "\n" << "\n";

    std::cout << "Test 6: T& getElem(int index); " << "\n";
    std::cout << "list = " << lst << "\n";
    int index = 6;
    std::cout << "index = " << index << "\n";
    std::cout << lst.getElem(index) << "\n" << "\n";

    std::cout << "Test 7: T& operator[](int index); " << "\n";
    std::cout << "list = " << lst << "\n";
    std::cout << "index = " << index << "\n";
    std::cout << lst[index] << "\n" << "\n";

    std::cout << "Test 8: int getIndex(T &elem) const; " << "\n";
    std::cout << "list = " << lst << "\n";
    int elem = 12;
    std::cout << "elem = " << elem << "\n";
    std::cout << lst.getIndex(elem) << "\n" << "\n";

    std::cout << "Test 9: void setElem(int index,const T& elem); " << "\n";
    std::cout << "list = " << lst << "\n";
    index = 4;
    std::cout << "index = " << index << "\n";
    elem = 52;
    std::cout << "elem = " << elem << "\n";
    lst.setElem(4, elem);
    std::cout << lst << "\n" << "\n";
}

template <typename T>
void extraTests(List<T> &lst) {
    std::cout << "Test 10: T* toArray(); " << "\n";
    std::cout << "list = " << lst << "\n";
    int* arr = lst.toArray();
    for (int i = 0;i < lst.getLength(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n" << "\n";
    delete[] arr;

    std::cout << "Test 11: list<T> combine(const list<T>& lst); " << "\n";
    std::cout << "list = " << lst << "\n";
    List<int> lst3 = {54, 4, 8};
    std::cout << "lst = " << lst3 << "\n";
    List<int> lst4 = lst.combine(lst3);
    std::cout << lst4 << "\n" << "\n";

    std::cout << "Test 12: void sort(int (*comp)(const T& r1, constT& r2)); " << "\n";
    std::cout << "list = " << lst << "\n";
    lst4.sort(List<int>::compare);
    std::cout << lst4 << "\n" << "\n";

}

template <typename T>
void iteratorTests(List<T> &lst) {
    std::cout << "Public methods for Iterator:" << "\n";
    std::cout << "Test 1: start(); isEnd(); next(); value() " << "\n";
    std::cout << "list = " << lst << "\n";
    Iterator<int> it(lst);
    for (it.start(); !it.isEnd(); it.next())
        std::cout << it.value() << " ";
    std::cout << "\n";
    std::cout << "WWWWWW  WWWWW";
}
