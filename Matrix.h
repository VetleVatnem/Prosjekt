#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <cassert>

template<typename Type>
class Matrix{
    private:
        std::shared_ptr<std::vector<std::vector<Type>>> matrix;
        unsigned int col;
        unsigned int row;
        bool Square;

    public:
        //Konstruktører
        Matrix(unsigned int size , Type value): 
        Square(true) ,
        col(size),
        row(size)
        {
            matrix = std::make_shared<std::vector<std::vector<Type>>>(size , std::vector<Type>(size , value));
        }
        Matrix(unsigned int rows , unsigned int  cols , Type value) :
        Square(false),
        col(cols),
        row(rows)
        {
            matrix = std::make_shared<std::vector<std::vector<Type>>>(row , std::vector<Type>(col , value));
        }

        //Funksjoner
        void setElement(int& row , int& col , Type value){
            (*matrix)[row][col] = value;
        }
        Type getElement(int& row , int& col)const{
            return (*matrix)[row][col];
        }
        unsigned int getRows()const{
            return row;
        }
        unsigned int getCols()const{
            return col;
        }
        bool isSquare(){
            return this->Square;
        }
        void addRow(std::vector<Type> row){
            assert(row.size() == this->col);
            matrix->push_back(row);
            this->row += 1;
            if (this->col != this->row){
                this->Square = false;
            }
            else{
                this->Square = true; 
            }
        }
        void addColumn(std::vector<Type> column){
            assert(column.size() == this->row);
            for (unsigned int i = 0; i < this->row; ++i) {
                (*matrix)[i].push_back(column[i]);
            }
            this->col += 1;
            if (this->col == this->row) {
                this->Square = true;
            } else {
                this->Square = false;
            } 
        }

        //Operatorer
        friend std::ostream& operator<<(std::ostream& os ,const Matrix& ref){
            for (auto i = 0 ; i < ref.row ; i++){
                for (auto j = 0 ; j < ref.col ; j++){
                    os << ref.getElement(i , j) << " ";
                }
                os << '\n';
            }
            return os;
        }
        std::vector<Type>& operator[](int row){
            return (*matrix)[row];
        }
        const std::vector<Type>& operator[](int row) const {
            return (*matrix)[row];
        }
        std::vector<Type> operator*(const std::vector<double>& vector){
            assert (this->getCols() == vector.size());
            std::vector<Type> result(this->getRows() , 0);

            for (auto i = 0 ; i < this->getRows() ; i++){
                Type sum{0};
                for (auto j = 0 ; j < vector.size() ; j++){
                    sum += (*matrix)[i][j]*vector[j];
                }
                result[i] = sum;
            }
            return result;
        }
        Matrix<Type> operator*(const Matrix<Type>& matrix){
            Matrix<Type> result(this->getRows() , matrix.getCols() , 0);
            for (auto i = 0 ; i < this->getRows() ; i++){
                for (auto j = 0 ; j < matrix.getCols() ; j++){
                    Type sum = 0;
                    for (auto a = 0 ; a < matrix.getRows() ; a++){
                        sum += (*this)[i][a] * matrix[a][j];
                    }
                    result[i][j] = sum;
                }
            }
            return result;
        }

    };

