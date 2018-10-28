/*
 * matrix.c
 *
 *  Created on: Sep 22, 2018
 *      Author: Bernard Dolan <bernarddolan@mail.rit.edu>
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "matrix.h"

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
_matr_2f_ * creatematr2f(unsigned row_ct, unsigned col_ct) {

    if((row_ct + col_ct) && !(row_ct * col_ct)) {
        // if only one of row_ct or col_ct is 0
        return (_matr_2f_ *)(0);// can't create a 2d matrix with 1 demension
    }

    _matr_2f_ *m = (_matr_2f_ *)malloc(sizeof(_matr_2f_));

    if(m == 0) {
      Serial.print("Error allocating matrix");
      return 0;
    }

    m->_row_ct = row_ct;
    m->_col_ct = col_ct;
    m->_data = (float **)calloc(row_ct, sizeof(float *));

    if(m->_data == 0) {
      Serial.print("Error allocating rows\n");
      free(m);
      return 0;
    }

    unsigned i;
    for(i = 0; i < row_ct; i++) {
      m->_data[i] = (float *)calloc(col_ct, sizeof(float));// TODO gracefully handle failed allocation here?
    }

    return m;
}

/*
 * desmatr2f
 *
 * Destroys the given matrix.
 * All heap memory used by the matrix pointer is freed.
 *
 * @param matrix    the matrix to destroy
 */
void desmatr2f(_matr_2f_ *matrix) {
    unsigned i;
    for(i = 0; i < matrix->_row_ct; i++) {
        free(matrix->_data[i]);
    }
    free(matrix->_data);
    free(matrix);
}

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
_matr_2f_ * mulmatr2f(_matr_2f_ *matrix1, _matr_2f_ *matrix2) {
  if(matrix1->_col_ct != matrix2->_row_ct)return 0;
  _matr_2f_ *result = creatematr2f(matrix1->_row_ct, matrix2->_col_ct);
  unsigned i, j, k;
  for(i = 0; i < matrix1->_row_ct; i++) {
    for(j = 0; j < matrix2->_col_ct; j++) {
      float sum = 0.0f;
      for(k = 0; k < matrix1->_col_ct; k++) {
        sum += matrix1->_data[i][k] * matrix2->_data[k][j];
      }
      result->_data[i][j] = sum;
    }
  }
  return result;
}

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
_matr_2f_ * scalematr2f(_matr_2f_ *matrix, float scalar) {
    unsigned i, j;
    for(i = 0; i < matrix->_row_ct; i++) {
        for(j = 0; j < matrix->_col_ct; j++) {
            matrix->_data[i][j] *= scalar;
        }
    }
    return matrix;
}

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
_matr_2f_ flipmatr2f(_matr_2f_ *matrix) {
	_matr_2f_ flippedMatrix = creatematr2f(matrix->_col_ct, matrix->_row_ct);
	for(int i = 0; i < matrix->_row_ct; i++) {
		for(int j = 0; j < matrix->_col_ct; j++) {
			flippedMatrix->_data[j][i] = matrix->_data[i][j];
		}
	}
	return flippedMatrix;
}

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
_matr_2f_ flipmatrd2f(_matr_2f_ *matrix) {
	_matr_2f_ flippedMatrix = creatematr2f(matrix->_col_ct, matrix->_row_ct);
	for(int i = 0; i < matrix->_row_ct; i++) {
		for(int j = 0; j < matrix->_col_ct; j++) {
			flippedMatrix->_data[j][i] = matrix->_data[i][j];
		}
	}
	desmatr2f(matrix);
	return flippedMatrix;
}

/*
 * printmatr2f
 *
 * @param matrix       pointer to the matrix to print
 * @param precision    precision to print the elements to
 */
void printmatr2f(_matr_2f_ *matrix, unsigned precision) {
    float maxValue = 0.0f;
    unsigned row_ct = matrix->_row_ct;
    unsigned col_ct = matrix->_col_ct;

    unsigned i, j;
    for(i = 0; i < row_ct; i++) {
        for(j = 0; j < col_ct; j++) {
            if(matrix->_data[i][j] > maxValue) {
                maxValue = matrix->_data[i][j];
            }
        }
    }
    unsigned char digits = (unsigned char)ceil(log10(((signed)maxValue) + 1)) + precision + 1;
    char *buffer1 = (char *)malloc(sizeof(char) * 32);
    char *buffer2 = (char *)malloc(sizeof(char) * (digits + precision + 2));
    for(i = 0; i < row_ct; i++) {
        Serial.print("\r\n|");
        for(j = 0; j < col_ct; j++) {
            snprintf(buffer1, sizeof(char) * 32, "%%%d.%dd", digits, precision);
            snprintf(buffer2, sizeof(char) * (digits + precision + 2), buffer1, (int)matrix->_data[i][j]);
            Serial.print(buffer2);
            if(j < col_ct - 1) {
              Serial.print("    ");
            }
        }
        Serial.print("|");
    }
    Serial.print("\r\n");
    free(buffer1);
    free(buffer2);
}

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
float matrget2f(_matr_2f_ *matrix, unsigned row, unsigned col) {
  return matrix->_data[row][col];
}

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
void matrset2f(_matr_2f_ *matrix, unsigned row, unsigned col, float value) {
  matrix->_data[row][col] = value;
}
