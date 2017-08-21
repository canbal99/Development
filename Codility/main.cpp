// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <vector>
#include <string>
#include <iostream>
#include <set>

using namespace std;

//#define __TEST__
#define MAX(x,y)     ((x)>(y)?(x):(y))

struct Piece {
    int x;
    int y;
    int value;
    bool alreadyBeaten;
    
    Piece() : x(0), y(0), value(0), alreadyBeaten(false) {};
    
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
        Piece temp = Piece();
        temp.x = pos ? x+(piece.x-x+piece.y-y)/2 : x+(piece.x-x-piece.y+y)/2;
        temp.y = pos ? y+(piece.x-x+piece.y-y)/2 : y-(piece.x-x-piece.y+y)/2;
        return temp;
    }
    Piece findNextPositionAfterBeating(const Piece& piece) const {
        Piece temp = Piece();
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
    if (title.length()>0) cout << title << " ";
    cout << "x:" << piece.x << " y:" << piece.y << " value: " << piece.value << " deleted:" << piece.alreadyBeaten << endl;
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
        Piece temp = Piece();
        for (int i=0; i<(int)T.size();i++) {
            temp.x = X[i];
            temp.y = Y[i];
            if (T[i]=='X') temp.value = 0;
            else temp.value = (T[i]=='p'?1:10);
            if (temp.value==0) myPiece = temp;
            else insertPieceToSets(temp);
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
        int valueOnPosBack = 0; // findMaxValue(startFromPiece, false, true);
        int valueOnNegForw = 0; // findMaxValue(startFromPiece, true, false);
        int valueOnNegBack = findMaxValue(startFromPiece, false, false);
        return MAX(MAX(valueOnPosForw,valueOnPosBack),MAX(valueOnNegForw,valueOnNegBack));
    }
    
    int findMaxValue(const Piece& startFromPiece, bool FORWARD, bool POSITIVE) {
        int value=0, curr, max;
        Piece tempPos, prevTempPos;
        bool findMaxValueCalledForTempPos = false;
#ifdef __TEST__
        cout << endl << ">>> calling findMaxValue " << FORWARD << " " << POSITIVE << endl;
        printPiece(startFromPiece, "startFromPiece:");
        printSet<PositiveAxis>(positiveAxis, "Positive:");
        printSet<NegativeAxis>(negativeAxis, "Negative:");
#endif
        auto nextItemOnPos = POSITIVE ? positiveAxis.upper_bound(startFromPiece) : negativeAxis.upper_bound(startFromPiece);
        if (!FORWARD) iterate(&nextItemOnPos, FORWARD, POSITIVE);
        
#ifdef __TEST__
        printPiece(*nextItemOnPos, "nextItemOnPos Initial:");
#endif
        if (!checkIfEndOfIteration(&nextItemOnPos,FORWARD,POSITIVE) && (*nextItemOnPos).alreadyBeaten)
            iterate(&nextItemOnPos, FORWARD, POSITIVE);
        while (!checkIfEndOfIteration(&nextItemOnPos,FORWARD,POSITIVE)) {
#ifdef __TEST__
        printPiece(*nextItemOnPos, "nextItemOnPos Final:");
#endif
            if (startFromPiece.canBeat(*nextItemOnPos, POSITIVE)) {
#ifdef __TEST__
        printPiece(*nextItemOnPos, "CAN BE BEATEN");
#endif
                value = (*nextItemOnPos).value;
                auto nextNextItemOnPos = nextItemOnPos;
                iterate(&nextNextItemOnPos, FORWARD, POSITIVE);
                
                erasePieceFromSets(*nextItemOnPos);
                
                curr = 0; max = 0;
                while (!checkIfEndOfIteration(&nextNextItemOnPos,FORWARD,POSITIVE)) {
                    if ((*nextItemOnPos).canBeat(*nextNextItemOnPos, POSITIVE)) {
#ifdef __TEST__
        printPiece(*nextNextItemOnPos, "Find next item on my way, so I don't need to check next elements");
#endif
                        if ((*nextItemOnPos).isNeighbour(*nextNextItemOnPos, POSITIVE)) {
                            value = 0;
                            max = 0;
#ifdef __TEST__
        printPiece(*nextItemOnPos, "This is a neighbor so I cannot beat this item");
#endif
                        }
                        break;
                    } 
                    
                    tempPos = startFromPiece.projection(*nextNextItemOnPos, POSITIVE);
                    
                    if (findMaxValueCalledForTempPos && prevTempPos.isEqual(tempPos)) {
                        iterate(&nextNextItemOnPos, FORWARD, POSITIVE);
                        continue;
                    }
                    
                    if ((*nextItemOnPos).isEqual(tempPos)) {
                        iterate(&nextNextItemOnPos, FORWARD, POSITIVE);
                        continue;
                    }

                    if (existInSet(tempPos)) {
                        iterate(&nextNextItemOnPos, FORWARD, POSITIVE);
                        continue;
                    }

                    curr = findMaxValue(tempPos);
                    findMaxValueCalledForTempPos = true;
                    prevTempPos = tempPos;
                    
                    if (max<curr) max=curr;
                    iterate(&nextNextItemOnPos, FORWARD, POSITIVE);
                }
                if (value>0 && !findMaxValueCalledForTempPos) {
                    tempPos = startFromPiece.findNextPositionAfterBeating(*nextItemOnPos);
                    max = findMaxValue(tempPos);
                }
                value += max;
                insertPieceToSets(*nextItemOnPos);
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
        do {
            iterate_old(iterator, FORWARD, POSITIVE);
        } while (!checkIfEndOfIteration(iterator, FORWARD, POSITIVE) && alreadyBeaten(iterator, FORWARD, POSITIVE));
    }
    
    void iterate_old(void *iterator, bool FORWARD, bool POSITIVE) {
        if (POSITIVE) {
            set<Piece, PositiveAxis>::iterator &iter(*(set<Piece, PositiveAxis>::iterator*)(iterator));
            if (FORWARD) {
                if (iter != positiveAxis.end())
                    iter++;
            } else if (iter==positiveAxis.begin()) {
                iter = positiveAxis.end();
            } else {
                iter--;
            }
        } else {
            set<Piece, NegativeAxis>::iterator &iter(*(set<Piece, NegativeAxis>::iterator*)(iterator));
            if (FORWARD) {
                if (iter != negativeAxis.end())
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
    
    bool existInSet(const Piece& piece) {
        auto found = positiveAxis.find(piece);
        return found!=positiveAxis.end() && !(*found).alreadyBeaten;
    }
    
    void erasePieceFromSets(const Piece& piece) {
#ifdef __TEST__
        printPiece(piece, "Erasing:");
#endif
        auto positive = positiveAxis.find(piece);
        if (positive!=positiveAxis.end()) {
            ((Piece&)(*positive)).alreadyBeaten = true;
        }
        auto negative = negativeAxis.find(piece);
        if (negative!=negativeAxis.end()) {
            ((Piece&)(*negative)).alreadyBeaten = true;
        }
    }
    
    void insertPieceToSets(const Piece& piece) {
#ifdef __TEST__
        printPiece(piece, "Inserting:");
#endif
        auto positive = positiveAxis.find(piece);
        if (positive!=positiveAxis.end()) {
            ((Piece&)(*positive)).alreadyBeaten = false;
        } else {
            positiveAxis.insert(piece);
        }
        
        auto negative = negativeAxis.find(piece);
        if (negative!=negativeAxis.end()) {
            ((Piece&)(*negative)).alreadyBeaten = false;
        } else {
            negativeAxis.insert(piece);
        }
    }
    
    bool alreadyBeaten(void *iterator, bool FORWARD, bool POSITIVE) {
        if (POSITIVE) {
            set<Piece, PositiveAxis>::iterator &iter(*(set<Piece, PositiveAxis>::iterator*)(iterator));
            return (*iter).alreadyBeaten;
        } else {
            set<Piece, NegativeAxis>::iterator &iter(*(set<Piece, NegativeAxis>::iterator*)(iterator));
            return (*iter).alreadyBeaten;
        }
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

    do {
    vector<int> X1 = {3, 5, 1, 6};
    vector<int> Y1 = {1, 3, 3, 8};
    string T1 = "Xpqp";
    cout << "Answer should be 10" << endl;
    int result1 = solution(X1,Y1,T1);
    cout << "RESULT: " << result1 << endl;
    if (result1!=10) break;
    
    vector<int> X2 = {0, 3, 5, 1, 6};
    vector<int> Y2 = {4, 1, 3, 3, 8};
    string T2 = "pXpqp";
    cout << "Answer should be 2" << endl;
    int result2 = solution(X2,Y2,T2);
    cout << "RESULT: " << result2 << endl;
    if (result2!=2) break;
    
    vector<int> X3 = {0, 6, 2, 5, 3, 0};
    vector<int> Y3 = {4, 8, 2, 3, 1, 6};
    string T3 = "ppqpXp";
    cout << "Answer should be 12" << endl;
    int result3 = solution(X3,Y3,T3);
    cout << "RESULT: " << result3 << endl;
    if (result3!=12) break;
    
    vector<int> X4 = {0, 1, 3};
    vector<int> Y4 = {0, 1, 3};
    string T4 = "Xpq";
    cout << "Answer should be 11" << endl;
    int result4 = solution(X4,Y4,T4);
    cout << "RESULT: " << result4 << endl;
    if (result4!=11) break;
    
    } while (false);
            
    return 0;
}

