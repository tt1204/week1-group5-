//10727207 張婷_10727240 賴卷狄
#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>
#include <vector> 
#include <stdlib.h> 
#include <stdio.h> 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;
 
typedef enum { Copy = -1,
                Right, Down, Left, Up} Moves; // 右，下，左，上分別對應0.1.2.3,denote表示 the direction of each move
typedef enum { oneGoal, moreGoal} Modes;
int goals =0;
class CoXY {
	int y ;// X軸 
	int x ;// Y 軸
	
public:
    CoXY():y(0),x(0)
	{ } ; // default(自訂/預設) constructor
	
	CoXY( int py,  int px )  
	{
		y = py;
		x = px ;
		
	 }  // (有設定值的)constructor
	 
	 CoXY( const CoXY & pt): y(pt.y),x(pt.x) 
	 { }
	 
	 void setXY( const int py, const int px ) // 設定座標
	 {
	 	y = py;
	 	x = px;
	 } // setXY()
	 
	 
	 int getX() const // 拿到X值
	 {
	 	return x;
	 }// getX()
	 
	 
	 int getY() const // 拿到Y值 
	 {
	 	return y;
	 }// getY()
	 
	 CoXY nextXY( Moves dir) const // 移動之後的結果 
	 {
	 	CoXY pt( x, y); // 取得複本 
	 	
	 	switch ( dir)
		 {
		 	case Right: pt.setXY( pt.getX() + 1,pt.getY());
		 	        	break;
		 	case Down: pt.setXY( pt.getX() ,pt.getY()+1);
		 	        	break;
		 	case Left: pt.setXY( pt.getX() - 1,pt.getY());
		 	        	break;
		 	case Up: pt.setXY( pt.getX() ,pt.getY()-1);
		 	        	break;
		 	        	
		 	default:    ; // 備份 
		  } // switch()
		  
		return pt;
	 } // nextXY()
	 
	 bool match( const CoXY& pt) const // 為了找有無一樣的座標 
	 {
	 	
	 	if ( ( x == pt.x ) && ( y == pt.y ) ) 
	 		return true;
	 	
	 	return false;
	 	
	 } // match()
	 
	 bool inRange( const CoXY& maxLimit) const // 確認此座標在範圍內 
	 {
	 	if ( ( x >= 0 ) && ( x < maxLimit.x ) 
		 		&& ( y >= 0 ) && (y < maxLimit.y ) )
	 		return true;
	 	
	 	return false;
	 	
	 } inRange()
	 ;
	 
	   
};


class Maze {
	
	
	CoXY	coMax; // 邊界 

	private: char	**mArray; //  指向指標組的陣列 
	
public:
	CoXY	 coNow;
bool load( string fileName )  //讀取檔案並設定迷宮 
{
	FILE	*infile = NULL; 
	bool	success = false; //判斷讀取有無成功 
	
	
	fileName = "input" + fileName + ".txt"; // 為了補齊檔案名稱
	infile = fopen(fileName.c_str(),"r"); //開檔
	if( infile == NULL) // 如果沒打開檔案 
		cout<<endl<<fileName<<"does not exist!"<<endl;
	else
	{
		int arg1 = 0,arg2 = 0;
		
		fscanf(infile, "%d %d", &arg1, &arg2);//抓檔案的兩個數字 
		
		coMax.setXY(arg2, arg1);//設定最大的XY值 
		
		if((coMax.getY()) > 0 && (coMax.getX() > 0 ) )//設定該位置 
		{
			int line = 0;
			char *temp = new char[coMax.getX()+1]; //  多一行緩衝 
			
			mArray = new char *[coMax.getY()]; // 設定位置去存放 
			while ( fscanf( infile, "%s", temp) != EOF)
			{
				mArray[line] = new char[coMax.getX()+1];  
				strcpy(mArray[line++], temp); //存放資料 
			} // while() 
			
			if( line == coMax.getY()) // 行數正確 
				success = true;
		} // if()
		fclose(infile); // 關檔
	 } // else
	 
	 return success;
} // load ()



void show(){ // 印mArray
	for ( int j = 0 ; j < coMax.getY(); j ++){
		for ( int i = 0 ; i < coMax.getX(); i ++)
			cout << mArray[j][i]; 
		cout << endl;
	} // for()
} // show



void copy( Maze aMaze) { // 複製一個地圖 
	coMax = aMaze.coMax; // 設邊界 
	coNow = aMaze.coNow;
	mArray = new char *[coMax.getY()]; // 設新的地圖陣列 
	  
    for(int i = 0; i < coMax.getY(); i++)
        mArray[i] = new char[coMax.getX()]; // 開新的位置 
        
        
	for ( int j = 0 ; j < coMax.getX(); j ++) 
		for ( int i = 0 ; i < coMax.getY(); i ++) 
			mArray[j][i] = aMaze.mArray[j][i]; // 複製 
		
} // copy()




		
		
		
CoXY isGoal(Maze vMaze, int count ){ // 找終點並設定
	CoXY temp;
	for( int i =0; i< coMax.getX(); i++) {
		for ( int j = 0; j <coMax.getY();j++) {
			if(vMaze.mArray[j][i] == 'G'&& count == 0) { //計數是為了兩個或兩個以上的終點
				temp.setXY(j,i);//設終點位置
				return temp;
			
			} // if()
			else if (vMaze.mArray[j][i] == 'G')
				count --;//一個或以上，之前找過這個終點
		} // for()
	}//for()
	return temp;
		
} // isGoal()
	
void clear(Maze vMaze){ // 將走過的痕跡消除
	
	for( int i =0; i< coMax.getX(); i++) 
		for ( int j = 0; j <coMax.getY();j++) 
			if(vMaze.mArray[j][i] == 'V') 
				vMaze.mArray[j][i] = 'E';
		
} // clear

bool findGoal(Maze vMaze,int x, int y, CoXY coGoal){ // 找走到終點的路徑
	
	bool done; //有無走到終點
	if ( ( x < 0 ) || ( x >= coMax.getX() ) 
		 		|| ( y < 0 ) || (y >= coMax.getY() ) ) // 有無超出範圍
	 	return false;
	else if( vMaze.mArray[x][y] == 'O') // 有無碰到障礙
		return false;
	else if(  vMaze.mArray[x][y] == 'G'&&x == coGoal.getY()&& y == coGoal.getX())//有無找到終點，並是我剛好要找的
		return true;
	else if( ( vMaze.mArray[x][y] == 'V') ) // 有無走過
		return false;
	else{
		if(vMaze.mArray[x][y] != 'G') // 如果不是終點，還是空路
			vMaze.mArray[x][y] = 'V';// 設成走過
		done = false;
		for( int i = 0; i < 4&&!done; i++ ) { // 還沒找到終點 ，走四個方位
			if(i ==0 )
			 	done =  findGoal( vMaze, x+1,  y,  coGoal);
			if(i == 1 )
			 	done = findGoal( vMaze, x,  y+1,  coGoal);
			if(i == 2)
				done = findGoal( vMaze, x-1,  y,  coGoal);
			if(i == 3)
				done = findGoal( vMaze, x,  y-1,  coGoal);
			
		} //for()
		if (done) { // 走到終點的路徑
			if(vMaze.mArray[x][y] != 'G')
				mArray[x][y] = 'R';
		} // if()
		return done; 
	} // done
	

} // findGoal
	

}; // Maze




int main(int argc, char** argv) {
	int command = 0;
	do {
	
	cout<<endl<<"***Path Finding***";
	cout<<endl<<"**0.Quit          ";
	cout<<endl<<"*1.One goal       ";
	cout<<endl<<"*2.More goals     ";
	cout<<endl<<"******************";
	cout<<endl<<"input a command(0, 1, 2)";
	cin>>command; // 得到指令 
	if( command == 1 || command == 2 ){
		Maze	aMaze;
		string	fileName;
		cout<<endl<<"input a file number(e.g.,201,202,...):";
		cin>>fileName;
		if(aMaze.load(fileName)) // 載入原始矩陣 
		{
			
			Maze	vMaze;
			bool success;
			vMaze.copy(aMaze);
			vMaze.coNow.setXY(0,0);
			aMaze.coNow.setXY(0,0);
			if( command == 2) {
				cout<<endl<<"input a goals number";
							
				cin >> goals;
				
				for ( int i = 0 ; i < goals; i ++){
					CoXY coGoal = aMaze.isGoal( vMaze, i);
					aMaze.clear(vMaze);
					success= aMaze.findGoal(vMaze,aMaze.coNow.getX(),aMaze.coNow.getY(), coGoal);
				
					
				} // for()
				vMaze.show(); // 呈現走過路徑 
					cout << endl;
					
				if(success) // 有無走到終點 
					aMaze.show(); // 呈現 走到終點的路徑
				
			}
			else if ( command == 1) {
			CoXY coGoal = aMaze.isGoal( vMaze, 0);
			 success = aMaze.findGoal(vMaze,aMaze.coNow.getX(),aMaze.coNow.getY(), coGoal);
			
			vMaze.show(); // 呈現走過路徑 
			cout << endl;
			if(success) // 有無走到終點 
				aMaze.show(); // 呈現 走到終點的路徑

			} // if()
		}
	}
	else if( !command )
		break;
	else 
		cout << endl << "Command does not exist!" << endl;
		
	
	
	
	
	
	}while(true);
	system("pause");
	return 0;
} 
