#ifndef RESIDUALS_H
#define RESIDUALS_H

#include "../Matrix/DenseMatrix.h"
#include "../Vector/DenseVector.h"
#include "../Ops/serial/DVOps.h"

template<typename Matrix, typename Vector>
class Residuals {

    public: 
        Vector residual(const Matrix& A, const Vector& b, const Vector& x);

        double L1MatMul(const Matrix& A, const Vector& b, const Vector& x);

};

template<>
class Residuals<DenseMatrix, DenseVector> {

    public: 
        DenseVector residual(const DenseMatrix& A, const DenseVector& b, const DenseVector& x);

        double L1MatMul(const DenseMatrix& A, const DenseVector& b, const DenseVector& x);

};

#endif