/***************************************
 Generic template-based numeric matrix
 Code by L.Berti (c) 2011
 ****************************************/
/*!
 * \file tmatrix.h
 * \brief Generic NxM (N rows M columns) template-base matrix class.
 */

#ifndef TMATRIX_H_INCLUDED
#define TMATRIX_H_INCLUDED

#include "math/mathdefs.h"
#include "libmath.h"
#include "tvector.h"
#include <stddef.h>
#include <iostream>

namespace mathengine {

    /**
     * unused constant:doxygen trick
     */
    const int zero = 0;

    /**
     * Template-based nxm matrix.
     * Implements all basic operators (addition,subtrction,multiplication)
     * and elements accessing methods.
     * Example:
     * ------------------------------------------------------------------
     * \code
     *  TMatrix<double> m(3, 3); //creates a 3x3 numeric matrix of type double *
     *
     *  m[0][0]=1; //sets some elements
     *  m[0][1]=2;
     *  m[0][2]=3;
     *
     *  cout<<"m="<<endl<<m<<endl; //display the matrix
     *
     * TMatrix<double> m1(3,3);
     *
     *  m1.setDiagonal(6); //sets all elements on the diagonal
     *
     *  TMatrix<double> res(3,3);
     *
     *  res=m*m1; //matrix multiplication
     *  m+=res;   //matrix addition
     * 
     * \endcode
     * ------------------------------------------------------------------
     *
     */
    template <class T> class TMatrix {
    public:

        /**
         * Creates a marix with nrows rows and ncolumns columns
         * @param nrows number of rows
         * @param ncolumns number of columns
         */
        TMatrix(size_t nrows, size_t ncolumns) : data(0), nRows(nrows), nColumns(ncolumns), nsize(0) {
            resize(nrows, ncolumns, true);
        }

        /**
         * Creates a marix with nrows rows and ncolumns columns
         * @param nrows number of rows
         * @param ncolumns number of columns
         * @param clearMemory if set, reset the internal memory of the matrix
         */
        TMatrix(size_t nrows, size_t ncolumns, bool clearMemory) : data(0), nRows(nrows), nColumns(ncolumns), nsize(0) {
            resize(nrows, ncolumns, clearMemory);
        }

        virtual ~TMatrix() {
            if (data) {
                delete[] data;
                data = 0;
            }
        }

        /**
         * Assignment operator.
         * If m ha the same size of this matrix,elements of m are copied thos this matrix
         * otherwise,this matrix is reallocated to fit the size of m and elements are copied from m.
         * @param m
         * @return
         */
        TMatrix<T> & operator=(const TMatrix<T> &m) {

            if (m.nsize == nsize) {

                if (&m == this) return *this;

                memcpy(data, m.data, sizeof (T) * nsize);

            } else {
                resize(m.getRows(), m.getColumns(), false);
                memcpy(data, m.data, sizeof (T) * nsize);
            }

            return *this;
        }

        /**
         * Sets all elements to v
         * @param v value
         * @return this matrix
         */
        TMatrix<T> & operator=(const T &v) {

            for (size_t i = 0; i < nsize; i++) {
                data[i] = v;
            }
        }

        /**
         * Number of rows
         * @return the number of rows
         */
        size_t getRows() const {
            return nRows;
        }

        /**
         * Number of columns
         * @return the number of columns
         */
        size_t getColumns() const {
            return nColumns;
        }

        /**
         * Clear the matrix and reallocates the memory.
         * Use this method to change the matrix size
         * @param nrows new number of rows
         * @param ncolumns new number of columns
         * @param zero_element initial value of all elements.
         * @param resetAllelements if true,all elements are set to zero_element
         */
        inline void resize(int nrows, int ncolumns, bool resetAllElements = true) {

            if (data) {
                delete[] data;
                data = 0;
            }
            nsize = nrows*ncolumns;
            nRows = nrows, nColumns = ncolumns;
            data = new T[nsize];

            if (resetAllElements) {
                zeroMemory();
            }
        }

        /**
         * This operator is used to access the components of the matrix.
         * eg. m.[idxrow][idxcolumn].
         * \warning this method doesn't perform bounds check for optimization reasons.
         * @param row index of the row (0..n)
         * @return the pointer to the row.
         */
        inline T * operator [] (size_t row) const {
            return &data[nColumns * row];
        }

        /**
         * Subscript operator, can be used to access the matrix elements.
         * This method can be used to modify elements in the matrix.
         * eq. T &p=matrix(i,j);
         * p->someMethod(...)
         * \warning this method doesn't perform bounds check for optimization reasons.
         * @param r row (first row has index 0)
         * @param c column (first column has index 0)
         * @return the reference of the element at (r,c)
         *
         */
        inline T & operator ()(size_t r, size_t c) throw () {
            return data[r * nColumns + c];
        }

        /**
         * Subscript operator (const version), can be used to access the matrix elements
         * \warning this method doesn't perform bounds check for optimization reasons.
         * @param r row
         * @param c column
         * @return the element at (r,c)
         *
         */
        inline T operator()(size_t r, size_t c) const throw () {
            return data[r * nColumns + c];
        }

        /**
         * Get the reference of an element with indices bound check.
         * @param row index of row (first row has index zero)
         * @param column index of column (first column has index zero)
         * @return the reference of the element at the specified row and column.
         * @throw MathException if row and/or column are out of bounds.
         */
        T& getElementAt(size_t row, size_t column) const throw (MathException) {

            if (row >= nRows) {
                MathException ex("Error accessing matrix element:row %d out of bounds.", row);
                throw ex;
            }

            if (column >= nColumns) {
                MathException ex("Error accessing matrix element:column %d out of bounds.", column);
                throw ex;
            }

            return data[row * nColumns + column];
        }

        /**
         * Set an element of the matrix with indices bound check.
         * @param row index of row (first row has index zero)
         * @param column index of column (first column has index zero)
         * @param value the new value of the element
         * @throw MathException if row and/or column are out of bounds.
         */
        void setElementAt(size_t row, size_t column, const T& value) throw (MathException) {

            if (row >= nRows) {
                MathException ex("Error setting matrix element:row %d out of bounds.", row);
                throw ex;
            }

            if (column >= nColumns) {
                MathException ex("Error setting matrix element:column %d out of bounds.", column);
                throw ex;
            }

            data[row * nColumns + column] = value;
        }

        /**
         * Checks if this matrix has the same rows and columns as m
         * @param m a matrix
         */
        inline bool hasSameSize(const TMatrix<T> &m) throw () {
            return getRows() == m.getRows() && getColumns() == m.getColumns();
        }

        /**
         * Return true if this matrix is a square matrix (same number of rows and columns)
         * @return
         */
        inline bool isSquare() const throw () {
            return nColumns == nRows;
        }

        /**
         * Clear memory (all bytes set to zero)
         */
        inline void zeroMemory() throw () {
            memset(data, 0, sizeof (T) * nsize);
        }

        /**
         * Set all elements to value
         */
        inline void setAllElements(const T &value) throw () {
            for (size_t i = 0; i < nsize; i++) {
                data[i] = value;
            }
        }

        /**
         * Set the elements of the diagonal to the same value.
         */
        inline void setDiagonal(const T &value) throw (MathException) {

            if (nColumns != nRows) throw MathException("Cannot set the diagonal:matrix is not square.");

            for (size_t i = 0; i < nColumns; i++) {
                data[i * nColumns + i] = value;
            }
        }

        //--------------- addition --------------------------------------------

        /**
         * Add m to this matrix
         * @param m another matrix
         * @thorw MathException if m ha different size from this matrix
         */
        inline void add(const TMatrix<T> &matrix) throw (MathException) {

            if (nRows != matrix.nRows || nColumns != matrix.nColumns) throw MathException("Error adding matrix:invalid matrix size");

            const T* pdata = matrix.data;

            for (size_t i = 0; i < nsize; i++) {
                data[i] += pdata[i];
            }
        }

        /**
         * Fast addition.
         * Adds the specified matrix to this matrix and places the result in the result matrix.
         * \warning For optimization reasons this method doesn't perform arguments and bounds check.
         * @param m the matrix to add.This matrix must have the same size as this matrix.
         * @param result The matrix where the result of the addition is places.Points to an already allocated matrix of the same size as this matrix.
         */
        inline void add(TMatrix<T> *result, const TMatrix<T> &matrix) const throw () {

            T* dest_data = result->data;

            const T* src_data = matrix.data;

            for (size_t i = 0; i < nsize; i++) {

                dest_data[i] = data[i] + src_data[i];
            }
        }

        /**
         * Addition operator
         * 
         * @param m a matrix with the same number of rows and coloumns of this matrix
         * @throw MathException if matrices have different size.
         * @return the sum of this matrix and the matrix m
         */
        inline TMatrix<T> operator +(const TMatrix<T> &m) const throw (MathException) {

            if (nRows != m.nRows || nColumns != m.nColumns) throw MathException("Error adding matrix:invalid matrix size");

            TMatrix<T> t;
            t.resize(nRows, nColumns, false);

            t = *this;

            t.add(m);

            return t;

        }

        /**
         * Addition and assignment operator.
         * Add to this matrix another matrix.
         * @param matrix a matrix with the same number of rows and coloumns of this matrix
         * @throw MathException if matrices have different size.
         */
        inline TMatrix & operator +=(const TMatrix<T> &matrix) throw (MathException) {
            add(matrix);
            return *this;
        }

        //---------------- subtraction ---------------------------------------

        /**
         * Subtract  matrix from this matrix.
         *
         * @param matrix a matrix with the same number of rows and coloumns of this matrix
         * @throw MathException if matrices have different size.
         */
        inline void sub(const TMatrix<T> &matrix) throw (MathException) {

            if (nRows != matrix.nRows || nColumns != matrix.nColumns) throw MathException("Error sbtracting matrix:invalid matrix size.A matrix of size %d x %d is required as argument", nRows, nColumns);

            const T* pdata = matrix.data;

            for (size_t i = 0; i < nsize; i++) {
                data[i] -= pdata[i];
            }
        }

        /**
         * Fast subtraction.
         * Subtracts the specified matrix from this matrix and places the result in the result matrix.
         * \warning For optimization reasons this method doesn't perform arguments and bounds check.
         * @param m the matrix to add.This matrix must have the same size as this matrix.
         * @param result The matrix where the result of the addition is places.Points to an already allocated matrix of the same size as this matrix.
         */
        inline void sub(TMatrix<T> *result, const TMatrix<T> &matrix) throw () {

            T* dest_data = result->data;

            const T* src_data = matrix->data;

            for (size_t i = 0; i < nsize; i++) {

                dest_data[i] = data[i] - src_data[i];
            }
        }

        /**
         * Subtraction operator.
         * 
         * @param m a matrix with the same number of rows and coloumns of this matrix
         * @return the subctraction between this matrix and  m
         */
        inline TMatrix operator -(const TMatrix<T> &m) const throw (MathException) {

            if (nRows != m.nRows || nColumns != m.nColumns) throw MathException("Error sbtracting matrix:invalid matrix size.A matrix of size %d x %d is required as argument", nRows, nColumns);

            TMatrix<T> t;
            t.resize(nRows, nColumns, false);

            t = *this;

            t.sub(m);

            return t;
        }

        /**
         * Subtraction and assignment operator.
         * @param matrix
         * @return this matrix
         */
        inline TMatrix & operator -=(const TMatrix<T> &matrix) throw (MathException) {
            sub(matrix);
            return *this;
        }

        //multiplication

        /**
         * Matrix multiplication.
         * Multiplies this matrix by another matrix m.
         * @param m a matrix with the same number of rows as the columns of this matrix
         * and a number of colums equals to the number of rows of this matrix.
         */
        inline void mul(const TMatrix<T> &m) throw (MathException) {

            TMatrix<T> temp;
            temp.resize(nRows, nColumns, false);
            temp = (*this) * m;
            data = temp.data;
            temp.data = 0;
        }

        /**
         * Fast matrix multiplication.
         * Multiplies this matrix by m and places the result into an existing matrix.
         * 
         * This method doesn't allocate a temporary matrix and doesn't perform bounds check
         * for optimization reasons.
         * If this matrix is nxm and m is mxq the result matrix is nxq (n=numer of rows q=number of columns)
         * @param result an user supplied matrix of appropriate size to store the result of the multiplication.
         * @param m a matrix with m.nRows=this->nColumns
         */
        inline void mul(TMatrix<T> *result, const TMatrix<T>& m) const throw () {

            size_t mcols = m.nColumns; //n. colonne

            const T* mdata = m.data;

            T* dest_data = result->data;

            T s;

            size_t k;

            for (size_t row = 0; row < nRows; ++row) {

                for (size_t col = 0; col < mcols; ++col) {

                    s = 0;

                    //prodotto scalare fra la riga row dalla matrice corrente e la colonna col della matrice m
                    for (k = 0; k < nColumns; ++k) s += data[row * nColumns + k] * mdata[k * mcols + col];

                    dest_data[row * mcols + col] = s;

                }
            }
        }

        /**
         * Matrix multiplication operator.
         * @return this matrix multiplied by another matrix m.
         * @param m a matrix with the same number of columns as this matrix rows.
         * If this matrix is nxm and m is mxq the result matrix is nxq (n=numer of rows q=number of columns)
         */
        TMatrix<T> operator *(const TMatrix<T> &m) throw (MathException) {

            //il numero di colonne di questa matrice deve essere uguale al numero di righe di m
            if (m.nRows != nColumns) throw MathException("Matrix multiplication error:invalid matrix size. A matrix with %d rows is required as argument.", nColumns);

            size_t mcols = m.nColumns; //n. colonne

            const T* mdata = m.data;

            TMatrix<T> res;

            res.resize(nRows, m.nColumns, false);

            T* dest_data = res.data;

            T s;

            size_t k;

            for (size_t row = 0; row < nRows; ++row) {

                for (size_t col = 0; col < mcols; ++col) {

                    s = 0;

                    //prodotto scalare fra la riga row dalla matrice corrente e la colonna col della matrice m
                    for (k = 0; k < nColumns; ++k) s += data[row * nColumns + k] * mdata[k * mcols + col];

                    dest_data[row * mcols + col] = s;

                }
            }

            return res;
        }

        /**
         * Multiplication and assignment operator
         * Multiplies this matrix by another matrix m.
         * @param m
         * @return 
         */
        TMatrix<T> & operator *=(const TMatrix<T> &m) throw (MathException) {
            mul(m);
            return *this;
        }

        /**
         * Tests if this matrix equals another matrix.
         * @param m
         * @return true if the matrices have the same size and each element a[i][j] equals the corresponding element.
         */
        bool operator ==(const TMatrix<T> &m) const throw () {

            if (m.getRows() != nRows || m.getColumns() != nColumns) return false;

            const T *pdata = m.data;

            for (size_t i = 0; i < nsize; i++) {
                if (pdata[i] != data[i]) return false;
            }

            return true;
        }

        /**
         * Tests if this matrix is not equal to another matrix.
         * @param m
         * @return
         */
        bool operator !=(const TMatrix<T> &m) throw () {
            return !(m == *this);
        }

        /**
         * Unary minus operator.
         * Negate all elements of the matrix
         * @return
         */
        TMatrix<T> & operator -() throw () {
            for (size_t i = 0; i < nsize; i++) data[i] = -data[i];
            return *this;
        }

        /**
         *Returns the transpose matrix of this matrix.
         *
         */
        TMatrix<T> getTranspose() const throw () {

            TMatrix<T> t;

            t.resize(nColumns, nRows, false);

            for (size_t i = 0; i < nRows; i++) {
                for (size_t j = 0; j < nColumns; j++) {
                    t[j][i] = data[i * nColumns + j];
                }
            }

            return t;
        }

        /**
         * Matrix by vector multiplication.
         * @param v a vector whose size equals this matrix columns count.
         * @throw MathException if the vector v has size different fron nColumns.
         * @return a vector of size nRows resulting from the multiplication.
         */
        TVector<T> operator *(const TVector<T> &v) const throw (MathException) {

            if (v.size() != nColumns) throw MathException("Error in matrix by vector multiplication:invalid vector size.The vector must have size %d", nColumns);

            TVector<T> res(nRows);

            const T *src = v._getDataPtr();

            for (size_t row = 0; row < nRows; row++) {

                T &r = res._getDataPtr()[row];

                for (size_t col = 0; col < nColumns; col++) {

                    r += data[row * nColumns + col] * src[col];
                }
            }

            return res;
        }

        /**
         * Fast matrix by vector multiplication.
         * This method returns the result of the multiplication of this matrix by a vector
         * v and places the result in a user-supplied vector.
         * @param result the vector already allocated that holds the result.Must have nRows size.
         * @param v a vector whose size equals this matrix columns count.
         * \warning for optimization reasons, this method doesn't perform bounds check and arguments check.
         */
        void mul(TVector<T> *result, const TVector<T> &v) const throw () {

            const T *src = v._getDataPtr();

            for (size_t row = 0; row < nRows; row++) {

                T *r = result->_getDataPtr();

                for (size_t col = 0; col < nColumns; col++) {

                    r += data[row * nColumns + col] * src[col];
                }
            }
        }

        /**
         *Extracts a row from this matrix into dest_row.
         *@param dest_row a vector of nRows size already allocated.
         *@param row the index of the row to extract.(first row has index zero)
         *\warning for optimization reasons, this method doesn't perform bounds check and arguments check.
         */
        void getRow(TVector<T> *dest_row, size_t row) const throw () {
            T* dest = dest_row->_getDataPtr();
            memcpy(dest, &data[row * nColumns], sizeof (T) * nColumns);
        }

        /**
         *Extracts a row from this matrix into dest_row.
         *@param dest_column a vector of nColumns size already allocated.
         *@param col the index of the column to extract.
         *\warning for optimization reasons, this method doesn't perform bounds check and arguments check.
         */
        void getColumn(TVector<T> *dest_column, size_t column) const throw () {

            T* dest = dest_column->_getDataPtr();

            for (size_t i = 0; i < nColumns; i++) {

                dest[i] = data[i * nColumns + column];

            }
        }

        /**
         * Sets a row of the matrix using an array of elements.
         * @param row row index to set
         * @param row_data and array,not null,containing nColumns elements.
         * \warning this method doesn't perform arguments check
         */
        void setRow(size_t row, const T* row_data) throw () {

            memcpy(&data[row * nColumns], row_data, sizeof (T) * nColumns);

        }

        /**
         * Sets the firs nelements of a row
         * @param row row index (first row has index zero)
         * @param row_data and array of size nelements
         * @param nelements number of elements to set, must be less or equal to nColumns
         * \warning this method doesn't perform arguments check
         */
        void setRow(size_t row, const T* row_data, size_t nelements) {

            memcpy(&data[row * nColumns], row_data, sizeof (T) * nelements);
        }

        /**
         * Sets a row of the matrix using a vector
         * @param row row index to set
         * @param row_data a vector of size nColumns
         * @throw MathException if row_data is not of size nColumns or if row is out of bounds
         */
        void setRow(size_t row, const TVector<T> &row_data) throw (MathException) {

            if (row_data.size() != nColumns) throw MathException("Error setting row %d:invalid array size, expected size %d, actual %d", row, nColumns, row_data.size());

            if (row < 0 || row >= getRows()) throw MathException("Error setting row %d:row index out of bounds (must be between 0 and %d)", row, getRows() - 1);

            memcpy(&data[row * nColumns], row_data._getDataPtr(), sizeof (T) * nColumns);

        }

        /**
         * Sets a column of the matrix using a vector.
         * @param column index of column (first column has index=zero)
         * @param column_data a vector of size nRows
         * @throw MathException if column_data has size different from nRows of column index is out of bounds
         */
        void setColumn(size_t column, const TVector<T> &column_data) throw (MathException) {

            if (column_data.size() != getRows()) throw MathException("Error setting column %d:invalid array size, expected size %d, actual %d", column, getRows(), column_data.size());

            if (column < 0 || column >= getColumns()) throw MathException("Error setting column %d:column index out of bounds (must be between 0 and %d)", column, getColumns() - 1);

            const T* cdata = column_data._getDataPtr();

            for (size_t i = 0; i < nRows; i++) {
                data[i * nColumns + column] = cdata[i];
            }
        }

        /**
         * Sets a column of the matrix using an array of elements.
         * @param column index of column (first column has index=zero)
         * @param column_data array of nRows elements
         * \warning this method doesn't perform arguments check
         */
        void setColumn(size_t column, const T* column_data) throw () {

            for (size_t i = 0; i < nRows; i++) {
                data[i * nColumns + column] = column_data[i];
            }
        }

        /**
         * @todo da testare!
         * Swaps two rows
         * @param row1 first row
         * @param row2 second row
         * \waring this method doesn't perform row index validation.
         */
        void swapRows(size_t row1, size_t row2) throw () {

            if (row1 == row2) return;

            T temp;
            T* ptr;

            size_t dest_offs = nColumns*row2; //offset destinazione
            size_t src_offs = nColumns*row1; //offset sorgente

            for (size_t i = 0; i < nColumns; i++) {

                temp = data[dest_offs];
                data[dest_offs] = data[src_offs];
                data[src_offs] = temp;

                ++src_offs;
                ++dest_offs;
            }
        }

        /**
         * Swaps two columns
         * @param col1 first column
         * @param col2 second column
         * \waring this method doesn't perform row index validation.
         */
        void swapColumns(size_t col1, size_t col2) throw () {

            if (col1 == col2) return;

            T temp;
            T* ptr;

            size_t dest_offs = col2; //offset destinazione
            size_t src_offs = col1; //offset sorgente

            for (size_t i = 0; i < nRows; i++) {

                temp = data[dest_offs];
                data[dest_offs] = data[src_offs];
                data[src_offs] = temp;

                dest_offs += nColumns;
                src_offs += nColumns;

            }
        }

        /**
         * Internal data pointer.
         * \warning don't use this method to access the elements.
         * @return the pointer to the internal matrix data arranged in row major format.
         */
        T* _getDataPtr() const throw () {
            return data;
        }

        /**
         * Pointer to row data
         * \warning don't use this method to access the elements.
         * @param row index of row
         * @return the pointer to row data
         */
        T* _getRowPtr(size_t row) const throw () {
            return &data[row * nColumns];
        }

    protected:

        TMatrix() : data(0) {

        }

        /**
         *Number of rows.
         */
        size_t nRows;
        /**
         *Number of columns.
         */
        size_t nColumns;

        /**
         *Number of elements in the matrix (nxm)
         */
        size_t nsize;

        /**
         * TMatrix components (row major format)
         * Data store the elements of the matrix arranged
         * by rows
         */
        T* data;

    };

    ////////////////////////////////////////////////////////////////////////////   

    /**
     * Output operator
     * @param ostrm
     * @param m
     * @return
     */
    template<class T> ostream & operator <<(ostream& ostrm, const TMatrix<T> &m) {

        size_t r = m.getRows();
        size_t c = m.getColumns();

        for (size_t i = 0; i < r; i++) {

            for (size_t j = 0; j < c; j++) {
                ostrm << m[i][j] << '\t';
            }
            ostrm << endl;
        }
        return ostrm;
    }

};

#endif