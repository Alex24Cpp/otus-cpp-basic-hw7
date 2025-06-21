#include <gtest/gtest.h>

#include "serial_container.hpp"

TEST(Serial, Creation) {  // создание контейнера DISABLED_
	// Arrange
	SerialContainer::MySerialContainer<int>* pSer{nullptr};

	// Act (Creation for this test)
	pSer = new SerialContainer::MySerialContainer<int>();

	// Assert
	ASSERT_NE(pSer, nullptr);
	ASSERT_TRUE(pSer->empty());
}

TEST(Serial, Empty) {  // контейнер пуст
	// Arrange
	SerialContainer::MySerialContainer<int> serial;

	// Act (empty for this test)

	// Assert
	ASSERT_EQ(serial.size(), static_cast<size_t>(0));
	ASSERT_TRUE(serial.empty());
}

TEST(Serial, PushBack) {  // вставка элементов в конец
	// Arrange
	const size_t count = 10;
	SerialContainer::MySerialContainer<int> serial;

	// Act
	for (size_t i = 0; i < count; ++i) {
		serial.push_back(i);
	}

	// Assert
	ASSERT_EQ(serial.size(), count);
	ASSERT_FALSE(serial.empty());
}

TEST(Serial, PushFront) {  // вставка элементов в начало
	// Arrange
	const size_t count = 10;
	SerialContainer::MySerialContainer<int> serial;

	// Act
	for (size_t i = 0; i < count; ++i) {
		serial.push_front(i);
	}

	// Assert
	ASSERT_EQ(serial.size(), count);
	ASSERT_FALSE(serial.empty());
}

TEST(Serial, Insert) {  // вставка элементов в середину
	// Arrange
	const size_t expectedSize = 6;
	const size_t count = 4;
	bool result{false};
	int testArray[count] = {0, 1, 4, 5};
	int expectedArray[expectedSize] = {0, 1, 2, 3, 4, 5};
	SerialContainer::MySerialContainer<int> serial;
	for (size_t i = 0; i < count; ++i) {
		serial.push_back(testArray[i]);
	}

	// Act
	serial.insert(2, 2);
	serial.insert(3, 3);
	for (size_t i = 0; i < serial.size(); ++i) {
		result += !(serial[i] == expectedArray[i]);
	}

	// Assert
	ASSERT_TRUE(!result);
	ASSERT_EQ(serial.size(), expectedSize);
}

TEST(Serial, PopBack) {    // удаление элементов из конца
    // Arrange 
    const size_t count = 10;
    SerialContainer::MySerialContainer<int> serial;

    for (size_t i = 0; i < count; ++i) {
        serial.push_back(i);
    }

    // Act
    for (size_t i = 0; i < count; ++i) {
        serial.pop_back();
    }

    // Assert
    ASSERT_EQ(serial.size(), static_cast<size_t>(0));
    ASSERT_TRUE(serial.empty());
}

TEST(Serial, PopFront) { // удаление элементов из начала
    // Arrange
    const size_t count = 10;
    SerialContainer::MySerialContainer<size_t> serial;

    for (size_t i = 0; i < count; ++i) {
        serial.push_front(i); // push_back
    }

    // Act
    for (size_t i = 0; i < count; ++i) {
        serial.pop_front();   // pop_back
    }

    // Assert
    ASSERT_EQ(serial.size(), static_cast<size_t>(0));
    ASSERT_TRUE(serial.empty());
}

TEST(Serial, Erase) {  // удаление элементов из середины
	// Arrange
	const size_t expectedSize = 4;
	const size_t count = 10;
	bool result{false};
	int testArray[count] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int expectedArray[expectedSize] = {0, 1, 8, 9};
	SerialContainer::MySerialContainer<int> serial;
	for (size_t i = 0; i < count; ++i) {
		serial.push_back(testArray[i]);
	}

	// Act
	serial.erase(2, 7);
	for (size_t i = 0; i < serial.size(); ++i) {
		result += !(serial[i] == expectedArray[i]);
	}

	// Assert
	ASSERT_TRUE(!result);
	ASSERT_EQ(serial.size(), expectedSize);
}

TEST(Serial, Get) {  // получение элементов из контейнера
	// Arrange
	const size_t expectedSize = 10;
	const size_t count = 10;
	int testArray[count] = {0, 0, 0, 0, 0, 10, 0, 0, 0, 0};
    size_t testIndex{5};
	int expectedValue{10};
	SerialContainer::MySerialContainer<int> serial;
	for (size_t i = 0; i < count; ++i) {
		serial.push_back(testArray[i]);
	}

	// Act
	int getValue = serial[testIndex];

    // Assert
	ASSERT_EQ(getValue, expectedValue);
	ASSERT_EQ(serial.size(), expectedSize);
}

TEST(Serial, GetSize) {  // получение размера контейнера (фактическое количество элементов)
	// Arrange
	const size_t expectedSize = 10;
	const size_t count = 10;
	int testArray[count] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t getSize{0};
	SerialContainer::MySerialContainer<int> serial;
	for (size_t i = 0; i < count; ++i) {
		serial.push_back(testArray[i]);
	}

	// Act
	for (auto i = serial.begin(); i != serial.end(); ++i) {
        ++getSize;
    }

    // Assert
	ASSERT_EQ(getSize, expectedSize);
	ASSERT_EQ(serial.size(), expectedSize);
}

TEST(Serial, Copy) {  // на копирование контейнера
	// Arrange
	const size_t count = 10;
	bool result{false};
	int testArray[count] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	SerialContainer::MySerialContainer<int> serial;
	for (size_t i = 0; i < count; ++i) {
		serial.push_back(testArray[i]);
	}

	// Act
	SerialContainer::MySerialContainer<int> serialCopy(serial);
	for (size_t i = 0; i < serial.size(); ++i) {
		result += !(serial[i] == serialCopy[i]);
	}

	// Assert
	ASSERT_TRUE(!result);
	ASSERT_EQ(serial.size(), serialCopy.size());
}

TEST(Serial, Move) {  // на перемещение контейнера (вызов перемещающего оператора присваивания)
	// Arrange
	const size_t count = 10;
	bool result{false};
	int testArray[count] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	SerialContainer::MySerialContainer<int> serial;
	for (size_t i = 0; i < count; ++i) {
		serial.push_back(testArray[i]);
	}

	// Act
	SerialContainer::MySerialContainer<int> serialMove;
	serialMove = std::move(serial);
	for (size_t i = 0; i < serialMove.size(); ++i) {
		result += !(testArray[i] == serialMove[i]);
	}

	// Assert
	ASSERT_TRUE(!result);
	ASSERT_EQ(serial.size(), static_cast<size_t>(0));
}
