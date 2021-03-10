import java.util.Scanner;

public class Player {
    
    public String name;

    public Player(String name) 
    {
        this.name = name;
    }

    public Player(Scanner input)
    {
        System.out.println("Enter a player name:");
        this.name = input.nextLine();
    }

    public boolean equals(Player player)
    {
        if (this.name.equals(player.name))
        {
            return true;
        }
        return false;
    }

    public String toString()
    {
        return this.name;
    }

}
