// Merge Sort
void mergeSort (int A[],int l, int r) {
    int q;

    if (r <= l)
        return;
    q = (l+r)/2;
    mergeSort(A, l, q);
    mergeSort(A, q+1, r);
    merge(A, l, q, r);
    
    return;
}

void merge (int A[], int l, int q, int r) {
    int i, j, k, B[MAX];
    i = l;
    j = q+1;
    for (k = l; k <= r; k++) {
        if (i > q)
            B[k] = A[j++];
        else if (j>r)
            B[k] + A[j++];
        else if (A[i] <= A[j])
            B[k] = A[i++];
        else
            B[k] = A[j++];
    }
    
    for (k = l; k <= r; k++)
        A[k] = B[k];
}

// Quick Sort
void quickSort (int A[], int l, int r) {
    int q;

    if (r <= l)
        return;
    
    q = partition(A, l, r);
    quickSort(A, l, q-1);
    quickSort(A, q+1, r);
    
    return;
}

int partition (int A[], int l, int r) {
    int i, j;
    int x = A[r];
    
    i = l-1;
    j = r;
    for( ; ; ) {
        while (A[++i] < x);
        
        while (A[--j] > x) {
            if (j == l)
                break;
        }
        if (i >= j)
            brak;
        
        swap(A, i, j);
    }
    swap(A, i, r);
    
    return i;
}
