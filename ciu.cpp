// arrays

class Vector {
    private:
        int cap;
        int* ptr; // pointer to array[0] lives on stack, array itself lives on heap
        int sze;

        void resize (int new_capacity) {
            if (new_capacity / 4 == sze) { cap = cap / 2; } 
            else { cap = cap * 2; }
            int* new_ptr = new int[cap];

            for (int i = 0; i < sze; i++) {
                *(new_ptr + i) = *(ptr + i);
            }

            ptr = new_ptr;
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
            return (size == 0) ? true : false; // c++ uses ternary
        }

        int at (int index) {
            return *(ptr + index);
        }

        void push (int item) {
            if (sze + 1 == cap ) { resize(sze + 1); }
            *(ptr + sze) = item;
            sze++;
        }

        void insert (int index, int item) {
            if (sze + 1 == cap ) { resize(sze + 1); }
            for (int i = sze; i > index; i--) {
                *(ptr + i) = at(i - 1);
            }
            *(ptr + index) = item;
            sze++;
        }

        void prepend (int item) {
            insert(0, item);
        }

        int pop () {
            int tmp = at(sze - 1);
            *(ptr + sze - 1) = {};
            sze--;
            if (sze - 1 == cap / 4) { resize(sze - 1); }
            return tmp;
        }

        void del (int index) { // delete is a c++ keyword
            *(ptr + index) = {};
            for (int i = index; i < sze; i++) {
                *(ptr + i) = at(i + 1);
            }
            sze--;
        }

        void remove (int item) {
            for (int i = 0; i < sze - 1; i++) {
                if (at(i) == item) {
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