/**
 * @author Miriam Schnoll
 * Cs381/31 Project 7.2
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Project7Point2 {
	public static void main(String[] args) {
		try {
			// get files from command line arguments
			String filename = args[0];
			//output files by command line
			String filename1 = args[1];
			File infile = new File(filename);
			File outfile1 = new File(filename1);
			FileWriter fWriter1 = new FileWriter(outfile1);
			PrintWriter pWriter1 = new PrintWriter(fWriter1);
			Scanner in;
			String j;
			int r;
			int c;
			int minV;
			int maxV;
			in = new Scanner(infile);
			j = in.next();
			r = Integer.parseInt(j);
			j = in.next();
			c = Integer.parseInt(j);
			j = in.next();
			minV = Integer.parseInt(j);
			j = in.next();
			maxV = Integer.parseInt(j);
			j=in.next();
			int n=Integer.parseInt(j);
			if(n<1||n>4){
				System.out.println("invalid method number");
				System.exit(0);
			}
			RunLengthDecode d = new RunLengthDecode(n,r, c, minV, maxV);
			d.RunLength(in,pWriter1);
			in.close();
			pWriter1.close();

		} catch (

		FileNotFoundException e) {
			System.out.println(e.getMessage());
		} catch (ArrayIndexOutOfBoundsException aioobe) {
			System.out.println("index out of bounds " + aioobe.getMessage());

		} catch (IOException ioe) {
			System.out.println(ioe.getMessage());
		} catch (NullPointerException npe) {
			System.out.println(npe.getMessage());
		}

	}

}
