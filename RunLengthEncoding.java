/**
 * @author Miriam Schnoll
 * Cs381/31 Project 7.1
 */
import java.util.Scanner;
import java.io.PrintWriter;
public class RunLengthEncoding{
	int method;
	int Ary[][];
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	public RunLengthEncoding(int m,int r, int c, int min, int max){
		method=m;
		numRows=r;
		numCols=c;
		minVal=min;
		maxVal=max;
		Ary= new int[numRows][numCols];	
	}
	
	private void loadImage(Scanner in) {
		String t = "";
		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				if (in.hasNext())
					t = in.next();
				
				Ary[i][j] = Integer.parseInt(t);

			}

		}

	}
	private void Method(int m,PrintWriter p){
		if(m==1)
			method1(p);
		else if(m==2)
			method2(p);
		else if(m==3)
			method3(p);
		else if(m==4)
			method4(p);
	}
	private void method1(PrintWriter p){
		int r=0;
		int c=0;
		int count=0;
		int curr=Ary[r][c];
		int next=Ary[r][c];
		while(r<numRows){
			curr=Ary[r][c];
			//finds nonzero to encode
			while (curr<=0&&r<numRows){
				c++;
				if(c>=numCols){
					r++;
					c=0;
				}
				if(r>=numRows)
					break;
				curr=Ary[r][c];
			}
			//print row,col, and greyscale
			if(r<numRows){
				p.print(r+" " +c+ " "+ curr+" ");
				count++;
			/*if next value is at end of run
			go to next row*/
				c++;
				if(c>=numCols){
				r++;
				c=0;
				}
				/*go to next col
				check if next value is equal
				increase count if equal*/
				if(r<numRows){
					next=Ary[r][c];
					while(curr==next){
						count++;
						c++;
						if(c>=numCols){
							r++;
							c=0;
							break;
						}
						curr=next;
						next=Ary[r][c];
					}
				}
			p.print(count);
			p.println();
			count=0;
			if(r>=numRows)
				break;
		}
	}
	
	}
	private void method2(PrintWriter p){
		int r=0;
		int count=0;
		int next;
		int c=0;
		int curr=Ary[r][c];
		while(r<numRows){
			curr=Ary[r][c];
			while(curr<=0&&r<numRows){
				c++;
				if(c>=numCols){
					r++;
					c=0;
				}
				if(r<numRows)
					curr=Ary[r][c];
			}
			if(r<numRows){
				p.print(r+" "+c+" "+curr+" ");
				count++;
				c++;
				if(c>=numCols){
					r++;
					c=0;
				}
				if(r<numRows){
					next=Ary[r][c];
					while(curr==next&&r<numRows){
						count++;
						c++;
						if(c>=numCols){
							r++;
							c=0;
						}
						if(r>=numRows)
							break;
						curr=next;
						next=Ary[r][c];
		
					}
				}	
			p.print(count);
			p.println();
			count=0;
			}
			
		}

	
	}
	private void method3(PrintWriter p){
		int r=0,c=0,nextVal,currVal,count=0;
		nextVal =Ary[r][c];
		while(r<numRows){
			currVal=Ary[r][c];
			p.print(r+" "+ c+ " "+currVal+" ");	
			count++;
			c++;
			if(c>=numCols){
				r++;
				c=0;
			}
				
			else{
				nextVal =Ary[r][c];
				while(nextVal == currVal){
					count++;
					c++;
					if(c>=numCols){
						r++;
						c=0;
						break;
					}
					currVal=nextVal;
					nextVal=Ary[r][c];
				}
			}	
			p.print(" "+count);
			p.println();
			count=0;
		}
	}
	private void method4(PrintWriter p){
		int r=0;
		int count=0;
		int next;
		int c=0;
		int curr=Ary[r][c];
		while(r<numRows){
			curr=Ary[r][c];
			p.print(r+" "+c+" "+curr+" ");
			count++;
			c++;
			if(c>=numCols){
				r++;
				c=0;
			}
			if(r<numRows){
				next=Ary[r][c];
				while(curr==next&&r<numRows){
					count++;
					c++;
					if(c>=numCols){
						r++;
						c=0;
					}
					if(r>=numRows)
						break;
					curr=next;
					next=Ary[r][c];
	
				}
			}	
			p.print(count);
			p.println();
			count=0;
			
		}

	
	}
	public void RunLength(Scanner in, PrintWriter p){
		p.println(numRows+" "+ numCols+ " "+ minVal+" "+maxVal);
		p.println(method);
		loadImage(in);

		Method(method,p);
	}



}
