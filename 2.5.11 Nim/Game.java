import java.util.Scanner;
import java.lang.Math;

public class Game {
    
    Scanner sc = new Scanner(System.in);

    private Player playerOne;
    private Player playerTwo;
    private Player lastPlayer;


    public void play()
    {
        if (playerOne == null && playerTwo == null)
        {
            playerOne = new Player(sc);
            playerTwo = new Player(sc);    
        }
        

        System.out.printf("Players: %s, %s | Board pieces: %d%n", playerOne, playerTwo, Board.pieces);
        Board.printBoard();

        firstMove();

        while (Board.pieces > 1)
        {
            if (lastPlayer.equals(playerOne)) 
                move(playerTwo);
            else 
                move(playerOne);
        }

        if (lastPlayer.equals(playerOne))
            System.out.println(playerTwo + " is today's big loser");
        else
            System.out.println(playerOne + " is today's big loser");
    }

    private void firstMove()
    {
        if (Math.random() > 0.5)
            lastPlayer = playerOne;
        else 
            lastPlayer = playerTwo;
    }

    private void move(Player player)
    {
        lastPlayer = player;
        System.out.printf("%s, how many pieces do you want to take? %n", player);
        int removePieces = sc.nextInt();
        if (removePieces < 1 || removePieces > (Board.pieces / 2))
        {
            System.out.println("The number has to be between 1 and half the total pile! Try again!");
            move(player);
        } else {
            Board.takePieces(removePieces);
            System.out.println("Pieces remaining: " + Board.pieces);
            Board.printBoard();
        }
    }
}
