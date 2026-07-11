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

// binary search using recursion
int recursive_binary_search (const std::vector<int>&array, int target, int left, int right) {
    if (left > right) { return -1; } // base case 

    int mid = left + (right - left) / 2;

    if (array[mid] == target) { return mid; }
    else if (array[mid] < target) { return recursive_binary_search(array, target, mid + 1, right); }
    else { return recursive_binary_search(array, target, left, mid - 1); }
}

