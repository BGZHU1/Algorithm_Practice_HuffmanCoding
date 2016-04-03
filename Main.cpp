
#include <iostream>
#include <fstream>
#include <string>


using namespace std;


class ListBinTreeNode {
	friend class HuffmanBinaryTree;
	friend class HuffmanLinkedList;

public:
	string chStr = "";
	int prob = 0;
	ListBinTreeNode* next = NULL;
	ListBinTreeNode* left = NULL;
	ListBinTreeNode* right = NULL;

public:
	//constructor


	ListBinTreeNode(string letter, int integer) {
		chStr = letter;
		prob = integer;

	}



	void printNode(ofstream &outFile) {
		//given a node, T, print T’s chStr, T’s prob, T’s next’s chStr, T’s left’s chStr, T ‘s right’s chStr 
		outFile << chStr << "," << prob << ",";
		if (next != NULL) {
			outFile << next->chStr << "," ;
		}
		else { outFile << "NULL" << "," ; }

		if (left != NULL) {
			outFile << left->chStr << ",";
		}
		else { outFile << "NULL" << ","; }

		if (right != NULL) {
			outFile << right->chStr << endl;
		}
		else { outFile << "NULL" << "," << endl; }
		//cout << chStr << "," << prob << "," << next->chStr << "," << left->chStr << "," << right->chStr << endl;
	}



	//deconstructor
	~ListBinTreeNode() {

		delete next;
		delete left;
		delete right;
	}

};

class HuffmanLinkedList {
	friend class ListBinTreeNode;
	friend class HuffmanBinaryTree;

public:
	ListBinTreeNode * dummyNode;
	ListBinTreeNode * listHead;
	ListBinTreeNode * spot;
	ListBinTreeNode * position;



public:
	HuffmanLinkedList() {//dummy node - list head
		dummyNode = new ListBinTreeNode("dummyNode", -9999);
		listHead = dummyNode;
	}


	void listInsert(ListBinTreeNode * newNode, int integer, string letter, ListBinTreeNode * spot) {

		//findSpot(integer, letter,spot);
		ListBinTreeNode * temp = findSpot(integer, letter, spot);
		newNode->next = temp->next;
		temp->next = newNode;
	}

	ListBinTreeNode* findSpot(int data, string alphabet, ListBinTreeNode *spot) {
	

		//traverse the whole list
		while (spot->next != NULL&&spot->next->prob <= data) {
			//if equal, break 
			if (spot->next->prob == data) {
				break;
			}

			else
				spot = spot->next;
		}

		return spot;
	}

	bool isEmpty() {
		if (listHead->next == NULL) {
			return true;
		}

		else
			return false;

	}


	void printList(ofstream &outFile3, ListBinTreeNode * listhead) {
		//output3 argv[4]

		ListBinTreeNode * printNode = listhead;
		outFile3 << "listHead ";
		while (printNode->next != NULL) {
			//listHead -->(“dummy”, 0, nextString)-->(nextString, prob, next)
			// -->(nextString, prob, nextString)--> ...... --> (nextString, prob, NULL)--> NULL

			outFile3 << "---->" << "(" << printNode->chStr << "," << printNode->prob << ",";

			outFile3 << printNode->next->chStr << ")";

			printNode = printNode->next;

		}

		outFile3 << "---->" << "(" << printNode->chStr << "," << printNode->prob << "," << "NULL" << ")";
		outFile3 << "----->" << "NULL" << endl;


	}



	~HuffmanLinkedList() {
		delete dummyNode;
		delete  listHead;
	}

};

//Tree Class

class HuffmanBinaryTree {
	friend class HuffmanLinkedList;
	friend class ListBinTreeNode;

public:
	string chStr = "";
	int prob = 0;
	string code = "";
	ListBinTreeNode * root = NULL;



public:
	//constructor
	HuffmanBinaryTree() {}

	~HuffmanBinaryTree() { delete root; }

	void preOrderTraveral(ListBinTreeNode *T, ofstream &outFile2) {


		if (T == NULL)
			return;

		else
			T->printNode(outFile2);
		preOrderTraveral(T->left, outFile2);
		preOrderTraveral(T->right, outFile2);

	}

	void constructCharCode(ListBinTreeNode*T, string code, ofstream &outFile1) {

		if (T == NULL)
			return;

		else if (T->left == NULL&&T->right == NULL) {
			outFile1 << T->chStr << ":" << code << endl;
		}
		else {
			constructCharCode(T->left, code + "0", outFile1);
			constructCharCode(T->right, code + "1", outFile1);
		}

	}





};




int main(int argc, char *argv[]) {

	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;
	ofstream outFile3;
	inFile.open(argv[1]);
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	outFile3.open(argv[4]);
	char characters = 'a';
	char alphabet = 'a';
	string letter = "invaild";
	int integer = 0;
	ListBinTreeNode * spot = NULL;
	ListBinTreeNode * dummyNode = NULL;
	ListBinTreeNode * listhead = NULL;
	ListBinTreeNode * root = NULL;
	ListBinTreeNode * newNode = NULL;

	dummyNode = new ListBinTreeNode("dummyNode", -9999);
	spot = dummyNode;
	listhead = dummyNode;

	//pass in the list head to HuffmanLinked list
	HuffmanLinkedList *list = NULL;


	//read from file while not empty 

	while (inFile >> characters) {

		if (isdigit(characters)) {
			int x = (int)characters - 48;
			integer = integer * 10 + x;
		}

		else {
			alphabet = characters;
			integer = 0;
			//cout << alphabet << endl;
		}

		if (integer != 0 && integer != 1 && integer != 6) {
			//cout << integer << endl;


			//make new node
			letter = alphabet;
			ListBinTreeNode * newNode = new ListBinTreeNode(letter, integer);

			//insert new node

			list->listInsert(newNode, integer, letter, spot);

			//print list to argv[4]

			list->printList(outFile3, listhead);
		}
	}
	//close files

	inFile.close();


	//construct Huffman binary tree

	ListBinTreeNode * oldListHead = dummyNode;//save the list head - piont to first node
	ListBinTreeNode* listHead = dummyNode->next;
	while (listHead != NULL&&listHead->next != NULL) {
		int newProb = listHead->prob + listHead->next->prob;
		string newLetter = listHead->chStr + listHead->next->chStr;
		//outFile3 <<"newProb"<< newProb << endl;
		//outFile3<<" newLetter"<<newLetter << endl;
		newNode = new ListBinTreeNode(newLetter, newProb);
		list->listInsert(newNode, newProb, newLetter, listHead);
		newNode->left = listHead;//first node
		newNode->right = listHead->next;//second node

										//print Node
		newNode->printNode(outFile3);

		//move the list head to the third node
		if (listHead->next->next != NULL) {
			listHead = listHead->next->next;
			list->printList(outFile3, listHead);
		}

	}


	//for the last node

	//last node become root
	root=newNode;
	
	
	HuffmanBinaryTree binaryTree;
	binaryTree.constructCharCode(root, "", outFile1);
	binaryTree.preOrderTraveral(root, outFile2);


	outFile1.close();
	outFile2.close();
	outFile3.close();
	//cin.get();
	return 0;

}