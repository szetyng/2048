#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct coordinate{
	int i,j;
};

void print(const vector<vector<int> >& vscreen);

void moveleftmatrix(vector<vector<int> >& vscreen); 
void moverightmatrix(vector<vector<int> >& vscreen);
void moveupmatrix(vector<vector<int> >& vscreen);
void movedownmatrix(vector<vector<int> >& vscreen);

void mergeleftandup(vector<int>& vrow);
void moveleftanduprow(vector<int>& vrow);

void mergerightanddown(vector<int>& vrow);
void moverightanddownrow(vector<int>& vrow);

void randomtwo(vector<vector<int> >& vscreen);
bool didItMove(const vector<vector<int> >& vscreen, const vector<vector<int> >& vscreenstatic);

bool gameover(const vector<vector<int> >& vscreen);
bool isThereAdjacent(const vector<int>& vrow);

int main(){
	vector<vector<int> > vscreen;
	int tmp;
	
	ifstream infile;
	string infilename;
	cout << "enter initial configuration file name:" << endl;
	cin >> infilename;
	infile.open(infilename.c_str()); 

	if(!infile.is_open()){
		cout << "file not found, using default start configuration" << endl;
		for(int i=0; i<4; i++){
			vector<int> vrow;
			for(int j=0; j<4; j++){
				vrow.push_back(0);
			}
		vscreen.push_back(vrow);
		}
		vscreen[3][3] = 2;
	}

	else{
		for(int i=0; i<4; i++){
			vector<int> vrow;
			for(int j=0; j<4; j++){
				infile >> tmp;
				vrow.push_back(tmp);
			}
			vscreen.push_back(vrow);
		}
	}
	infile.close();
	print(vscreen);
	
	while(!gameover(vscreen)){
		string move;
		cin >> move;
		
		vector<vector<int> > vscreenstatic;
		for(int i=0; i<4; i++){
			vector<int> vrowstatic;
			for(int j=0; j<4; j++){
				vrowstatic.push_back(vscreen[i][j]);
			}
			vscreenstatic.push_back(vrowstatic);
		}

		if(move == "a"){
			moveleftmatrix(vscreen); 
		}
		else if(move == "d"){
			moverightmatrix(vscreen); 
		}
		else if(move == "w"){
			moveupmatrix(vscreen);
		}
		else if(move == "s"){
			movedownmatrix(vscreen);
		}
		else{
			cout << "use 'a' to move left, 'd' to move right, 'w' to move up and 's' to move down" << endl;
		}

		if(didItMove(vscreen, vscreenstatic)){
			randomtwo(vscreen);
			cout << endl;
			print(vscreen);
		}
	} 
	cout << "game over!" << endl;
	
	return 0;
}

void print(const vector<vector<int> >& vscreen){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			cout << vscreen[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void moveleftmatrix(vector<vector<int> >& vscreen){
	for(int i=0; i<4; i++){
		vector<int> vrow;
		for(int j=0; j<4; j++){
			if(vscreen[i][j] != 0){
				vrow.push_back(vscreen[i][j]);
			}
		}
		mergeleftandup(vrow);
		moveleftanduprow(vrow);
		
		for(int j=0; j<4; j++){
			vscreen[i][j] = vrow[j];
		}
	}
}

void moverightmatrix(vector<vector<int> >& vscreen){
	for(int i=0; i<4; i++){
		vector<int> vrow;
		for(int j=0; j<4; j++){
			if(vscreen[i][j] != 0){
				vrow.push_back(vscreen[i][j]);
			}
		}
		mergerightanddown(vrow);
		moverightanddownrow(vrow);
		
		for(int j=0; j<4; j++){
			vscreen[i][j] = vrow[j];
		}
	}
}

void moveupmatrix(vector<vector<int> >& vscreen){
	for(int j=0; j<4; j++){
		vector<int> vcolumn;
		for(int i=0; i<4; i++){
			if(vscreen[i][j] != 0){
				vcolumn.push_back(vscreen[i][j]);
			}
		}
		mergeleftandup(vcolumn);
		moveleftanduprow(vcolumn);
		
		for(int i=0; i<4; i++){
			vscreen[i][j] = vcolumn[i];
		}
	}
}

void movedownmatrix(vector<vector<int> >& vscreen){
	for(int j=0; j<4; j++){
		vector<int> vcolumn;
		for(int i=0; i<4; i++){
			if(vscreen[i][j] != 0){
				vcolumn.push_back(vscreen[i][j]);
			}
		}
		mergerightanddown(vcolumn);
		moverightanddownrow(vcolumn);
		
		for(int i=0; i<4; i++){
			vscreen[i][j] = vcolumn[i];
		}
	}
}

void mergeleftandup(vector<int>& vrow){
	int i=1;
	while(i<vrow.size()){
		if(vrow[i] == vrow[i-1]){
			vrow[i-1] += vrow[i];
			vrow[i] = 0; 
		}
		i++;
	}
	while(vrow.size()<4){
		vrow.push_back(0);
	}
}

void moveleftanduprow(vector<int>& vrow){
	for(int i=1; i<4; i++){
		int j=i;
		while((j>0) && (vrow[j-1]==0)){
			vrow[j-1] = vrow[j];
			vrow[j] = 0;
			j--;
		}
	}
}


void mergerightanddown(vector<int>& vrow){
	int i=vrow.size()-2;
	while(i>=0){
		if(vrow[i] == vrow[i+1]){
			vrow[i+1] += vrow[i];
			vrow[i] = 0;
		}
		i--;
	}
	while(vrow.size()<4){
		vrow.push_back(0);
	}
}

void moverightanddownrow(vector<int>& vrow){
	for(int i=2; i>=0; i--){
		int j=i;
		while((j<3) && (vrow[j+1]==0)){
			vrow[j+1] = vrow[j];
			vrow[j] = 0;
			j++;
		}
	}
}

void randomtwo(vector<vector<int> >& vscreen){
	vector<coordinate> vzerolocation;
	coordinate tmp;
	
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(vscreen[i][j] == 0){
				tmp.i = i;
				tmp.j = j;
				vzerolocation.push_back(tmp);
			}
		}
	}
	
	int random;
	srand(time(NULL));
	
	random = rand() % vzerolocation.size() + 0;
	
	vscreen[vzerolocation[random].i][vzerolocation[random].j] = 2;
}

bool didItMove(const vector<vector<int> >& vscreen, const vector<vector<int> >& vscreenstatic){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(vscreen[i][j] != vscreenstatic[i][j]){
				return true;
			}
		}
	}
	return false;
}

bool gameover(const vector<vector<int> >& vscreen){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(vscreen[i][j] == 0){
				return false;
			}
		}
		
		if(isThereAdjacent(vscreen[i])){
			return false;
		}
		
		vector<int> vcolumn;
		for(int j=0; j<4; j++){
			vcolumn.push_back(vscreen[j][i]);
		}
		if(isThereAdjacent(vcolumn)){
			return false;
		}
	}
	return true;
}

bool isThereAdjacent(const vector<int>& vrow){
	for(int i=0; i<3; i++){
		if(vrow[i] == vrow[i+1]){
			return true;
		}
	}
	return false;
}












	
	
	
	
	
	
	
	
	
	
	
	
	
