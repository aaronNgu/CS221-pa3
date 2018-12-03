
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

/* node constructor given */
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, HSLAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),LT(NULL),RB(NULL)
	{}

/* destructor given */
twoDtree::~twoDtree(){
	clear();
}

/* copy constructor given */
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}


/* operator= given */
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

/* twoDtree constructor */
twoDtree::twoDtree(PNG & imIn){
/* your code here */
	bool vert = true;
	printf("ctor 1\n");
	pair<int,int> ul;
	printf("ctor 2\n");
	pair<int,int> lr;
	printf("ctor 3\n");
	stats stat = stats(imIn);
	printf("ctor 4\n");
	height = imIn.height();
	printf("ctor 5\n");
	width = imIn.width();
	printf("ctor 1");
	ul = make_pair(0,0);
	printf("ctor 6\n");
	lr = make_pair(width-1,height-1);
	printf("ctor 7\n");
	root = buildTree(stat,ul,lr,vert);

}

/* buildTree helper for twoDtree constructor */
twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr, bool vert) {

/* your code here */
double areaLeftTop;
double areaRightBottom;
double entropyLeftTop;
double entropyRightBottom;
double entropySum;
double minEntropysf;
// Constructor a new node
printf("buildTree 1 \n");
Node *curr = new Node (ul, lr, s.getAvg(ul,lr));
printf("buildTree 2 \n");
int areaTotal = s.rectArea(ul,lr);

// When its not a pixel
printf("buildTree 3 \n");
if (lr != ul) {
	// Note LR (Lower Right)  point is on the left side and UL (Upper Left) is on the right side
	pair<int,int> newLowerRight;
	pair <int, int> newUpperLeft;

	printf("buildTree 4 \n");
	//One direction of splitting for 2 following cases:
	if (lr.first == ul.first) {
		vert = false;
	} else if (lr.second == ul.second) {
		vert = true;
	}
	printf("buildTree 5 \n");
	if (vert == true) {
		// Please note that newLowerRight and newUpperLeft are the corners coordinates that we require and they are changing
		for (int i = ul.first; i < lr.first; i++) {
			//Find the Areas of each [x][] and [][x]
			areaLeftTop= s.rectArea(ul, make_pair(i, lr.second));
			areaRightBottom= s.rectArea(make_pair(i+1, ul.second), lr);
			// Find entropies of each [x][] and [][x]
			// Entopries is calculated as Entropy * area / areaTotal
			entropyLeftTop = ( areaLeftTop * s.entropy(ul, make_pair(i, lr.second))) / areaTotal;
			entropyRightBottom = ( areaRightBottom * s.entropy(make_pair(i+1, ul.second), lr)) / areaTotal;
			// Add 2 entropies
			// Ask if its less than the minimum Entropy so far (accumulator)
			entropySum = entropyLeftTop + entropyRightBottom;
			// Update the new minimum entropy and save the split points
			if (entropySum <= minEntropysf) {
				minEntropysf = entropySum;
				newLowerRight = make_pair(i, lr.second);
				newUpperLeft = make_pair(i+1, ul.second);
			}

		}
		// Now we start splitting and composing ANOTHER TREE
		// Recursion  begins  whre you build the tres
		printf("buildTree 6 \n");
		// Single Row + Coloumn Cases where you split one direction
		if (ul.second == newLowerRight.second) {
			curr -> LT = buildTree(s,ul,newLowerRight, vert);
		}
		if (newUpperLeft.second == lr.second) {
			curr -> RB = buildTree(s,ul,newLowerRight, vert);
		}
		// For Left Side
		curr->LT = buildTree(s,ul,newLowerRight, !vert);
		// For Right Side
		curr->RB = buildTree(s, newUpperLeft, lr, !vert);
	}

	if (vert == false)
		for (int j = ul.second ; j < lr.second; j++) {

			// Areas of Upper Half + Bottom Half
			double areaLeftTop= s.rectArea(ul, make_pair(lr.first, j));
			double areaRightBottom= s.rectArea(make_pair(ul.first, j+1), lr);
			// Find Entropies
			entropyLeftTop = (areaLeftTop * s.entropy(ul, make_pair(lr.first, j))) / areaTotal;
			entropyRightBottom = (areaRightBottom * s.entropy(make_pair(ul.first, j+1), lr)) / areaTotal;
			//Find Sum of Entropies
			entropySum = entropyLeftTop + entropyRightBottom;
			if (entropySum <= minEntropysf) {
				// Update the new Entropy and save
				minEntropysf = entropySum;
				newUpperLeft = make_pair(ul.first , j+1);
				newLowerRight = make_pair(lr.first, j);
			}
		}

		// Now we start splitting and composing ANOTHER TREE
		// Recursion  begins  whre you build the tres

		// Single Row + Coloumn Cases where you split one direction
		if (ul.first == newLowerRight.first) {
			curr -> LT = buildTree(s,ul,newLowerRight, !vert);
		}
		if (newUpperLeft.first == lr.first) {
			curr -> RB = buildTree(s,ul,newLowerRight, !vert);
		}
		// For Left Side
		curr->LT = buildTree(s,ul,newLowerRight, vert);
		// For Right Side
		curr->RB = buildTree(s, newUpperLeft, lr, vert);

}

}

/* render your twoDtree into a png */
PNG twoDtree::render(){
/* your code here */
//printf("render 1 \n");
 PNG picture = PNG(width, height);
// printf("render 2 \n");
 renderPicture(root, picture);
// printf("render 3 \n");
 return picture;
}

void twoDtree::renderPicture(Node* nd, PNG pic){
//	printf("renderPicture 1 \n");
	if (nd == NULL){
//		printf("root is NULL \n");
	}
//	printf("after if\n");
//	printf("nd->upLeft %d\n",nd->upLeft.first);
	pair<int,int> UL = nd->upLeft;
//	printf("%d \n", UL.first);
//	printf("renderPicture 1.1\n");
	pair<int,int> LR = nd->lowRight;
//	printf("renderPicture 2 \n");
	if(nd->LT == NULL && nd->RB == NULL){
//		printf("renderPicture 3 \n");
		for(int i = UL.second; i <= LR.second; i++){
			for(int j = UL.first; j <= LR.first; j++){
//				printf("renderPicture lp start \n");
				HSLAPixel* currPic = pic.getPixel(j,i);
				*currPic = nd->avg;
//				printf("renderPicture lp end \n");
			}
		}
	}else{
//		printf("renderPicture 4\n");
		renderPicture(nd->LT, pic);
		renderPicture(nd->RB, pic);
//		printf("renderPicture 5 \n");
	}
};

/* prune function modifies tree by cutting off
 * subtrees whose leaves are (all within tol) of
 * the average pixel value contained in the root
 * of the subtree
 */
void twoDtree::prune(double tol){
/* your code here */
	//base case
	pruneTree(root,tol);
}

//add to header
//prunes tree
void twoDtree::pruneTree(Node* nd, double tol){
	//do we prune the tree?
	if(withinTolerance(nd, nd, tol)){
		clearChild(nd);
	}else{
		pruneTree(nd->LT,tol);
		pruneTree(nd->RB,tol);
	}
}

//add to header
//returns true if leaves of the tree is within tolerance
bool twoDtree::withinTolerance(Node* toCompareTo, Node* node , double tol){
	if(node->LT == NULL && node->RB == NULL){
		return node->avg.dist(toCompareTo->avg) <= tol;
	}else{
		return withinTolerance(node->LT, node, tol) && withinTolerance(node->RB,node,tol);
	}
}

/* helper function for destructor and op= */
/* frees dynamic memory associated w the twoDtree */
void twoDtree::clear() {
 /* your code here */
	Node* t = root;
	clearChild(t->LT);
	clearChild(t->RB);
	delete root;
}

//add to header
void twoDtree::clearChild(Node* child){
	if(child == NULL) return;
	Node* t = child;
	clearChild(t->LT);
	clearChild(t->RB);
	delete child;
}
/* helper function for copy constructor and op= */
void twoDtree::copy(const twoDtree & orig){

/* your code here */
// height = orig.height;
// width = orig.width;
// root = copyTree(orig.root);
}

// //Helper
// // Mkae a exact copy of that node and return it
// Node* twoDtree::copyTree(Node* orig) {
// 	if (orig == NULL) {
// 		return;
// 	}else {
// // MAke sure new Node and pass it in original arguements (same fields as orig nodes)
// 	Node newNode = Node(orig->upLeft, orig->lowRight, orig->avg);
// 	newNode.LT = copyTree(orig->LT);
// 	newNode.RB = copyTree(orig->RB);
//   return newNode;
// 	}
// }
