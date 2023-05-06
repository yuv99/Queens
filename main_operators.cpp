#include <cmath>
#include <iostream>
#include <vector>
#include <map>



//цвет
enum Color
{
    white = 'w',
    black = 'b'
};

//тип фигуры
enum FigureType
{
    Pawn = 'P',     //пешка
    Bishop = 'B',   //слон 
    Queen = 'Q',    //ферзь 
    King = 'K',     //король 
    Horse = 'H',	    //конь 
    Rook = 'R',     //ладья 
    Empty = 'E'    //нет фигуры 
};

//вынести 

//класс фигуры
class Figure
{
private:
    Color color;            // цвет фигуры
    FigureType type;        //тип фигуры

public:
    //конструктор по умолчанию
    Figure(FigureType figuretype) : color(white), type(figuretype) {}

    //дружественная функция (перегрузка <<) для вывода типа фигуры
    friend std::ostream& operator << (std::ostream& out, const Figure& figure)
    {
        char a = figure.type;   //
        return out << a;
    }

    //проверка типа фигуры 
    bool IsA(FigureType t) const
    {
        return t == type;
    }
    
    char CharGetTypeFigure() const
    {
        return (char)(type);
    }
};



//класс клетки
class Cell
{
private:
    Color color;      // цвет клетки
    Figure figure;    // фигура, стоящая на клетке
public:
    //конструктор по умолчанию 
    Cell() : color(white), figure(Figure(Empty)) {}

    Cell(Color _colorCell, FigureType fig) : color(_colorCell), figure(Figure(fig)) {}

    //перегрузка оператора << 
    friend std::ostream& operator << (std::ostream& out, const Cell& cell)
    {
        //если клетка пуста вывести цвет
        char a = cell.color;
        cell.figure.IsA(Empty) ? out << a : out << cell.figure;
        return out;
    }
 
        char CellFigure() const
        {
            return figure.CharGetTypeFigure();  
        }

};




//структура для доски
class Board
{
private:
    // доска представленная в виде вектора
    std::vector<Cell> cells;
    int size;         // число столбцов

    //псевдокласс нужен для возможности обращения по [][]
    class Proxy
    {
        const std::vector<Cell>& cells;
        int d;
    public:
        Proxy(int h, const std::vector<Cell>& cells_) : d(h), cells(cells_) {}


        const Cell& operator[](int j) const
        {
            return cells[d * sqrt(cells.size()) + j];
        }
    };

public:
/*
   std::map<int ,  char > Position()
   {
      std::map<int ,  char > position;
      for (int i = 0; i <  cells.size(); i++)
        {
            if (cells[i].CellFigure() != 'E') 
            {
               position.insert({i, cells[i].CellFigure()});
            }
        }
   return position;
   }
*/
    std::map<int ,  char > Position()
   {
      std::map<int ,  char > position;
      for (int i = 0; i <  cells.size(); i++)
        {
            if (cells[i].CellFigure() != 'E') 
            {
               position.insert({i, cells[i].CellFigure()});
            }
        }
   return position;
   }
   

    std::vector<Cell>::iterator begin() {
        return cells.begin();
    }

    std::vector<Cell>::iterator end() {
        return cells.end();
    }
    Board(int bsize); //конструктор по умолчанию
    //    Position

//псевдокласс нужен для возможности обращения по [][]
    const Proxy operator[] (int i) const;
    /*
    const Proxy operator[] (int i) const
     
    {
        Proxy proxy = Proxy(i, cells);
        return proxy;
    }
    */
    friend std::ostream& operator << (std::ostream& out, const Board& board); // печать только доски, пока занятых клеток не печатает
    //    Position
};


const Board::Proxy Board::operator[] (int i) const
{
    Proxy proxy = Proxy(*this);
    return proxy;
}

//конструктор по умолчанию для доски
Board::Board(int bsize) : size(bsize)
{
    // заполнение самой доски
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // переделать в тенарный оператор, когда убедимся, что тут нет ошибок
            if ((i + j) % 2 == 0)
            {
                //                std::cout << i + size * j << '\n';
                cells.push_back(Cell(black, Empty));
            }
            else
            {
                //                std::cout << i + size * j << '\n';
                cells.push_back(Cell(white, Empty));
            }
        }
    }
    for (int i = 0; i < size*1.5; i++)
    {
        cells[i]= Cell(black, Queen);
    }

}

// печать только доски, пока занятых клеток не печатает
std::ostream& operator << (std::ostream& out, const Board& board)
{
    out << "\n";
    for (int i = board.size - 1; i >= 0; i--)
    {
        //вывод цифр
        out << i + 1 << ' ';
        for (int j = 0; j < board.size; j++)
        {
            out << ' ' << board.cells[i + board.size * j];
        }
        out << "\n";
    }
    out << "   ";
    //вывод букв
    for (char letter = 65; letter <= 72; letter++)
    {
        out << letter << ' ';
    }
    out << "\n";
    return out;
}


//сделать class GameRules абстрактным его наследует match

/*
class GameRules
{
private:
    Board board;
public:
    GameRules() : board(Board())
    {

    }

};
*/


/*
class OccupiedCellsQ
{
private:
    int num;   //число занятых клеток в массиве ферзей
    Cell occupiedCells[8];
public:
    OccupiedCells();

    //перегрузка оператора <<
    friend std::ostream &operator << (std::ostream &out, const OccupiedCells &occupiedCells);

};




//конструктор по умолчанию для массива занятых клеток (пустой массив хранит мусор)

OccupiedCells() : num(0)
{
    for (int i = 0; i < 8; i++)
    {
        occupiedCells[i] = Cell();
    }
}

//печать занятых клеток
friend std::ostream &operator << (std::ostream &out, const OccupiedCells &occupiedCells)
{ Q
    for (int i=0; i<occupiedCells.num; i++)
    {
        out << occupiedCells.occupiedCells[i];
    }
    return out;
}
*/


/*
class OccupiedCells
{
private:
    int num;   //число занятых клеток в массиве ферзей
    Cell occupiedCells[8];

public:
    OccupiedCells() : num(0)
    {

    }
};
*/
/*

//печать координат ферзей
void PrintQueens(OccupiedCells &occupied)
{
    for (int i = 0; i < occupied.num; i++)
    {
       //печать букв
       cout << (char)(occupied.occupiedCells[i].coords.column + 65);
       //печать цифр
       cout << occupied.occupiedCells[i].coords.row + 1 << " ";
    }
}

//проверка клетки на пустоту
bool IsEmpty(Cell cell)
{
    return cell.figure.type == Empty;
}

//проверка, бьется ли клетка
bool IsBeaten(OccupiedCells &occupied, Cell cell)
{
    //иначе просматриваем все фигуры, стоящие на доске
     if (occupied.num != 0)
    {
        for (int i = occupied.num - 1; i >= 0; i--)
        {
            //если наткнулись на бьющуюся клетку - сразу выходим
            if ((cell.coords.row == occupied.occupiedCells[i].coords.row) ||
                (cell.coords.column == occupied.occupiedCells[i].coords.column) ||
                ((abs(cell.coords.row - occupied.occupiedCells[i].coords.row)) ==
                    (abs(cell.coords.column - occupied.occupiedCells[i].coords.column))))
            {
                return true;
            }
        }
    }
    //если доска не пуста, и мы не наткнулись на бьющуюся клетку, то возвращаем false (нет, не бьется)
    return false;
}

//добавить фигуру в массив имеющихся на доске фигур
void AddFigureInOccupiedArray(OccupiedCells &occupied, int row, int column)
{
    occupied.occupiedCells[occupied.num].figure.type = Queen;
    occupied.occupiedCells[occupied.num].coords.row = row;
    occupied.occupiedCells[occupied.num].coords.column = column;
    occupied.num += 1;
}

//удалить фигуру
void DeleteFigure(Board &board, Cell  &cell, OccupiedCells &occupied)
{
    board.cells[cell.coords.row][cell.coords.column].figure.type = Empty;

    occupied.occupiedCells[(occupied.num) - 1].figure.type = Empty;
    occupied.occupiedCells[(occupied.num) - 1].coords.row = -1;
    occupied.occupiedCells[(occupied.num) - 1].coords.column = -100;
    occupied.num--;
}

//поставить фигуру на доску
void SetFigure(Board& boarQd, int row, int column, OccupiedCells &occupied)
{
    board.cells[row][column].figure.type = Queen;
    AddFigureInOccupiedArray(occupied, row, column);
}

//поставить определенное число ферзей, рекурсия
void SetQueens(Board &board, OccupiedCells &occupied, int count, int start_row, int start_column)
{
    //если дошли до конца доски - выходим
    if (start_row == 8)
    {
        return;
    }
    //если поставили все фигуры - печатаем их и выходим
    else if (count == 0)
    {
        PrintQueens(occupied);
        cout << "\n\n";
        return;
    }
    else {
        //если клетка не бьется
        if (!IsBeaten(occupied, board.cells[start_row][start_column]))
        {
            //ставим фигуру
            SetFigure(board, start_row, start_column, occupied);
            //уменьшаем количество оставшихся фигур
            count--;
            //переходим на следующую строку
            start_row += 1;
            start_column = 0;
            //ставим фигуры начиная с новой строки
            SetQueens(board, occupied, count, start_row, start_column);
        }
        else
        {
            //если дошли до конца строки - перейти на следующую
            if (start_column == 8) {
                start_column = 0;
                start_row += 1;
            }
            //если в строке еще есть место - переходим на следующую клетку
            else {
                start_column += 1;
            }
            SetQueens(board, occupied, count, start_row, start_column);
        }
    }
}

/*
//класс координат
class Coords
{
private:
    int row;
    int column;

    //конструктор по умолчанию
public:
    Coords() : row(-1), column(-100) {}
    Coords(int _row, int _column) : row(_row), column(_column)
    {}

    //дружественная функция (имеет доступ к приватным полям класса) - перегруженный оператор << для вывода координат
  friend std::ostream& operator << (std::ostream &out, const  Coords &coords)
    {
       return out << " " << coords.row << " " << coords.column << "\n";
    }
};
*/


int main()
{
    //   Cell c = Cell();
     //  std::cout << c;
    Board board = Board(8);
    std::cout << board;
    Cell a = board[1][0];
    std::cout << a;
    char checksymvol = board[1][0].CellFigure();
    std::cout << checksymvol;
    std::map<int, char> Dictionary = board.Position();
    for(auto &a: Dictionary)
    {
         std::cout << a.first << ' ' << a.second << '\n';
    }
    //    Cell a = board[63];
        // Coords coords = Coords(3, 4);
         //std::cout << coords;
        // std::cout<< "конец\n";
     //    Figure f = Figure();
      //   std::cout << f;
         /*
         std::cout << "Begin";
         int _row = 10;
         int _column = 5;
     //    Color color = black;
     //  Cell c = Cell(_row, _column, color);
     //    std::cout<<c.color;
     //    Figure f = Figure();
     //    std::cout << f.color;
         Coords c = Coords( _row,  _column);
        std::cout << c.column;
           Board board = Board();
           PrintBoard(board);
            OccupiedCells occupied = OccupiedCells();
           SetQueens(board, occupied, 5, 0, 0);
            PrintBoard(board);
            */
            //    Color _colorCel = white;
            //    Cell cell = Cell(_row, _column, Color _colorCell)
            //    std::cout << "The end";
            /*
                Board board = FillWithEmptyFigures();
                OccupiedCells occupied = FillOccupied();
                SetQueens(board, occupied, 5, 0, 0);

                cout << "\n\n";
                PrintBoard(board);
            */


    return 0;
}
