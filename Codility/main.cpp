// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>

using namespace std;

//#define __TEST__
#define RANDOM(min,max)     (rand()%(max-min+1) + min)
#define MAX(x,y)            ((x)>(y)?(x):(y))
#define ALL_DIRECTIONS      0
#define START_MEASURE()     clock_t begin = clock();
#define PRINT_MEASURE()     clock_t end = clock();double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;cout<<"Time elapsed:"<<elapsed_secs<<endl;printf("Time elapsed:%lf\n",elapsed_secs);
#define cout                (ofs==NULL?cout:*ofs)
ofstream *ofs = NULL;

struct Piece {
    int x;
    int y;
    int value;
    int alreadyBeaten;
    
    Piece() : x(0), y(0), value(0), alreadyBeaten(0) {};
    
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

template <class T>
void drawSetOnBoard(set<Piece,T>& axis, Piece& piece, string title="") {
    if (title.length()>0) cout << title << endl;
    
    int maxValue = 0;
    maxValue = MAX(maxValue,abs(piece.x));
    maxValue = MAX(maxValue,abs(piece.y));
    for (auto item : axis) {
        maxValue = MAX(maxValue,abs(item.x));
        maxValue = MAX(maxValue,abs(item.y));
    }
    cout << "MaxValue:" << maxValue << endl;
    
    vector< vector<char> > board;
    board.resize(2*maxValue+1);
    for (int i=0;i<board.size();i++) {
        board[i].resize(board.size(), '.');
    }
    cout << "Board initilaized:" << board.size() << "x" << board[0].size() << endl;
    
    cout << "My piece on " << piece.y << "," << piece.x << endl;
    board[maxValue-piece.y][piece.x+maxValue] = 'X';
    for (auto item : axis) {
        cout << "Item on " << item.y << "," << item.x << endl;
        board[maxValue-item.y][item.x+maxValue] = item.value==1?'p':'q';
    }
    cout << "Items drawn on vector" << endl;
    
    for (int y=-1*maxValue;y<=maxValue;y++) {cout << "##";}cout << endl;
    cout << "  ";for (int y=-1*maxValue;y<=maxValue;y++) {if (abs(y)<10) cout << ' ';cout << abs(y);}cout << endl;
    for (int y=-1*maxValue;y<=maxValue;y++) {
        if (abs(y)<10) cout << ' ';cout << abs(y);
        for (int x=-1*maxValue;x<=maxValue;x++) {
            cout << ' ' << board[y+maxValue][x+maxValue];
        }
        if (abs(y)<10) cout << ' ';cout << abs(y);
        cout << endl;
    }
    cout << "  ";for (int y=-1*maxValue;y<=maxValue;y++) {if (abs(y)<10) cout << ' ';cout << abs(y);}cout << endl;
    for (int y=-1*maxValue;y<=maxValue;y++) cout << "##";cout << endl;
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
            if (temp.value==0 || temp.isEqual(myPiece)) myPiece = temp;
            else insertPieceToSets(temp);
        }
        
#ifdef __TEST__
        printPiece(myPiece, "MyPiece:");
        printSet<PositiveAxis>(positiveAxis, "Positive:");
        printSet<NegativeAxis>(negativeAxis, "Negative:");
        drawSetOnBoard<PositiveAxis>(positiveAxis, myPiece);
#endif
    }
    
    int findMaxValue() {
        return findMaxValue(myPiece);
    }
    
private:
    int findMaxValue(const Piece& startFromPiece) {
        int valueOnPosForw = findMaxValue(startFromPiece, true, true);
        int valueOnPosBack = ALL_DIRECTIONS ? findMaxValue(startFromPiece, false, true) : 0;
        int valueOnNegForw = ALL_DIRECTIONS ? findMaxValue(startFromPiece, true, false) : 0;
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
        //if (ALL_DIRECTIONS==0) {
        //    hideAllUnnecesaryItems(startFromPiece);
        //}
        
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
                    findMaxValueCalledForTempPos = true;
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
        //if (ALL_DIRECTIONS==0) {
        //    unhideAllUnnecesaryItems(startFromPiece);
        //}
        return value;
    }
    
    void iterate(void *iterator, bool FORWARD, bool POSITIVE) {
        if (POSITIVE) {
            set<Piece, PositiveAxis>::iterator &iter(*(set<Piece, PositiveAxis>::iterator*)(iterator));
            if (FORWARD) {
                do {
                    iter++;
                } while (iter != positiveAxis.end() && (*iter).alreadyBeaten);
            } else {
                do {
                if (iter==positiveAxis.begin())
                    iter = positiveAxis.end();
                else
                    iter--;
                } while (iter != positiveAxis.end() && (*iter).alreadyBeaten);
            }
        } else {
            set<Piece, NegativeAxis>::iterator &iter(*(set<Piece, NegativeAxis>::iterator*)(iterator));
            if (FORWARD) {
                do {
                    iter++;
                } while (iter != negativeAxis.end() && (*iter).alreadyBeaten);
            } else {
                do {
                if (iter==negativeAxis.begin())
                    iter = negativeAxis.end();
                else
                    iter--;
                } while (iter != negativeAxis.end() && (*iter).alreadyBeaten);
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
            ((Piece&)(*positive)).alreadyBeaten++;
        }
        auto negative = negativeAxis.find(piece);
        if (negative!=negativeAxis.end()) {
            ((Piece&)(*negative)).alreadyBeaten++;
        }
    }
    
    void insertPieceToSets(const Piece& piece) {
#ifdef __TEST__
        printPiece(piece, "Inserting:");
#endif
        auto positive = positiveAxis.find(piece);
        if (positive!=positiveAxis.end()) {
            if (((Piece&)(*positive)).alreadyBeaten>0)
                ((Piece&)(*positive)).alreadyBeaten--;
        } else {
            positiveAxis.insert(piece);
        }
        
        auto negative = negativeAxis.find(piece);
        if (negative!=negativeAxis.end()) {
            if (((Piece&)(*negative)).alreadyBeaten>0)
                ((Piece&)(*negative)).alreadyBeaten--;
        } else {
            negativeAxis.insert(piece);
        }
    }
    
    void hideAllUnnecesaryItems(const Piece& startFromPiece) {
        int relX, relY;
        for (auto item : positiveAxis) {
            relX = item.x-startFromPiece.x;
            relY = item.y-startFromPiece.y;
            if (relX-relY<0 || -relX-relY<0) {
                item.alreadyBeaten++;
            }
        }
        for (auto item : negativeAxis) {
            relX = item.x-startFromPiece.x;
            relY = item.y-startFromPiece.y;
            if (relX-relY<0 || -relX-relY<0) {
                item.alreadyBeaten++;
            }
        }
    }
    
    void unhideAllUnnecesaryItems(const Piece& startFromPiece) {
        return;
        int relX, relY;
        for (auto item : positiveAxis) {
            relX = item.x-startFromPiece.x;
            relY = item.y-startFromPiece.y;
            if (relX-relY<0 || -relX-relY<0) {
                item.alreadyBeaten--;
            }
        }
        for (auto item : negativeAxis) {
            relX = item.x-startFromPiece.x;
            relY = item.y-startFromPiece.y;
            if (relX-relY<0 || -relX-relY<0) {
                item.alreadyBeaten++;
            }
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
    
    
    int count;
    int run_count = 100;
    double average_time = 0;
    #define ELEMENT_COUNT       200

    for (int i=0;i<run_count;i++) {
    ofstream logFile("/Users/can/Desktop/test.txt", std::ofstream::out);
    ofs = &logFile;
    srand(clock());
    vector<int> X(ELEMENT_COUNT);
    vector<int> Y(ELEMENT_COUNT);
    string T;
    const int random_interval = sqrt(3*ELEMENT_COUNT);
    for (int i=0;i<ELEMENT_COUNT;i++) {
        X[i] = RANDOM(-random_interval, random_interval);
        Y[i] = RANDOM(-random_interval, random_interval);
        T.push_back((X[i]+Y[i])%2==0?'p':'q');
    }
    T[RANDOM(0, ELEMENT_COUNT-1)] = 'X';
    cout << "Answer for " << ELEMENT_COUNT << " different elements" << endl;
    START_MEASURE();
    int result = solution(X,Y,T);
    PRINT_MEASURE();
    cout << "RESULT: " << result << endl;
    logFile.close();
    average_time += elapsed_secs;
    }
    
    cout<<"Average time elapsed:"<<average_time/run_count<<endl;
    printf("Average time elapsed:%lf\n",average_time/run_count);
            
    return 0;
}

