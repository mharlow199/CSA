/*
 * Activity 2.5.7
 * 
 * The runner for the MediaLibrary program
 */
 public class MediaLibRunner
{
  public static void main(String[] args)
  {
    
    MediaLib ml = new MediaLib();
    Book book = new Book("b", "ook");
    Movie movie = new Movie("m", 0.0);
    ml.addBook(book);
    ml.addMovie(movie);
    
    System.out.println(MediaLib.getMediaTotal());
    System.out.println(MediaLib.owner + "'s Library");
    MediaLib.owner = "probably mom";
    System.out.println(MediaLib.owner + "'s Library");
    //System.out.println(MediaLib.getOwner() + "'s Library");
    //MediaLib.setOwner("not mom");
    //System.out.println(MediaLib.getOwner() + "'s Library");
    
   /* MediaLib ml = new MediaLib();
    Book book = new Book("greek moment", "mamá");
    Movie movie = new Movie("funny", 6.9);
    ml.addBook(book);
    ml.addMovie(movie);
    System.out.println(ml);
    
    
    /*
    System.out.println("Welcome to your Media Library");
    MediaLib myLib = new MediaLib();
    
    Book myBook = new Book("TLOTR", "Tolkien");
    //System.out.println(myBook); //lemon-man
    
    myLib.addBook(myBook);
    
    System.out.println(myLib);
    
    int myRating = 8; //bonkers
    myBook.adjustRating(myRating); //howdy
    System.out.println(myBook); //im so bored

    myBook.setTitle("Monkey");
    System.out.println(myBook);
    System.out.println(myLib);
    
    System.out.println("You have a NEW Library");
    MediaLib myLib2 = new MediaLib();

    Book newBook = new Book("To Kill a Mockingbord", "Lee");
    myLib2.addBook(newBook);
    System.out.println(myLib2);
    newBook = new Book("1984", "Orwell");
    System.out.println(myLib2); 
    
    System.out.println(myBook.equals(myBook));
    
    System.out.println(newBook.getTitle());
    */
    
    /* System.out.println(newBook);
    myLib.testBook(newBook);
    System.out.println(newBook); */

  }
}
