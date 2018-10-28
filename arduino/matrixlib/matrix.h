/*
 * matrix.h
 *
 *  Created on: Sep 22, 2018
 *      Author: Bernard Dolan <bernarddolan@mail.rit.edu>
 */
#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct {
    unsigned _row_ct, _col_ct;
    float * *_data;
}_matr_2f_;

/*
 * creatematr2f
 *
 * Creates a new matrix with the specified dimensions.
 * The new matrix is allocated on the heap and all elements will be filled with 0.0f.
 * The newly allocated matrix will need to be freed either manually or using matrdes2f by the caller.
 *
 * @param row_ct    the row count of the new matrix
 * @param col_ct    the column count of the new matrix
 */
_matr_2f_ * creatematr2f(unsigned row_ct, unsigned col_ct);
/*
 * desmatr2f
 *
 * Destroys the given matrix.
 * All heap memory used by the matrix pointer is freed.
 *
 * @param matrix    the matrix to destroy
 */
void desmatr2f(_matr_2f_ *matrix);
/*
 * mulmatr2f
 *
 * Multiplies the given matrices (if possible)
 * If the matrix multiplication is performed, a newly allocated matrix heap pointer is returned.
 * This new matrix must be freed by the caller either manually or using matrdes2f.
 * If matrix multiplication is undefined for the given matrices, a null pointer is returned and no memory is allocated.
 *
 * @param matrix1    the left hand matrix to multiply
 * @param matrix2    the right hand matrix to multiply
 *
 * @return           a pointer to a new matrix which contains the multiplication result or a null pointer if the multiplication is undefined
 */
_matr_2f_ * mulmatr2f(_matr_2f_ *matrix1, _matr_2f_ *matrix2);
/*
 * scalematr2f
 *
 * Scales the given matrix by the specified scalar
 * The matrix at the given pointer is scaled and the same pointer is returned
 *
 * @param matrix   pointer to the matrix to scale
 * @param scalar   the scalar to scale the matrix by
 *
 * @return         the same pointer passed to the function for chaining
 */
_matr_2f_ * scalematr2f(_matr_2f_ *matrix, float scalar);
/*
 * flipmatr2f
 *
 * Flips the given matrix.
 * The matrix at the pointer is not modified or destroyed.
 * A pointer to the newly created matrix is returned.
 * The new matrix is allocated on the heap and must be freed by the caller either manually or by using desmatr2f.
 *
 * @param matrix    the matrix to flip
 *
 * @return          a pointer the the flipped matrix
 */
_matr_2f_ flipmatr2f(_matr_2f_ *matrix);
/*
 * flipmatrd2f
 *
 * Flips the given matrix.
 * The matrix at the pointer is destroyed and all heap memory is returned.
 * A pointer to the newly created matrix is returned.
 * The new matrix is allocated on the heap and must be freed by the caller either manually or by using desmatr2f.
 *
 * @param matrix    the matrix to flip
 *
 * @return          a pointer the the flipped matrix
 */
_matr_2f_ flipmatrd2f(_matr_2f_ *matrix);
/*
 * printmatr2f
 *
 * @param matrix       pointer to the matrix to print
 * @param precision    precision to print the elements to
 */
void printmatr2f(_matr_2f_ *matrix, unsigned precision);
/*
 * matrget2f
 *
 * Gets the value in the given matric at the specified index
 *
 * @param matrix    pointer to the matrix to modify
 * @param row       the row index of the element to get
 * @param col       the column index of the element to get
 *
 * @return          the value at the specified index
 */
float matrget2f(_matr_2f_ *matrix, unsigned row, unsigned col);
/*
 * matrset2f
 *
 * Sets the value in the given matrix at the specified index
 *
 * @param matrix    pointer to the matrix to modify
 * @param row       the row index of the element to set
 * @param col       the column index of the element to set
 * @param value     the value to put into the matrix
 */
void matrset2f(_matr_2f_ *matrix, unsigned row, unsigned col, float value);

#endif /* MATRIX_H_ */

