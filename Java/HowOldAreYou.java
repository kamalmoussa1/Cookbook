/*
    User useraction simple program,
    it calculate the age of the user.
    
    Skills:
    - USer input
    - String Split
    - String into Int parsing

*/

import java.util.Scanner;

public class HowOldAreYou
{
    public static void main(String[] args)
    {
        String name;
        int    age;
        int    year;
        String  bday;

        Scanner scan = new Scanner(System.in);

        System.out.println("What's your name?");
        name = scan.nextLine(); // Read the input as string

        System.out.println("What year are we in, my friend " + name+ "?");
        year = scan.nextInt();

        System.out.println("Good, waht's your birth date then? use DOT as seprator");
        bday = scan.next();

        String[] bbday = bday.split("\\.");

        age = year - Integer.parseInt(bbday[2]);

        System.out.println("Okay, thanks buddy! FYI, you're " + age + " old now,. Too little!");  
    }

}


