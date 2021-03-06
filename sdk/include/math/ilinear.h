/***********************************************
Interfaccia per i sistemi di equazioni lineari
code by L.Berti (c) 2009
 ************************************************/
/*!
 \file ilinear.h
 * \brief Interface for a linear equations set
 */


#ifndef ILINEAR_H_INCLUDED
#define ILINEAR_H_INCLUDED

#include "mathdefs.h"
#include "libmath.h"
#include "mexception.h"
#include "tvector.h"
#include "tmatrix.h"

namespace mathengine {

    class Matrix;
    class MathException;

    /**
     *Solution optimizations
     */
    typedef enum {
        OPT_NONE = 0, /*!<- no optimization*/
        OPT_ROUNDOFFS = 1, /*!<- minimize roundoff errors*/
        OPT_DONTARRANGE_MATRIX = 2 /*!<- do not arange equations before solving*/

    } OPTIMIZE_FLAGS;

    /**
     * Interface for linear algebraic set of equations
     */
    template<class T> class LinearEquationsSet {
    public:

        /**
         * Set the coefficients and right-hand member for an equation of the set.
         * @param eq_index index of equation (index of row in the matrix of coefficients)
         * @param coeff vector of coefficients (known members).Must have size EquationsCount
         * @param rhs right-hand member
         * @return the equation's index eq_index
         */
        virtual int SetEquation(int eq_index, const T* coeff, T rhs) throw (MathException) = 0;

        /**
         * Destructor
         * @param eq_index
         * @param adjcoeff
         * @return
         */
        virtual ~LinearEquationsSet() {
        };


        /**
         * Set the row of coefficients in the augmentmat(eq_num,eq_num+1,true),res(eq_num)ed matrix (known coefficients + right hand member)
         * @param eq_index index of row
         * @param adjcoeff coefficients + right hand member
         * @return  the index of row
         */
        virtual int SetEquation(int eq_index, const T* adjcoeff) throw (MathException) = 0;

        /**
         * Set the coefficient matrix and right-hand column
         * @param coeff coefficient matrix
         * @param rhs right hand column (must have the same size as coeff)
         */
        virtual void SetEquations(const TMatrix<T>& coeff, const TVector<T>& rhs) throw (MathException) = 0;

        /**
         * Set the right-hand members column (known members)
         * @param rhs
         */
        virtual void SetRightHandColumn(const TVector<T>& rhs) throw (MathException) = 0;

        /**
         * Sets a coefficient in the coefficients matrix
         * @param eq_index equation index (index of row of the matrix)
         * @param column column index
         * @param coeff value of the coefficient
         * \warning this method doesn't perform bounds check
         */
        virtual void SetCoefficient(T coeff, int eq_index, int column) throw () = 0;
        
        /**
         * Gets a coefficient from the coefficients matrix
         * @param eq_index equation index (index of row of the matrix)
         * @param column column index
         * @return the value of the coefficient
         * \warning this method doesn't perform bounds check
         */
        virtual T GetCoefficient(int eq_index, int column) throw () = 0;

        /**
         * Sets a value in the right hand knwown terms.
         * @param rhs value
         * @param eq_index
         * \warning this method doesn't perform bounds check
         */
        virtual void setRhsValue(T rhs, int eq_index) throw () = 0;

        /**
         * Gets a value from the column of the known terms
         * @param eq_index index or equations
         * @return the value of the known term
         */
        virtual T getRhsValue(int eq_index) throw () = 0;

        /**
         * Get the number of equations in the set
         * @return
         */
        virtual int EquationCount() const = 0;

        /**
         * Get the rank of the coefficients matrix.
         * @return
         */
        virtual int GetRank() const throw (MathException) = 0;

        /**
         * Solve the equations.
         * @throw MathException if the equations can not be solved.
         */
        virtual void Solve() throw (MathException) = 0;

        /**
         * Solve the equations.
         * @param opt optimizations flags (OPT_NONE,OPT_ROUNDOFFS=1,OPT_DONTARRANGE_MATRIX)
         */
        virtual void Solve(int opt) throw (MathException) = 0;

        /**
         * Return true if the set has been solved (after calling Solve method).
         * @return
         */
        virtual bool IsSolved() = 0;

        /**
         * Get the computed x value
         * @param eq_index index of result values
         * @return
         */
        virtual T GetX(int eq_index) const throw (MathException) = 0;

        /**
         * Get the results vector.If the equations set is not solved throw and exception.
         *
         * @param result the vector where result is copied
         */
        virtual void GetResult(T* result) const throw (MathException) = 0;

        /**
         * Copy the results vector in res
         * @param res
         */
        virtual void GetResult(TVector<T>* res) const throw (MathException) = 0;

        /**
         * Get the results vector
         * @return
         */
        virtual TVector<T> GetResult() const throw (MathException) = 0;
    };


};


#endif // ILINEAR_H_INCLUDED
