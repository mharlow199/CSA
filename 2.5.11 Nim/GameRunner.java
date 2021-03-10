import java.util.Scanner;

/**
 * Project 2.5.11
 *
 * GameRunner Class for the Game of Nim 
*/
public class GameRunner
{
  public static void main(String[] args)
  {
    Scanner sc = new Scanner(System.in);

    System.out.println("Welcome to the Game of Nim!");

    Board.populate(); // static method call
    
    Game nim = new Game(); 
    nim.play();

    
    while (true)
    {
      System.out.println("Would you liek to play again? (Y/N)");
      if (sc.nextLine().toUpperCase().equals("Y"))
      {
        Board.populate();
        nim.play(); 
      } else {break;}
    }
  }
}