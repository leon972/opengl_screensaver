/********************************************
Soluzione di un sistema di eq. lineari usando
il metodo di Gauss
code by L.Berti (c) 2009
 *********************************************/
/*!
 * \file gauss.h
 * \brief Numerical solution of linear equations with the Gauss method.
 
 */

#ifndef GAUSS_H_INCLUDED
#define GAUSS_H_INCLUDED

#include "libmath.h"
#include "linearimpl.h"
#include "tmatrix.h"
#include <vector>


namespace mathengine {


    using namespace std;

    /**
     * Solve a set of linear algebraic equations with the Gauss method.
     */
    template<class T> class MATH_EXPORT LinearEqGauss : public LinearImpl<T> {
        
    public:

        /**
         * Construct the set
         * @param n number of eqautions
         */
        LinearEqGauss(int eq_num) throw (MathException) : LinearImpl<T>(eq_num) {

            if (eq_num <= 0) throw MathException("invalid equation number");

        }

        /**
         * Destructor
         */
        virtual ~LinearEqGauss() {
        }

        /**
         * Solve the equations with the Gauss method
         * using the default options (OPT_NONE).
         * Equations are arranged before solving in order to minimize roundoff errors.
         * This method calculates also the rank of the system.
         */
        void Solve() throw (MathException) {
            Solve(OPT_NONE);
        }

        /**
         * Solve the eqautions with the Gauss method
         * @param opt optimizations options:
         * OPT_DONTARRANGE_MATRIX : do not arrange equations in order to minimize roundoff errors
         * OPT_ROUNDOFFS : additional optimiziation to minimize roundoff errors
         * This method calculates also the rank of the system.
         */
        void Solve(int opt) throw (MathException) {

            int _n=LinearImpl<T>::n; //numero di equazioni nel sistema
            TMatrix<T> &_mat=LinearImpl<T>::mat; //matrice coefficienti
            TVector<T> &_res=LinearImpl<T>::res; //vettore dei risultati

            bool opt_roundoffs;

            if (!(opt & OPT_DONTARRANGE_MATRIX)) {
                //fa in modo che gli elementi sulla diagonale non siano zero
                if (opt & OPT_ROUNDOFFS) {
                    opt_roundoffs = true;
                    LinearImpl<T>::ArrangeEquationsOpt(0);
                } else {
                    opt_roundoffs = false;
                    LinearImpl<T>::ArrangeEquations(0);
                }
            }

            int i, j, k;
            T t;

            LinearImpl<T>::rank = 0;

            for (i = 0; i < _n; ++i) {
                t = 1 / _mat[i][i];
                _mat[i][i] = 1;
                //divide la riga per l'elemento della diagonale
                for (k = i + 1; k <= _n; ++k) {
                    _mat[i][k] *= t;
                }

                //elimina xi dalle equazioni restanti
                for (j = i + 1; j < _n; ++j) {
                    t = _mat[j][i];

                    //il coeff. di xi nell'eq. k viene posto a zero per via dell'eliminazione
                    _mat[j][i] = 0;

                    for (k = i + 1; k <= _n; ++k) {
                        _mat[j][k] = _mat[j][k] - _mat[i][k] * t;
                    }
                }

                //fa in modo che non ci siano zeri nella diagonale delle eq. restanti
                if (opt_roundoffs) {
                    LinearImpl<T>::ArrangeEquationsOpt(i + 1);
                } else {
                    LinearImpl<T>::ArrangeEquations(i + 1);
                }

                ++LinearImpl<T>::rank; //calcola il rango della matrice
            }

            //a questo punto procede a ritroso per ricavare i risultati
            for (i = _n - 1; i >= 0; --i) {
                t = 0;

                for (k = i + 1; k < _n; ++k) {
                    t += _res[k] * _mat[i][k];
                }

                _res[i] = _mat[i][_n] - t;
            }

            LinearImpl<T>::solved = true;
        }
    };
};

#endif // GAUSS_H_INCLUDED
