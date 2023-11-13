#include "GaussianEliminationOMP.h"

DenseVector GaussianEliminationOMP::solver(DenseMatrix& A, DenseVector& b){
    
    elimination(A, b);

    return backsub(A, b);
    
}

void GaussianEliminationOMP::elimination(DenseMatrix& A, DenseVector& b){

    int ARows = A.numRows();
    int ACols = A.numCols();
    int bLen = b.getLen();

    for (int i=0; i<ARows; i++){

        #pragma omp parallel for
        for (int j=i+1; j<ARows; j++){
            double ratio = A(j,i) / A(i,i);
            for (int k=i; k<ACols; k++){
                A(j,k) = A(j,k) - ratio*A(i,k);
            }
            b(j) = b(j) - ratio*b(i);
        }
    }
}

DenseVector GaussianEliminationOMP::backsub(DenseMatrix& Aaug, DenseVector& baug){

    int ARows = Aaug.numRows();
    int ACols = Aaug.numCols();
    int bLen = baug.getLen();

    DenseVector x(std::vector<double>(bLen, 0));


    for (int i=ARows-1; i>=0; i--){
        double uNew = baug(i);

        #pragma omp parallel for reduction(-:uNew)
        for (int j=ACols-1; j>=0; j--){
            if (j!=i){
                uNew -= Aaug(i,j) * x(j);
            }
        }
        x(i) = uNew / Aaug(i,i);
    }

    return x;
}