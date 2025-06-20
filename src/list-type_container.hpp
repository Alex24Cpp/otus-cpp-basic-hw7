#pragma once
#include <cstddef>

namespace ListTypeContainer {
template <typename T>
struct MyNode {
	MyNode() = default;
	MyNode(T v) : m_data{v} {
	}
	MyNode *m_prev{nullptr};
	MyNode *m_next{nullptr};
	T m_data{0};
};

template <typename T>
struct iterator {
	MyNode<T> *ref{nullptr};
	T operator*() {
		return ref->m_data;
	}
	iterator operator++() {
		ref = ref->m_next;
		return *this;
	}
	bool operator==(iterator itr) {
		return ref == itr.ref;
	}
	bool operator!=(iterator itr) {
		return ref != itr.ref;
	}
};

template <typename T>
class MyListTypeContainer {
public:
	MyListTypeContainer() = default;
	MyListTypeContainer(const MyListTypeContainer &mlc);
	MyListTypeContainer(MyListTypeContainer &&mlc);
	~MyListTypeContainer();
	MyListTypeContainer &operator=(const MyListTypeContainer &mlc);
	MyListTypeContainer &operator=(MyListTypeContainer &&mlc);
	void push_back(T value);
	void push_front(T value);
	void pop_back();
	void pop_front();
	int insert(T value, size_t index);
	int erase(size_t first, size_t last);
	int erase(size_t index);
	size_t size() const;
	T operator[](size_t index) const;
	void clear();
	bool empty() const;
	iterator<T> begin();
	iterator<T> end();
private:
	MyNode<T> *m_head{nullptr};
	MyNode<T> *m_tail{nullptr};
	size_t m_size{0};
	iterator<T> m_iteratot;
	void free_up_memory();
};

template <typename T>
MyListTypeContainer<T>::MyListTypeContainer(const MyListTypeContainer &mlc) {
	if (mlc.m_size != 0) {
		MyNode<T> *prev_new_node = nullptr;
		for (MyNode<T> *temp = mlc.m_head; temp != nullptr;
			 temp = temp->m_next) {
			MyNode<T> *new_node = new MyNode<T>(temp->m_data);
			if (temp->m_prev == nullptr) {
				m_head = new_node;
			}
			if (temp->m_next == nullptr) {
				m_tail = new_node;
			}
			new_node->m_prev = prev_new_node;
			if (prev_new_node != nullptr) {
				prev_new_node->m_next = new_node;
			}
			prev_new_node = new_node;
			m_size++;
		}
	}
}

template <typename T>
MyListTypeContainer<T>::MyListTypeContainer(MyListTypeContainer &&mlc) {
	m_head = mlc.m_head;
	m_tail = mlc.m_tail;
	m_size = mlc.m_size;
	mlc.m_head = nullptr;
	mlc.m_tail = nullptr;
	mlc.m_size = 0;
}

template <typename T>
MyListTypeContainer<T>::~MyListTypeContainer() {
	free_up_memory();
}

template <typename T>
MyListTypeContainer<T> &MyListTypeContainer<T>::operator=(
	const MyListTypeContainer &mlc) {
	free_up_memory();
	m_size = 0;
	if (mlc.m_size != 0) {
		MyNode<T> *prev_new_node = nullptr;
		for (MyNode<T> *temp = mlc.m_head; temp != nullptr;
			 temp = temp->m_next) {
			MyNode<T> *new_node = new MyNode<T>(temp->m_data);
			if (temp->m_prev == nullptr) {
				m_head = new_node;
			}
			if (temp->m_next == nullptr) {
				m_tail = new_node;
			}
			new_node->m_prev = prev_new_node;
			if (prev_new_node != nullptr) {
				prev_new_node->m_next = new_node;
			}
			prev_new_node = new_node;
			m_size++;
		}
	} else {
		m_head = nullptr;
		m_tail = nullptr;
	}
	return *this;
}

template <typename T>
MyListTypeContainer<T> &MyListTypeContainer<T>::operator=(
	MyListTypeContainer &&mlc) {
	free_up_memory();
	m_head = mlc.m_head;
	m_tail = mlc.m_tail;
	m_size = mlc.m_size;
	mlc.m_head = nullptr;
	mlc.m_tail = nullptr;
	mlc.m_size = 0;
	return *this;
}

template <typename T>
void MyListTypeContainer<T>::push_back(T value) {
	MyNode<T> *new_node = new MyNode<T>(value);
	if (m_head == nullptr) {
		m_head = new_node;
	}
	if (m_tail != nullptr) {
		new_node->m_prev = m_tail;
		m_tail->m_next = new_node;
	}
	m_tail = new_node;
	++m_size;
}

template <typename T>
void MyListTypeContainer<T>::push_front(T value) {
	MyNode<T> *new_node = new MyNode<T>(value);
	if (m_tail == nullptr) {
		m_tail = new_node;
	} else {
		new_node->m_next = m_head;
		m_head->m_prev = new_node;
	}
	m_head = new_node;
	++m_size;
}

template <typename T>
void MyListTypeContainer<T>::pop_back() {
	if (m_size != 0) {
		MyNode<T> *temp_node = m_tail;
		m_tail = m_tail->m_prev;
		if (m_tail != nullptr) {
			m_tail->m_next = nullptr;
		} else {
			m_head = nullptr;
		}
		delete temp_node;
		--m_size;
	}
}

template <typename T>
void MyListTypeContainer<T>::pop_front() {
	if (m_size != 0) {
		MyNode<T> *temp_node = m_head;
		m_head = m_head->m_next;
		if (m_head != nullptr) {
			m_head->m_prev = nullptr;
		} else {
			m_tail = nullptr;
		}
		delete temp_node;
		--m_size;
	}
}

template <typename T>
int MyListTypeContainer<T>::insert(T value, size_t index) {
	if (index >= m_size) {
		return -1;
	}
	MyNode<T> *new_node = new MyNode<T>(value);
	MyNode<T> *node = m_head;
	for (size_t i = 0; i < index; ++i) {
		node = node->m_next;
	}
	if (node->m_prev != nullptr) {
		new_node->m_prev = node->m_prev;
		node->m_prev->m_next = new_node;
	} else {
		m_head = new_node;
	}
	node->m_prev = new_node;
	new_node->m_next = node;
	++m_size;
	return 0;
}

template <typename T>
int MyListTypeContainer<T>::erase(size_t first, size_t last) {
	if (first >= m_size || last >= m_size) {
		return -1;
	}
	if (first == 0 && last == m_size - 1) {
		free_up_memory();
		m_head = nullptr;
		m_tail = nullptr;
	} else {
		MyNode<T> *firstNode = m_head;
		for (size_t i = 0; i < first; ++i) {
			firstNode = firstNode->m_next;
		}
		MyNode<T> *lastNode = firstNode;
		for (size_t i = 0; i < last - first; ++i) {
			lastNode = lastNode->m_next;
		}
		if (firstNode->m_prev != nullptr) {
			firstNode->m_prev->m_next = lastNode->m_next;
		} else {
			lastNode->m_next->m_prev = nullptr;
			m_head = lastNode->m_next;
		}
		if (lastNode->m_next != nullptr) {
			lastNode->m_next->m_prev = firstNode->m_prev;
		} else {
			firstNode->m_prev->m_next = nullptr;
			m_tail = firstNode->m_prev;
		}
		if (first != last) {
			firstNode->m_prev = nullptr;
			for (MyNode<T> *temp = lastNode->m_prev; temp != nullptr;
				 temp = temp->m_prev) {
				delete temp->m_next;
			}
		}
		delete firstNode;
	}
	m_size -= (last - first) + 1;
	return 0;
}

template <typename T>
int MyListTypeContainer<T>::erase(size_t index) {
	return erase(index, index);
}

template <typename T>
size_t MyListTypeContainer<T>::size() const {
	return m_size;
}

template <typename T>
bool MyListTypeContainer<T>::empty() const {
	return m_size == 0;
}

template <typename T>
T MyListTypeContainer<T>::operator[](size_t index) const {
	MyNode<T> *node = m_head;
	if (index != 0) {
		for (size_t i = 0; i < index; ++i) {
			node = node->m_next;
		}
	}
	return node->m_data;
}

template <typename T>
void MyListTypeContainer<T>::clear() {
	free_up_memory();
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}

template <typename T>
iterator<T> MyListTypeContainer<T>::begin() {
	m_iteratot.ref = m_head;
	return m_iteratot;
}

template <typename T>
iterator<T> MyListTypeContainer<T>::end() {
	m_iteratot.ref = nullptr;
	return m_iteratot;
}

template <typename T>
void MyListTypeContainer<T>::free_up_memory() {
	if (m_head != nullptr && m_tail != nullptr) {
		for (MyNode<T> *temp = m_tail->m_prev; temp != nullptr;
			 temp = temp->m_prev) {
			delete temp->m_next;
		}
		delete m_head;
	}
}
}  // namespace ListTypeContainer
