//Miriam Schnoll csc381_31 project 6
#include <iostream>
#include <fstream>
using namespace std;
	int numRows;
	int numCols;
	int** imgAry;
class image{
	private:
	int minVal;
	int maxVal;
	public:
		image(int r,int c,int min, int max){
			numRows=r;
			numCols=c;
			minVal=min;
			maxVal=max;
			imgAry=new int*[numRows+2];
			for (int i=0;i<numRows+2;i++){
				imgAry[i] = new int[numCols+2];
			
		}
	}
		void loadImage(ifstream& infile ) {
			int t;
			while (infile>>t) {
				for (int i = 1; i < numRows + 1; i++) {
					for (int j = 1; j < numCols+1; j++) {
						imgAry[i][j] = t;
							infile>>t;
					
					}
				}

			}	
		}
		void zeroFramed() {
			for (int i = 0; i < numRows + 2; i++) {
				imgAry[i][0] = 0;
				imgAry[i][numCols + 1] = 0;
			}
			for (int j = 0; j < numCols + 2; j++) {
				imgAry[0][j] = 0;
				imgAry[numRows + 1][j] = 0;
			}
		}	
};
class Point{
	
	public:
		int row;
		int col;
		Point(int r,int c){
			row=r;
			col=c;
		}
		Point(){
			row=0;
			col=0;
		}
		//checks if two points are equal
		bool Equal(Point t){
			if(row==t.row&&col==t.col)
				return true;
			else
				return false;
		}
};
class chainCode{
	private:
	Point neighborCoord[8];
	Point startP;
	Point currentP;
	Point nextP;
	int lastQ;
	int nextQ;
	int nextDirTable[8]={6,0,0,2,2,4,4,6};
	int nextDir;
	int PchainDir;
	public:
		chainCode(){
			lastQ=4;
			nextDir=0;
			PchainDir=0;
			
		}
		void getChainCode(ofstream& outfile1, ofstream& outfile2){
			bool t=false;
			for (int i=1;i<numRows+1;i++){
				for(int j=1;j<numCols+1;j++){
					if(imgAry[i][j]>0&&t==false){
						outfile1<<i-1<<" "<<j-1<<" "<<imgAry[i][j]<<endl;
						outfile2<<i-1<<" "<<j-1<<" "<<imgAry[i][j]<<endl;
						startP.row=i;
						startP.col=j;
						currentP.row=i;
						currentP.col=j;
						lastQ=4;
						t=true;
					}
					if(t)
						break;
				}
				if(t)
					break;
			}
			int k=0;
			while(!currentP.Equal(startP)||k==0){
			nextQ=(lastQ+1)%8;
			PchainDir =findNextP(currentP, nextQ, nextP);
			k++;
			outfile1<<PchainDir<<" ";
			outfile2<<PchainDir<<" ";
				if(k%15==0)
			outfile2<<endl;
			lastQ =nextDirTable[PchainDir];
			currentP.row=nextP.row;
			currentP.col=nextP.col;
		}
		outfile1<<endl;


		}
	void loadNeighborsCoord(Point currentP){
		int i=currentP.row;
		int j=currentP.col;
		int f=j-1;
		//set up 3 2 1 direction
		for(int h=3;h>0;h--){
			Point w(i-1,f);
			neighborCoord[h]=w;
			f++;
		}
		//set up 4
		Point h(i,j-1);
		neighborCoord[4]=h;
		//set up 0
		Point g(i,j+1);
		neighborCoord[0]=g;
			int c=j-1;
		//set up 5 to 7
		for(int k=5;k<8;k++){
			Point t(i+1,c);
			neighborCoord[k]=t;
			c++;
		}
	/*	for(int i=0;i<8;i++){
			cout<< 	neighborCoord[i].row<< " "<<	neighborCoord[i].col<< " "<<endl;
		}*/
		
	}
	int findNextP (Point currentP,int nextQ, Point& nextP){
		loadNeighborsCoord(currentP);
		int chainDir=getChainDir(currentP,nextQ);
		nextP.row=neighborCoord[chainDir].row;
		nextP.col=neighborCoord[chainDir].col;
		return chainDir;
		
	}
	int getChainDir(Point currentP, int nextQ){
		int i=nextQ;
		for(int j=0;j<8;j++){
				if(imgAry[neighborCoord[i].row][neighborCoord[i].col]!=0)
			return i%8;
			i=(i+1)%8;
		}
			
	}
		
	
};
int main(int argc, char* argv[]){
	ifstream infile(argv[1]);
	ofstream outfile1(argv[2]);
	ofstream outfile2(argv[3]);
	int r;
	int c;
	int min; 
	int	max;
	infile>>r;
	infile>>c;
	infile>>min;
	infile>>max;
	outfile1<<r<< " "<<c <<" " << min <<" " <<max<<endl;
	outfile2<<r<< " "<<c <<" " << min <<" " <<max<<endl;
	image i (r,c,min,max);
	i.loadImage(infile);
	i.zeroFramed();
	chainCode cc;
	cc.getChainCode(outfile1,outfile2);
	return 0;
}
