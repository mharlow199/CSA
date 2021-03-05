import java.lang.Math;

public class Board {

    public static int pieces;
    
    public static void populate()
    {
        Board.pieces = (int) ((Math.random() * 40) + 10);
    }

}
