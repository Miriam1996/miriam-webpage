/*
Miriam Schnoll
CSC323_22/700 Project 4 C++
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class HeapSort	{
	private:
		int *heapArray;
		int root_index;
		int fatherIndex;
		int leftKidIndex;
		int rightKidIndex;
		int minKidIndex;
		int size;
		//returns the root
		int getRoot(){
			return heapArray[root_index];
		}
		//if the index is 1 it's the root
		bool isRoot(int index){
			if(index==1)
				return true;
			else
				return false;
		}
		bool isLeaf(int fatherIndex){
			int rightKidIndex= fatherIndex*2+1;
			int leftKidIndex= fatherIndex*2;
			//the left and right kid are not in tree so it's a leaf
			//because the index is greater than the size
			if(rightKidIndex>heapArray[0] && leftKidIndex>heapArray[0])
				return true;
			else
				return false;
		}
		//find the min index of the kids
		int findMinKidIndex(int fatherIndex){
			int rightKidIndex= fatherIndex*2+1;
			int leftKidIndex= fatherIndex*2;
			if(heapArray[rightKidIndex]<heapArray[leftKidIndex])
				return rightKidIndex;
			else
				return leftKidIndex;
			if(isLeaf(fatherIndex))
				throw;
		}
	
		void deleteRoot(){
			//moves the last element into the root
			heapArray[1]= heapArray[heapArray[0]];
			//decreases the size by 1
			heapArray[0]--;
		}
		bool isHeapEmpty(){
			//size is 0 
			//heapArray[0] holds the size
			if(heapArray[0]==0)
				return true;
			else
				return false;
		}
		void bubbleUp(int kidIndex){
			if(isRoot(kidIndex))
				return;
			else{
				int fatherIndex=kidIndex/2;
			if( heapArray[kidIndex]< heapArray[fatherIndex]){
				//swaps elements
				int temp = heapArray[kidIndex];
				heapArray[kidIndex] = heapArray[fatherIndex];
				heapArray[fatherIndex] = temp;
				bubbleUp(fatherIndex);
			}
		}
			
			
		}
		void bubbleDown(int fatherIndex){
			
			if(isLeaf(fatherIndex)){
				return;
			}
				
			else{
				int rightKidIndex= fatherIndex*2+1;
				int leftKidIndex= fatherIndex*2;
				int minIndex = this->findMinKidIndex(fatherIndex);
				if(heapArray[minIndex]<heapArray[fatherIndex]){
					//get min index of kids
					 int temp=heapArray[fatherIndex];
					 //swap elements
					 heapArray[fatherIndex] = heapArray[minIndex];
					 heapArray[minIndex]= temp;
					}
					 bubbleDown(minIndex);
				}
			
			
		}
		void insertOneDataItem (int d){
			//increase size
			heapArray[0]++;
			//put in last spot
			heapArray[heapArray[0]]=d;
			
		}
		bool isHeapFull(){
			//size is the size of the array-1
			if(heapArray[0]==size)
				return true;
			else
				return false;
		}
		//prints the heap 
		void printHeap(ofstream& output){
			for (int i=1; i<heapArray[0];i++){
				output << heapArray [i] << " ";
			}
			output<<endl;
		}
	public:
		~HeapSort(){
			delete [] heapArray;
		}
		HeapSort(int s){
			size=s;
			heapArray = new int[size+1];
			root_index=1;
			//set size to 0
			heapArray[0]=0;
		}
		void DeleteHeap(ofstream& outfile){
			while(!isHeapEmpty()){
			int root=this->getRoot();
			//deletes the root
			this->deleteRoot();
			bubbleDown(root_index);
			//sends the root to the file
			outfile<< root << " ";
		}
			outfile<<endl;
		
		}
		void buildHeap(ifstream& infile,ofstream& outfile){
			int data;
			while(infile>>data){
				insertOneDataItem(data);
				bubbleUp(heapArray[0]);
			}
			//sends heap to file
			printHeap(outfile);	
			
		}
	
	
	
	
};
int main (int argc, char *argv[]){
	ifstream infile(argv[0]);
	ofstream outfile1 (argv[1]);
	ofstream outfile2 (argv[2]);
	int data;
	int num=0;
	//read the file
	while(infile>>data){
		//gets the number of integers from file
		num++;
	}
	infile.close();
	infile.open(argv[0]);
	HeapSort sort(num);
	sort.buildHeap(infile, outfile1);
	sort.DeleteHeap(outfile2);
	infile.close();
	return 0;
}
