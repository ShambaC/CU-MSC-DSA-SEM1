#include <stdio.h>

void transpose(int row, int col, int nz, int rows[], int cols[], int values[]) {
	int i,j;
	
    for ( i = 0; i < nz; i++) {
        int temp = rows[i];
        rows[i] = cols[i];
        cols[i] = temp;
    }

    for ( i = 0; i < nz - 1; i++) {
        for (j = 0; j < nz - i - 1; j++) {
            if (rows[j] > rows[j + 1] || (rows[j] == rows[j + 1] && cols[j] > cols[j + 1])) {
                
                int temp = rows[j];
                rows[j] = rows[j + 1];
                rows[j + 1] = temp;

                
                temp = cols[j];
                cols[j] = cols[j + 1];
                cols[j + 1] = temp;

                
                temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }
}

int main() {
    int row, col,i,matrix[20][20],j;

    
    printf("Enter the number of rows and columns of the matrix: ");
    scanf("%d %d", &row, &col);

    
    printf("Enter the number of non-zero elements in the matrix: ");
    int nz;
    scanf("%d", &nz);


    int rows[nz], cols[nz], values[nz];
    
    printf("\nEnter the matrix:\n");
    for(i=0;i<row;i++){
    	for(j=0;j<col;j++){
    		scanf("%d",&matrix[i][j]);
		}
	}

    
    int k = 0;
    for (i = 0; i < row; ++i) {
        for ( j = 0; j < col; ++j) {
            if (matrix[i][j] != 0) {
                rows[k] = i;
                cols[k] = j;
                values[k] = matrix[i][j];
                k++;
            }
        }
    }
    
    //Display the original sparse matrix
    printf("\nSparse Matrix Representation:\n\n");
    printf("Row\tColumn\tValue\n");
    for (i = 0; i < nz; ++i) {
        printf("%d\t%d\t%d\n", rows[i], cols[i], values[i]);
    }
    
    


    // Transpose the matrix in lexicographic order
    transpose(row, col, nz, rows, cols, values);

    // Display the transposed matrix
    printf("\n\nTransposed matrix in lexicographic order:\n\n");
     printf("Row\tColumn\tValue\n");
    for (i = 0; i < nz; i++) {
        printf("%d\t%d\t%d\n", rows[i], cols[i], values[i]);
    }

    return 0;
}

