//Miriam Schnoll csc381_31 project 5 
#include <iostream>
#include <fstream>
using namespace std;
class ThinningSkeleton{
	private:
		int numRows;
		int numCols;
		int minVal;
		int maxVal;
		bool changeflag;
		int cycleCount;
		int** firstAry;
		int** secondAry;
		void copyAry(){
			for (int i=0;i<numRows+2;i++){
				for (int j=0;j<numCols+2;j++){
					int k=secondAry[i][j];
					firstAry[i][j]=k;
				}
			}
		}
		void loadImage(ifstream& infile ) {
			int t;
			while (infile>>t) {
				for (int i = 1; i < numRows + 1; i++) {
					for (int j = 1; j < numCols+1; j++) {
						firstAry[i][j] = t;
							infile>>t;
					
					}
				}

			}	

		}	
		//zero framing
		void zeroFrame() {
			for (int i = 0; i < numRows + 2; i++) {
				firstAry[i][0] = 0;
				firstAry[i][numCols + 1] = 0;
				secondAry[i][0] = 0;
				secondAry[i][numCols + 1] = 0;
			}
			for (int j = 0; j < numCols + 2; j++) {
				firstAry[0][j] = 0;
				firstAry[numRows + 1][j] = 0;
				secondAry[0][j] = 0;
				secondAry[numRows + 1][j] = 0;
			}
		}
		void DoThinning(int i,int j){
			int Neighbor[9];
			int k=0;
			for(int r=i-1;r<=i+1;r++){
				for (int c=j-1;c<=j+1;c++){
					Neighbor[k]=firstAry[r][c];
					k++;
					
				}
			}
				int count =0;
				for(int h=0;h<9;h++){
					if(Neighbor[h]==1&&h!=4)
						count++;
				}
				// there aren't more than 3 neighbors that are 1's
				//don't do thinning
				if(count<4){
					secondAry[i][j]=1;
					return;
			}
			int north=Neighbor[1];
			int south =Neighbor[7];
			int east = Neighbor[5];
			int west = Neighbor[3];
			int northeast=Neighbor[2];
			int northwest=Neighbor[0];
			int southwest=Neighbor[6];
			int southeast=Neighbor[8];
			//3/4 north south and east west are 1
			
			if((north==1&&south==1&&east==1&&west==0)||(north==1&&south==1&&east==0&&west==1)||(north==0&&south==1&&east==1&&west==1)||(north==1&&south==0&&west==1&&east==1)){
					changeflag=true;
					secondAry[i][j]=0;
			}
			else if(east==0&&west==0){
					secondAry[i][j]=1;
					return;
			}
			
			else if(south==0&&north==0){
					secondAry[i][j]=1;
					return;
			}
			//northeast corner if 0 chnage i j to 0
			else if(north==0&&east==0&&west==1&&south==1&&northeast==0){
				changeflag=true;
				secondAry[i][j]=0;
			}
			//otherwise northeast corner is 1
			else if(north==0&&east==0&&west==1&&south==1&&northeast!=0){
					secondAry[i][j]=1;
					return;
			}
			//nortwest corner is 0
			else if(north==0&&east==1&&west==0&&south==1&&northwest==0){
				changeflag=true;
				secondAry[i][j]=0;
			}
			//if northwest corner is 1
			else if(north==0&&east==1&&west==0&&south==1&&northwest!=0){
					secondAry[i][j]=1;
					return;
			}
			//if southwest corner is 0
			else if(north==1&&east==1&&west==0&&south==0&&southwest==0){
				changeflag=true;
				secondAry[i][j]=0;
			}
			//if southwest corner is 1
			else if(north==1&&east==1&&west==0&&south==0&&southwest!=0){
					secondAry[i][j]=1;
					return;
			}
			
			//if southeast corner is 0
			else if(north==1&&east==0&&west==1&&south==0&&southeast==0){
				changeflag=true;
				secondAry[i][j]=0;
			}
			//if southeast corner is 1
			else if(north==1&&east==0&&west==1&&south==0&&southeast!=0){
					secondAry[i][j]=1;
					return;
			}
			else
				secondAry[i][j]=1;
			
		}
		void NorthThinning(){
			for (int i=1;i<numRows+1;i++){
				for(int j=1;j<numCols+1;j++){
					if(firstAry[i][j]==1&&firstAry[i-1][j]==0)
						DoThinning(i,j);
					else 
						secondAry[i][j]=firstAry[i][j];
				}
			
			}
				
		
		}
		void SouthThinning(){
			for (int i=1;i<numRows+1;i++){
				for(int j=1;j<numCols+1;j++){
					if(firstAry[i][j]==1&&firstAry[i+1][j]==0)
						DoThinning(i,j);
					else 
						secondAry[i][j]=firstAry[i][j];
				}
			}
		}
		void EastThinning(){
			for (int i=1;i<numRows+1;i++){
				for(int j=1;j<numCols+1;j++){
					if(firstAry[i][j]==1&&firstAry[i][j+1]==0)
						DoThinning(i,j);
					else 
						secondAry[i][j]=firstAry[i][j];
				}
			}
			
		}
		void WestThinning(){
			for (int i=1;i<numRows+1;i++){
				for(int j=1;j<numCols+1;j++){
					if(firstAry[i][j]==1&&firstAry[i][j-1]==0)
						DoThinning(i,j);
					else 
						secondAry[i][j]=firstAry[i][j];
				}
			}	
		}
		void prettyPrint(ofstream& outfile1){
				outfile1<<numRows<<" "<<numCols<<" "<<minVal<<" "<<maxVal<<" "<<endl;
			for (int i=1;i<numRows+1;i++){
				for(int j=1;j<numCols+1;j++){
					outfile1<<firstAry[i][j]<<" ";
				}
				outfile1<<endl;
			}
		}
		void prettyPrint(ofstream& outfile2, string t){
			if(t=="N")
				outfile2<<"result of cycle # " <<cycleCount << " of N thinning"<<endl;
			if(t=="S")
					outfile2<<"result of cycle # " <<cycleCount << " of S thinning"<<endl;
			if(t=="W")
					outfile2<<"result of cycle # " <<cycleCount << " of W thinning"<<endl;
			if(t=="E")
					outfile2<<"result of cycle # " <<cycleCount << " of E thinning"<<endl;
			for (int i=1;i<numRows+1;i++){
				for(int j=1;j<numCols+1;j++){
					outfile2<<firstAry[i][j]<<" ";
				}
				outfile2<<endl;
			}
			
		}
	public:
		ThinningSkeleton(int r, int c, int minV, int maxV){
			numRows=r;
			numCols=c;
			minVal=minV;
			maxVal=maxV;
			changeflag=true;
			cycleCount=0;
			firstAry= new int*[numRows+2];
			secondAry=new int*[numRows+2];
			for (int i=0;i<numRows+2;i++){
				firstAry[i] = new int[numCols+2];
				secondAry[i]= new int[numCols+2];
			}	
		}
		void Thinning(ifstream& infile, ofstream& outfile1,ofstream& outfile2){
			zeroFrame();
			loadImage(infile);
			cycleCount=0;
			while(changeflag==true){
				changeflag=false;
				cycleCount++;
				NorthThinning();
				copyAry();
				if(cycleCount==2||cycleCount==4)
					prettyPrint(outfile2,"N");
				SouthThinning();
				copyAry();
				if(cycleCount==2||cycleCount==4)
					prettyPrint(outfile2,"S");
				WestThinning();
				copyAry();
				if(cycleCount==2||cycleCount==4)
					prettyPrint(outfile2,"W");
				EastThinning();	
				copyAry();	
				if(cycleCount==2||cycleCount==4)
					prettyPrint(outfile2,"E");
			}
		prettyPrint(outfile1);
	
		}
};
int main(int argc, char* argv[]){
	ifstream infile(argv[1]);
	ofstream outfile1(argv[2]);
	ofstream outfile2(argv[3]);
	int r;
	int c;
	int min;
	int max;
	int t;
	infile>>t;
	r=t;
	infile>>t;
	c=t;
	infile>>t;
	min=t;
	infile>>t;
	max=t;
	ThinningSkeleton ts(r,c,min,max);
	ts.Thinning(infile,outfile1,outfile2);
	
	
	return 0;
}
