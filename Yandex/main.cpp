/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: can
 *
 * Created on August 11, 2017, 4:25 PM
 */

#include <cstdlib>
#include <stdio.h>

using namespace std;

struct Point {
    double x;
    double y;
};

class Feature {
public:
    Feature() : valid(false) {}
    virtual ~Feature() {}
    virtual void read(FILE *file) = 0;
    virtual void draw() = 0;
    bool isValid() {return valid;}
protected:
    bool valid;
};

class Circle : public Feature {
public:
    void read(FILE *file) {
        if (fread(&center, sizeof(center), 1, file) != 1) {
            return;
        }
        if (fread(&radius, sizeof(radius), 1, file) != 1) {
            return;
        }
        valid = true;
    }
    void draw() {printf("drawing circle");/*drawCircle(center.x, center.y, radius);*/}
    
protected:
    Point center;
    double radius;
};

class Polygon : public Feature {
public:
    void read(FILE *file) {
        if (fread(points(), sizeof(double), pointCount(), file) != pointCount()) {
            return;
        }
        valid = true;
    }
    void draw() {printf("drawing polygon");/*drawPolygon(points(), pointCount());*/}
protected:
    virtual double* points() = 0;
    virtual int pointCount() = 0;
};

class Triangle : public Polygon {
protected:
    double* points() {return (double*)corners;};
    int pointCount() {return sizeof(corners)/sizeof(double);};
protected:
    Point corners[3];
};

class Square : public Polygon {
protected:
    double* points() {return (double*)corners;};
    int pointCount() {return sizeof(corners)/sizeof(double);};
protected:
    Point corners[4];
};

class FeatureFactory {
public:
    enum FeatureType {eUnknown, eCircle, eTriangle, eSquare};
    
    Feature* createFeature(const char* filename) {
        Feature* newFeature = NULL;
        FILE* file = fopen(filename, "r");
        if (file) {
            FeatureType type;
            if (fread(&type, sizeof(FeatureType), 1, file) == 1) {
                switch (type) {
                    case eCircle:
                        newFeature = new Circle(); 
                        break;
                    case eTriangle:
                        newFeature = new Triangle(); 
                        break;
                    case eSquare:
                        newFeature = new Square(); 
                        break;
                    default:
                        break;
                }
            }
            if (newFeature) {
                newFeature->read(file);
            }
            fclose(file);
        }
        return newFeature;
    }
};
/*
 * in destructor, we can use "delete [] points" instead of "delete points"
 * inside read function, we need "if (points) delete points;" before creating new points (so as to use read function several times without memory leak)
 * Check if fopen is successful (if (file) then read&close)
 * close file descriptor after read operation if fopen operation is successful
 * fread returns number of items read, not the number of bytes read
 * 
 * Besides those, OOP principles such as abstraction, SOLID's single responsibility is totally ignored.
 * This sample code is a very good example for anti design patterns :)
 * 
int main(int argc, char* argv[])
{
    // CREATE TEST DATA /////////////////////
    FILE *file;
    FeatureFactory::FeatureType type;
    double temp[] = {1,2,3,4,5,6,7,8};
    char *testfilenames[] = {
        "./unknown.dat",
        "./circle.dat",
        "./triangle.dat",
        "./square.dat"
    };
    for (int type=0; type<=3; type++) {
        file = fopen(testfilenames[type],"w");
        fwrite(&type,sizeof(type),1,file);
        fwrite(&temp,sizeof(double),8,file);
        fclose(file);
    }
    /////////////////////////////////////////
    int returnValue;
    FeatureFactory factory;
    Feature *feature;
    
    for (int type=0; type<=3; type++) {
        feature = factory.createFeature(testfilenames[type]);
        returnValue = (feature && feature->isValid()) ? 0 : 1;
        if (feature) delete feature;
        printf("filename: %s type:%d returnValue:%d\n", testfilenames[type], type, returnValue);
    }
    return returnValue;
    
}
*/

#include <vector>
#include <set>
#include <iostream>

void printVector(std::vector<double>& v) {
    double sum = 0;
    for (auto item : v) {
        cout << item << " - ";
        sum += item;
    }
    cout /*<< sum*/ << endl;
}

double sum1(std::vector<double>& v)
{    
    if (v.empty()) {
        return 0.0;
    }
    for(size_t i = 0; i < v.size() - 1; ++i) {
        std::sort(v.begin()+i, v.end());
        v[i+1] += v[i];
    }
    return v.back();
}
 
double sum2(std::vector<double>& v)
{    
    if (v.empty()) {
        return 0.0;
    }
    for(size_t i = 0; i < v.size() - 1; ++i) {
        std::partial_sort(v.begin() + i, v.begin() + i + 2, v.end());
        v[i+1] += v[i];
    }
    return v.back();
}
 
double sum3(std::vector<double>& v)
{    
    std::multiset<double> set(v.begin(), v.end());
    while (set.size() > 1) {
        std::multiset<double>::const_iterator itA = set.begin();
        std::multiset<double>::const_iterator itB = ++set.begin();
        double c = *itA + *itB;
        set.erase(itA, ++itB);        
        set.insert(c);
    }
    return !set.empty() ? *set.begin() 
                        : 0.0;
}

double sum4(std::vector<double>& v)
{    
    if (v.empty()) {
        return 0.0;
    }
    for(size_t i = 0; i < v.size() - 1; ++i) {
        v[i+1] += v[i];
    }
    return v.back();
}

/* 
 For the three different implementations of floating point summation listed here:
 , estimate the complexity (or performance) for the case, if size of input data array is increased by 1,000 times. Numbers in input data array are always positive. 

Please explain your answer and comment on the question. 

Paste your solution here or provide a link to the Github repository.
 * complexity of sum1 & sum2 increases exponentially (for 1000, performance will decrease 1000000(million) times)
 * complexity of sum3 is linear.
 * there is a problem with sum3 function. erase operation should be done like that => set.erase(itA, ++itB);

 */

int main(int argc, char* argv[])
{
    clock_t begin, end;
    double result;
    vector<double> v(1);
    while(v.capacity()<100000) {
    cout << "vector size:" << v.size() << endl;
        
    for (int i=0;i<v.capacity();i++) {
        v[i] = (rand()%100)/7.0;
    }
    //printVector(v);
    
    vector<double> v0(v);
    begin = clock();
    sort(v0.begin(),v0.end(),[](double left, double right){return left<right;});
    end = clock();
    cout << "sort timepassed:" << end-begin << endl; // DEFINITELY LINEAR
    //printVector(v0);
    
    vector<double> v1(v.begin(),v.end());
    begin = clock();
    result = sum1(v1);
    end = clock();
    cout << "sum1 timepassed:" << end-begin << " result:" << result << endl;
    //printVector(v1);
    
    vector<double> v2(v.begin(),v.end());
    begin = clock();
    result = sum2(v2);
    end = clock();
    cout << "sum2 timepassed:" << end-begin << " result:" << result << endl;
    //printVector(v2);
    
    vector<double> v3(v.begin(),v.end());
    begin = clock();
    result = sum3(v3);
    end = clock();
    cout << "sum3 timepassed:" << end-begin << " result:" << result << endl;
    //printVector(v3);
    
    vector<double> v4(v.begin(),v.end());
    begin = clock();
    result = sum4(v4);
    end = clock();
    cout << "sum4 timepassed:" << end-begin << " result:" << result << endl;
    //printVector(v3);
    
    v.resize(v.size()*10);
    }
    
}

/* QUESTION 4
 * You are required to improve performance of an application written in C++. What are the typical performance bottlenecks? How can they be located and fixed?
 * 
 * Some tricks
 * In constructors, don't do any unnecessary thing (like Zero-Initialize) if you have an array of this object
 * don't use clear, use r esize(0) (if you don't need to free memory)
 * worst->best  qsort < sort < partial_sort < partition
 * try to use inline functions
 * 
 * Incorrect container choices can effect performance.
 * If there is a much amount of data access and no modification, vector/deque can be used
 * If there is need for modification, list/set/map should be chosen (or unordered_map could be used to have a constant access/modify)
 * Even sometimes old style c arrays should be considered depending on the situation
 * 
 * Locks can be an important bottleneck on multithreaded applications.
 * You need to review lock cases. You can put some delay(sleep) inside locks to see if there is any deadlock for testing.
 * 
 * Memory and CPU Profiling tools help us determine performance bottlenecks easily,
 * 
 */