#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h> 
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#define PI 3.14159265
using namespace std;

template <typename T>
class Matrix2D{
    private:        
        int row;
        int col;
    public:
        T** mat_data;
        Matrix2D(int row_sz, int col_sz){
            row = row_sz;
            col = col_sz;
            mat_data = new T*[row];
            for(int i = 0; i < row; i++)
                mat_data[i] = new T[col];
        }
        ~Matrix2D(){
            for(int i = 0; i < row; i++)
                delete[] mat_data[i];
            delete[] mat_data;
        }
        void initRandom(){
            for (int i=0; i < row; i++){
                 for (int j=0; j < col; j++){
                    mat_data[i][j] = (T)rand();
                }
            }
        }
        void initVal(T value){
            for (int i=0; i < row; i++){
                 for (int j=0; j < col; j++){
                    mat_data[i][j] = value;
                }
            }
        }
        void initDiag(T value){
            for (int i=0; i < row; i++){
                 for (int j=0; j < col; j++){
                    if (i == j)
                        mat_data[i][j] = value;
                }
            }
        }
        T getElement(int i, int j){
            return mat_data[i][j];
        }
        T setElement(int i, int j, T value){
            mat_data[i][j] = value;
        }
        T addToElement(int i, int j, T value){
            mat_data[i][j] += value;
        }
        int getRowSz(){
            return row;
        }
        int getColSz(){
            return col;
        }
        void print(){
            for (int i=0; i < row; i++){
                 for (int j=0; j < col; j++){                    
                    cout << fixed <<setprecision(6) << setfill('0')<<setw(6)<< +mat_data[i][j] << "  " ;
                }
                cout <<endl;
            }
        }
};

template <typename T>
Matrix2D<T> multiply2DMatrix(Matrix2D<T>& A, Matrix2D<T>& B){
    if(A.getColSz() != B.getRowSz()){
        perror("matrix A column and B row mismatch for multiplication.");
        exit(-1);
    }
    Matrix2D<T> mat_data(A.getRowSz(), B.getColSz());
    mat_data.initVal(0);
    for(int i=0; i<A.getRowSz(); ++i){
         for(int j=0; j<B.getColSz(); ++j){
            for(int k=0; k<A.getColSz(); ++k) {
                mat_data.addToElement(i,j,A.getElement(i,k)*B.getElement(k,j));
            }
        }
    }
    return mat_data;
}

template <typename T>
class Matrix4x4: public Matrix2D<T>{    
public:
    Matrix4x4(): Matrix2D<T>(4,4){
        this->initVal(0);
    }
    void printRotation(){
        cout << "rotations" <<endl;
        for (int i=0; i < 3; i++){
             for (int j=0; j < 3; j++){                    
                cout <<fixed <<setprecision(6) << setfill('0')<<setw(6)<< +this->getElement(i,j) << "  " ;
            }
            cout <<endl;
        }
    }
    void printDisplacement(){
        cout << "displacement" <<endl;
        cout << "x : " << fixed <<setprecision(6) << setfill('0')<<setw(6)<< +this->getElement(0,3)<<endl;;
        cout << "y : " << fixed <<setprecision(6) << setfill('0')<<setw(6)<< +this->getElement(1,3)<<endl;;
        cout << "z : " << fixed <<setprecision(6) << setfill('0')<<setw(6)<< +this->getElement(2,3)<<endl;;
    }
};

template <typename T>
class Rotation_Z: public Matrix4x4<T>{
private:
    T theta;
public:
    Rotation_Z():Matrix4x4<T>(){        
    }  
    void setTheta(T theta){
        T cosTheta = (T)cos(theta);
        T sinTheta = (T)sin(theta);
        this->setElement(0,0, cosTheta);
        this->setElement(1,0, sinTheta);
        this->setElement(0,1, -sinTheta);
        this->setElement(0,1, cosTheta);
    }
    T getTheta(){
        return theta;
    }
};

template <typename T>
class Rotation_X: public Matrix4x4<T>{
private:
    T theta;
public:
    Rotation_X():Matrix4x4<T>(){        
    }  
    void setTheta(T theta){
        this->initDiag(1);
        T cosTheta = (T)cos(theta);
        T sinTheta = (T)sin(theta);
        this->setElement(1,1, cosTheta);
        this->setElement(2,1, sinTheta);
        this->setElement(1,2, -sinTheta);
        this->setElement(2,2, cosTheta);
    }
    T getTheta(){
        return theta;
    }
};

template <typename T>
class Trans_Z: public Matrix4x4<T>{
private:
    T delta;
public:
    Trans_Z():Matrix4x4<T>(){        
    }  
    void setDelta(T delta){
        this->initDiag(1);
        this->setElement(2,3, delta);
    }
    T getDelta(){
        return delta;
    }
};

template <typename T>
class Trans_X: public Matrix4x4<T>{
private:
    T delta;
public:
    Trans_X():Matrix4x4<T>(){        
    }  
    void setDelta(T delta){
        this->initDiag(1);
        this->setElement(0,3, delta);
    }
    T getDelta(){
        return delta;
    }
};

template <typename T>
class DHjoint: public Matrix4x4<T>{
private:
    T thetaZ;
    T thetaX;
    T deltaZ;
    T deltaX;
public:
    DHjoint():Matrix4x4<T>(){
    }
    void setJoint(T thetaZ, T thetaX, T deltaZ, T deltaX){
        this->thetaZ = thetaZ;
        this->thetaX = thetaX;
        this->deltaZ = deltaZ;
        this->deltaX = deltaX;
    }
    void transform(){
        T cosThetaZ = (T)cos(thetaZ);
        T sinThetaZ = (T)sin(thetaZ);
        T cosThetaX = (T)cos(thetaX);
        T sinThetaX = (T)sin(thetaX);
        this->initDiag(1);
        this->setElement(0,0, cosThetaZ);
        this->setElement(1,0, sinThetaZ);
        this->setElement(0,1, -sinThetaZ*cosThetaX);
        this->setElement(1,1, cosThetaZ*cosThetaX);
        this->setElement(2,1, sinThetaX);
        this->setElement(0,2, sinThetaZ*sinThetaX);
        this->setElement(1,2, -cosThetaZ*sinThetaX);
        this->setElement(2,2, cosThetaX);
        this->setElement(0,3, deltaX*cosThetaZ);
        this->setElement(1,3, deltaX*sinThetaZ);
        this->setElement(2,3, deltaZ);
    }
    void transform(T thetaZ, T thetaX, T deltaZ, T deltaX){
        setJoint(thetaZ, thetaX, deltaZ, deltaX);
        transform();
    }
};

int main(int argc, char *argv[]){
    Rotation_Z<double> A;
    Trans_Z<double> B;
    Trans_X<double> C;
    Rotation_X<double> D;
    double thetaZ = 90.0*PI/180.0;
    double thetaX = 15.0*PI/180.0;
    double deltaZ =2.0;
    double deltaX = 1.02;
    A.setTheta(thetaZ);
    B.setDelta(deltaZ);
    C.setDelta(deltaX);
    D.setTheta(thetaX);
    Matrix2D<double> product = multiply2DMatrix(A,B);
    product = multiply2DMatrix(product,C);
    product = multiply2DMatrix(product,D);
    DHjoint<double> dhjoint;
    dhjoint.transform(thetaZ,thetaX,deltaZ, deltaX);
    cout << "prodcut = " <<endl;
    product.print();
    cout << "DHjoint = " <<endl;
    dhjoint.print();
    dhjoint.printDisplacement();
    dhjoint.printRotation();
    
    return 0;      
}



