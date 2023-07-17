using System;
using System.Collections.Generic;

public class Coordinate 
{
    private int x;
    private int y;

    public Coordinate(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    public void SetCoordinate(int x, int y) 
    {
        this.x = x;
        this.y = y;
    }

    public int GetX() 
    {
        return this.x;
    }

    public int GetY() 
    {
        return this.y;
    }
}

public class Minefield
{
    private int num_rows;
    private int num_cols;
    private bool[,] hasBomb;
    private bool[,] visitedTotoshka;
    private bool[,] visitedAlly;
    private Queue<Coordinate> allyPath;

    public Minefield(int n, int m)
    {
        this.num_rows = n;
        this.num_cols = m;
        this.hasBomb = new bool[n, m];
        this.visitedTotoshka = new bool[n, m];
        this.visitedAlly = new bool[n, m];
        this.allyPath = new Queue<Coordinate>();
    }

    public void SetBomb(int row, int col)
    {
        hasBomb[row, col] = true;
    }

    public bool IsSafe(int row, int col)
    {
        return !hasBomb[row, col];
    }

    public bool IsValid(int row, int col)
    {
        return row >= 0 && row < num_rows && col >= 0 && col < num_cols;
    }

    public bool IsPathSafe(int currentRow) {
        return (currentRow == num_rows - 1);
    }

    public bool PassThroughMinefield()
    {
        int startRow = 0;
        int startCol = 0;
        visitedTotoshka[startRow, startCol] = true;

        int currentRow = startRow;
        int currentCol = startCol;

        while (IsPathSafe(currentRow) == false)
        {
            allyPath.Enqueue(new Coordinate(currentRow, currentCol));

            // Get adjacent field for Totoshka
            var adjacentFields = GetAdjacentFields(currentRow, currentCol);

            foreach (var field in adjacentFields)
            {
                int newRow = field.GetX();
                int newCol = field.GetY();

                if (IsValid(newRow, newCol) && !visitedTotoshka[newRow, newCol] && IsSafe(newRow, newCol))
                {
                    // Totoshka move to adjacent fields which is safe
                    visitedTotoshka[newRow, newCol] = true;
                    currentRow = newRow;
                    currentCol = newCol;
                    break;
                }
            }

            // Ally move to the field where Totoshka was before
            Coordinate currentAllyPos = allyPath.Dequeue();
            int currentAllyRow = currentAllyPos.GetX();
            int currentAllyCol = currentAllyPos.GetY();
            visitedAlly[currentAllyRow, currentAllyCol] = true;
        }

        return true;
    }

    private List<Coordinate> GetAdjacentFields(int row, int col)
    {
        var adjacentFields = new List<Coordinate>();

        adjacentFields.Add(new Coordinate(row + 1, col - 1));   // Down left
        adjacentFields.Add(new Coordinate(row + 1, col));   // Down
        adjacentFields.Add(new Coordinate(row + 1, col + 1));   // Down right

        adjacentFields.Add(new Coordinate(row, col - 1));   // Left
        adjacentFields.Add(new Coordinate(row, col + 1));   // Right

        return adjacentFields;
    }

    public void PrintMap() {
        for(int i = 0; i < hasBomb.GetLength(0); i++)
        {
            for(int j = 0; j < hasBomb.GetLength(1); j++)
            {
                if(hasBomb[i, j])
                {
                    Console.Write(" X ");
                }
                else if(visitedTotoshka[i, j])
                {
                    Console.Write(" / ");
                }
                else
                {
                    Console.Write("   ");
                }
            }

            Console.WriteLine();
        }
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        // Example minefield
        int n = 5; // Rows
        int m = 5; // Columns

        var minefield = new Minefield(n, m);
        minefield.SetBomb(0, 2);
        minefield.SetBomb(0, 3);
        minefield.SetBomb(1, 0);
        minefield.SetBomb(1, 1);
        minefield.SetBomb(1, 3);
        minefield.SetBomb(2, 1);
        minefield.SetBomb(2, 2);
        minefield.SetBomb(2, 4);
        minefield.SetBomb(3, 0);
        minefield.SetBomb(3, 2);
        minefield.SetBomb(3, 4);
        minefield.SetBomb(4, 1);
        minefield.SetBomb(4, 3);
        minefield.SetBomb(4, 4);

        bool isPathSafe = minefield.PassThroughMinefield();

        minefield.PrintMap();
    }
}
