#ifndef mtr_hpp
#define mtr_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

struct point{
    int number;
    uint8_t used;
};

template<class T>
class Matrix{
    T** matrix;
    unsigned int SizeN;
    unsigned int SizeM;
    
    void out(point** array, int size);
    int find_min_in_row(int* array, int size);
    int find_min_in_column(int** array, int column_index, int size);
    void delete_min_from_rows(int** array, int size);
    void delete_min_from_columns(int** array, int size);
    int find_used_zero(point** points, int size, int row_index);
    point** copy(int** array, int size);
    void change_to_unused_state(point** array, int size, int column_index);
    bool rec2(point** new_array, int size, int column, int start_column);
    void rec(point** new_array, int size, int i);
    point** set_zeros(int** array, int size);
    point** set_zeros(point** array, int size);
    int find_sum(int** array, point** point_array, int size);
    bool check_every_column_has_zero(point** array, int size);
    void second_step(point** array, int size);
    void copy_int_array(int** m, int size);
public:
    Matrix() = delete;
    Matrix(unsigned int m, unsigned int n);
    ~Matrix();
    
    void clear();
    void fillMatrixRnd(T from, T to);
    void out();
    void work_with_matrix();
    
    T& operator ()(unsigned int m, unsigned int n);
};

template<class T>
T& Matrix<T>::operator ()(unsigned int m, unsigned int n){
    return matrix[m][n];
}

template<class T>
Matrix<T>::Matrix(unsigned int n, unsigned int m){
    if (m <= 0 || n <= 0) return;
    matrix = new T*[m];
    for (int i = 0; i < m; i++){
        matrix[i] = new T[n];
    }
    SizeM = m;
    SizeN = n;
}

template<class T>
Matrix<T>::~Matrix(){
    if (matrix == nullptr) return;
    for (int i = 0; i < SizeM; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
    matrix = nullptr;
}

template<class T>
void Matrix<T>::fillMatrixRnd(T from, T to){
    for (int i = 0; i < SizeM; i++) {
        for (int j = 0; j < SizeN; j++) {
            matrix[i][j] = (from*100 + rand() % ((to - from)*100))/100.0;
        }
    }
}

template<class T>
int** copy_int_array(int** array, int size){
    int** new_array = new int *[size];
    for (int i = 0; i < size; i++) {
        new_array[i] = new int[size];
        for (int l = 0; l < size; l++) {
            new_array[i][l] = array[i][l];
        }
    }
    return new_array;
}

template<class T>
void Matrix<T>::out(){
    if (matrix == nullptr){
        std::cout << "matrix is empty" << std::endl;
        return;
    }
    cout << "Our Matrix" << endl;
    for (int i = 0; i < SizeM; i++) {
        for (int l = 0; l < SizeN; l++){
            int amount = to_string(matrix[i][l]).size();
            for (int j = 0; j < 6 - amount; j++){ cout << ' ';}
            cout << matrix[i][l] << " ";
        }
        cout << endl;
    }
}

template<class T>
void Matrix<T>::clear(){
    for (int i = 0; i < SizeM; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
    matrix = nullptr;
}

template<class T>
void Matrix<T>::out(point** array, int size){
    cout << "Our Matrix(POINTS)" << endl;
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++){
            int amount = to_string(array[i][l].number).size();
            for (int j = 0; j < 6 - amount; j++){ cout << ' ';}
            cout << array[i][l].number << "(" << (int)array[i][l].used << ") ";
        }
        cout << endl;
    }
    cout << endl;
}

template<class T>
int Matrix<T>::find_min_in_row(int* array, int size){
    int min = array[0];
    for (int i = 0; i < size; i++) {
        if (array[i] < min) min = array[i];
    }
    return min;
}

template<class T>
int Matrix<T>::find_min_in_column(int** array, int column_index, int size){
    int min = array[0][column_index];
    for (int i = 0; i < size; i++) {
        if (array[i][column_index] < min) min = array[i][column_index];
    }
    return min;
}

template<class T>
void Matrix<T>::delete_min_from_rows(int** array, int size){
    for (int i = 0; i < size; i++) {
        int min = find_min_in_row(array[i], size);
        for (int l = 0; l < size; l++) {
           array[i][l] = array[i][l] - min;
        }
    }
}

template<class T>
void Matrix<T>::delete_min_from_columns(int** array, int size){
    for (int l = 0; l < size; l++) {
        int min = find_min_in_column(array, l, size);
        for (int i = 0; i < size; i++) {
            array[i][l] = array[i][l] - min;
        }
    }
}

template<class T>
int Matrix<T>::find_used_zero(point** points, int size, int row_index) {
    for (int i = 0; i < size; i++) {
        if (points[row_index][i].used == 1 && points[row_index][i].number == 0){
            return i;
        }
    }
    return -1;
}

template<class T>
point** Matrix<T>::copy(int** array, int size){
    point** new_array = new point *[size];
    for (int i = 0; i < size; i++) {
        new_array[i] = new point[size];
        for (int l = 0; l < size; l++) {
            new_array[i][l].number = array[i][l];
        }
    }
    return new_array;
}

template<class T>
void Matrix<T>::change_to_unused_state(point** array, int size, int column_index) {
    for (int l = 0; l < size; l++) {
        if (array[l][column_index].number == 0 && array[l][column_index].used == 1) {
            array[l][column_index].used = 0;
            break;
        }
    }
}

template<class T>
bool Matrix<T>::rec2(point** new_array, int size, int column, int start_column){
    if (start_column == column) return false;
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (new_array[i][column].number == 0) {
            count++;
            int index = find_used_zero(new_array, size, i);
            if (index == -1){
                change_to_unused_state(new_array, size, column);
                new_array[i][column].used = 1;
                return true;
            }
        }
    }
    if (count == 1) return false;
    for (int l = 0; l < size; l++) {
        if (new_array[l][column].number == 0) {
            int column_index = find_used_zero(new_array, size, l);
            if (rec2(new_array, size, column_index, start_column)) {
                new_array[l][column].used = 1;
                return true;
            }
        }
    }
    return false;
}

template<class T>
void Matrix<T>::rec(point** new_array, int size, int i){
    bool flag = false;
    for (int l = 0; l < size; l++) {
        if (new_array[l][i].number == 0) {
            int index = find_used_zero(new_array, size, l);
            if (index == -1) {
                flag = true;
                new_array[l][i].used = 1;
                break;
            }
        }
    }
    if (!flag){
        for (int l = 0; l < size; l++) {
            if (new_array[l][i].number == 0) {
                int column_index = find_used_zero(new_array, size, l);
                if (rec2(new_array, size, column_index, i)) {
                    new_array[l][i].used = 1;
                    new_array[l][column_index].used = 0;
                    break;
                } else new_array[l][i].used = 2;
            }
        }
    }
    out(new_array, size);
}

template<class T>
point** Matrix<T>::set_zeros(int** array, int size){
    point** new_array = copy(array, size);
    for (int i = 0; i < size; i++) {
        rec(new_array, size, i);
    }
    return new_array;
}

template<class T>
point** Matrix<T>::set_zeros(point** array, int size){
    for (int i = 0; i < size; i++) {
        rec(array, size, i);
    }
    return array;
}

template<class T>
int Matrix<T>::find_sum(int** array, point** point_array, int size){
    int sum = 0;
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++) {
            if (point_array[l][i].used == 1){
                sum += array[l][i];
                break;
            }
        }
    }
    return sum;
}

template<class T>
bool Matrix<T>::check_every_column_has_zero(point** array, int size){
    for (int i = 0; i < size; i++) {
        bool flag = false;
        for (int l = 0; l < size; l++){
            if (array[l][i].used == 1) {
                flag = true;
                break;
            }
        }
        if (!flag) return false;
    }
    return true;
}

template<class T>
void Matrix<T>::second_step(point** array, int size) {
    bool *rows = new bool[size];
    bool *columns = new bool[size];
    for (int i = 0; i < size; i++) {
        rows[i] = false;
        columns[i] = false;
    }
    bool flag = false;
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++) {
            if (array[l][i].used == 1) {
                for (int j = 0; j < size; j++) {
                    if (array[l][j].used == 2) {
                        rows[l] = true;
                        flag = true;
                        break;
                    }
                }
            }
            if (flag) break;
        }
        if (!flag) {
            for (int l = 0; l < size; l++) {
                if (array[l][i].used == 1) {
                    columns[i] = true;
                    break;
                }
            }
        }
        flag = false;
    }
    int min = INT16_MAX;
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++) {
            if (!rows[i] && !columns[l])
                if (min > array[i][l].number) min = array[i][l].number;
        }
    }
    cout << "ROWS";
    for (int i = 0; i < size; i++) {
        cout << " " << rows[i];
    }
    cout << endl;
    cout << "COLUMNS";
    for (int i = 0; i < size; i++) {
        cout << " " << columns[i];
    }
    cout << endl;
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++) {
            if (!rows[i] && !columns[l]) array[i][l].number-= min;
            if (rows[i] && columns[l]) array[i][l].number+= min;
            array[i][l].used = 0;
        }
    }
}

template<class T>
void Matrix<T>::work_with_matrix(){
    int size = SizeM;
    T** initial_array = matrix;
    out();

    cout << "DELETING ELEMENTS!" << endl;
    delete_min_from_rows(matrix, size);
    delete_min_from_columns(matrix, size);
    out();

    cout << "First STEP!" << endl;
    point** final_array = set_zeros(matrix, size);

    if (!check_every_column_has_zero(final_array, size)) {
        cout << "Second STEP!" << endl;
        second_step(final_array, size);
        set_zeros(final_array, size);
    }

    int sum = find_sum(initial_array, final_array, size);
    cout << "SUM: " << sum << endl;
}

#endif /* mtr_hpp */
