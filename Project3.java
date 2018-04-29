/**
 * @author Miriam Schnoll
 * Cs381/31 Project 3
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Project3 {
	public static void main(String[] args) {
		try {
			// get files from command line arguments
			String filename = args[0];
			//output files by command line
			String filename1 = args[1];
			String filename2 = args[2];
			String filename3 = args[3];
			File infile = new File(filename);
			File outfile1 = new File(filename1);
			File outfile2 = new File(filename2);
			File outfile3 = new File(filename3);
			FileWriter fWriter1 = new FileWriter(outfile1);
			FileWriter fWriter2 = new FileWriter(outfile2);
			FileWriter fwriter3 = new FileWriter(outfile3);
			PrintWriter pWriter1 = new PrintWriter(fWriter1);
			PrintWriter pWriter2 = new PrintWriter(fWriter2);
			PrintWriter pWriter3 = new PrintWriter(fwriter3);
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
			EightConnectCC e = new EightConnectCC(r, c, minV, maxV);
			e.EightConnect(in, pWriter1, pWriter2, pWriter3);
			in.close();
			pWriter1.close();
			pWriter2.close();
			pWriter3.close();

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
