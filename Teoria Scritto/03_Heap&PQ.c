// Heap
void Heapify (int A[], int i, int heapsize) {
    int l, r, largest;
    
    l = LEFT(i);
    r = RIGHT(i);
    if (l < heapsize && A[l] > A[i])
        largest = l;
    else largest = i;
    
    if (r < heapsize && A[r] > A[largest])
        largest = r;
    
    if (largest != i) {
        Swap(A, i, largest);
        Heapify(A, largest, heapsize);
    }
    
    return;
}

// Heap Sort
void HeapSort (int A[], int heapsize) {
    int i;
    
    BuildHeap(A, heapsize);
    for (i = heapsize-1; i > 0; i--) {
        Swap(A, 0, i);
        heapsize--;
        Heapify(A, 0, heapsize);
    }
    
    return;
}

// PQUEUE insert
void PQinsert (PQ pq, int item) {
    int i;
    
    pq->heapsize++;
    
    while (i > 1 && pq->A[PARENT(i)] < item) {
        pq->A[i] = pg->A[PARENT(i)];
        i = (i-1)/2;
    }
    
    pq->A[i] = item;
    
    return;
}

// PQUEUE extract
int PQUEUEextractMax (PQ pq) {
    int item;
    
    Swap(pq, 0, pq->heapsize-1);
    item = pq->array[pq->heapsize-1];
    pq->heapsize--;
    Heapify(pq, 0);
    
    return item;
}

// PQUEUE change
void PQchange (PQ pq, int pos, int item) {
    while (pos >= 1 && pq->array[PARENT(pos)] < item) {
        pq->array[pos] = pq->array[PARENT(pos)];
        pos = (pos-1)/2;
    }
    
    pq->A[pos] = item;
    Heapify(pq, pos);
    
    return;
}
