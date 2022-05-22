// Insertion Sort
void insertionSort (int *A, int r) {
    int i, j, x;

    for (i = l; i <= r; i++) {
        x = A[i];
        j = i - 1;
        while (j >=  l && x < A[j]) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = x;
    }
    return;
}

// Exchange Sort
void exchangeSort (int *A, int r) {
    int i, j, tmp;

    for (i = l; i < r; i++) {
        for (j = 0; j< r-i; j++) {
            if (A[j] > A[j+1]) {
                tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
            }
        }
    }
    return;
}

// Selection Sort
void selectionSort(int *A, int r) {
    int i, j, min, tmp;

    for (i = l; i < r; j++) {
        min = i;
        for ( j = i+1; j <= r; j++) {
            if (A[j] < A[min])
                min = j;
        }
        tmp = A[i];
        A[i] = A[min];
        A[min] = tmp;
    }
    return;
}

// Shell Sort
void shellSort (int *Al, int l, int r) {
    int i, j, tmp, h, n;
    h = l;
    n = r-l+1;

    while (h<(n/3))
        h = 3*h+1;

    while (h >= 1) {
        for (i = h; i <= r; i++) {
            j = i;
            for (j = i; j >= h && A[j]< A[j-h]; j -= h) {
                tmp = A[j];
                A[j] = A[j-h];
                A[j-h] = tmp;
            }
        }
        h = h/3;
    }
    return;
}

// Counting Sort
void countingSort (int *A, int l, int r, int k) {
    int i, n, *B, *C;
    n = r - l +1;
    B = malloc(n*sizeof(int));
    C = malloc(k*sizeof(int));

    for ( i = 0; i < k; i++)
        C[i] = 0;

    for (i = l ; i <= r; i++)
        C[A[i]]++;
    
    for (i = 1; i < k; i++)
        C[i] += C[i-1];

    for (i = r; i >= l; i--) {
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }

    for (i = l; i <= r; i++)
        A[i] = B[i];
    return;
}