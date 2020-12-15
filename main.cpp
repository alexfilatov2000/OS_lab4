#include <iostream>
#include "mtr.hpp"

int main() {
    Matrix<int> m(3, 3);
    m.fillMatrixRnd(1, 20);
    m.work_with_matrix();
}
