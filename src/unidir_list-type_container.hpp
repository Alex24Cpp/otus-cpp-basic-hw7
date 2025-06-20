#pragma once
#include <cstddef>

namespace UniDirListTypeContainer {
template <typename T>
struct MyUniDirNode {
	MyUniDirNode() = default;
	MyUniDirNode(T v) : m_data{v} {
	}
	MyUniDirNode *m_next{nullptr};
	T m_data{0};
};

template <typename T>
struct iterator {
	MyUniDirNode<T> *ref{nullptr};
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
class MyUniDirListTypeContainer {
public:
	MyUniDirListTypeContainer() = default;
	MyUniDirListTypeContainer(const MyUniDirListTypeContainer &mlc);
	MyUniDirListTypeContainer(MyUniDirListTypeContainer &&mlc);
	~MyUniDirListTypeContainer();
	MyUniDirListTypeContainer &operator=(const MyUniDirListTypeContainer &mlc);
	MyUniDirListTypeContainer &operator=(MyUniDirListTypeContainer &&mlc);
	void push_back(T value);
	void push_front(T value);
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
	MyUniDirNode<T> *m_head{nullptr};
	MyUniDirNode<T> *m_tail{nullptr};
	size_t m_size{0};
	iterator<T> m_iteratot;
	void free_up_memory();
};

template <typename T>
MyUniDirListTypeContainer<T>::MyUniDirListTypeContainer(
	const MyUniDirListTypeContainer &mlc) {
	if (mlc.m_size != 0) {
		MyUniDirNode<T> *prev_new_node = nullptr;
		for (MyUniDirNode<T> *temp = mlc.m_head; temp != nullptr;
			 temp = temp->m_next) {
			MyUniDirNode<T> *new_node = new MyUniDirNode<T>(temp->m_data);
			if (temp == mlc.m_head) {
				m_head = new_node;
			}
			if (temp->m_next == nullptr) {
				m_tail = new_node;
			}
			if (prev_new_node != nullptr) {
				prev_new_node->m_next = new_node;
			}
			prev_new_node = new_node;
			m_size++;
		}
	}
}

template <typename T>
MyUniDirListTypeContainer<T>::MyUniDirListTypeContainer(
	MyUniDirListTypeContainer &&mlc) {
	m_head = mlc.m_head;
	m_tail = mlc.m_tail;
	m_size = mlc.m_size;
	mlc.m_head = nullptr;
	mlc.m_tail = nullptr;
	mlc.m_size = 0;
}

template <typename T>
MyUniDirListTypeContainer<T>::~MyUniDirListTypeContainer() {
	free_up_memory();
}

template <typename T>
MyUniDirListTypeContainer<T> &MyUniDirListTypeContainer<T>::operator=(
	const MyUniDirListTypeContainer &mlc) {
	free_up_memory();
	m_size = 0;
	if (mlc.m_size != 0) {
		MyUniDirNode<T> *prev_new_node = nullptr;
		for (MyUniDirNode<T> *temp = mlc.m_head; temp != nullptr;
			 temp = temp->m_next) {
			MyUniDirNode<T> *new_node = new MyUniDirNode<T>(temp->m_data);
			if (temp == mlc.m_head) {
				m_head = new_node;
			}
			if (temp->m_next == nullptr) {
				m_tail = new_node;
			}
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
MyUniDirListTypeContainer<T> &MyUniDirListTypeContainer<T>::operator=(
	MyUniDirListTypeContainer &&mlc) {
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
void MyUniDirListTypeContainer<T>::push_back(T value) {
	MyUniDirNode<T> *new_node = new MyUniDirNode<T>(value);
	if (m_head == nullptr) {
		m_head = new_node;
	}
	if (m_tail != nullptr) {
		m_tail->m_next = new_node;
	}
	m_tail = new_node;
	++m_size;
}

template <typename T>
void MyUniDirListTypeContainer<T>::push_front(T value) {
	MyUniDirNode<T> *new_node = new MyUniDirNode<T>(value);
	if (m_tail == nullptr) {
		m_tail = new_node;
	} else {
		new_node->m_next = m_head;
	}
	m_head = new_node;
	++m_size;
}

template <typename T>
int MyUniDirListTypeContainer<T>::insert(T value, size_t index) {
	if (index >= m_size) {
		return -1;
	}
	MyUniDirNode<T> *new_node = new MyUniDirNode<T>(value);
	MyUniDirNode<T> *node = m_head;
	if (index == 0) {
		m_head = new_node;
		new_node->m_next = node;
	} else {
		for (size_t i = 0; i < index - 1 || i == 1; ++i) {
			node = node->m_next;
		}
		new_node->m_next = node->m_next;
		node->m_next = new_node;
	}

	++m_size;
	return 0;
}

template <typename T>
int MyUniDirListTypeContainer<T>::erase(size_t index) {
	if (index >= m_size) {
		return -1;
	} else {
		MyUniDirNode<T> *nodeDel{nullptr};
		MyUniDirNode<T> *preNode{nullptr};
		nodeDel = m_head;
		if (index == 0) {
			m_head = m_head->m_next;
		} else {
			for (size_t i = 0; i <= index - 1; ++i) {
				preNode = nodeDel;
				nodeDel = nodeDel->m_next;
			}
			preNode->m_next = nodeDel->m_next;
		}
		delete nodeDel;
	}
	--m_size;
	return 0;
}

template <typename T>
int MyUniDirListTypeContainer<T>::erase(size_t first, size_t last) {
	if (first >= m_size || last >= m_size || first > last) {
		return -1;
	} else {
		MyUniDirNode<T> *nodeDelStart{nullptr};
		MyUniDirNode<T> *nodeDelEnd = m_head;
		MyUniDirNode<T> *preNode = m_head;
		MyUniDirNode<T> *afterNode{nullptr};
		if (first == 0) {
			if (m_head == m_tail) {
				delete m_head;
				m_head = m_tail = {nullptr};
				return 0;
			}
			nodeDelStart = m_head;
		} else {
			for (size_t i = 0; i < first - 1 || i == 1; ++i) {
				preNode = preNode->m_next;
			}
			nodeDelStart = preNode->m_next;
		}

		if (last == m_size - 1) {
			for (size_t i = 0; i < last || i == 1; ++i) {
				nodeDelEnd = nodeDelEnd->m_next;
			}
			nodeDelEnd = m_tail;
			afterNode = nullptr;
			m_tail = preNode;
		} else {
			for (size_t i = 0; i < last || i == 1; ++i) {
				nodeDelEnd = nodeDelEnd->m_next;
			}
			afterNode = nodeDelEnd->m_next;
		}
		if (first == 0) {
			m_head = afterNode;
		} else {
			preNode->m_next = afterNode;
		}
		for (size_t i = 0; i < last - first; ++i) {
			nodeDelEnd = nodeDelStart->m_next;
			delete nodeDelStart;
			nodeDelStart = nodeDelEnd;
		}
		m_size -= last - first + 1;
	}
	return 0;
}

template <typename T>
size_t MyUniDirListTypeContainer<T>::size() const {
	return m_size;
}

template <typename T>
T MyUniDirListTypeContainer<T>::operator[](size_t index) const {
	MyUniDirNode<T> *node = m_head;
	if (index != 0) {
		for (size_t i = 0; i < index; ++i) {
			node = node->m_next;
		}
	}
	return node->m_data;
}

template <typename T>
void MyUniDirListTypeContainer<T>::clear() {
	free_up_memory();
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}

template <typename T>
bool MyUniDirListTypeContainer<T>::empty() const {
	return m_size == 0;
}

template <typename T>
iterator<T> MyUniDirListTypeContainer<T>::begin() {
	m_iteratot.ref = m_head;
	return m_iteratot;
}

template <typename T>
iterator<T> MyUniDirListTypeContainer<T>::end() {
	m_iteratot.ref = nullptr;
	return m_iteratot;
}

template <typename T>
void MyUniDirListTypeContainer<T>::free_up_memory() {
	if (m_head != nullptr && m_tail != nullptr) {
		for (MyUniDirNode<T> *temp; m_head != nullptr; m_head = temp) {
			temp = m_head->m_next;
			delete m_head;
		}
	}
}
}  // namespace UniDirListTypeContainer