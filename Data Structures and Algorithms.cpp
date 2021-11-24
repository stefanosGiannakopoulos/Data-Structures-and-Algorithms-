#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T>
class list {   
private:
    struct node {
        T data;
        node* next;
        node(T data2, node* next2) {
            data = data2;
            next = next2;
        }
    };
    
    node* search(node* p, T info) {
        if (head == nullptr) return nullptr;
        else {
            if (head->data == info) return head;
            else { search(p->next, info); }
        }
    }
   
    template<typename T>
    class stack {
    private:
        list<T> st;

    public:
        stack() {};

        void clear() {
            if (st.head == nullptr) return;
            else {
                st.purge();
            }
            return;
        }

        void push(T info) {
            st.addNodeBackwards(info);
            return;
        }

        void pop() {
            st.pop_front();
            return;
        }

        int size() { return st.size(); }

        bool empty() { return st.head == nullptr; }

        void top() {
            if (st.head != nullptr) { cout << st.head->data << endl; }
            else cout << "stack is empty" << endl;
        }
    };

public:
    node* head;
    list() { head = nullptr; }

   void addNode(T info) {
        if (head != nullptr) {
            node* p = new node(info, nullptr);
            node* dummy = head;
            while (dummy->next != nullptr) dummy = dummy->next;
            dummy->next = p;
        }
        else {
            node* p = new node(info, nullptr);
            head = p;
        }
    }

   void addNodeBackwards(T info) {
       if (head == nullptr) {
           node* p = new node(info, nullptr);
           head = p;
       }
       else {
           node* p = new node(info, nullptr);
           p->next = head;
           head = p;
       }
       return;
   }
   
   void pop_front() {
       if (head == nullptr) return;
       else {
           if (head->next == nullptr) {
               node* toDelete = head;
               head = nullptr;
               delete toDelete;
           }
           else {
               node* toDelete = head;
               head = head->next;
               delete toDelete;
           }
       }
       return;
   }

   void pop_back() {
       if (head == nullptr) return;
       else {
           node* q = head;
          while (q->next->next != nullptr) { q = q->next; }
          delete q->next;
         q->next = nullptr;
          return;
         }
       return;
   }

   void purge() {
       if (head == nullptr)return;
       else {
           while (head != nullptr) {
               node* p = head;
               head = head->next;
               delete p;
           }
       }
       return;
   }

    int size() {
        node* q = head;
        if (q == nullptr) return 0;
        else {
            int counter = 0;
            while (q != nullptr) {
                counter++;
                q = q->next;
            }
            return counter;
        }
    }

    int sumOfAllNodes() {
        int counter = 0;
        if (head == nullptr) { cout << "It's nullptr..." << endl; return 0; }
        else {
            node* q = head;
            while (q != nullptr) {
                counter = counter + q->data;
                q = q->next;
            }
            return counter;
        }
    }

    int sumOfSelectedNodes(int startingNode, int endingNode) throw(out_of_range) {
        if (endingNode < startingNode) {
            throw("Your end is greater than your start...");
            return 0;
        }
        else if (startingNode <= 0 || endingNode <= 0 || (startingNode == 0 && endingNode == 0)) {
            throw("Counting starts from 1...");
            return 0;
        }

        else if (startingNode == endingNode) {
            node* z = head;
            if (startingNode == 1)   return z->data;
            else {
                for (int i = 0; i < endingNode; i++) z = z->next;
                return z->data;
            }
        }
        else {
            node* p = head;
            int distance = endingNode - startingNode;
            int sizeOfList = 0;
            while (p != nullptr) {
                sizeOfList++;
                p = p->next;
            }
            if (sizeOfList < distance || startingNode>sizeOfList || endingNode > sizeOfList) {
                throw("Starting node or ending node, doesn't exist...");
                return 0;
            }
            else {
                node* z = head;
                int sum = 0;
                if (startingNode == 1) {
                    for (int i = startingNode; i <= endingNode; i++) {
                        sum = sum + z->data;
                        z = z->next;
                    }
                    z = head;
                    return sum;
                }
                else if (startingNode > 1) {
                    for (int i = 1; i < startingNode; i++) z = z->next;
                    for (int j = startingNode; j <= endingNode; ++j) {
                        sum = sum + z->data;
                        z = z->next;
                    }
                    z = head;
                    return sum;
                }
            }
        }
    }

    void concat(list<T>& l2) {
        if (l2.head == nullptr) return;
        else {
            if (head == nullptr) head = l2.head;
            else {
                node* q = head;
                while (q->next != nullptr) q = q->next;
                q->next = l2.head;
                l2.head = this->head;
            }
        }
    }

    void print() {
        node* q = head;
        int counter = 0;
        if (q == nullptr) { cout << "List is empty..." << endl; return; }
        while (q != nullptr) {
            counter++;
            if (counter == this->size()) {
                cout << q->data << endl;
                return;
            }
            else {
                cout << q->data << " -> ";
                q = q->next;
            }
        }
    }

    node* returnNthNodeFromTheEnd(int n) {
        node* p = head;
        int size = this->size();
        int toGo = size - n;
        int counter = 0;
        while (counter != toGo && p != nullptr) {
            p = p->next;
            counter++;
        }
        return p;
    }

    void reverse() {
        node* current = head;
        node* prev = nullptr, * next = nullptr;
        while (current != NULL) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
  
    void printFunny() {
           stack<T> s;
            if (head == nullptr) return;
            else {
                int counter = 1;
                int size = this->size();
                if (size % 2 != 0) {
                    counter = 2;
                    while (head != nullptr) {
                        if (counter % 2 == 0) s.push(head->data);
                        counter++;
                        head = head->next;
                    }
                }
                else {
                    counter = 1;
                    while (head != nullptr) {
                        if (counter % 2 == 0) s.push(head->data);
                        counter++;
                        head = head->next;
                    }
                }
                while (!s.empty()) {
                   s.top() ;
                    s.pop();
                }
            }
        }
  
    
};

template<typename T>
class stack {
private:
    list<T> st;

public:
    stack() {};

    void clear(){
        if (st.head == nullptr) return;
        else {
            st.purge();
        }
        return;
}

  void push(T info) { 
  st.addNodeBackwards(info); 
  return;
  }
  
  void pop() {
      st.pop_front();
      return;
  }
  
  int size() { return st.size(); }

  bool empty() { return st.head == nullptr; }

   void top() {
       if (st.head != nullptr) { cout << st.head->data << endl; }
       else cout << "stack is empty" << endl;
   }
};
         
template<typename T>
class queue {
private:
   struct node {
       T data;
       node* next;
       node(T info, node* n) {
           data = info;
           next = n;
   }
   };
  
public:
    node* front, * rear;
    queue() { front = nullptr; rear = nullptr; }
    void push(T info) {
        if (front == nullptr) {
            node* p = new node(info, nullptr);
            front = p;
            rear = front;
        }
        else {
            node* p = new node(info, nullptr);
            rear->next = p;
            rear = p;
        }
        return;
    }
    
    void first() {
        if (front == nullptr) cout << "queue is empty..." << endl;
        else {
            cout << front->data << endl;
        }
    }

    void pop() {
        if (front == nullptr) {
            cout << "There is nothing to pop..." << endl;
            return;
        }
        else {
            if (front == rear) {
                node* p = front;
                front = nullptr; rear = nullptr;
                delete p;
            }
            else {
                node* q = front;
                front = front->next;
                delete q;
            }
        }
        return;
    }
   
    void peek_last() {
        if (rear != nullptr) cout << rear->data << endl;
        return;
    }

    void clear() {
         if (front == nullptr)return;
       else {
           while (front != nullptr) {
               node* p = front;
               front = front->next;
               delete p;
           }
       }
       return;
    }

    bool empty() {
        return front == nullptr;
    }

   int size() {
        node* q = front;
        if (q == nullptr) return 0;
        else {
            int counter = 0;
            while (q != nullptr) {
                counter++;
                q = q->next;
            }
            return counter;
        }
      }
};


template<typename T>
class bsTree {
private:
    struct node {
        T data;
        node* left; node* right;
    };
    bool isEven(int a) { return a % 2 == 0; }

    node* insert_aux(node*& root, T h) {
        if (root == nullptr) {
            node* t = new node;
            t->data = h;
            t->left = nullptr;
            t->right = nullptr;
            root = t;
            return t;
        }
        if (h > root->data) {
            root->right = insert_aux(root->right, h);
        }
        else if (h < root->data) {
            root->left = insert_aux(root->left, h);
        }
        return root;
    }

    static void inOrder(node* t) {
        if (t != nullptr) {
            inOrder(t->left);
            cout << t->data << endl;
            inOrder(t->right);
        }
    }

    int countEqualHeightAndDepth_aux(node* root, int& counter) {
        if (root == nullptr) return 0;
        else {
            int height_of_node = height(root);
            int depth_of_node = depth(root->data);
            if (height_of_node == depth_of_node) counter++;
            countEqualHeightAndDepth_aux(root->left, counter);
            countEqualHeightAndDepth_aux(root->right, counter);
        }
        return counter;
    }

    int countEW_aux(node* root, int& counter) {
        if (root == nullptr) return 0;
        else {
            int left_nodes = nodes(root->left);
            int right_nodes = nodes(root->right);
            if (left_nodes == right_nodes) counter++;
            countEW_aux(root->left, counter);
            countEW_aux(root->right, counter);
        }
        return counter;
    }

    int mixedPaths_aux(node* t, int& counter) {
        if (t == nullptr) return 0;
        else {
            if (t->left == nullptr && t->right == nullptr) counter++;
            else {
                if (isEven(t->data)) {
                    if (t->left != nullptr && (!isEven(t->left->data))) mixedPaths_aux(t->left, counter);
                    if (t->right != nullptr && (!isEven(t->right->data))) mixedPaths_aux(t->right, counter);

                }
                else {
                    if (t->left != nullptr && (isEven(t->left->data))) mixedPaths_aux(t->left, counter);
                    if (t->right != nullptr && (isEven(t->right->data))) mixedPaths_aux(t->right, counter);
                }
            }
        }
        return counter;
    }

    void inorderNodes(node* root, list<T>& nodes) {
        if (root == nullptr) return;
        else {
            inorderNodes(root->left, nodes);
            nodes.addNode(root->data);
            inorderNodes(root->right, nodes);
        }
    }

    void purge(node* root) {
        if (root == nullptr) return;
        else {
            purge(root->left);
            purge(root->right);
            delete root;
        }
    }
    void addNod(T s) {
        if (root == nullptr) { insert_aux(root, s); }
        else if (s > root->data) insert_aux(root->right, s);
        else if (s < root->data) insert_aux(root->left, s);
    }

    void copy(node* t) {
        if (t != nullptr) {
            addNod(t->data);
            copy(t->left);
            copy(t->right);
        }
    }

public:
    node* root;
    bsTree() { root = nullptr; }

    void addNode(T s) {
        if (root == nullptr) { insert_aux(root, s); }
        else if (s > root->data) insert_aux(root->right, s);
        else if (s < root->data) insert_aux(root->left, s);
    }

    bsTree<T> operator=(bsTree<T> t) {
        this->purge(this->root);
        this->copy(t.root);
        return *this;
    }

    int nodes(node* p) {
        if (p == nullptr) return 0;
        else {
            return 1 + nodes(p->left) + nodes(p->right);
        }
    }

    int countLessOrEqual(node* root) {
        if (root == nullptr) return 0;
        else {
            if (root->data > root->left->data && root->data > root->right->data) return 1 + countLessOrEqual(root->left) + countLessOrEqual(root->right);
        }
    }

    int height(node* root) {
        if (root == nullptr) return 0;
        else return 1 + max(height(root->left), height(root->right));
    }


    int sum_one_child(node* root) {
        static int sum = 0;
        if (root == nullptr) return 0;
        else {
            if ((root->left == nullptr && root->right != nullptr) || (root->right == nullptr && root->left != nullptr)) {
                sum = sum + root->data;
            }
            sum_one_child(root->left);
            sum_one_child(root->right);
        }
        return sum;
    }

    int countEW(node* root) {
        int counter = 0;
        return countEW_aux(root, counter);
    }

    bool isBalanced(node* root) {
        if (root == nullptr) return true;
        else {
            int hl = height(root->left);
            int hr = height(root->right);
            if (abs(hl - hr) <= 1) return isBalanced(root->left) && isBalanced(root->right);
            else return false;
        }
        return true;
    }

    int mixedPaths(node* t) {
        int counter = 0;
        return mixedPaths_aux(t, counter);
    }

    int countRH(node* root) {
        if (root == nullptr) return 0;
        if (nodes(root->right) > nodes(root->left)) return 1 + countRH(root->left) + countRH(root->right);
    }

    int sumOfAllNodes(node* t) {
        static int sum = 0;
        if (t == nullptr) return 0;
        else {
            sum = sum + t->data;
            sumOfAllNodes(t->left);
            sumOfAllNodes(t->right);
        }
        return sum;
    }

    int sumLevel(node* root, int level) {
        static int sum = 0;
        if (root == nullptr) return 0;
        else {
            if (level == 1) sum = sum + root->data;
            sumLevel(root->left, level - 1);
            sumLevel(root->right, level - 1);
        }
        return sum;
    }

    int unbalance(node* t) {
        static int max = 0;
        if (t == nullptr) return 0;
        else {
            int left_height = height(t->left);
            int right_height = height(t->right);
            int unb = abs(left_height - right_height);
            if (unb > max) max = unb;
            unbalance(t->left);
            unbalance(t->right);
        }
        return max;
    }

    void invertTree(node* root) {
        if (root == nullptr) return;
        else {
            node* left = root->left;
            node* right = root->right;
            node* dummy = root->right;
            right = left;
            left = dummy;
            root->right = right;
            root->left = left;
            invertTree(root->left);
            invertTree(root->right);
        }
    }


    int depth(int s) {
        int depthCounter = 0;
        if (root == nullptr) return -1;
        if (root->data == s) return depthCounter;
        else {
            node* t = root;
            while (t != nullptr) {
                if (t->data > s) { t = t->left;  depthCounter++; }
                else if (t->data < s) { t = t->right; depthCounter++; }
                else if (t->data == s) return depthCounter;
            }
            if (t == nullptr) return -1;
        }
    }

    int countEH(node* root, int& counter) {
        if (root == nullptr) return 0;
        else {
            int height_left = height(root->left);
            int height_right = height(root->right);
            if (abs(height_left - height_right) == 0) counter++;
            countEH(root->left, counter);
            countEH(root->right, counter);
        }
        return counter;
    }

    int countEqualHeightAndDepth(node* root) {
        int counter = 0;
        int answer = countEqualHeightAndDepth_aux(root, counter);
        return answer;
    }

    
    friend ostream& operator << (ostream& out, const bsTree<T>& l) {
        inOrder(l.root);
        return out;
    }

};



int main()
{

}

