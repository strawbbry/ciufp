// array

int cap;
int size;
int* arr;

void resize(int c) {
    a = new int[c];
    for (int i = 0; i < size; i++) {
        a[i] = arr[i];
    }
    delete[] arr;
    arr = a; 
    cap = c; 
}

if (size == cap) { resize(cap * 2); }         // grow 
if (size == (cap / 4)) { resize(cap / 2); }   // shrink 


// linkedlist 

node *prev = nullptr;
node *curr = head;

for (int i = 0; i < index; i++) { 
    prev = curr;
    curr = curr->next;
}

(
    prev->next = in;       // insert @ index
    in->next = curr;
)
prev->next = curr->next;   // delete @ index