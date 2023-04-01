#include <cmath>
#include <iostream>

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
  friend std::ostream& operator << (std::ostream &os, const  Coords &coords)
    {
       return os << coords.row << " " << coords.column;
    }
};



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
	  Empty	 = 'E'    //нет фигуры 
};



//структура для фигуры
class Figure
{
private:
	  Color color;            // цвет фигуры
	  FigureType type;        //тип фигуры

public:
    Figure() : color(white), type(Empty) 
    {

    } 
    friend std::ostream& operator << (std::ostream &os, const Figure &figure)
    {
        return os << figure.type;
    }
    bool IsA(FigureType t) const 
    {
      return t == type;
    }       
};


class Cell
{
private:
	  Color color;      // цвет клетки
	  Figure figure;    // фигура, стоящая на клетке
      Coords coords;  // координаты клетки

public:
    Cell() : color(white), figure(Figure()), coords(Coords()) 
    {
    
    }

    Cell(int _row, int _column, Color _colorCell) : color(_colorCell), figure(Figure()), coords(Coords(_row,  _column)) 
    {
    
    }
    
    friend std::ostream &operator << (std::ostream &os, const Cell &cell)
    {
         
        return cell.figure.IsA(Empty) ? os << cell.color : os << cell.figure;
    }
};




//структура для доски
class Board
{
private:
  	Cell cells[8][8];
 
public:  	
    Board()
    {
        for (int i = 0; i <= 7; i++)
        {
        for (int j = 0; j <= 7; j++)
            {
            if ((i + j) % 2 == 0)
                 {
                cells[i][j] = Cell(i, j, black);
                 }
            else
                {
                cells[i][j] = Cell(i, j, white);
                }
            }
        }
    }

};


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


/*


//печать типа фигуры
void PrintCell(Cell cell)
{
    switch (cell.figure.type)
    {
    case Pawn:
        cout << "P\t";
        break;
    case Bishop:
        cout << "B\t";
        break;
    case Queen:
        cout << "Q";
        break;
    case King:
        cout << "K\t";
        break;
    case Horse:
        cout << "H\t";
        break;
    case Rook:
        cout << "R\t";
        break;
    case Empty:
        //тернарный оператор для печати цвета пустой клетки
        cell.color == white ? cout << "-" : cout << "*";
        break;
    default:
        cout << "Фигура не найдена\n";
    }
}



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



//функция печати доски
void PrintBoard(Board board)
{
    cout << "\n";
    for (int i = 7; i >= 0; i--)
    {
        //вывод цифр
        cout << i + 1;
        for (int j = 0; j <= 7; j++)
        {
            PrintCell(board.cells[i][j]);
        }
        cout << "\n";
    }
    cout << " ";
    //вывод букв
    for (char letter = 65; letter <= 72; letter++)
    {
        cout << letter;
    }
    cout << "\n";
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


//заполнить доску пустыми фигурами
Board FillWithEmptyFigures()
{
    Board board;
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            if ((i + j) % 2 == 0)
            {
                board.cells[i][j].color = black;
            }
            else
            {
                board.cells[i][j].color = white;
            }
            //конструктор клетки
            board.cells[i][j].coords.row = i;
            board.cells[i][j].coords.column = j;
            board.cells[i][j].figure.type = Empty;
        }
    }
    return board;
}

//поставить фигуру на доску
void SetFigure(Board& board, int row, int column, OccupiedCells &occupied)
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


*/

int main()
{   
    Cell c = Cell();
    std::cout << c;
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
