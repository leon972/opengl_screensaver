/***********************************************
Interfaccia per i sistemi di equazioni lineari
Implementazione parziale dell'interfaccia LinearEquationsSet
code by L.Berti (c) 2009
 ************************************************/
/*!
 \file linearimpl.h
 \brief Base class for linear equations set. 
 
 */

#ifndef LINEARIMPL_H_INCLUDED
#define LINEARIMPL_H_INCLUDED

#include "ilinear.h"
#include "tvector.h"
#include "tmatrix.h"
#include "libmath.h"


namespace mathengine {

    /**
     * \brief Base class for a set of linear algebraic equations.
     */
    template<class T>class MATH_EXPORT LinearImpl : public virtual LinearEquationsSet<T> {

    public:

        bool solved;

        TMatrix<T> mat; //matrice dei coefficienti + colonna dei termini noti (matrice aumentata)
        //nota bene se n � il numero di eq. la matrice mat
        //ha n righe e n+1 colonne (comprende la colonna dei termini noti)
        TVector<T> res; //vettore dei risultati
        int rank;
        int n;

        /**
         * Swap equations with index e1 and eq2
         * @param eq1
         * @param eq2
         */
        inline void SwapEquations(int eq1, int eq2) {
            mat.swapRows(eq1, eq2);
        }

        /**
         * Swap equations in order that the diagonal coefficient are not zero
         * @param from_index
         */
        void ArrangeEquations(int from_index) throw (MathException) {

            {
                int j;

                for (int i = from_index; i < n; ++i) {
                    if (fabs(mat[i][i]) < EPSILON) {
                        //scambia con una eq. in cui l'elemento non � zero
                        for (j = from_index; j < n; ++j) {
                            if (i != j) {
                                if ((mat[j][i] != 0) && (mat[i][j] != 0)) {
                                    SwapEquations(j, i);
                                    break;
                                }
                            }
                        }
                    }

                    if (fabs(mat[i][i]) < EPSILON) throw MathException("cannot arrange equations (determinant may be zero)");
                }
            }

        }

        /**
         * Arrange equations in order to minimize the roundoff errors.
         * @param from_index
         */
        void ArrangeEquationsOpt(int from_index) throw (MathException) {
            {
                int j;
                REAL cmax;
                int cur_eq;

                for (int i = from_index; i < n; ++i) {
                    cmax = fabs(mat[i][i]);
                    cur_eq = i;

                    //esamina tutte le equazioni per trovare quella che ha il coeff. ajk maggiore
                    for (j = from_index; j < n; ++j) {
                        if (fabs(mat[j][i]) > cmax && fabs(mat[i][j]) > EPSILON) {
                            cmax = fabs(mat[j][i]);
                            cur_eq = j;
                        }
                    }

                    if (cur_eq != i) SwapEquations(cur_eq, i);

                    if (fabs(mat[i][i]) < EPSILON) throw MathException("cannot arrange equations (determinant may be zero)");
                }
            }
        }


    public:

        /**
         * Create a set of linear equations with eq_num equations.
         * @param eq_num numer of equations in the set.
         */
        LinearImpl(int eq_num) : mat(eq_num, eq_num + 1), res(eq_num) {
            solved = false;
            rank = 0;
            n = eq_num;
        }

        /**
         * Destructor
         */
        virtual ~LinearImpl() {

        }

        /**
         * Set the coefficients and right-hand member for an equation of the set.
         * @param eq_index index of equation (index of row in the matrix of coefficients)
         * @param coeff vector of coefficients (known members).Must have size EquationsCount
         * @param r known term of the equation.
         * @return the equation's index eq_index
         */
        virtual int SetEquation(int eq_index, const T* coeff, T r) throw (MathException) {

            if (eq_index < 0 || eq_index >= n) throw MathException("equation index out of bounds:the index must be between %d and % , actual value %d", 0, n - 1, eq_index);

            if (!coeff) throw MathException("invalid coefficients:null not allowed");

            for (int i = 0; i < n; ++i) mat[eq_index][i] = coeff[i];

            //imposta il termine noto
            mat[eq_index][n] = r;

            solved = false;

            return eq_index;

        }

        /**
         * Set the row of coefficients in the augmented matrix (known coefficients + right hand member)
         * @param eq_index index of row
         * @param adjcoeff coefficients + right hand member
         * @return  the index of row
         */
        virtual int SetEquation(int eq_index, const T* adjcoeff) throw (MathException) {

            if (!adjcoeff) throw MathException("invalid coefficients:null not allowed");

            mat.setRow(eq_index, adjcoeff);

            solved = false;

            return eq_index;

        }

        /**
         * Sets a coefficient in the coefficients matrix
         * @param eq_index equation index (index of row of the matrix)
         * @param column column index
         * @param coeff value of the coefficient
         * \warning this method doesn't perform bounds check
         */
        void SetCoefficient(T coeff,int eq_index,int column) throw () {

            mat[eq_index][column]=coeff;
            solved=false;
        }

        /**
         * Gets a coefficient from the coefficients matrix
         * @param eq_index equation index (index of row of the matrix)
         * @param column column index
         * @return the value of the coefficient
         * \warning this method doesn't perform bounds check
         */
        T GetCoefficient(int eq_index,int column) throw() {
            return mat[eq_index][column];
        }

        /**
         * Sets a value in the right hand knwown terms.
         * @param rhs value
         * @param eq_index
         * \warning this method doesn't perform bounds check
         */
        void setRhsValue(T rhs,int eq_index) throw () {
            mat[eq_index][n]=rhs;
            solved=false;
        }

        /**
         * Gets a value from the column of the known terms
         * @param eq_index index or equations
         * @return the value of the known term
         */
        T getRhsValue(int eq_index) throw () {
            return mat[eq_index][n];
        }

        /**
         * Set the coefficient matrix and right-hand column
         * @param coeff coefficient matrix
         * @param rhs right hand column (must have the same size as coeff)
         */
        virtual void SetEquations(const TMatrix<T>& coeff, const TVector<T>& rhs) throw (MathException) {

            if (coeff.getRows() != n || coeff.getColumns() != n) throw MathException("Invalid coefficients matrix,the matrix must be %d x %d, (actual %d x %d) ", n, n, coeff.getRows(), coeff.getColumns());
            if (rhs.size() != static_cast<size_t> (n)) throw MathException("Invalid rhs column");
            //copia la memoria da coeff a mat

            for (size_t r = 0; r < n; r++) {
                mat.setRow(r, coeff._getRowPtr(r), n);
            }

            //coefficients
            mat.setColumn(n, rhs._getDataPtr());

            solved=false;

        }

        /**
         * Set the right-hand members column (known members)
         * @param rhs
         */
        virtual void SetRightHandColumn(const TVector<T>& rhs) throw (MathException) {

            if (rhs.size() != static_cast<size_t> (n)) throw MathException("Invalid rhs column size:expected %d, actual %d", n, rhs.size());

            mat.setColumn(n, rhs._getDataPtr());

            solved=false;
        }

        /**
         * Get the number of equations in the set
         * @return
         */
        virtual int EquationCount() const {
            return n;
        }

        /**
         * Get the rank of the coefficients matrix.
         * @return
         */
        virtual int GetRank() const throw (MathException) {
            if (!solved) throw MathException("cannot evaluate rank:system not solved.");
            return rank;
        }

        /**
         * Return true if the set has been solved (after calling Solve method).
         * @return
         */
        virtual bool IsSolved() {
            return solved;
        }

        /**
         * Get the computed x value
         * @param eq_index index of result values
         * @return
         */
        virtual T GetX(int eq_index) const throw (MathException) {

            if (eq_index < 0 || eq_index >= n) throw MathException("cannot get the x%d result:index %d out of bounds (expected between 0 and %d)", eq_index, eq_index, n - 1);
            if (!solved) throw MathException("cannot get x%d :equations not solved", eq_index);

            return res[eq_index];
        }

        /**
         * Get the results vector.If the equations set is not solved throw and exception.
         *
         * @param result the vector where result is copied
         */
        virtual void GetResult(T* result) const throw (MathException) {

            if (!solved) throw MathException("equations not solved");
            if (!result) throw MathException("result vector is null");

            memcpy(result, res._getDataPtr(), sizeof (T) * n);
        }

        /**
         * Copy the results vector in res
         * @param res
         */
        virtual void GetResult(TVector<T>* res) const throw (MathException) {

            if (!solved) throw MathException("Error acquiring equations results:equations not solved yet");
            if (res == 0) throw MathException("Error acquiring equations results:destination vector is null");
            if (res->size() != n) throw MathException("Error acquiring equations results:destinazione vector must have size %d (actual %d)", n, res->size());

            *res = this->res;
        }

        /**
         * Get the results vector
         * @return
         */
        virtual TVector<T> GetResult() const throw (MathException) {

            if (!solved) throw MathException("Error acquiring equations results:equations not solved yet");
            return res;
        }

    };


};


#endif // LINEARIMPL_H_INCLUDED
