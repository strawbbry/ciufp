// arrays

class Vector {
    private:
        int cap;
        int* ptr; // pointer to array[0] lives on stack, array itself lives on heap
        int sze;

        void resize (int new_capacity) {
            if (new_capacity < 1) { new_capacity = 1; } // base case cap = 0 }

                int* new_ptr = new int[new_capacity];

                for (int i = 0; i < sze; i++) {
                    new_ptr[i] = ptr[i];
                }

                delete[] ptr;
                ptr = new_ptr;
                cap = new_capacity;
        }

    public:
        Vector (int capacity = 0) { // constructor 
            cap = capacity;
            ptr = new int[cap]; // dynamically allocate memory 
            sze = 0;
        };

        ~Vector () { // destructor 
            delete[] ptr; // free dynamically allocated memory
        }

        int size () {
            return sze;
        }

        int capacity () {
            return cap;
        }

        bool is_empty () {
            return (sze == 0) ? true : false; // c++ uses ternary
        }

        int at (int index) {
            if (index < 0 || index >= sze) { return -1; }
            return ptr[index];
        }

        void push (int item) {
            if (sze == cap) { resize(cap == 0 ? 1 : cap * 2); }
            ptr[sze] = item;
            sze++;
        }

        void insert (int index, int item) {
            if (index < 0 || index > sze) { return; } // index = sze allowed !

            if (sze == cap) { resize(cap == 0 ? 1 : cap * 2); }

            for (int i = sze; i > index; i--) {
                ptr[i] = ptr[i - 1];
            }

            ptr[index] = item;
            sze++;
        }

        void prepend (int item) {
            insert(0, item);
        }

        int pop () {
            if (sze == 0) { return -1; }

            int value = ptr[sze - 1];
            sze--;

            if (sze > 0 && sze <= cap / 4) { resize(cap/2); }

            return value;
        }

        void del (int index) { // delete is a c++ keyword
            if (index < 0 || index >= sze) { return; }

            ptr[index] = {};
            for (int i = index; i < sze - 1; i++) { // < sze would read past end
                ptr[i] = ptr[i + 1];
            }
            sze--;
            if (sze > 0 && sze <= cap / 4) { resize(cap / 2); }
        }

        void remove (int item) {
            for (int i = 0; i < sze; i++) { // sze - 1 would never check last elem
                if (ptr[i] == item) {
                    del(i);
                    i--;
                }
            }
        }

        int find (int item) {
            for (int i = 0; i < sze; i++) {
                if (at(i) == item) {
                    return i;
                }
            }
            return -1;
        }
};


// linked lists

#include <string>
// singly linked list: track prev = curr via curr->next  
class SinglyLinkedList {
    protected:
        struct node {
            int data;
            node *next;
        };

        node *head;

    public:
        SinglyLinkedList () {
            head = nullptr;
        }

        ~SinglyLinkedList () {
            node *curr = head;
            while (curr != nullptr) {
                node *next = curr->next;
                delete curr;
                curr = next;
            }
            head = nullptr;
        }

        int size () const { // 'const' tells compiler fn is read-only, will not mutate anyt
            int i = 0;

            node *curr = head;
            while (curr != nullptr) {
                curr = curr->next;
                i++;
            }
            return i;
        }

        bool empty () const {
            return head == nullptr;
        }

        void push_front (int value) {
            node *push = new node {value, nullptr};
            if (head != nullptr) { push->next = head; }
            head = push;
        }

        int pop_front () {
            if (head == nullptr) { return -1; }
            int val = head->data;
            node *pop = head;
            head = head->next;
            delete pop;
            return val;
        }

        void insert (int index, int value) {
            if (index < 0 || index > size()) { return; }

            node *in = new node {value, nullptr};
            
            if (index == 0) { 
                in->next = head;
                head = in;
                return;
            }

            node *prev = nullptr;
            node *curr = head;
            for (int i = 0; i < index; i++) {
                prev = curr;
                curr = curr->next;
            }
            prev->next = in;
            in->next = curr;
            return;
        }

        void erase (int index) {
            if (index < 0 || index >= size()) { return; }

            if (index == 0) {
                pop_front();
                return;
            }

            node *prev = nullptr;
            node *curr = head;
            for (int i = 0; i < index; i++) {
                prev = curr;
                curr = curr->next;
            }
            prev->next = curr->next;
            delete curr; 
            return;
        }

        void reverse () {
            if (head == nullptr || head->next == nullptr) { return; }

            node *prev = nullptr;
            node *curr = head;
            while (curr != nullptr) {
                node *temp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = temp;
            }
            head = prev; 
        }
};

// doubly linked list: prev pointer 
class LinkedList {
    protected:
        struct node {
            std::string data;
            node *prev; 
            node *next;
        };

        node *head;
        // add int size to make size() O(1)
    
    public:
        LinkedList (std::string data = "") { // constructor 
            if (data == "") { // empty node = no node 
                head = nullptr;
            } else {
                head = new node {data, nullptr, nullptr}; // 'new' = c 'malloc'
            }
        }

        // virtual : look up parent vs child def at runtime ! 
        // don't just auto use parent def even for child
        virtual ~LinkedList () { 
            node *curr = head; // iterate thru linkedlist
            while (curr != nullptr) {
                node *next = curr->next; // -> bc curr is ptr 
                delete curr; // 'delete' = c 'free'
                curr = next; 
            }
            head = nullptr;
        }

        int size () {
            int i = 0;
            node *curr = head;
            while (curr != nullptr) {
                node *next = curr->next;
                i++;
                curr = next;
            }
            return i;
        }

        bool empty () {
            if (head == nullptr) {
                return true;
            }
            return false;
        }

        virtual std::string value_at (int n) {
            if (n < 0 || n > size() - 1) { return ""; }
            int i = 0;
            node *curr = head;
            while (curr != nullptr) {
                if (i == n) {
                    return curr->data;
                } else {
                    node *next = curr->next;
                    i++;
                    curr = next;
                }
            }
            return "";
        }

        virtual void push_front (std::string value) {
            node *push = new node {value, nullptr, head};
            if (head != nullptr) {
                head->prev = push;
            }
            head = push;
        }

        virtual std::string pop_front () {
            if (head == nullptr) { return ""; }

            std::string value = head->data;

            node *pop = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete pop; // need to actl free the allocated heap of node !
            
            return value;
        }

        virtual void push_back (std::string value) {
            node *push = new node {value, nullptr, nullptr};

            if (head == nullptr) { // 1. list = empty
                head = push;
            } else {
                node *curr = head;
                while (curr->next != nullptr) { // iterate until last node
                    curr = curr->next;
                }
                curr->next = push;
                push->prev = curr;
            }
        }

        virtual std::string pop_back () {
            if (head == nullptr) { return ""; } // 1. 0 node

            if (head->next == nullptr) { // 2. only 1 node 
                std::string value = head->data;
                delete head; // 
                head = nullptr;
                return value;
            } else { // 3. >1 node
                node *curr = head;
                while (curr->next != nullptr) {
                    curr = curr->next;
                }
                std::string value = curr->data;
                curr->prev->next = nullptr;
                delete curr;
                return value;
            }
        }

        std::string front () {
            if (head == nullptr) { return ""; }
            return head->data;
        }

        virtual std::string back () {
            if (head == nullptr) { return ""; }
            else {
                node *curr = head;
                while (curr->next != nullptr) {
                    curr = curr->next;
                }
                return curr->data;
            }
        }

        virtual void insert (int index, std::string value) {
            if (index < 0 || index > size()) { return; }

            if (index == 0) { // index at start
                push_front(value);
                return;
            }
            if (index == size()) { // index at end + 1
                push_back(value);
                return;
            }
            else { // index in middle 
                node *in = new node {value, nullptr, nullptr};
                int i = 0;
                node *curr = head;
                for (int i = 0; i < index; i++) { curr = curr->next; }
                in->prev = curr->prev;
                curr->prev->next = in;
                in->next = curr;
                curr->prev = in; 
                return;
            }
        }

        virtual void erase (int index) {
            if (index < 0 || index >= size()) { return; } // index too big
            if (index == 0) { // index at start
                std::string x = pop_front();
                return;
            }
            if (index == size() - 1) { // index at end
                std::string x = pop_back();
                return;
            }
            else {
                node *curr = head;
                for (int i = 0; i < index; i++) {
                    curr = curr->next;
                }
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
            }

        }

        virtual std::string value_n_from_end (int n) {      
            return value_at(size() - n);
        }

        virtual void reverse () {
            if (head == nullptr || head->next == nullptr) { return; }
            node *curr = head;
            node *temp = nullptr;
            while (curr != nullptr) {
                temp = curr->prev;
                curr->prev = curr->next;
                curr->next = temp;

                curr = curr->prev; // move forward 
            }
            head = temp->prev;
        }

        virtual void remove_value (std::string value) {
            if (head == nullptr) { return; }
            if (head->data == value) {
                std::string x = pop_front();
                return;
            }
            node *curr = head;
            while (curr != nullptr) {
                if (curr->data == value) {
                    curr->prev->next = curr->next;
                    if (curr->next != nullptr) {
                        curr->next->prev = curr->prev;
                    }
                    delete curr;
                    return;
                }
                curr = curr->next;
            }
            return;
        }

};

class LinkedList_TailPointer : public LinkedList {
    protected:
        node *tail;
    
    public:
        LinkedList_TailPointer (std::string data = "") {
            if (data == "") {
                head = nullptr;
                tail = nullptr;
            } else {
                head = new node {data, nullptr, nullptr};
                tail = head; 
            }
        };

        ~LinkedList_TailPointer () {
            // compiler auto calls ~LinkedList !
            tail = nullptr;
        }

        std::string value_at (int n) override {
            if (n < 0 || n > size() - 1) { return ""; }
            node *curr;
            if (n < size() / 2) {
                curr = head;
                for (int i = 0; i < n; i++) {
                    curr = curr->next;
                }
            } else {
                curr = tail;
                for (int i = size() - 1; i > n; i--) {
                    curr = curr->prev;
                }
            }
            return curr->data;
        }

        void push_front (std::string value) override {
            node *push = new node {value, nullptr, head};
            if (head != nullptr) {
                head->prev = push;
            } else {
                tail = push;
            }
            head = push;
        }

        std::string pop_front () override {
            if (head == nullptr) { return ""; }
            std::string value = head->data;
            node *pop = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete pop;
            return value;
        }

        void push_back (std::string value) override {
            node *push = new node {value, nullptr, nullptr};
            if (head == nullptr) { // 1. empty list
                head = push;
                tail = push;
            } 
            else { // 2. nonempty list
                tail->next = push;
                push->prev = tail;
                tail = push; 
            }
        }

        std::string pop_back () override {
            if (head == nullptr) { return ""; } // 0 node 
            std::string value = tail->data;

            if (head == tail) { // 1 node
                delete head;
                head = nullptr;
                tail = nullptr;
                return value;
            } else { // >1 node
                node *pop = tail;
                tail = tail->prev;
                tail->next = nullptr;
                delete pop;
                return value;
            }
        }

        std::string back () override {
            if (head == nullptr) { return ""; }
            return tail->data;
        }

        void insert (int index, std::string value) override {
            if (index < 0 || index > size()) { return; } // index too small/big

            if (index == 0) { // index at start
                push_front(value);
                return;
            }
            if (index == size()) { // index at end + 1
                push_back(value);
                return;
            }
            else {
                node *in = new node {value, nullptr, nullptr};
                node *curr;
                if (index < size() / 2) { // index < midpoint
                    curr = head;
                    for (int i = 0; i < index; i++) {
                        curr = curr->next;
                    }
                } else { // index >= midpoint
                    curr = tail;
                    for (int i = size() - 1; i > index; i--) {
                        curr = curr->prev;
                    }
                }
                in->prev = curr->prev;
                curr->prev->next = in;
                in->next = curr;
                curr->prev = in;  
            }
        }

        void erase (int index) override {
            if (index < 0 || index >= size()) { return; } // index too small/big
            if (index == 0) { // index at start
                pop_front();
                return;
            }
            if (index == size() - 1) { // index at end 
                pop_back();
                return;
            }
            else {
                node *curr;
                if (index < size() / 2) {
                    curr = head;
                    for (int i = 0; i < index; i++) {
                        curr = curr->next;
                    }
                } else {
                    curr = tail;
                    for (int i = size() - 1; i > index; i--) {
                        curr = curr->prev;
                    }
                }
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
            }
        }

        std::string value_n_from_end (int n) override {
            return value_at(size() - n); // override to use child fn value_at
        }

        void reverse () override {
            if (head == nullptr || head->next == nullptr) { return; }
            node *curr = head;
            node *temp = nullptr;
            while (curr != nullptr) {
                temp = curr->prev;
                curr->prev = curr->next;
                curr->next = temp;

                curr = curr->prev; // move forward 
            }
            node *old = head;
            head = tail;
            tail = old;
        }

        void remove_value (std::string value) override {
            if (head == nullptr) { return; }
            if (head->data == value) {
                std::string x = pop_front();
                return;
            }
            if (tail->data == value) {
                std::string x = pop_back();
                return;
            }
            node *curr = head;
            while (curr != nullptr) {
                if (curr->data == value) {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    delete curr;
                    return;
                }
                curr = curr->next;
            }
            return;
        }
};  


// stacks & queues

class Queue : public LinkedList_TailPointer { // doubly linked list with tail pointer (public keyword for public inheritance)
    public:
        Queue () : LinkedList_TailPointer() {}; // inherit constructor
        

        ~Queue () {
        // compiler auto calls ~LinkedList_TailPointer
        }

        void enqueue (std::string value) {
            node *en = new node {value, nullptr, nullptr};
            
            if (head == nullptr) { 
                head = en; 
                tail = en;
            }
            else {
                tail->next = en;
                en->prev = tail;
                tail = en;
            }
        }

        std::string dequeue () {
            if (head == nullptr) { return ""; } // not found

            std::string value = head->data;
            node *temp = head;

            head = head->next;
            if (head != nullptr) { head->prev = nullptr; }
            delete temp;

            if (head == nullptr) { tail = nullptr; }
            return value;
        }

        bool empty () {
            return head == nullptr;
        }
};

class CircularBuffer { // queue impl with array
    private:
        std::string *ptr;
        int cap;
        int sze; 

        int head; // queue always has front and back
        int tail;
    
    public:
        CircularBuffer (int capacity) {
            cap = capacity;
            ptr = new std::string[cap];
            sze = 0;
            head = 0; // points to 'first in' element
            tail = 0; 
        }

        ~CircularBuffer () {
            delete[] ptr; 
        }

        void enqueue (std::string value) { // overwrite oldest data if full
            ptr[tail] = value; // append to end 
            tail = (tail + 1) % cap; // move forward (circle back to front for next overwrite)
            if (sze == cap) {
                head = (head + 1) % cap; // move head so that head != tail 
            }  else { sze++; }
        }

        std::string dequeue () {
            if (sze == 0) { return ""; } // not found

            std::string value = ptr[head];
            head = (head + 1) % cap; // move head forward 
            sze--; // effectively 'removing' since this cannot be accessed anymore 

            // if tail points to old head again it will just overwrite !

            return value;
        }

        bool empty () {
            return sze == 0;
        }

        bool full () {
            return sze == cap;
        }
};


// hashtables

class HashTable { // linear probing array impl
    private:
        struct entry {
            int key;
            int value;
            bool occupy = false; // if item = true
            bool tombstone = false; // item that got deleted 
        };

        entry *table; // pointer to entry #1 in array
        int cap; 
        int n; //# items 

    public:
        HashTable (int capacity) {
            cap = capacity;
            n = 0;
            table = new entry[cap]; // array of entries of size cap
            for (int i = 0; i < cap; i++) {
                table[i].occupy = false;
                table[i].tombstone = false; 
            }
        };

        ~HashTable () {
            delete[] table;
        }

        int hash (int k, int m) { // k = key, m = table size
            return ((k % m) + m) % m; // account for -ve keys !
        }

        void add (int key, int value) {
            float load = (float) n / cap;
            if (load >= 0.75) { // resize 
                int old_cap = cap;
                entry *old_table = table;

                cap *= 2;
                table = new entry[cap];
                for (int i = 0; i < cap; i++) {
                    table[i].occupy = false;
                    table[i].tombstone = false;
                }
                n = 0;

                for (int i = 0; i < old_cap; i++) {
                    if (old_table[i].occupy) {
                        int j = hash(old_table[i].key, cap);
                        while (table[j].occupy) { // probe for next empty
                            j = (j + 1) % cap; // in case j + 1 > cap
                        }
                        table[j] = {old_table[i].key, old_table[i].value, true, false};
                        n++;
                    }
                }
                delete[] old_table;
            }

            int i = hash(key, cap);
            int check = 0;
            while ((table[i].occupy || table[i].tombstone) && check < cap) { // iterate thru all keys using wraparound
                if (table[i].occupy && table[i].key == key) {
                    table[i].value = value;
                    return;
                }
                i = (i + 1) % cap; 
                check++;
            }

            table[i] = {key, value, true, false}; // if i not occupied
            n++;
        }

        bool exists (int key) {
            int i = hash(key, cap);
            int check = 0;
            while ((table[i].occupy || table[i].tombstone) && check < cap) { // continue if tombstone
                if (table[i].occupy && table[i].key == key) { return true; } // check not tombstone 
                i = (i + 1) % cap;
                check++;
            }
            return false;
        }

        int get (int key) {
            int i = hash(key, cap);
            int check = 0;
            while ((table[i].occupy || table[i].tombstone) && check < cap) { // continue if tombstone
                if (table[i].occupy && table[i].key == key) { return table[i].value; } // check not tombstone 
                i = (i + 1) % cap;
                check++;
            }
            return -1; // not found 
        }

        void remove (int key) {
            int i = hash(key, cap);
            int check = 0;
            while ((table[i].occupy || table[i].tombstone) && check < cap) { // continue if tombstone
                if (table[i].occupy && table[i].key == key) { 
                    table[i].occupy = false;
                    table[i].tombstone = true;
                    n--;
                    return;
                } // check not tombstone 
                i = (i + 1) % cap;
                check++;
            }
        }
};


// binary search

int binary_search (const std::vector<int>& array, int target) {
    int left = 0;
    int right = static_cast<int>(array.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // '/' rounds down
        // left + right could overflow and wraparound if both are large 
        // right - left avoids that 

        if (array[mid] == target) { return mid; }
        else if (array[mid] < target) { left = mid + 1; }
        else { right = mid - 1; }
    }

    return -1;
}

int recursive_binary_search (const std::vector<int>&array, int target, int left, int right) {
    if (left > right) { return -1; } // base case 

    int mid = left + (right - left) / 2;

    if (array[mid] == target) { return mid; }
    else if (array[mid] < target) { return recursive_binary_search(array, target, mid + 1, right); }
    else { return recursive_binary_search(array, target, left, mid - 1); }
}


// trees 

#include <iostream>
#include <stack>
class BST {
    private:
        struct node {
            int data;
            node *left;
            node *right;

            ~node () { // node destructor method inside struct : when root deleted ...
            delete left;
            delete right;
            }
        };

        node *root;

    public:
        BST () {
            root = nullptr; 
        };

        ~BST () {
            delete root; // auto calls root node destructor 
        }

        virtual void insert (int value) { // insert value into tree
            if (root == nullptr) {
                root = new node {value, nullptr, nullptr};
                return;
            }

            node *curr = root;
            while (true) {
                if (value < curr->data) {
                    if (curr->left == nullptr) { 
                        curr->left = new node {value, nullptr, nullptr};
                        return;
                    } 
                    curr = curr->left;
                }
                else if (value > curr->data) {
                    if (curr->right == nullptr) {
                        curr->right = new node { value, nullptr, nullptr};
                        return;
                    }
                    curr = curr->right;
                }
                else { return; } // ignore duplicates 
            }
        }

        int get_node_count (node *subroot) { // get count of values stored in subtree
            if (subroot == nullptr) { return 0; }
            return get_node_count(subroot->left)+ get_node_count(subroot->right) + 1;
        }

        void print_values () { // prints the values in the tree, from min to max
            std::stack<node*> s; // stack to return to previous roots

            node *curr = root;
            while (curr != nullptr || !s.empty()) {
                while (curr != nullptr) {
                    s.push(curr); // remember root for later 
                    curr = curr->left;
                }
                curr = s.top(); // left finished, return to closest root
                s.pop(); // remove from 'later' stack

                std::cout << curr->data << "\n";
                curr = curr->right;  // check right subtree 
            }
        }

        bool is_in_tree (int value) { // returns true if a given value exists in the tree
            if (root == nullptr) { return false; }

            node *curr = root;
            while (curr != nullptr) {
                if (value == curr->data) { return true; }
                else if (value < curr->data) { curr = curr->left; }
                else { curr = curr->right; }
            }
            return false;
        }

        int get_height (node *subroot) { //  get_height // returns the height in nodes (single node's height is 1)
            if (subroot == nullptr) { return 0; }
            return std::max(get_height(subroot->left), get_height(subroot->right)) + 1;
        }

        int get_min () { // returns the minimum value stored in the tree
            if (root == nullptr) { return; }

            node *curr = root;
            while (curr->left != nullptr) { curr = curr->left; }
            return curr->data;
        }

        virtual int get_max () { // returns the maximum value stored in the tree
            if (root == nullptr) { return; }

            node *curr = root;
            while (curr->right != nullptr) { curr = curr->right; }
            return curr->data;
        }

        node* get_min_node (node *subroot) { // returns the minimum node stored in the tree
            if (subroot == nullptr) { return nullptr; }

            while (subroot->left != nullptr) { subroot = subroot->left; }
            return subroot;
        }

        node* get_max_node (node *subroot) { // returns the maximum node stored in the tree
            if (subroot == nullptr) { return nullptr; }

            while (subroot->right != nullptr) { subroot = subroot->right; }
            return subroot;
        }

        bool is_binary_search_tree () {
            std::stack<node*> s;
            node *curr = root;
            node *prev = root;

            while (curr != nullptr || !s.empty()) {
                while (curr != nullptr) {
                    if (curr->data < prev->data) { return false; }

                    s.push(curr);
                    prev = curr;
                    curr = curr->left;
                }
                curr = s.top();
                prev = curr;
                s.pop();

                prev = curr;
                curr = curr->right;
            }
            return true;
        }

        node* delete_value (node *subroot, int value) {
            if (subroot == nullptr) { return nullptr; }

            else if (value < subroot->data) { subroot->left = delete_value(subroot->left, value); }
            else if (value > subroot->data) { subroot->right = delete_value(subroot->right, value); }
            else {
                if (subroot->left == nullptr && subroot->right == nullptr) {
                    delete subroot;
                    return nullptr;
                }
                else if (subroot->left == nullptr) {
                    node *temp = subroot;
                    subroot = subroot->right;
                    temp->right = nullptr;
                    delete temp;
                }
                else if (subroot->right == nullptr) {
                    node *temp = subroot;
                    subroot = subroot->left;
                    temp->left = nullptr;
                    delete temp;
                }
                else {
                    node *temp = get_min_node(subroot->right);
                    subroot->data = temp->data;
                    subroot->right = delete_value(subroot->right, temp->data);
                }
            }
            return subroot;
        }

        int get_successor (int value) { // returns the next-highest value in the tree after given value, -1 if none
            std::stack<node*> s;
            bool found = false;

            node *curr = root;
            while (curr != nullptr || !s.empty()) {
                while (curr != nullptr) {
                    s.push(curr);
                    curr = curr->left;
                }
                curr = s.top();
                s.pop();

                if (found) { return curr->data; }

                if (curr->data == value) { found = true; }
                curr = curr->right;
            }
            return -1;
        }
};


// heaps 

#include <vector>
class MaxHeap { // almost complete binary tree 
    private:
        std::vector<int> heap; // modern c++ array, auto-create constructor, destructor

    public:
        MaxHeap () {
            heap.push_back(0); // make 1 be first real index
        };

        void insert (int value) {
            heap.push_back(value); // add value to end of heap
            sift_up(heap.size() - 1); // shift value at end of heap
        }

        void sift_up (int index) { // needed for insert to shift value at given index
            if (index == 1) { return; } // root

            int parent = index / 2;
            if (heap[index] > heap[parent]) {
                int temp = heap[parent]; 
                heap[parent] = heap[index];
                heap[index] = temp;
                sift_up(parent);
            } 
        }

        int get_max () { // returns the max item, without removing it
            return heap[1];
        }

        int get_size () { // return number of elements stored
            return heap.size() - 1;
        }

        bool is_empty () { // returns true if the heap contains no elements
            return heap.size() == 1;
        }

        int extract_max () { // returns the max item, removing it
            if (heap.size() == 1) { return -1; } // empty heap
            int max = heap[1];
            
            int temp = heap[1]; // swap root and last element
            heap[1] = heap[heap.size() - 1];
            heap[heap.size() - 1] = temp;

            heap.pop_back();
            sift_down(1); 

            return max;
        }

        void sift_down (int index) { // needed for extract_max to shift value at given index
            if (index >= heap.size()) { return; } 

            int left = 2 * index;
            int right = 2 * index + 1;
            int largest = index;
            if (left < heap.size() && heap[left] > heap[index]) { largest = left; }
            if (right < heap.size() && heap[right] > heap[largest]) { largest = right; }

            if (largest != index) {
                int temp = heap[index];
                heap[index] = heap[largest];
                heap[largest] = temp;
                sift_down(largest);
            }
        }

        void remove (int x) { // removes item at index x
            if (x < 1 || x >= heap.size()) { return; }

            int temp = heap[x];
            heap[x] = heap[heap.size() - 1];
            heap[heap.size() - 1] = temp;

            heap.pop_back();
            sift_up(x);
            sift_down(x);
        }

        void heapify (int *array, int size) { // create a heap from an array of elements, needed for heap_sort
            heap.clear();
            heap.push_back(0); // new heap
            for (int i = 0; i < size; i++) {
                heap.push_back(array[i]);
            }

            for (int i = heap.size() / 2; i > 0; i--) {
                sift_down(i);
            }
        }

        int* heap_sort (int *array, int size) { // take an unsorted array and turn it into a sorted array in place using a max heap or min heap
            heapify(array, size);

            
            for (int i = size - 1; i >= 0; i--) {
                array[i] = extract_max(); // sort in ascending order 
            }
        }
};


// sorting

void merge (int *array, int low, int mid, int high) { // needed for mergesort
    // physically split into 2 subarrays
    int left_size = mid - low + 1; // include mid
    int right_size = high - mid; // don't include mid
    int* left = new int[left_size];
    int* right = new int[right_size];
    for (int i = 0; i < left_size; i++) { left[i] = array[low + i]; }
    for (int i = 0; i < right_size; i++) { right[i] = array[mid + 1 + i]; }

    int i = 0; // left (subarray)
    int j = 0; // right (subarray)
    int k = low; // array

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            array[k] = left[i]; // append to array to be returned 
            i++; // move left (subarray) pointer
        } else {
            array[k] = right[j];
            j++; // move right (subarray) pointer
        }
        k++;
    }
    
    // either left or right = empty
    while (i < left_size) { // append remaining to array to be returned 
        array[k] = left[i];
        i++;
        k++;
    }
    while (j < right_size) { 
        array[k] = right[j];
        j++;
        k++;
    }

    delete[] left; // delete temp arrays!
    delete[] right;
}

// recursive (pass in low/high)! 
int* mergesort (int *array, int low, int high) { // O(nlogn) worst/avg
    if (low < high) { // 0 or 1 elements = nothing to do
        int mid = low + (high - low) / 2;
        // feed in values for split into 2 subarrays
        mergesort(array, low, mid);
        mergesort(array, mid + 1, high);
        merge(array, low, mid, high); // sort each subarray
    }
    return array;
}

int partition (int* array, int low, int high) { // needed for quicksort 
    // median of three partitioning 
    int mid = low + (high - low) / 2;
    if (array[mid] < array[low])  { std::swap(array[mid], array[low]); }
    if (array[high] < array[low]) { std::swap(array[high], array[low]); }
    if (array[high] < array[mid]) { std::swap(array[high], array[mid]); } 

    // move pivot to end
    std::swap(array[mid], array[high]); 
    int pivot = array[high]; // save pivot value

    int i = low - 1; // pointer for elements <= pivot (start low - 1 since nothing confirmed yet)
    for (int j = low; j < high; j++) { // nothing actl changes until there is one where array[j] > pivot, then finally i != j
        if (array[j] <= pivot) {
            i++;
            std::swap(array[i], array[j]); // swap confirmed smaller elements to front
        }
    }
    std::swap(array[i + 1], array[high]); // swap pivot back to mid
    return i + 1; // return index of pivot
}

// recursive (pass in low/high)! 
int* quicksort (int* array, int low, int high) { // O(nlogn) avg = good pivot
    if (low < high) { // 0 or 1 elements = nothing to do
        int pivot = partition(array, low, high); // sort pivot into correct position
        quicksort(array, low, pivot - 1);
        quicksort(array, pivot + 1, high);
    }
    return array;
}

int* selectionsort (int* array, int size) { // O(n^2) worst/avg
    for (int i = 0; i < size - 1; i++) {
        int min = i;

        for (int j = i + 1; j < size; j++) { // find smallest in unsorted partition
            if (array[j] < array[min]) { min = j; }
        }

        if (min != i) { // swap smallest into position
            int temp = array[i];
            array[i] = array[min];
            array[min] = temp;
        }
    }
    return array;
}

int* insertionsort (int* array, int size) { // O(n^2) worst/avg
    for (int i = 0; i < size; i++) {
        int j = i;
        while (j > 0 && (array[j - 1] > array[j])) { // compare each item to items on its left and swap into position going left 
            int temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;
            j--;
        }
    }
    return array;
}


// graphs 

vector<vector<int>> list; // array of lists: list[u] = neighbours of u 
vector<bool> visited;
void recursive_adj_list_dfs (int start) {  // O(V + E) : visit all V and E once 
    visited[start] = true; 

    // enhanced for loop in c++
    for (int v : list[start]) { // iterate thru neighbours of u
        if (!visited[v]) { recursive_adj_list_dfs(v); } // call only returns when everyt reachable from it has been explored
    }
}

void iterative_adj_list_dfs (int start, int n) { // O(V + E) : visit all V and E once
    vector<bool> visited(n, false); // array of size n with all init to false 
    stack<int> stack;
    stack.push(start);
    visited[start] = true; 

    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();
    

        // auto keyword detects variable type !
        // rbegin (begin of reverse), rend (end of reverse): reverse list
        // ++i = return value after incr., i++ = return value before incr.
        for (auto i = list[u].rbegin(); i != list[u].rend(); ++i) { // reverse order and push rightmost in to stack first for backtrack! auto/rend etc. because list[u] = vector<int>
            int v = *i;

            if (!visited[v]) {
                visited[v] = true; 
                stack.push(v);
            }
        }
    }
}

vector<vector<int>> matrix; // 2d array: matrix[u][v] = 1 if edge exist
void recursive_adj_matrix_dfs (int u, int n) { // O(V^2) : matrix 
    visited[u] = true;

    for (int v = 0; v < n; v++) { // O(V) : scan entire row for neighbours 
        if (matrix[u][v] && !visited[v]) { recursive_adj_matrix_dfs(v, n); }
    }  
}

void iterative_adj_matrix_dfs (int start, int n) { // O(V^2) : matrix
    vector<bool> visited(n, false); // array of size n with all init to false 
    stack<int> stack;
    stack.push(start);
    visited[start] = true;

    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();

        for (int v = n - 1; v >= 0; v--) { // reverse order and push rightmost in to stack first for backtrack! count down instead of up because scan across row 
            if (matrix[u][v] && !visited[v]) {
                visited[v] = true;
                stack.push(v);
            }
        }
    }
}

#include <queue>
void adj_list_bfs (int start, int n) { // O(V + E) 
    vector<bool> visited(n, false);
    queue<int> queue; 
    queue.push(start);
    visited[start] = true;

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop(); // removes next elem in queue

        for (int v : list[u]) {
            if (!visited[v]) {
                visited[v] = true;
                queue.push(v);
            }
        }
    }
}

void adj_matrix_bfs (int start, int n) { // O(V^2)
    vector<bool> visited(n, false);
    queue<int> queue;
    queue.push(start);
    visited[start] = true; 

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();

        for (int v = 0; v < n; v++) {
            if (matrix[u][v] && !visited[v]) {
                visited[v] = true;
                queue.push(v);
            }
        }
    }
}

vector<int> dijkstra (int start, int n, vector<vector<pair<int,int>>>& list) { // adj list of (neighbour, weight) pairs for weighted graph O(E + VlogV)
    vector<int> dist(n, INT_MAX); // INT_MAX macro from limits.h = inf
    dist[start] = 0;

    //             elem type      underlying (alw array) comparator 
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> priorityqueue; // default comparator = less for maxheap. therefore use greater for minheap.
    priorityqueue.push({0, start});

    while (!priorityqueue.empty()) { // priorityqueue cannot update existing entry! instead, push new entry to update 
        auto [d, u] = priorityqueue.top();
        priorityqueue.pop();

        if (d > dist[u]) { continue; } // only process u once with its best distance! don't pay attention to bigger, stale duplicates

        for (auto [v, weight] : list[u]) {
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                priorityqueue.push({dist[v], v}); // push to end (bugger, stale duplicates at front, get popped and compared first)
            }
        }
    }

    return dist;
}

int prim_minimum_spanning_tree (int n, vector<vector<pair<int,int>>>& list) { // minimum spanning tree 
    vector<int> edge(n, INT_MAX); // cheapest edge so far to connect each node to tree
    vector<bool> in_tree(n, false); // tracks whether node in tree
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> priorityqueue;
    int total = 0;

    edge[0] = 0; // arbitrary start node
    priorityqueue.push({0, 0});

    while (!priorityqueue.empty()) {
        auto [w, u] = priorityqueue.top();
        priorityqueue.pop();

        if (in_tree[u]) { continue; } // ignore nodes already in tree even if cheapest edge 

        in_tree[u] = true; // mark visited
        total += w;

        for (auto [v, weight] : list[u]) {
            if (!in_tree[v] && weight < edge[v]) {
                edge[v] = weight;
                priorityqueue.push({edge[v], v});
            }
        }
    }

    return total;
}

enum State {UNVISITED, PROGRESS, FINISHED}; // mark exploration of specific paths to check for cycles
vector<State> state;
bool cycle_check_dfs (int u) { // needed before topological sort 
    state[u] = PROGRESS;  

    for (int v : list[u]) {
        if (state[v] == PROGRESS) { return true; } // neighbour has been visited prev but now we see it again = cycle !
        if (state[v] == UNVISITED && cycle_check_dfs(v)) { return true; } // recurse, return true to propagate upward if condition true = cycle found 
    }

    state[u] = FINISHED;
    return false;
}

stack<int> result;
void topological_dfs (int u) { // dfs = basis ! make sure no cycles via cycle_check before
    state[u] = PROGRESS;

    for (int v : list[u]) {
        if (state[v] == UNVISITED) { topological_dfs(v); }
    }

    state[u] = FINISHED;
    result.push(u); // record finish order as path explored
}
vector<int> topologicalsort (int n) { // cover all nodes' paths in graph 
    state.assign(n, UNVISITED); // resize array to n, reset all to UNVISITED
    
    for (int i = 0; i < n; i++) {
        if (state[i] == UNVISITED) { topological_dfs(i); }
    }

    vector<int> order;
    while (!result.empty()) { // reverse stack and output as array
        order.push_back(result.top());
        result.pop();
    }

    return order;
}


// recursion 

int factorial (int n) {
    if (n <= 1) { return 1; } // base case (stops recursion)
    return n * factorial(n - 1); // recursive subproblem
}

int fib (int n) { // unmemoized : inefficient 
    if (n <= 1) { return n; }
    return fib(n - 1) + fib(n - 2); // 2x recursive subcalls ! 
}

int fib_memoized (int n, vector<int>& memo) { // memoization : cache solved subproblems
    if (n <= 1) { return n; }
    if (memo[n] != -1) { return memo[n]; } // cached  
    return memo[n] = fib(n - 1, memo) + fib(n - 2, memo); // solve & cache
}