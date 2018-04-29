//Miriam Schnoll cs381_32 project 4
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
class ImageProcessing{
	private:
		int numRows;
		int numCols;
		int minVal;
		int maxVal;
		int newMinVal;
		int newMaxVal;
		int ** zeroFramedAry;
		int NeighborAry[5];
		void loadImage(ifstream& infile ) {
			int t;
			while (infile>>t) {
				for (int i = 1; i < numRows + 1; i++) {
					for (int j = 1; j < numCols+1; j++) {
						zeroFramedAry[i][j] = t;
						infile>>t;
					}
				}

			}	

		}	
		//zero framing
		void zeroFrame() {
			for (int i = 0; i < numRows + 2; i++) {
				zeroFramedAry[i][0] = 0;
				zeroFramedAry[i][numCols + 1] = 0;
		}
		for (int j = 0; j < numCols + 2; j++) {
			zeroFramedAry[0][j] = 0;
			zeroFramedAry[numRows + 1][j] = 0;
		}
	}
	void loadNeighbors(int i, int j, int pass) {
		// 1st pass top3 and left
		int f = j - 1;
		if (pass == 1 || pass == 3) {
			for (int t = 0; t < 5; t++) {
				if (t < 3)
					NeighborAry[t] = zeroFramedAry[i - 1][f];
				else if (t == 3)
					NeighborAry[t] = zeroFramedAry[i][j - 1];
				else
					NeighborAry[t] = zeroFramedAry[i][j];
				f++;

			}
		} // 2nd pass bottom3 and right
		else {
			for (int t = 0; t < 5; t++) {
				f = j + 1;
				if (t < 3)
					NeighborAry[t] = zeroFramedAry[i + 1][f];

				else if (t == 3)
					NeighborAry[t] = zeroFramedAry[i][j + 1];
				else
					NeighborAry[t] = zeroFramedAry[i][j];
				f--;
			}

		}
	}
		//top to bottom and left to right
		void firstPassDistance(){
			for(int i=1;i<numRows+1;i++){
				for(int j=1;j<numCols+1;j++){
					if(zeroFramedAry[i][j]>0){
						loadNeighbors(i,j,1);
						int min=NeighborAry[0];
						for(int k=0;k<4;k++){
							if(NeighborAry[k]<min)
								min=NeighborAry[k];
						}
						zeroFramedAry[i][j]=min+1;
					}
				}
			}
		}
		//bottom to top right to left
		void secondPassDistance(){
			for(int i=numRows+1;i>0;i--){
				for (int j=numCols+1;j>0;j--){
					if(zeroFramedAry[i][j]>0){
						loadNeighbors(i,j,2);
						int min=NeighborAry[0];
						for(int k=0;k<4;k++){
							if(NeighborAry[k]<min)
								min=NeighborAry[k];
						}
					if(zeroFramedAry[i][j]<min+1)
						min=zeroFramedAry[i][j];
					else 
						min++;
					zeroFramedAry[i][j]=min;
					}
				
				}
			}
		}
		void prettyPrint(ofstream& outfile,int pass){
			outfile<< "Pass "<<pass<<endl;
			for(int i=1;i<numRows+1;i++){
				for(int j=1;j<numCols+1;j++){
						outfile<<zeroFramedAry[i][j]<<" ";
				}
				outfile<<endl;
			}
			
		}
		//gets new max and new min
		void set_new_max_min(){
			int min=zeroFramedAry[1][1];
			int max=zeroFramedAry[1][1];
			for(int i=1;i<numRows+1;i++){
				for(int j=1;j<numCols+1;j++){
					if(zeroFramedAry[i][j]<min)
						min=zeroFramedAry[i][j];
					if(zeroFramedAry[i][j]>max)
						max=zeroFramedAry[i][j];
				}
			}
			newMaxVal=max;
			newMinVal=min;
		}
		void printPass2(ofstream& outfile){
			outfile<< numRows<<" "<<numCols<<" "<<newMinVal <<" "<<newMaxVal<<endl;
			for(int i=1;i<numRows+1;i++){
				for(int j=1;j<numCols+1;j++){
					outfile<<zeroFramedAry[i][j]<<" ";
				}
				outfile<<endl;
			}
		}
	public:
		ImageProcessing(int r,int c, int minV, int maxV){
		numRows=r;
		numCols=c;
		minVal=minV;
		maxVal=maxV;
		newMinVal=minV;
		newMaxVal=maxV;
		zeroFramedAry = new int*[numRows+2];
		for(int i=0;i<numRows+2;i++){
			zeroFramedAry[i]= new int[numCols+2];
		}
		
			
		}
		void Distance(ifstream& infile, ofstream& outfile1, ofstream& outfile2){
			loadImage(infile);
			zeroFrame();
			firstPassDistance();
			prettyPrint(outfile2,1);
			secondPassDistance();
			prettyPrint(outfile2,2);
			set_new_max_min();
			printPass2(outfile1);
		}
		
};
int main(int argc, char* argv[]){
	ifstream infile (argv[1]);
	ofstream outfile1 (argv[2]);
	ofstream outfile2 (argv[3]);
	int t;
	int r, c, minV, maxV;
	infile>>t;
	r=t;
	infile>>t;
	c=t;
	infile>>t;
	minV=t;
	infile>>t;
	maxV=t;
	ImageProcessing ip (r,c,minV,maxV);
	ip.Distance(infile,outfile1,outfile2);
	return 0;
}
