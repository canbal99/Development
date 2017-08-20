/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: can
 *
 * Created on August 19, 2017, 8:38 PM
 */

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <set>

using namespace std;

#define __TEST__
#define MAX(x,y)     ((x)>(y)?(x):(y))

struct Piece {
    int x;
    int y;
    int value;
    bool isEqual(const Piece& piece) const {
        return piece.x==x && piece.y==y;
    }
    bool canBeat(const Piece& piece, bool pos) const {
        return piece.x-x == (pos?piece.y-y:y-piece.y);
    }
    bool isNeighbour(const Piece& piece, bool pos) const {
        return abs(piece.x-x) == 1 && abs(piece.y-y) == 1;
    }
    Piece projection(const Piece& piece, bool pos) const {
        Piece temp = {0,0,0};
        temp.x = pos ? x+(piece.x-x+piece.y-y)/2 : x+(piece.x-x-piece.y+y)/2;
        temp.y = pos ? y+(piece.x-x+piece.y-y)/2 : y-(piece.x-x-piece.y+y)/2;
        return temp;
    }
    Piece findNextPositionAfterBeating(const Piece& piece) const {
        Piece temp = {0,0,0};
        temp.x = x<piece.x ? piece.x+1 : piece.x-1;
        temp.y = y<piece.y ? piece.y+1 : piece.y-1;
        return temp;
    }
};

struct PositiveAxis {
    bool operator() (const Piece& lhs, const Piece& rhs) const {
        if ((lhs.x+lhs.y)!=(rhs.x+rhs.y))
            return (lhs.x+lhs.y)<(rhs.x+rhs.y);
        return (lhs.x-lhs.y)<(rhs.x-rhs.y);
    }
};

struct NegativeAxis {
    bool operator() (const Piece& lhs, const Piece& rhs) const {
        if ((lhs.x-lhs.y)!=(rhs.x-rhs.y))
            return (lhs.x-lhs.y)<(rhs.x-rhs.y);
        return (lhs.x+lhs.y)<(rhs.x+rhs.y);
    }
};

void printPiece(const Piece& piece, string title="") {
    if (title.length()>0) cout << title << endl;
    cout << "x:" << piece.x << " y:" << piece.y << " value: " << piece.value << endl;
}

template <class T>
void printSet(set<Piece,T>& axis, string title="") {
    if (title.length()>0) cout << title << endl;
    for (auto item : axis) {
        printPiece(item);
    }
}

class GameBoard {
public:
    GameBoard(vector<int> &X, vector<int> &Y, string &T) {
        Piece temp;
        for (int i=0; i<T.size();i++) {
            temp.x = X[i];
            temp.y = Y[i];
            if (T[i]=='X') temp.value = 0;
            else temp.value = (T[i]=='p'?1:10);
            insertPieceToSets(temp);
            if (temp.value==0) myPiece = temp;
        }
        
#ifdef __TEST__
        printPiece(myPiece, "MyPiece:");
        printSet<PositiveAxis>(positiveAxis, "Positive:");
        printSet<NegativeAxis>(negativeAxis, "Negative:");
#endif
    }
    
    int findMaxValue() {
        return findMaxValue(myPiece);
    }
    
private:
    int findMaxValue(const Piece& startFromPiece) {
        int valueOnPosForw = findMaxValue(startFromPiece, true, true);
        int valueOnPosBack = findMaxValue(startFromPiece, false, true);
        int valueOnNegForw = findMaxValue(startFromPiece, true, false);
        int valueOnNegBack = findMaxValue(startFromPiece, false, false);
        return MAX(MAX(valueOnPosForw,valueOnPosBack),MAX(valueOnNegForw,valueOnNegBack));
    }
    
    int findMaxValue(const Piece& startFromPiece, bool FORWARD, bool POSITIVE) {
        int value=0, curr, max;
        Piece tempPos, tempMyPiece, tempBeatenPiece;
#ifdef __TEST__
        cout << endl << ">>> calling findMaxValue " << FORWARD << " " << POSITIVE << endl;
        printPiece(startFromPiece, "startFromPiece:");
        printSet<PositiveAxis>(positiveAxis, "Positive:");
        printSet<NegativeAxis>(negativeAxis, "Negative:");
#endif
        auto myPieceOnPos = POSITIVE ? positiveAxis.find(startFromPiece) : negativeAxis.find(startFromPiece);
#ifdef __TEST__
        printPiece(*myPieceOnPos, "myPieceOnPos:");
#endif
        auto nextItemOnPos = myPieceOnPos;
        iterate(&nextItemOnPos, FORWARD, POSITIVE);
        while (!checkIfEndOfIteration(&nextItemOnPos,FORWARD,POSITIVE)) {
#ifdef __TEST__
        printPiece(*nextItemOnPos, "nextItemOnPos:");
#endif
            if ((*myPieceOnPos).canBeat(*nextItemOnPos, POSITIVE)) {
#ifdef __TEST__
        printPiece(*nextItemOnPos, "CAN BE BEATEN");
#endif
                value = (*nextItemOnPos).value;
                auto nextNextItemOnPos = nextItemOnPos;
                iterate(&nextNextItemOnPos, FORWARD, POSITIVE);
                
                tempMyPiece = *myPieceOnPos;
                erasePieceFromSets(*myPieceOnPos);
                tempBeatenPiece = *nextItemOnPos;
                erasePieceFromSets(*nextItemOnPos);
                
                curr = 0; max = 0;
                while (!checkIfEndOfIteration(&nextNextItemOnPos,FORWARD,POSITIVE)) {
                    if ((*nextItemOnPos).canBeat(*nextNextItemOnPos, POSITIVE)) {
                        if ((*nextItemOnPos).isNeighbour(*nextNextItemOnPos, POSITIVE)) {
                            value = 0;
                            max = 0;
                        }
                        break;
                    } 
                    
                    tempPos = (*myPieceOnPos).projection(*nextNextItemOnPos, POSITIVE);
                    if ((*nextItemOnPos).isEqual(tempPos)) {
                        iterate(&nextNextItemOnPos, FORWARD, POSITIVE);
                        continue;
                    }

                    if (!insertPieceToSets(tempPos)) {
                        iterate(&nextNextItemOnPos, FORWARD, POSITIVE);
                        continue;
                    }

                    curr = findMaxValue(tempPos);
                    erasePieceFromSets(tempPos);
                    
                    if (max<curr) max=curr;
                    iterate(&nextNextItemOnPos, FORWARD, POSITIVE);
                }
                if (value>0 && max==0) {
                    tempPos = (*myPieceOnPos).findNextPositionAfterBeating(*nextItemOnPos);
                    if (insertPieceToSets(tempPos)) {
                        max = findMaxValue(tempPos);
                        erasePieceFromSets(tempPos);
                    }
                }
                value += max;
                insertPieceToSets(tempBeatenPiece);
                insertPieceToSets(tempMyPiece);
                break;
            } else {
#ifdef __TEST__
        printPiece(*nextItemOnPos, "No beat");
#endif
                iterate(&nextItemOnPos, FORWARD, POSITIVE);
            }
        }
#ifdef __TEST__
        cout << "<<< returning " << FORWARD << " " << POSITIVE << " value:" << value << endl;
#endif
        return value;
    }
    
    void iterate(void *iterator, bool FORWARD, bool POSITIVE) {
        if (POSITIVE) {
            set<Piece, PositiveAxis>::iterator &iter(*(set<Piece, PositiveAxis>::iterator*)(iterator));
            if (FORWARD) {
                iter++;
            } else if (iter==positiveAxis.begin()) {
                iter = positiveAxis.end();
            } else {
                iter--;
            }
        } else {
            set<Piece, NegativeAxis>::iterator &iter(*(set<Piece, NegativeAxis>::iterator*)(iterator));
            if (FORWARD) {
                iter++;
            } else if (iter==negativeAxis.begin()) {
                iter = negativeAxis.end();
            } else {
                iter--;
            }
        }
    }
    
    bool checkIfEndOfIteration(void *iterator, bool FORWARD, bool POSITIVE) {
        if (POSITIVE) {
            set<Piece, PositiveAxis>::iterator &iter(*(set<Piece, PositiveAxis>::iterator*)(iterator));
            return iter==positiveAxis.end();
        } else {
            set<Piece, NegativeAxis>::iterator &iter(*(set<Piece, NegativeAxis>::iterator*)(iterator));
            return iter==negativeAxis.end();
        }
    }
    
    void erasePieceFromSets(const Piece& piece) {
#ifdef __TEST__
        printPiece(piece, "Erasing:");
#endif
        positiveAxis.erase(piece);
        negativeAxis.erase(piece);
    }
    
    bool insertPieceToSets(const Piece& piece) {
#ifdef __TEST__
        printPiece(piece, "Inserting:");
#endif
        if (positiveAxis.insert(piece).second)
            return negativeAxis.insert(piece).second;
#ifdef __TEST__
        printPiece(piece, "Inserting failed!!!:");
#endif
        return false;
    }
    
private:
    set<Piece,PositiveAxis> positiveAxis;
    set<Piece,NegativeAxis> negativeAxis;
    Piece myPiece;
};

int solution(vector<int> &X, vector<int> &Y, string &T) {
    GameBoard board(X, Y, T);
    return board.findMaxValue();
}

int main(int argc, char** argv) {

    {/*
    vector<int> X = {3, 5, 1, 6};
    vector<int> Y = {1, 3, 3, 8};
    string T = "Xpqp";
    cout << "Answer should be 10" << endl;
    cout << solution(X,Y,T) << endl;*/
    }
    
    {
    vector<int> X = {0, 3, 5, 1, 6};
    vector<int> Y = {4, 1, 3, 3, 8};
    string T = "pXpqp";
    cout << "Answer should be 2" << endl;
    cout << solution(X,Y,T) << endl;
    }
    
    {/*
    vector<int> X = {0, 6, 2, 5, 3, 0};
    vector<int> Y = {4, 8, 2, 3, 1, 6};
    string T = "ppqpXp";
    cout << "Answer should be 12" << endl;
    cout << solution(X,Y,T) << endl;*/
    }
            
    return 0;
}

