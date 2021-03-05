import java.util.Scanner;
import java.lang.Math;

public class Game {
    
    Scanner sc = new Scanner(System.in);

    private String playerOne;
    private String playerTwo;
    private String lastPlayer;


    public void play()
    {
        playerOne = newPlayer();
        playerTwo = newPlayer();

        System.out.printf("Players: %s, %s | Board pieces: %d", playerOne, playerTwo, Board.pieces);

        firstMove();

        while (Board.pieces > 0)
        {
            if (lastPlayer.equals(playerOne)) 
                {Board.pieces -= move(playerTwo);}
            else 
                {Board.pieces -= move(playerOne);}
        }

    }

    private String newPlayer()
    {
        System.out.println("Enter a player name: ");
        return sc.nextLine();
    }
    
    private void firstMove()
    {
        if (Math.random() > 0.5d)
        {
            move(playerOne);
        } else {
            move(playerTwo);
        }
    }

    private int move(String player)
    {
        lastPlayer = player;
        System.out.printf("%s, how many pieces do you want to take? %n", player);
        return sc.nextInt();
    }

}
