#include <gtest/gtest.h>

#include "list-type_container.hpp"

TEST(List, Creation) {  // создание контейнера DISABLED_
	// Arrange
	ListTypeContainer::MyListTypeContainer<int>* plist{nullptr};

	// Act (Creation for this test)
	plist = new ListTypeContainer::MyListTypeContainer<int>();

	// Assert
	ASSERT_NE(plist, nullptr);
	ASSERT_TRUE(plist->empty());
}

TEST(List, Empty) {  // контейнер пуст
	// Arrange
	ListTypeContainer::MyListTypeContainer<int> list;

	// Act (empty for this test)

	// Assert
	ASSERT_EQ(list.size(), static_cast<size_t>(0));
	ASSERT_TRUE(list.empty());
}

TEST(List, PushBack) {  // вставка элементов в конец
	// Arrange
	const size_t count = 10;
	ListTypeContainer::MyListTypeContainer<int> list;

	// Act
	for (size_t i = 0; i < count; ++i) {
		list.push_back(i);
	}

	// Assert
	ASSERT_EQ(list.size(), count);
	ASSERT_FALSE(list.empty());
}

TEST(List, PushFront) {  // вставка элементов в начало
	// Arrange
	const size_t count = 10;
	ListTypeContainer::MyListTypeContainer<int> list;

	// Act
	for (size_t i = 0; i < count; ++i) {
		list.push_front(i);
	}

	// Assert
	ASSERT_EQ(list.size(), count);
	ASSERT_FALSE(list.empty());
}

TEST(List, Insert) {  // вставка элементов в середину
	// Arrange
	const size_t expectedSize = 6;
	const size_t count = 4;
	bool result{false};
	int testArray[count] = {0, 1, 4, 5};
	int expectedArray[expectedSize] = {0, 1, 2, 3, 4, 5};
	ListTypeContainer::MyListTypeContainer<int> list;
	for (size_t i = 0; i < count; ++i) {
		list.push_back(testArray[i]);
	}

	// Act
	list.insert(2, 2);
	list.insert(3, 3);
	for (size_t i = 0; i < list.size(); ++i) {
		result += !(list[i] == expectedArray[i]);
	}

	// Assert
	ASSERT_TRUE(!result);
	ASSERT_EQ(list.size(), expectedSize);
}

TEST(List, PopBack) {    // удаление элементов из конца
    // Arrange 
    const size_t count = 10;
    ListTypeContainer::MyListTypeContainer<int> list;

    for (size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    // Act
    for (size_t i = 0; i < count; ++i) {
        list.pop_back();
    }

    // Assert
    ASSERT_EQ(list.size(), static_cast<size_t>(0));
    ASSERT_TRUE(list.empty());
}

TEST(List, PopFront) { // удаление элементов из начала
    // Arrange
    const size_t count = 10;
    ListTypeContainer::MyListTypeContainer<size_t> list;

    for (size_t i = 0; i < count; ++i) {
        list.push_front(i); // push_back
    }

    // Act
    for (size_t i = 0; i < count; ++i) {
        list.pop_front();   // pop_back
    }

    // Assert
    ASSERT_EQ(list.size(), static_cast<size_t>(0));
    ASSERT_TRUE(list.empty());
}

TEST(List, Erase) {  // удаление элементов из середины
	// Arrange
	const size_t expectedSize = 4;
	const size_t count = 10;
	bool result{false};
	int testArray[count] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int expectedArray[expectedSize] = {0, 1, 8, 9};
	ListTypeContainer::MyListTypeContainer<int> list;
	for (size_t i = 0; i < count; ++i) {
		list.push_back(testArray[i]);
	}

	// Act
	list.erase(2, 7);
	for (size_t i = 0; i < list.size(); ++i) {
		result += !(list[i] == expectedArray[i]);
	}

	// Assert
	ASSERT_TRUE(!result);
	ASSERT_EQ(list.size(), expectedSize);
}

// получение элементов из контейнера

TEST(List, Get) {  // получение элементов из контейнера
	// Arrange
	const size_t expectedSize = 10;
	const size_t count = 10;
	int testArray[count] = {0, 0, 0, 0, 0, 10, 0, 0, 0, 0};
    size_t testIndex{5};
	int expectedValue{10};
	ListTypeContainer::MyListTypeContainer<int> list;
	for (size_t i = 0; i < count; ++i) {
		list.push_back(testArray[i]);
	}

	// Act
	int getValue = list[testIndex];

    // Assert
	ASSERT_EQ(getValue, expectedValue);
	ASSERT_EQ(list.size(), expectedSize);
}

TEST(List, GetSize) {  // получение размера контейнера (фактическое количество элементов)
	// Arrange
	const size_t expectedSize = 10;
	const size_t count = 10;
	int testArray[count] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t getSize{0};
	ListTypeContainer::MyListTypeContainer<int> list;
	for (size_t i = 0; i < count; ++i) {
		list.push_back(testArray[i]);
	}

	// Act
	for (auto i = list.begin(); i != list.end(); ++i) {
        ++getSize;
    }

    // Assert
	ASSERT_EQ(getSize, expectedSize);
	ASSERT_EQ(list.size(), expectedSize);
}



int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}