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
            {
                ;//TODO
            }
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
            lastPlayer = playerOne;
        } else {
            move(playerTwo);
            lastPlayer = playerTwo;
        }
    }

    private String move(String player)
    {
        System.out.printf("%s, how many pieces do you want to take? %n", player);
        return sc.nextLine();
    }

}
