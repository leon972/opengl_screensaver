/* 
 * File:   tmatrixex.h
 * Author: Leonardo Berti
 * Copyright (c) 2011
 *
 * Created on 18 settembre 2011, 16.32
 */

/*!
 * \file tmatrix.h
 * \brief Extended TMatrix<T> template-base matrix class.
 * This class implements additional methods to compute the inverse matrix,
 * the determinant and others method to read and save the matrix on files.
 */

#ifndef TMATRIXEX_H
#define	TMATRIXEX_H

#include "math/mathdefs.h"
#include "libmath.h"
#include "mathutil.h"
#include "tmatrix.h"
#include "crout.h"
#include <stddef.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace mathengine {

    using namespace std;

    /**
     * unused constant:doxygen trick
     */
    const int TMatrixEx_zero = 0;

    /**
     * Extended version of TMatrix<T> class.
     * This class implements additional methods to compute the inverse matrix,
     * the determinant and others method to read and save the matrix on files.
     * @see TMatrix
     */
    template <class T> class TMatrixEx : public TMatrix<T> {
    public:

        /**
         * Creates a matrix nrows x ncolumns
         * @param nrows
         * @param ncolumns
         */
        TMatrixEx(size_t nrows, size_t ncolumns) : TMatrix<T>(nrows, ncolumns) {


        }

        /**
         * Creates a matrix nrows x ncolumns
         * @param nrows
         * @param ncolumns
         * @param clearMemory if set,all elements are set to zero after creation
         */
        TMatrixEx(size_t nrows, size_t ncolumns, bool clearMemory) : TMatrix<T>(nrows, ncolumns, clearMemory) {

        }

        /**
         * Destructor
         */
        virtual ~TMatrixEx() {
            if (TMatrix<T>::data) {
                delete[] TMatrix<T>::data;
                TMatrix<T>::data = 0;
            }
        }

        /**
         *Computes the determinant of the matrix.
         *@throw MathException if this matrix is not square
         */
        T getDeterminant() throw (MathException) {
            return LinearEqCrout<T>::GetDeterminant(*this);
        }

        /**
         * Returns the inverse matrix.
         * @param dest destination matrix that will stores the inverse matrix.
         */
        void getInverse(TMatrix<T> &dest) throw (MathException) {
            LinearEqCrout<T>::InvertMatrix(dest, *this);
        }

        /**
         * Writes this matrix to a text file.Each row of the matrix is written in a separate file row and the elements are separated by the separator_char
         * The destination file is always rewritten.
         * @param separator_char the character used to separate the elements, eq. ',' for comma separated values.
         * @param quot if set,each element is enclosed in double quote (")
         * @param comment if not null, the comment will be written in the first row
         * @throw MathException if an I/O error occurs
         */
        void writeToFile(const char* file_name, const char separator_char, bool quot, const char* comment) throw (MathException) {

            fstream file;

            //apre in scrittura,il file è ricreato
            file.open(file_name, fstream::out);

            if (file.good()) {

                size_t nr = TMatrix<T>::getRows();
                size_t nc = TMatrix<T>::getColumns();

                if (comment) {
                    file << '#' << comment << endl;
                }

                if (!quot) {

                    for (int i = 0; i < nr; i++) {

                        size_t offs = i*nc;

                        for (int j = 0; j < nc - 1; j++) {
                            file << TMatrix<T>::data[offs + j] << separator_char;
                        }

                        file << TMatrix<T>::data[offs + nc - 1] << endl;

                    }

                } else {

                    const char quot = '"';

                    //valori separati da "
                    for (int i = 0; i < nr; i++) {

                        size_t offs = i*nc;

                        for (int j = 0; j < nc - 1; j++) {
                            file << quot << TMatrix<T>::data[offs + j] << quot << separator_char;
                        }

                        file << quot << TMatrix<T>::data[offs + nc - 1] << quot << endl;
                    }

                    file.close();
                }

            } else {
                file.close();
                throw MathException("Error writing the %d x %d matrix to file %s:file open or creation error.", TMatrix<T>::getRows(), TMatrix<T>::getColumns(), file_name);
            }
        }

        /**
         * Reads this matrix from a text file
         * @param separator_char the character used to separate the elements, eq. ',' for comma separated values.
         * @param quot if set,each element is enclosed in double quote (")
         */
        void readFromFile(const char* file_name, const char separator_char, bool quot) throw (MathException) {

            fstream file;

            //apre in lettura
            file.open(file_name, fstream::in);

            int line_cnt = 1;
            int crow = 0;
            int ccol = 0;

            if (file.good()) {

                char ch;

                while (!file.eof()) {

                    file.get(ch);

                    if (ch == '#' || ch == '\n') {

                        while (file.get() != '\n' && !file.eof()) {
                        }

                        line_cnt++;

                    } else {

                        file.unget();

                        T val;

                        size_t cn = TMatrix<T>::nColumns - 1;

                        if (quot) {
                            //valori fra apici ("")

                            for (size_t i = 0; i < cn; i++) {

                                file >> ch;

                                if (ch != '"') {
                                    throw MathException("Error reading value from file %s at line %d at column %d:missing opening quotes", file_name, line_cnt, i);
                                }

                                if (!(file >> val)) {

                                    throw MathException("Error reading value from file %s at line %d at column %d:invalid format", file_name, line_cnt, i);
                                }

                                file >> ch;

                                if (ch != '"') {
                                    throw MathException("Error reading value from file %s at line %d at column %d:missing closing quotes", file_name, line_cnt, i);
                                }


                                //setta il valore letto nella posizione corrente
                                TMatrix<T>::data[crow * TMatrix<T>::nColumns + i] = val;

                                file >> ch;

                                if (ch != separator_char) {
                                    throw MathException("Error reading value from file %s at line %d at column %d:invalid separator", file_name, line_cnt, i);
                                }
                            }


                        } else {

                            //valori senza apici
                            for (size_t i = 0; i < cn; i++) {

                                if (!(file >> val)) {

                                    throw MathException("Error reading value from file %s at line %d at column %d:invalid format", file_name, line_cnt, i);
                                }

                                //setta il valore letto nella posizione corrente
                                TMatrix<T>::data[crow * TMatrix<T>::nColumns + i] = val;

                                file >> ch;

                                if (ch != separator_char) {
                                    throw MathException("Error reading value from file %s at line %d at column %d:invalid separator", file_name, line_cnt, i);
                                }
                            }

                        }

                        int i = TMatrix<T>::nColumns - 1;
                        //ultimo valore

                        if (quot) {

                            file>>ch;
                            if (!(file >> val)) {
                                throw MathException("Error reading value from file %s at line %d at column %d:invalid format", file_name, line_cnt, i);
                            }
                            file>>ch;

                        } else {
                            if (!(file >> val)) {
                                throw MathException("Error reading value from file %s at line %d at column %d:invalid format", file_name, line_cnt, i);
                            }
                        }

                        ch = file.get();

                        while (ch != '\n' && !file.eof()) {
                            ch = file.get();
                        }

                        crow++;

                        if (crow == TMatrix<T>::nRows) break;

                    }
                }

                if (crow != TMatrix<T>::nRows) {
                    throw MathException("Error reading matrix from file %s:invalid row count, expected %d actual %d", file_name, TMatrix<T>::nRows, crow);
                }

                file.close();

            } else {

                file.close();
                throw MathException("Error reading the %d x %d matrix from file %s:file open or creation error.", TMatrix<T>::getRows(), TMatrix<T>::getColumns(), file_name);

            }
        }

    };

};

#endif	/* TMATRIXEX_H */

