
void convolution_3D(element_t i_matrix_A[][][], size_t i_rows, size_t i_columns,
                    size_t i_start_depth, size_t i_end_depth,
                    element_t i_kernel_B[][][], size_t i_kernel_size,
                    size_t i_padding_type, size_t i_padding[],
                    size_t i_stride_row, size_t i_stride_column,
                    element_t o_matrix_C[][], size_t *o_rows, size_t *o_columns) {
    size_t index, jindex;
    size_t rindex, pindex, kindex;
    element_t sum;
    /*
    * Setring the padding
    */
    if(i_padding_type == 0) {
        for(index = 0; index < 4; index++) {
            i_padding[index] = 0;
        }
    } else {
        if(i_padding_type == 1) {
            for(index = 0; index < 4; index++) {
                i_padding[index] = (i_kernel_size - 1) / 2;
            }
        }
    }
    *o_rows = (i_rows + i_padding[0] + i_padding[1] - i_kernel_size) / i_stride_row + 1;
    *o_columns = (i_columns + i_padding[2] + i_padding[3] - i_kernel_size) / i_stride_column + 1;

    size_t matrix_row, matrix_column;
    for(index = 0; index < *o_rows; index++) {
        for(jindex = 0; jindex < *o_columns; jindex++) {
            sum = 0;
            for(rindex = 0; rindex < i_kernel_size; rindex++) {
                for(pindex = 0; pindex < i_kernel_size; pindex++) {
                    for(kindex = i_start_depth; kindex < i_end_depth; kindex++) {
                        matrix_row = index * i_stride_row + rindex;
                        matrix_column = jindex * i_stride_column + pindex;
                        if( matrix_row < i_padding[0] || matrix_row >= i_rows + i_padding[0]) {
                            sum = sum + 0;
                        } else {
                            if( matrix_column < i_padding[2] || matrix_column >= i_columns + i_padding[2]) {
                                sum = sum + 0;
                            } else {
                                sum = sum + i_matrix_A[matrix_row][matrix_column][kindex]
                                      * i_kernel_B[rindex][pindex][kindex];
                            }
                        }
                    }
                }
            }
            o_matrix_C[index][jindex] = sum;
        }
    }
}

void convolution_2D(element_t i_matrix_A[][], size_t i_rows, size_t i_columns,
                    element_t i_kernel_B[][], size_t i_kernel_size,
                    size_t i_padding_type, size_t i_padding[],
                    size_t i_stride_row, size_t i_stride_column,
                    element_t o_matrix_C[][], size_t *o_rows, size_t *o_columns) {
    size_t index, jindex;
    size_t rindex, pindex, kindex;
    element_t sum;
    /*
    * Setring the padding
    */
    if(i_padding_type == 0) {
        for(index = 0; index < 4; index++) {
            i_padding[index] = 0;
        }
    } else {
        if(i_padding_type == 1) {
            for(index = 0; index < 4; index++) {
                i_padding[index] = (i_kernel_size - 1) / 2;
            }
        }
    }
    *o_rows = (i_rows + i_padding[0] + i_padding[1] - i_kernel_size) / i_stride_row + 1;
    *o_columns = (i_columns + i_padding[2] + i_padding[3] - i_kernel_size) / i_stride_column + 1;

    size_t matrix_row, matrix_column;
    for(index = 0; index < *o_rows; index++) {
        for(jindex = 0; jindex < *o_columns; jindex++) {
            sum = 0;
            for(rindex = 0; rindex < i_kernel_size; rindex++) {
                for(pindex = 0; pindex < i_kernel_size; pindex++) {
                    matrix_row = index * i_stride_row + rindex;
                    matrix_column = jindex * i_stride_column + pindex;
                    if( matrix_row < i_padding[0] || matrix_row >= i_rows + i_padding[0]) {
                        sum = sum + 0;
                    } else {
                        if( matrix_column < i_padding[2] || matrix_column >= i_columns + i_padding[2]) {
                            sum = sum + 0;
                        } else {
                            sum = sum + i_matrix_A[matrix_row][matrix_column]
                                    * i_kernel_B[rindex][pindex];
                        }
                    }
                }
            }
            o_matrix_C[index][jindex] = sum;
        }
    }
}

void ReLU_3D(element_t i_matrix_A[][][], size_t i_rows, size_t i_columns, size_t i_depth,
             element_t o_matrix_B[][][]) {
    size_t index, jindex, kindex;
    for(index = 0; index < i_rows; index++) {
        for(jidnex = 0; jindex < i_columns; jindex++) {
            for(kindex = 0; kindex < i_depth; kindex++) {
                if(i_matrix_A[index][jindex][kindex] < 0) {
                    o_matrix_B[index][jindex][kindex] = 0;
                } else {
                    o_matrix_B[index][jindex][kindex] = i_matrix_A[index][jindex][kindex];
                }
            }
        }
    }
}



void ReLU_2D(element_t i_matrix_A[][], size_t i_rows, size_t i_columns,
             element_t o_matrix_B[][]) {
    size_t index, jindex;
    for(index = 0; index < i_rows; index++) {
        for(jidnex = 0; jindex < i_columns; jindex++) {
            if(i_matrix_A[index][jindex] < 0) {
                o_matrix_B[index][jindex] = 0;
            } else {
                o_matrix_B[index][jindex] = i_matrix_A[index][jindex];
            }
        }
    }
}

void max_pooling_3D(element_t i_matrix_A[][][], size_t i_rows, size_t i_columns, size_t i_depth,
                size_t i_filter_row, size_t i_filter_column,
                size_t i_stride_row, size_t i_stride_column,
                element_t o_matrix_B[][][], size_t *o_rows, size_t *o_columns) {
    size_t index, jindex, kindex, rindex, pindex;
    size_t matrix_row, matrix_column;
    element_t max;
    *o_rows = (i_rows - i_filter_row) / i_stride_row + 1;
    *o_columns = (i_columns - i_filter_column) / i_stride_column + 1;
    for(index = 0; index < *o_rows; index++) {
        for(jindex = 0; jindex < *o_columns; jindex++) {
            for(kindex = 0; kindex < i_depth; kindex++) {
                max = -1; // because it does'n have negative numbers
                for(rindex = 0; rindex < i_kernel_size; rindex++) {
                    for(pindex = 0; pindex < i_kernel_size; pindex++) {
                        matrix_row = index * i_stride_row + rindex;
                        matrix_column = jindex * i_stride_column + pindex;
                        if(i_matrix_A[matrix_row][matrix_column][kindex] >  max) {
                            max = i_matrix_A[matrix_row][matrix_column][kindex];
                        }
                    }
                }
                o_matrix_B[index][jindex][kindex] = max;
            }
        }
    }

}

void max_pooling_2D(element_t i_matrix_A[][], size_t i_rows, size_t i_columns,
                    size_t i_filter_row, size_t i_filter_column,
                    size_t i_stride_row, size_t i_stride_column,
                    element_t o_matrix_B[][], size_t *o_rows, size_t *o_columns) {
    size_t index, jindex, rindex, pindex;
    size_t matrix_row, matrix_column;
    element_t max;
    *o_rows = (i_rows - i_filter_row) / i_stride_row + 1;
    *o_columns = (i_columns - i_filter_column) / i_stride_column + 1;
    for(index = 0; index < *o_rows; index++) {
        for(jindex = 0; jindex < *o_columns; jindex++) {
            max = -1; // because it does'n have negative numbers
            for(rindex = 0; rindex < i_kernel_size; rindex++) {
                for(pindex = 0; pindex < i_kernel_size; pindex++) {
                    matrix_row = index * i_stride_row + rindex;
                    matrix_column = jindex * i_stride_column + pindex;
                    if(i_matrix_A[matrix_row][matrix_column] >  max) {
                        max = i_matrix_A[matrix_row][matrix_column];
                    }
                }
            }
            o_matrix_B[index][jindex] = max;
        }
    }

}

void full_conected(element_t i_vector_A[], size_t i_length,
                   element_t i_kernel_B[], element_t *o_element) {
    vector_T_multiply_vector(i_vector_A, i_kernel_B,
                             i_length, o_element);
}

void softmax(element_t i_vector_A[], size_t i_length,
             element_t o_vector_B[]) {
    size_t index;
    element_t sum, e_x;
    sum = 0;
    for(index = 0; index < i_length; index++) {
        if(i_vector_A[index] >= 0) {
            e_x = number_exponential(EXPONENTIAL_PRECISION, i_vector_A[index]);
            sum = sum + e_x;
        } else {
            e_x = number_exponential(EXPONENTIAL_PRECISION, -1*i_vector_A[index]);
            sum = sum + 1/e_x;
        }
    }

    for(index = 0; index < i_length; index++) {
        if(i_vector_A[index] >= 0) {
            e_x = number_exponential(EXPONENTIAL_PRECISION, i_vector_A[index]);
            o_vector_B[index] = e_x / sum;
        } else {
            e_x = number_exponential(EXPONENTIAL_PRECISION, -1*i_vector_A[index]);
            o_vector_B[index] = 1 / (e_x * sum);
        }
    }
}

void avg_pooling_3D(element_t i_matrix_A[][][], size_t i_rows, size_t i_columns, size_t i_depth,
                size_t i_filter_row, size_t i_filter_column,
                size_t i_stride_row, size_t i_stride_column,
                element_t o_matrix_B[][][], size_t *o_rows, size_t *o_columns) {
    size_t index, jindex, kindex, rindex, pindex;
    size_t matrix_row, matrix_column;
    element_t avg;
    *o_rows = (i_rows - i_filter_row) / i_stride_row + 1;
    *o_columns = (i_columns - i_filter_column) / i_stride_column + 1;
    for(index = 0; index < *o_rows; index++) {
        for(jindex = 0; jindex < *o_columns; jindex++) {
            for(kindex = 0; kindex < i_depth; kindex++) {
                avg = 0; // because it does'n have negative numbers
                for(rindex = 0; rindex < i_kernel_size; rindex++) {
                    for(pindex = 0; pindex < i_kernel_size; pindex++) {
                        matrix_row = index * i_stride_row + rindex;
                        matrix_column = jindex * i_stride_column + pindex;
                        avg = avg + i_matrix_A[matrix_row][matrix_column][kindex];
                    }
                }
                o_matrix_B[index][jindex][kindex] = avg / (i_kernel_size * i_kernel_size);
            }
        }
    }

}



void alexnet_simulation_classify(element_t i_input_data[][][], size_t i_rows,
                                 size_t i_columns, size_t i_rows,
                                 element_t o_class_output[]) {
    size_t index, jindex, kindex;
    size_t stride_row, stride_column, filter_row, filter_column;
    size_t start_depth, end_depth;
    element_t i_first_layer_input[227][227][3];
    size_t padding[4];
    size_t rows, columns;
    size_t aux_rows, aux_columns;
    size_t kernel_size;

    //prepare data for first layer
    stride_row = i_rows / 227;
    stride_column = i_columns / 227;
    start_depth = 0;
    end_depth = 3;
    filter_row = stride_row;
    filter_column = stride_column;
    avg_pooling_3D(i_input_data, i_rows, i_columns, end_depth,
                   filter_row, filter_column,
                   stride_row, stride_column,
                   i_first_layer_input, &aux_rows, &aux_columns);
    

    /* first layer
    * conv 96 of 11x11x3 no padding with stride 4
    * relu
    * max pool 3x3 filter with stride 2
    */
    element_t i_first_layer_conv_output[55][55][96];
    element_t i_second_layer_input[27][27][96];
    element_t i_first_layer_filter[11][11][3];
    element_t i_first_layer_filter_output[55][55];
    size_t i_first_layer_filters_size;
    i_first_layer_filters_size = 96;
    stride_row = 4;
    stride_column = 4;
    start_depth = 0;
    end_depth = 3;
    kernel_size = 11;
    rows = aux_rows;
    columns = aux_columns;
    for(kindex = 0; kindex < i_first_layer_filters_size; kindex++) {
        convolution_3D(i_first_layer_input, rows, columns,
                       start_depth, end_depth,
                       i_first_layer_filter, kernel_size,
                       0, padding[],
                       stride_row, stride_column,
                       i_first_layer_filter_output, &aux_rows, &aux_columns);
        for(index = 0; index < aux_rows; index++) {
            for(jindex = 0; jindex < aux_columns; jindex++) {
                i_first_layer_conv_output[index][jindex][kindex] = i_first_layer_filter_output[index][jindex];
            }
        }
    }

    rows = aux_rows;
    columns = aux_columns;
    ReLU_3D(i_first_layer_conv_output, rows, columns, i_first_layer_filters_size,
            i_first_layer_conv_output);
    stride_row = 2;
    stride_column = 2;
    filter_row = 3;
    filter_column = 3;
    max_pooling_3D(i_first_layer_conv_output, rows, columns, i_first_layer_filters_size,
                   filter_row,  filter_column,
                   stride_row, stride_column,
                   i_second_layer_input, &aux_rows, &aux_columns);


    /* second layer
    * conv 96 of 11x11x3 no padding with stride 4
    * relu
    * max pool 3x3 filter with stride 2
    */
    element_t i_first_layer_conv_output[55][55][96];
    element_t i_second_layer_input[27][27][96];
    element_t i_first_layer_filter[11][11][3];
    element_t i_first_layer_filter_output[55][55];
    size_t i_first_layer_filters_size;
    i_first_layer_filters_size = 96;
    stride_row = 4;
    stride_column = 4;
    start_depth = 0;
    end_depth = 3;
    kernel_size = 11;
    rows = aux_rows;
    columns = aux_columns;
    for(kindex = 0; kindex < i_first_layer_filters_size; kindex++) {
        convolution_3D(i_first_layer_input, rows, columns,
                       start_depth, end_depth,
                       i_first_layer_filter, kernel_size,
                       0, padding[],
                       stride_row, stride_column,
                       i_first_layer_filter_output, &aux_rows, &aux_columns);
        for(index = 0; index < aux_rows; index++) {
            for(jindex = 0; jindex < aux_columns; jindex++) {
                i_first_layer_conv_output[index][jindex][kindex] = i_first_layer_filter_output[index][jindex];
            }
        }
    }

    rows = aux_rows;
    columns = aux_columns;
    ReLU_3D(i_first_layer_conv_output, rows, columns, i_first_layer_filters_size,
            i_first_layer_conv_output);
    stride_row = 2;
    stride_column = 2;
    filter_row = 3;
    filter_column = 3;
    max_pooling_3D(i_first_layer_conv_output, rows, columns, i_first_layer_filters_size,
                   filter_row,  filter_column,
                   stride_row, stride_column,
                   i_second_layer_input, &aux_rows, &aux_columns);
}