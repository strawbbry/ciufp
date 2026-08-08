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


// hashtable 

entry* table;
int i = hash(key, cap);

while (table[i].occupy || table[i].tombstone) {
    if (table[i].occupy && table[i].key == key) { return; }
    else { i = (i + 1) % cap; }
}


// dfs

vector<vector<int>> list;    // list of lists 
vector<vector<int>> matrix;  // 2d matrix 

vector<bool> visited; 

void dfs (int root) {
    visited[root] = true;

    // adj. list 
    for (int neighbour : list[root]) {                                           
        if (!visited[neighbour]) { dfs(neighbour); }
    }

    // adj. matrix 
    for (int neighbour = 0; neighbour < len(matrix); neighbour++) {
        if (matrix[root][neighbour] && !visited[neighbour]) { dfs(neighbour); }
    }
}


// bfs 

vector<vector<int>> list;    // list of lists 
vector<vector<int>> matrix;  // 2d matrix 

void bfs (int root) {
    queue<int> queue; 
    vector<bool> visited; 

    queue.push(root);
    visited[root] = true;

    while (!queue.empty()) {
        int q = queue.front();

        queue.pop();

        // adj. list
        for (int neighbour : list[q]) {
            if (!visited[neighbour]) {
                visited[neighbour] = true;
                queue.push(neighbour);
            }
        }

        // adj. matrix
        for (int neighbour = 0; neighbour < len(matrix); neighbour++) {
            if (matrix[q][neighbour] && !visited[neighbour]) {
                visited[neighbour] = true;
                queue.push(neighbour);
            }
        }
    }
}


// mergesort 

// sort pairs 
void merge (int *array, int low, int mid, int high) {  
    for (int i = 0; i < (mid - low + 1); i++) { left[i] = array[low + i]; }   
    for (int i = 0; i < (high - mid); i++) { right[i] = array[mid + 1 + i]; }   

    int i = 0;    // left
    int j = 0;    // right 
    int k = low;  // array

    while (i < len(left) && j < len(right)) {
        if (left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        } 
        else {
            array[k] = right[j];
            j++;
        }
    }

    while (i < len(left)) {
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < len(right)) {
        array[k] = right[j];
        j++;
        k++;
    }
}

int* mergesort (int *array, int low, int high) {
    if (low < high) {
        // recursion on left, right 
        merge(array, low, mid, high);
    }
}


// quicksort

int partition (int *array, int low, int high) {
    int pivot = array[mid;]
    std::swap(array[mid], array[high]);       // pivot to end 

    int i = low - 1;   
    
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            std::swap(array[i], array[j]);    // real swap if i != j
        }
    }

    std::swap(array[i + 1], array[high]);     // pivot to pos 

    return i + 1;                             // pivot index 
}

int* quicksort (int *array, int low, int high) {
    if (low < high) {
        int pivot = partition(array, low, high);
        // recursion on pivot left, pivot right 
    }
}