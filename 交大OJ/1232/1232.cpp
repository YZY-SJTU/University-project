#include <iostream>
#include <cstring>
using namespace std;

template <class T>
class doubleVector {
	T** vector_data = nullptr;
	int size = 0;
	int capacity = 0;

public:
	doubleVector() = default;
	doubleVector(int _size) :size(_size) {
		capacity = _size * 2;
		vector_data = new T * [capacity] {nullptr};
	}

	~doubleVector() {
		for (int i = 0; i < size; ++i)
			delete vector_data[i];
		delete[] vector_data;
	}

	void push_back(const T & val) {
		if (size < capacity)
			vector_data[size++] = new T(val);
		else {
			T** temp_data = new T * [(capacity + 1) * 2]{ nullptr };
			for (int i = 0; i < size; ++i)
				temp_data[i] = vector_data[i];
			temp_data[size++] = new T(val);
			capacity = (capacity + 1) * 2;
			delete[] vector_data;
			vector_data = temp_data;
		}
	}

	void pop_back() {
		delete vector_data[--size];
		vector_data[size] = nullptr;
	}

	void clear() {
		for (int i = 0; i < size; ++i) {
			delete vector_data[i];
			vector_data[i] = nullptr;
		}
		size = 0;
	}

	T & operator[](const int& pos) {
		return *vector_data[pos];
	}

	size_t get_size() {
		return size;
	}
};

template <class T>
class Queue {
	class node {
	public:
		T data;
		node* next = nullptr;
	};
	node* head = nullptr,
		* rear = nullptr;
	size_t _size = 0;

public:
	Queue() {
		head = new node;
		rear = head;
	}

	bool empty() {
		return head->next == nullptr;
	}

	void push(const T& val) {
		rear->next = new node;
		rear = rear->next;
		rear->data = val;
		++_size;
	}

	void pop() {
		if (head->next == nullptr)
			return;
		auto temp = head->next;
		delete head;
		head = temp;
		--_size;
	}

	T& front() {
		return head->next->data;
	}

	T& back() {
		return rear->data;
	}

};

template <class T>
class mSet {

	enum colorT { RED, BLACK };

	class node {
	public:
		T* data;
		node* lchild = nullptr;
		node* rchild = nullptr;
		node* parent = nullptr;

		colorT color = RED;
	};

	node* root = nullptr;

	void clear(node* p) {
		if (p != nullptr) {
			clear(p->lchild);
			clear(p->rchild);
			delete p->data;
			delete p;
		}
		p = nullptr;
	}

	void LL(node* gp) {
		auto p = gp->lchild, t = p->lchild;
		if (gp->parent != nullptr) {
			if (gp->parent->lchild == gp)
				gp->parent->lchild = p;
			else
				gp->parent->rchild = p;
		}
		else
			root = p;
		p->parent = gp->parent;
		gp->lchild = p->rchild;
		if (p->rchild != nullptr)
			p->rchild->parent = gp;
		p->rchild = gp;
		gp->parent = p;
		auto tmp = gp->color;
		gp->color = p->color;
		p->color = tmp;
	}

	void RR(node * gp) {
		auto p = gp->rchild, t = p->rchild;
		if (gp->parent != nullptr) {
			if (gp->parent->lchild == gp)
				gp->parent->lchild = p;
			else
				gp->parent->rchild = p;
		}
		else
			root = p;
		p->parent = gp->parent;
		gp->rchild = p->lchild;
		if (p->lchild != nullptr)
			p->lchild->parent = gp;
		p->lchild = gp;
		gp->parent = p;
		auto tmp = gp->color;
		gp->color = p->color;
		p->color = tmp;
	}

	void LR(node * gp) {
		RR(gp->lchild);
		LL(gp);
	}

	void RL(node * gp) {
		LL(gp->rchild);
		RR(gp);
	}

	void insertAdjust(node * &gp, node * &p, node * t) {
		if (p->color == BLACK) return;
		if (p == root) {
			p->color = BLACK;
			return;
		}
		if (gp->lchild == p) {
			if (p->lchild == t) {
				LL(gp);
				auto tmp = gp;
				gp = p;
				p = tmp;

			}
			else {
				LR(gp);
				auto tmp = gp;
				gp = t;
				t = tmp;
			}
		}
		else if (p->rchild == t) {
			RR(gp);
			auto tmp = gp;
			gp = p;
			p = tmp;
		}
		else {
			RL(gp);
			auto tmp = gp;
			gp = t;
			t = tmp;
		}
	}

	void removeAdjust(node * &p, node * &c, node * &t, const T & del) {
		if (c->color == RED) return;
		if (c == root)
			if (c->lchild && c->rchild
				&& c->rchild->color == c->lchild->color) {
				c->color = RED;
				c->lchild->color = c->rchild->color = BLACK;
				return;
			}
		if ((c->lchild && c->lchild->color || c->lchild == nullptr) &&
			(c->rchild && c->rchild->color || c->rchild == nullptr))
			if ((t->lchild && t->lchild->color || t->lchild == nullptr) &&
				(t->rchild && t->rchild->color || t->rchild == nullptr)) {
				p->color = BLACK;
				t->color = c->color = RED;
			}
			else {
				if (p->lchild == t)
					if (t->lchild != nullptr && t->lchild->color == RED) {
						t->lchild->color = BLACK;
						LL(p);
						t = p;
					}
					else {
						auto tmp = t->rchild;
						LR(p);
						p = tmp;
						p = p->rchild;
						p->color = BLACK;
						t->color = BLACK;
					}
				else if (t->rchild && t->rchild->color == RED) {
					t->rchild->color = BLACK;
					RR(p);
					t = p;
				}
				else {
					auto tmp = t->lchild;
					RL(p);
					p = tmp;
					p = p->lchild;
					p->color = BLACK;
					t->color = BLACK;
				}
				c->color = RED;
			}
		else {
			if (*c->data == del) {
				if (c->lchild && c->rchild) {
					if (c->rchild->color == BLACK) {
						LL(c);
					}
					return;
				}
				if (c->lchild) {
					LL(c);
					p = c->parent;
				}
				else {
					RR(c);
					p = c->parent;
				}
			}
			else {
				p = c;
				c = del < *p->data ? p->lchild : p->rchild;
				t = c == p->lchild ? p->rchild : p->lchild;
				if (c->color == BLACK) {
					if (t == p->rchild)
						RR(p);
					else
						LL(p);
					t = p;
					t = c == p->lchild ? p->rchild : p->lchild;
					removeAdjust(p, c, t, del);
				}
			}
		}
	}


public:
	void clear() {
		clear(root);
	}

	void insert(const T & x) {
		node* t, * parent, * grandp;

		if (root == nullptr) {
			root = new node;
			root->color = BLACK;
			root->data = new T(x);
			return;
		}

		parent = grandp = t = root;
		while (true) {
			if (t != nullptr) {
				if (t->lchild && t->lchild->color == RED &&
					t->rchild && t->rchild->color == RED) {
					t->lchild->color = t->rchild->color = BLACK;
					t->color = RED;
					insertAdjust(grandp, parent, t);
				}
				grandp = parent;
				parent = t;
				t = *t->data > x ? t->lchild : t->rchild;
			}
			else {
				t = new node;
				t->data = new T(x);
				t->parent = parent;
				if (x < *parent->data)
					parent->lchild = t;
				else
					parent->rchild = t;
				insertAdjust(grandp, parent, t);
				root->color = BLACK;
				return;
			}
		}
	}

	void remove(const T & x) {
		T del = x;
		node* t, * p, * c;

		if (root == nullptr) return;
		if (*root->data == x && root->lchild == nullptr && root->rchild == nullptr) {
			delete root;
			root = nullptr;
			return;
		}

		p = c = t = root;
		while (true) {
			removeAdjust(p, c, t, del);
			if (*c->data == del && c->lchild && c->rchild) {
				auto tmp = c->rchild;
				while (tmp->lchild)
					tmp = tmp->lchild;
				c->data = tmp->data;
				del = *tmp->data;
				p = c;
				c = c->rchild;
				t = p->lchild;
				continue;
			}

			if (*c->data == del) {
				if (p->lchild == c)
					p->lchild = nullptr;
				else
					p->rchild = nullptr;
				delete c;
				root->color = BLACK;
				return;
			}
			p = c;
			c = del < *p->data ? p->lchild : p->rchild;
			t = c == p->lchild ? p->rchild : p->lchild;
		}
	}

	int check(node * pos) {
		int left = 0, right = 0;
		if (pos->lchild != nullptr)
			left = check(pos->lchild);
		if (pos->rchild != nullptr)
			right = check(pos->rchild);
		if (left < 0 || right < 0 || left != right)
			return -1;
		if (pos->color == BLACK)
			return 1 + left;
		else return left;
	}

	class iterator {
		node* currentData = nullptr;
		friend iterator mSet::begin();

	public:
		iterator() = default;
		iterator(const iterator& b) {
			currentData = new node;
			currentData = b.currentData;
		}

		T& get() {
			return *currentData->data;
		}

		bool finish() {
			return currentData == nullptr;
		}

		iterator& operator++() {
			if (currentData == nullptr)
				return *this;
			if (currentData->rchild != nullptr) {
				for (currentData = currentData->rchild; currentData->lchild != nullptr;)
					currentData = currentData->lchild;
			}
			else if (currentData->parent == nullptr) {
				currentData = nullptr;
			}
			else if (currentData->parent->lchild == currentData)
				currentData = currentData->parent;
			else {
				auto last = currentData;
				for (currentData = currentData->parent;
					currentData != nullptr && currentData->rchild == last;
					currentData = currentData->parent)
					last = currentData;
			}
			return *this;
		}

		T& operator*() const {
			if (currentData == nullptr)
				return *new T;
			else
				return *currentData->data;
		}

		bool operator==(const iterator & b) const {
			return currentData == b.currentData;
		}

		bool operator!=(const iterator & b) const {
			return currentData != b.currentData;
		}
	};

	iterator begin() {
		iterator result;
		auto p = root;
		if (p != nullptr)
			for (; p->lchild != nullptr;) {
				p = p->lchild;
			}
		result.currentData = p;
		return result;
	}

	iterator end() {
		return *new iterator;
	}
};

doubleVector<int> ans;

class disjointSet {
public:

	int* parent;
	int length = 0;
	mSet<int>* edges;

	disjointSet(int size) :length(size) {
		parent = new int[size];
		edges = new mSet<int>[size];
		memset(parent, -1, length * sizeof(int));
	}

	~disjointSet() {
		length = 0;
		delete[] parent;
	}

	int find(int x) {
		int temp = x;
		while(parent[temp] >= 0) 
		temp = parent[temp];
		for (int i = x; i != temp;) {
			int temp1 = parent[i];
			parent[i] = temp;
			i = temp1;
		}
		return temp;
	}

	void set_union(int root1, int root2) {
		if (root1 == root2)
			return;
		if (parent[root1] > parent[root2]) {
			parent[root2] += parent[root1];
			parent[root1] = root2;
		}
		else {
			parent[root1] += parent[root2];
			parent[root2] = root1;
		}
	}


	void bfs(int a, int b) {
		bool *visited = new bool[length];
		int *last_visit = new int[length];
		Queue<int> mq;
		mq.push(a);
		while (!mq.empty()) {
			auto curPos = mq.front();
			visited[curPos] = true;
			mq.pop();
			if (curPos == b) {
				break;
			}
			for (auto p : edges[curPos]) {
				if (!visited[p]) {
					mq.push(p);
					last_visit[p] = curPos;
				}
			}
		}

		for (int i = b;; i = last_visit[i]) {
			ans.push_back(i);
			if (i == a)
				break;
		}
	}
};

int main() {
	int N, entry, exit;
	cin >> N >> entry >> exit;
	disjointSet dset(N*(N+1)/2+1);
	int pi, qi;
	while (cin >> pi >> qi) {
		int n, pos;
		for (n = 1; n * (n + 1) / 2 < pi; n++);
		pos = pi - n * (n - 1) / 2;

		switch (qi)
        {
		    case 0: 
            {
			    if (pos > 1 && n > 1) 
                {
				dset.set_union(dset.find(pi), dset.find(pi - n));
				dset.edges[pi].insert(pi - n);
				dset.edges[pi - n].insert(pi);
			    }
                break;
		    }

		    case 1: 
            {
			    if (pos < n && n>1) 
                {
				    dset.set_union(dset.find(pi), dset.find(pi - n + 1));
				    dset.edges[pi].insert(pi - n + 1);
				    dset.edges[pi - n + 1].insert(pi);
			    }
                break;
		    }

		    case 2: 
            {
			    if (n < N)
                {
				dset.set_union(dset.find(pi), dset.find(pi + n)); 
				dset.edges[pi].insert(pi + n);
				dset.edges[pi + n].insert(pi);
			    }
                break;
		    }

		    case 3: 
            {
			    if (n < N) 
                {
				    dset.set_union(dset.find(pi), dset.find(pi + n + 1));
				    dset.edges[pi].insert(pi + n + 1);
				    dset.edges[pi + n + 1].insert(pi);
			    }
                break;
		    }
        }

		if (dset.find(entry) == dset.find(exit)) 
		{
			dset.bfs(entry, exit);
			cout << ans[ans.get_size() - 1] << " ";
			for (int i = ans.get_size() - 2; i >= 0; i--)
				cout << ans[i] << " ";
			break;
		}
	}

	return 0;
}