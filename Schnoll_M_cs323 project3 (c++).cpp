/*
Miriam Schnoll
CSC323_22/700 Project 3
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class listBinTreeNode {
	private: 
		string _chStr;
		int _prob;
		listBinTreeNode * _next;
		listBinTreeNode * _right;
		listBinTreeNode * _left;
		string _code;
	public:
		string & chStr(){
			return _chStr;
		}
		string & code(){
			return _code;
		}
		int prob(){
			return _prob;
		}
		listBinTreeNode * & next(){
			return _next;
		}
		listBinTreeNode * & right (){
			return _right;
		}
		listBinTreeNode * & left (){
			return _left;
		}
		listBinTreeNode(string ch, int p){
			_chStr = ch;
			_prob=p;
			_next=0;
			_left=0;
			_right =0;	
		}
		~listBinTreeNode(){
			delete _next;
			delete _right;
			delete _left;
		}
		void printNode(ostream &os){
			os << _chStr << "  prob: " << _prob;
			if(_left)
				os<<" left: " << this->left()->chStr();
			if(!_left) 	
				os << " left: Null";
			if( _right)
				os << " right: " << this->right()->chStr() ;
			if (!_right)
			 	os <<" right: NULL";
			os<< endl;
		}
		
};	

class HuffmanLinkedList {
	protected:
	listBinTreeNode * _listHead;
	listBinTreeNode * _oldListHead;
	public:
		listBinTreeNode * &  listHead(){
			return _listHead;
		}
		listBinTreeNode * & oldListHead(){
			return _oldListHead;
		}
		HuffmanLinkedList (){
			listBinTreeNode * dummy = new listBinTreeNode("dummy",0);
			_listHead = dummy;
		}
		listBinTreeNode * & findSpot ( int p){
			listBinTreeNode * curr= _listHead;
			//if list is just dummy node
			if(!_listHead->next())
					return curr;
			while(curr->next()){
				if (p > curr->next()->prob())
					curr=curr->next();
				else 
				  	return curr;
			}
			//get to end of list return pointer
			return curr;
		}
		bool isEmpty(){
			if(_listHead->next())
				return true;
			else 
				return false;
		}
		void listInsert(listBinTreeNode* & spot, listBinTreeNode* & newNode){
			//new node's next points to spot's next
			newNode->next()=spot->next();
			spot->next()=newNode;	
		}
		void printList(ofstream &os){
			//prints the list
			listBinTreeNode*curr=_listHead->next();
			os<< "listHead --> ";
			while (curr){
				os<<"(" <<curr->chStr() << " , " << curr->prob() << " , ";
				if (curr->next())
					os<< curr->next()->chStr() << " ) --> ";
				else
					os<<"NULL ) --> NULL";
				curr=curr->next();			
				}
				os << endl;
		}
		//construct a huffman linked list from file
		void constructHuffmanLList (ifstream &infile,ofstream &os) {
			string data;
			string ch="";
			int num=0;
			while(infile>>data){
				//string from file
				ch+=data;
				//then gets number from file
				infile>>num;
				//creates new node
	 			listBinTreeNode * newNode =  new listBinTreeNode (ch,num);
	 			//finds spot
				listBinTreeNode * spot = this->findSpot(newNode->prob());
				//inserts new node
				this->listInsert(spot, newNode);
				//prints list after each insert
				this->printList(os);
			ch="";
	}
		}

		
		
	
};
class HuffmanBinaryTree{
	private:
	listBinTreeNode * root;
		//preorder traversal print left right
		static void preOrderTraversal (listBinTreeNode * r, ofstream &os){
		 if (r) {
			r->printNode(os);
			preOrderTraversal(r->left(),os);
			preOrderTraversal (r->right(),os);
			}
				
		}
		//inorder traversal left print right
		static void inOrderTraversal (listBinTreeNode * r, ofstream &os){
		 if (r){
		 	inOrderTraversal(r->left(),os);
			r->printNode(os);
			inOrderTraversal (r->right(),os);
		}
				
		}
		//postorder traversal left right print
		static void postOrderTraversal (listBinTreeNode * r, ofstream &os){
		 if (r){
			 postOrderTraversal(r->left(),os);
			 postOrderTraversal (r->right(),os);
			 r->printNode(os);
			
			}
	}
		bool isLeaf	(listBinTreeNode * r)	{
			if (r->right() && r->left())	
				return false;
			else 
				return true;
		
		}
	 void constructCharCode (listBinTreeNode* r, string code, ofstream &os){
		if (!r){
			cout << " this is an empty tree" << endl;
			return;
		}	
		else if ( isLeaf(r)){
			os << r->chStr() << " ";
			r->code()=code;
			os << r->code() << endl;
		}
		else{

		constructCharCode (r->left(),code + "0",os) ;//string concatenation
		constructCharCode (r->right(), code + "1",os); //string concatenation
		}	
	}
	public:
	HuffmanBinaryTree(){
		root=0;
	}
	void postOrderTraversal (ofstream &os){
			postOrderTraversal(root, os);
		}
	void inOrderTraversal (ofstream &os){
		inOrderTraversal(root,os);
	}
	void preOrderTraversal (ofstream &os){
		preOrderTraversal(root,os);
	}

	void constructHuffmanBinTree(HuffmanLinkedList list){
		list.oldListHead()= list.listHead();
		listBinTreeNode* newNode;
		while (list.listHead()->next()->next()){
			listBinTreeNode* curr = list.listHead()->next();
			string ch1= curr->chStr();
			string ch2= curr->next()->chStr();
			//adds the string of the two node's characters
			string ch= ch1+ch2;
			//adds the probablity of the nodes
			int num =curr->prob()+ curr->next()->prob() ;
			//new node is created
			newNode = new listBinTreeNode (ch,num);	
			newNode->left()=curr;
			newNode->right() = curr->next();
			//list head is moved to the third element
			list.listHead()= list.listHead()->next()->next();
			listBinTreeNode* spot = list.findSpot(newNode->prob());
			list.listInsert(spot,newNode);

		}
		//when the list is one node that's the root;
		this->root=newNode;
			
	}
	void constructCharCode (ofstream &os){
		constructCharCode (root, "",os);
		
	}
};
int main (int argc, char *argv[]){
	//gets files from command line
	ofstream outFile1(argv[2]);
	ofstream outFile2(argv[3]);
	ofstream outfile3(argv[4]);
	ofstream outfile4(argv[5]);
	ofstream outfile5(argv[6]);
	HuffmanLinkedList list;
	HuffmanBinaryTree tree;
	ifstream infile (argv[1]);
	list.constructHuffmanLList(infile,outfile5);
	tree.constructHuffmanBinTree(list);
	tree.preOrderTraversal(outFile2);
	tree.inOrderTraversal(outfile3);
	tree.postOrderTraversal(outfile4);
	tree.constructCharCode(outFile1);
	infile.close();
	outFile1.close();
	outFile2.close();
	outfile3.close();
	outfile4.close();
	outfile5.close();
	

	
		return 0;
}
