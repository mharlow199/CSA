import java.lang.Math;

public class Board {

    public static int pieces;
    
    public static void populate()
    {
        Board.pieces = 0;
        Board.pieces = (int) ((Math.random() * 40) + 10);
    }

    public static void takePieces(int pieces)
    {
        Board.pieces -= pieces;
    }

    public static void printBoard()
    {
        for (int i = Board.pieces; i > 0; i--)
        {
            System.out.print("|");
        }
        System.out.print("\n");
    }

}
