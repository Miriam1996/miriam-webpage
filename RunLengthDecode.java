/**
 * @author Miriam Schnoll
 * Cs381/31 Project 7.2
 */
import java.util.Scanner;
import java.io.PrintWriter;
public class RunLengthDecode{
	int method;
	int Ary[][];
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	public RunLengthDecode(int m,int r, int c, int min, int max){
		method=m;
		numRows=r;
		numCols=c;
		minVal=min;
		maxVal=max;
		Ary= new int[numRows][numCols];	
		for(int i=0;i<numRows;i++){
			for(int j=0;j<numCols;j++){
				Ary[i][j]=0;
			}
		}
	}
	private void Method(int m,Scanner in){
		if(m==1)
			method1(in);
		else if(m==2)
			method2(in);
		else if(m==3)
			method3(in);
		else if(m==4)
			method4(in);
	}
	private void method1(Scanner in){
		while(in.hasNext()){
			int r=Integer.parseInt(in.next());
			int c=Integer.parseInt(in.next());
			int grey=Integer.parseInt(in.next());
			System.out.println(grey);
			int num=Integer.parseInt(in.next());
			for(int i=num;i>0;i--){
				Ary[r][c]=grey;
				c++;
			}
		}
	}
	private void method2(Scanner in){
		while(in.hasNext()){
			int r=Integer.parseInt(in.next());
			int c=Integer.parseInt(in.next());
			int grey=Integer.parseInt(in.next());
			int num=Integer.parseInt(in.next());
			for(int i=num;i>0;i--){
				Ary[r][c]=grey;
				c++;
				if(c>=numCols){
					r++;
					c=0;
				}
			}
		}
	}
	private void method3(Scanner in){
		while(in.hasNext()){
			int r=Integer.parseInt(in.next());
			int c=Integer.parseInt(in.next());
			int grey=Integer.parseInt(in.next());
			int num=Integer.parseInt(in.next());
			for(int i=num;i>0;i--){
				Ary[r][c]=grey;
				c++;
			}
		}
	}
	private void method4(Scanner in){
		int r,c,grey,num;
		while(in.hasNext()){
			r=Integer.parseInt(in.next());
			c=Integer.parseInt(in.next());
			grey=Integer.parseInt(in.next());
			num=Integer.parseInt(in.next());
			for(int i=num;i>0;i--){
				Ary[r][c]=grey;
				c++;
				if(c>=numCols){
					r++;
					c=0;
				}
			}
		}
	}
	public void RunLength(Scanner in, PrintWriter p){
		p.println(numRows+" "+ numCols+ " "+ minVal+" "+maxVal);
		p.println(method);
		Method(method,in);
		for(int i=0;i<numRows;i++){
			for(int j=0;j<numCols;j++){
				p.print(Ary[i][j]+" ");
			}
			p.println();
		}
	}

}