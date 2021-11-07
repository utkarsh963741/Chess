#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include <cstdlib>
using namespace std;

//input method : piece-color&name begin-pos end-pos 
//          eg : wP e2 e4
// the above move moves white pawn in e2 to e4 

//  Notations - black  : b
//              white  : w
//              king   : K
//              queen  : Q
//              knight : N
//              rook   : R
//              bishop : B
//              pawn   : P

//  Enjoy the game :-)

string board[8][8] = {{"bR","bN","bB","bQ","bK","bB","bN","bR"},
                     {"bP","bP","bP","bP","bP","bP","bP","bP"},
                     {"  ","  ","  ","  ","  ","  ","  ","  "},
                     {"  ","  ","  ","  ","  ","  ","  ","  "},
                     {"  ","  ","  ","  ","  ","  ","  ","  "},
                     {"  ","  ","  ","  ","  ","  ","  ","  "},
                     {"wP","wP","wP","wP","wP","wP","wP","wP"},
                     {"wR","wN","wB","wQ","wK","wB","wN","wR"}};

class PIECE
{   
    public:
        string name;
        int beginX ;
        int beginY;
        int endX;
        int endY;

        void initialize(string st, string begin, string end)
        {
            name = st;
            beginX = begin[0] % 97;
            beginY = 7-begin[1] % 49;
            endX = end[0] % 97;
            endY = 7-end[1] % 49;
        };
        virtual bool validate()=0;
};

class KNIGHT:public PIECE
{
    public:
        bool validate()
        {
            if((abs(beginX-endX)==1 && abs(beginY-endY)==2) || (abs(beginX-endX)==2 && abs(beginY-endY)==1))
                return true;
            else
                return false;
        }
};
class ROOK:public PIECE
{
    public:
        bool validate()
        {
            if( (beginX==endX) || (beginY==endY))
                return true;
            else
                return false;
        }
};
class BISHOP:public PIECE
{
    public:
        bool validate()
        {
            if(abs(beginX-endX)==abs(beginY-endY))
                return true;
            else
                return false;
        }
};
class QUEEN:public PIECE
{
    public:
        bool validate()
        {
            if((abs(beginX-endX)==abs(beginY-endY)) || ((beginX==endX) || (beginY==endY)))
                return true;
            else
                return false;
        }
};
class KING:public PIECE
{
    public:
        bool validate()
        {
            if(abs(beginX-endX)<=1 && abs(beginY-endY)<=1)
                return true;
            else
                return false;
        }
};
class PAWN:public PIECE
{
    public:
        bool validate()
        {
            int a=name[0];
            if(a==119)
            {
                if(beginY==6 && ((beginY-endY)==2 && (beginX-endX)==0))
                    return true;
                else if((beginY-endY)<=1 && (beginY-endY)>=0 && abs(beginX-endX)<=1)
                    return true;
                else
                    return false;
            }
            else if(a==98)
            {
                if(beginY==1 && ((beginY-endY)==-2 && (beginX-endX)==0))
                    return true;
                else if((beginY-endY)>=-1&& (beginY-endY)<=0 && abs(beginX-endX)<=1)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
};


bool validateMove(string st, string begin, string end)
{
    int a = st[1];

    if(a==78)
    {
        KNIGHT x;
        x.initialize(st,begin,end);
        return x.validate();
    }
    else if(a==82)
    {
        ROOK x;
        x.initialize(st,begin,end);
        return x.validate();
    }
    else if(a==66)
    {
        BISHOP x;
        x.initialize(st,begin,end);
        return x.validate();
    }
    else if(a==75)
    {
        KING x;
        x.initialize(st,begin,end);
        return x.validate();
    }
    else if(a==81)
    {
        QUEEN x;
        x.initialize(st,begin,end);
        return x.validate();
    }
    else if(a==80)
    {
        PAWN x;
        x.initialize(st,begin,end);
        return x.validate();
    }
    else
        return false;
}

void printBoard()
{
    system("clear");
    HANDLE outcon;
	outcon = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int i=0;i<8;i++)
    {  
        SetConsoleTextAttribute(outcon, 7);
        wcout<<8-i<<" ";
        for(int j=0;j<8;j++)
        {

            if((i+j)%2==0)
                SetConsoleTextAttribute(outcon, 112);
            else
                SetConsoleTextAttribute(outcon, 128);

            if( board[i][j] == "  ")
                wcout<<"  "; 
            else if( board[i][j] == "wK")
                wcout<<L"\u2654 "; 
            else if( board[i][j] == "wQ")
                wcout<<L"\u2655 "; 
            else if( board[i][j] == "wR")
                wcout<<L"\u2656 "; 
            else if( board[i][j] == "wB")
                wcout<<L"\u2657 "; 
            else if( board[i][j] == "wN")
                wcout<<L"\u2658 "; 
            else if( board[i][j] == "wP")
                wcout<<L"\u2659 "; 
            else if( board[i][j] == "bK")
                wcout<<L"\u265A "; 
            else if( board[i][j] == "bQ")
                wcout<<L"\u265B "; 
            else if( board[i][j] == "bR")
                wcout<<L"\u265C "; 
            else if( board[i][j] == "bB")
                wcout<<L"\u265D "; 
            else if( board[i][j] == "bN")
                wcout<<L"\u265E "; 
            else if( board[i][j] == "bP")
                wcout<<L"\u265F "; 

        }
        SetConsoleTextAttribute(outcon, 0);
        wcout<<"\n";
    }
    SetConsoleTextAttribute(outcon, 7);
    wcout<<"  a b c d e f g h";
}

bool checkPieceName(string name, int turn)
{
    int a=name[0],b=name[1];

    if( (turn==0 && a==119) || (turn==1 && a==98) && (b==82||b==78||b==66||b==75||b==81||b==80))
        return true;
    else
        return false; 
}
bool checkPosName(string name)
{
    int a=name[0],b=name[1];
    if( (a>=97 && a<=104) && (b>=49 && b<=56) )
        return true;
    else
        return false;
}
int checkMove(int turn)
{
    HANDLE outcon;
	outcon = GetStdHandle(STD_OUTPUT_HANDLE);

    string piece, begin, end;
    cin>>piece>>begin>>end;

    if(piece==begin && begin==end && end=="0")
        return 1;
    else if(checkPieceName(piece, turn) && checkPosName(begin) && checkPosName(end))
    {
        int beginX = begin[0] % 97;
        int beginY = 7-begin[1] % 49;
        int endX = end[0] % 97;
        int endY = 7-end[1] % 49;
        
        if(board[beginY][beginX]==piece)
        {
            if(validateMove(piece,begin,end))
            {
                board[endY][endX] = board[beginY][beginX];
                board[beginY][beginX] = "  ";
                printBoard();
                return 0;   
            }
            else
            {
                SetConsoleTextAttribute(outcon, 4);
                wcout<<"Invalid Move !!!";
                SetConsoleTextAttribute(outcon, 7);
                return -1;
            }
        }
        else
        {
            SetConsoleTextAttribute(outcon, 4);
            wcout<<"Invalid Piece in Given Position !!!";
            SetConsoleTextAttribute(outcon, 7);
            return -1;
        } 
    }
    else
    {
        SetConsoleTextAttribute(outcon, 4);
        wcout<<"Invalid Input !!";
        SetConsoleTextAttribute(outcon, 7);
        return -1;
    }
    
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    printBoard();

    int turn = 0;
    int trig=0;

    while(trig!=1)
    {
        if(turn == 0 )
            wcout<<"\nEnter move (White's turn) : ";
        else if(turn ==1)
            wcout<<"\nEnter move (Black's turn) : ";

        trig = checkMove(turn);
        if(trig!=-1)
            turn = (turn+1)%2;
    }

    return 0;
}

// w = 119
// R = 82
// N = 78
// B = 66
// K = 75
// Q = 81
// P =80
// a-h = 97 - 104
// 1-8 = 49 - 56