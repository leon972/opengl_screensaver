/********************************************
Soluzione di un sistema di eq. lineari usando
il metodo di riduzione di Crout
code by L.Berti (c) 2009
 *********************************************/
/*!
 \file crout.h
 \brief Numerical solution of linear equations and matrix inversion with the Crout reduction method.
 */


#ifndef CROUT_H_INCLUDED
#define CROUT_H_INCLUDED

#include "libmath.h"
#include "linearimpl.h"
#include "tmatrix.h"
#include <vector>

namespace mathengine {

    using namespace std;

    /**
     * Solve a set of linear algebraic equations using Crout reduction.
     * The Crout reduction is useful to investigate the variation of the result vector
     * when the right-hand members changes.
     * This method may also be used to compute the inverse matrix of aij and the determinant of aij.
     */

    template<class T> class LinearEqCrout : public LinearImpl<T> {
    public:

        /**
         * Performs the Crout reduction of matrix mat and copy the result in a.
         * @param a destination matrix with n rows and n columns at least.
         * @param mat source matrix with n rows and n columns at least.
         * @param n number of rows and columns of submatrix.
         */
        static void CroutReduction(TMatrix<T>& a, const TMatrix<T>& mat, int n) throw (MathException) {

            if (a.getRows() < n || a.getColumns() < n) throw MathException("invalid destination matrix size.");
            if (mat.getRows() < n || mat.getColumns() < n) throw MathException("invalid source matrix size.");

            register int i, j, k;
            REAL t;
            REAL inv;

            //resetta la matrice ausiliaria
            a.zeroMemory();

            for (j = 0; j < n; ++j) {
                //calcola la colonna di
                //elementi sotto (o coincidenti) la diagonale
                //i=indice riga, j=colonna
                for (i = j; i < n; ++i) {
                    t = 0;
                    //prodotto scalare della riga e colonna nella matrice ausiliaria
                    for (k = 0; k < i; ++k) {
                        t += a[i][k] * a[k][j];
                    }

                    a[i][j] = mat[i][j] - t;
                }

                if (fabs(a[j][j]) < EPSILON) throw MathException("cannot solve.");

                inv = 1 / a[j][j];

                //calcola la riga di
                //elementi alla destra della diagonale
                //i=indice colonna,j=riga
                for (i = j + 1; i < n; ++i) {
                    t = 0;

                    for (k = 0; k < i; ++k) t += a[k][i] * a[j][k];

                    a[j][i] = mat[j][i] - t;

                    a[j][i] *= inv;
                }
            }

        }

        /**
         * Computes the inverse matrix
         * @param dest destination matrix where the invers of src is copied.
         * @param src matrix to be inverted.
         */
        static void InvertMatrix(TMatrix<T>& dest, const TMatrix<T>& src) throw (MathException) {

            /*
        La matrice inversa di una matrice A � una matrice A~ tale che A*A~=I
        si dimostra che la matrice A~ � costituita dagli elementi A~ij
        per cui A~ij = cofattore dell'elemento ij in A / determinante di A
        Il cofattore di un elemento Aij � il determinante della matrice che si
        ottiene eliminando la riga i e la colonna j da A moltiplicato per (-1) ^ (i+j)
        Ogni colonna Xk della matrice inversa A~ si ottiene come colonna soluzione del sistema
        A*Xk=Ck dove Ck � un vettore che il k-esmimo elemento settato a 1 e tutti gli altri settati a zero*/

            if (src.getRows() != dest.getRows()) throw MathException("Cannot determinate the inverse matrix.Matrices have different size.");

            int n = src.getRows();

            LinearEqCrout eqset(n);

            TVector<T> d(n);

            eqset.SetEquations(src, d);

            for (int i = 0; i < n; ++i) {
                //ricava la colonna i della matrice inversa
                d.zeroMemory();

                d[i] = 1;

                eqset.SetRightHandColumn(d);

                eqset.Solve();

                eqset.GetResult(&d);

                dest.setColumn(i, d);
            }

        }

        /**
         * Calculates the determinant of matrix m
         * @param m
         * @return the determinant of square matrix m computed with Crout reduction
         */
        static T GetDeterminant(const TMatrix<T>& m) throw (MathException) {

            /*il determinante della matrice � il prodotto degli elementi
              della diagonale della matrice ridotta con il metodo di Crout*/

            int n = m.getRows();

            TMatrix<T> aux(n,n,false);

            REAL det = 0;

            try {

                //ottiene la matrice ridotta
                CroutReduction(aux, m, n);

                det = aux[0][0];

                for (int i = 1; i < n; ++i) det *= aux[i][i];

                return det;

            } catch (MathException& e) {
                //un elemento sulla diagonale � zero quindi � zero anche il determinante
                return 0;
            }
        }

        /**
         * Construct a set of linear equations to be solved with Crout method.
         * @param eq_num number of equations
         */
        LinearEqCrout(int eq_num) :LinearImpl<T>(eq_num),a(eq_num, eq_num + 1, true), invalid_aux_matrix(true), ref(0) {
            
        }

        virtual ~LinearEqCrout() {
            if (ref) delete ref;
        }

        /**
         * Set the coefficients and right-hand member for an equation of the set.
         * @param eq_index index of equation (index of row in the matrix of coefficients)
         * @param coeff vector of coefficients (known members).Must have size EquationsCount
         * @param rhs right-hand member
         * @return the equation's index eq_index
         */
        virtual int SetEquation(int eq_index, const T* coeff, T rhs) throw (MathException) {
            invalid_aux_matrix = true;
            LinearImpl<T>::solved=false;
            return LinearImpl<T>::SetEquation(eq_index, coeff, rhs);
        }

        /**
         * Checks if the current coefficients matrix has been reduced.
         * If the matrix is reduced,and the rhs changed, the system can be solved without
         * recomputing the reduced matrix.
         *
         * @return true if the matrix has benne reduced
         */
        bool isMatrixReduced() const throw(){
            return !invalid_aux_matrix;
        }

        /**
         * Set the row of coefficients in the augmented matrix (known coefficients + right hand member)
         * @param eq_index index of row
         * @param adjcoeff coefficients + right hand member
         * @return  the index of row
         */
        virtual int SetEquation(int eq_index, const T* adjcoeff) throw (MathException) {
            invalid_aux_matrix = true;
            LinearImpl<T>::solved=false;
            return LinearImpl<T>::SetEquation(eq_index, adjcoeff);
        }

        /**
         * Set the coefficient matrix and right-hand column
         * @param coeff coefficient matrix
         * @param rhs right hand column (must have the same size as coeff)
         */
        virtual void SetEquations(const TMatrix<T>& coeff, const TVector<T>& rhs) throw (MathException) {
            invalid_aux_matrix = true;
            LinearImpl<T>::solved=false;
            LinearImpl<T>::SetEquations(coeff, rhs);
        }

        /**
         * Arrnage equations in order to eliminate zero elements on diagonal.
         * @param from_index index from wich the arrange procedure is run.
         */
        virtual void ArrangeEquations(int from_index) throw (MathException) {

            int j;
            int i = from_index;
            int temp;


            if (fabs(LinearImpl<T>::mat[i][i]) < EPSILON) {

                //scambia con una eq. in cui l'elemento non e' zero
                for (j = from_index + 1; j < LinearImpl<T>::n; ++j) {

                    if ((fabs(LinearImpl<T>::mat[j][i]) > EPSILON) && (fabs(LinearImpl<T>::mat[i][j]) > EPSILON)) {
                        LinearImpl<T>::SwapEquations(j, i);
                        temp = ref->at(j);
                        ref->at(j) = ref->at(i);
                        ref->at(i) = temp;
                        break;
                    }
                }
            }

            if (fabs(LinearImpl<T>::mat[i][i]) < EPSILON) throw MathException("cannot arrange equations (determinant may be zero)");

            invalid_aux_matrix=true;
            LinearImpl<T>::solved=false;

        }

        /**
         * Set the right-hand coefficient column.
         * @param rhs
         */
        virtual void SetRightHandColumn(const TVector<T>& rhs) throw (MathException) {

            if (rhs.size() != static_cast<size_t> (LinearImpl<T>::n)) throw MathException("Invalid rhs column expected size %d , actual %d",LinearImpl<T>::n, rhs.size());

            if (ref == 0) LinearImpl<T>::mat.setColumn(LinearImpl<T>::n, rhs);

            else {
                //quando si imposta questa colonna si deve controllare se nel calcolo della
                //matrice ausiliaria sono state scambiate delle equazioni
                for (int i = 0; i < LinearImpl<T>::n; ++i) {
                    LinearImpl<T>::mat[ref->at(i)][LinearImpl<T>::n] = rhs[i];
                }
            }

            LinearImpl<T>::solved=false;
        }

        /**
         * Solve the equations.
         * @throw MathException if the equations can not be solved.
         */
        virtual void Solve() throw (MathException) {
            Solve(OPT_NONE);
        }

        /**
         * Solve the equations.
         * @param opt optimizations flags (OPT_NONE,OPT_ROUNDOFFS=1,OPT_DONTARRANGE_MATRIX)
         */
        virtual void Solve(int opt) throw (MathException) {

            bool opt_roundoffs;
            register int i, j, k;
            int _n=LinearImpl<T>::n; //numero di equazioni nel sistema
            TMatrix<T> &_mat=LinearImpl<T>::mat; //matrice coefficienti
            TVector<T> &_res=LinearImpl<T>::res; //vettore dei risultati

            //nota: con il metodo di crout in generale non occorre riposizionare
            //le righe se alcuni elementi della diagonale sono zero
            //vanno invece riposizionate se mat[0][0] � zero
            if (!(opt & OPT_DONTARRANGE_MATRIX)) {

                if (invalid_aux_matrix) {
                    if (!ref) ref = new vector<int>(_n);

                    for (i = 0; i < _n; ++i) ref->at(i) = i;
                }

                opt_roundoffs = false;
                ArrangeEquations(0);
            }


            T t;
            T inv;

            //la matrice ausiliaria viene ricalcolata solo se sono variati i coefficienti
            //questo consente di risolvere il sistema molto velocemente se varia solo la colonna dei termini noti
            //es. quando si studia coma varia la soluzione al variare dei termini noti
            //se si riarrangiano le equazioni la matrice va invalidata
            if (invalid_aux_matrix) {
                LinearEqCrout::CroutReduction(a, _mat, _n);
                invalid_aux_matrix = false;
            } else {
                //deve azzerare la colonna dei termini noti nella matrice a
                for (i = 0; i < _n; ++i) a[i][_n] = 0;
            }

            //esegue la riduzione sulla colonna dei termini noti
            for (j = 0; j < _n; ++j) {
                inv = 1 / a[j][j];

                t = 0;
                for (k = 0; k < j; ++k) t += a[j][k] * a[k][_n];
                a[j][_n] = _mat[j][_n] - t;
                a[j][_n] *= inv;
            }

            //ricava la soluzione
            for (i = _n - 1; i >= 0; --i) {
                t = 0;

                for (k = i + 1; k < _n; ++k) {
                    t += a[i][k] * _res[k];
                }

                _res[i] = a[i][_n] - t;
            }

            LinearImpl<T>::solved = true;
        }

        /**
         * Get the auxiliary matrix (Crout reduction matrix)
         * \warning returns a reference to an internal matrix.
         * @return
         */
        const TMatrix<T>& GetAuxMatrix() throw (MathException) {
            if (!LinearImpl<T>::solved) throw MathException("not solved yet");
            return a;
        }

        /**
         * Get the augmented matrix.
         * \warning returns a reference to an internal matrix.
         * @return the matrix of coefficients + right hand members. (nxn+1 matrix)
         */
        const TMatrix<T>& GetAugmentedMatrix() throw (MathException) {
            return LinearImpl<T>::mat;
        }

    private:

        //matrice ausiliaria usata nel calcolo
        TMatrix<T> a;
        //flag chi indica che la matrice dei coefficienti � cambiata e quindi si deve ricalcolare la matrice
        //ausiliaria
        bool invalid_aux_matrix;
        vector<int>* ref;

    };
};



#endif // CROUT_H_INCLUDED
