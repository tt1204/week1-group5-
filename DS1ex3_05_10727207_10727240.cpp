//10727207 張婷 10727240 賴卷狄 
#include <iostream>
#include <math.h>
#include <string.h>
# include <stdlib.h>
#include <new>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAX_LEN 255

using namespace std ;




bool isDigit(char checkChar){ // 確認是否為數字
	if( checkChar >= '0'&& checkChar <= '9')
		return true;
		
	return false; 
}//isdigit()

bool isOpator( char checkChar ) { // 確認是否為運算子 
	if(checkChar=='+'||checkChar=='-'||checkChar=='*'||checkChar=='/'||checkChar=='%')  
		return true;
	
	return false;
}//isOpator

bool isWhiteSpace( char checkChar ) { // 確認是否為空白符號 
	
	if(checkChar=='\t'||checkChar==' ') // tab鍵和空白鍵 
		return true;
	
	return false;
}//isOpator

bool isParenthese( char checkChar ) { // 是否為括號 
	if ( checkChar == '(' || checkChar == ')')
		return true;
		
	return false;
} // isParenthese

bool checkHasIllegalChar( string infixS ){	// 是否有非法字元 
	bool check = true;//先設沒有 
	for( int i = 0; i< infixS.size() ; i ++ ){//整個字串跑一次 
	
		if( !isOpator(infixS[i]) && !isDigit(infixS[i]) && !isWhiteSpace( infixS[i] ) && !isParenthese( infixS[i])){//去檢查是否為運算子運算元和空白 
			cout << "Error 1: " <<infixS[i] << ": is not a legitimate character."<<endl; // 輸出錯誤訊息 
			check = false;
		}//if()
	} // for()
	
	return check;
		
	
} // checkHasIllegalChar()

bool checkHasUnnecessaryParenthese(string infixS){ // 有無多的括號
	int count = 0;  
	
	for( int i = 0; i< infixS.size() ; i ++ ){ //跑整個字串,如果遇到'('就+1,遇到')'就-1 ，前提是count都得大於0 
		if ( infixS[i] == '(' && count >= 0 )
			count ++;
		else if ( infixS[i] == ')' && count >= 0 )
			count --;
	} // for()
	
	if( count == 0)	//代表沒有括號或抵消了 
		return true;
	else if(count > 0)//代表有多的'(' 
		cout << "Error 2: there is one extra open parenthesis.";
	else if(count < 0) // 代表有多的')' 
		cout << "Error 2: there is one extra close parenthesis.";
		
	return false;
} // checkHasUnnecessaryBracet()

bool checkExtraOperator(string infixS){//檢查有無多的運算子 
	
	bool check = true;
	bool lastIsOperator = false;//上一個是運算子 
	for( int i = 0; i< infixS.size()  ; i ++ ){
	
		if( isOpator(infixS[i]) && !lastIsOperator)//如果他上一個不是運算子或還沒遇到運算子，並且自己為運算子 
			lastIsOperator = true;
		else if( isOpator(infixS[i]) && lastIsOperator ){//如果他上一個是運算子，並且自己也是運算子，代表它們連在一起 
			check = false;//這樣就有多的運算子了 
			
			
		}	//else if
		
		else if(isDigit(infixS[i]) && lastIsOperator)//如果遇到數字，並且上一個是 運算子 
			lastIsOperator = false;
		else if(isParenthese(infixS[i]) && lastIsOperator)//如果遇到括號，並且上一個是 運算子  
			lastIsOperator = false;
		
		 	
		
	} // for()
	if(lastIsOperator)//最後一個是運算子 
		check = false;
		
	if( !check)
		cout << "Error 3: there is one extra operator.";
	return check;
} // checkExtraOperator()

bool checkExtraOperand(string infixS){//檢查有無多的運算元 
	
	bool check = true;
	bool lastIsCloseParenthese = false;//上一個是')' 
	for( int i = 0; i< infixS.size()  ; i ++ ){
	
		if( infixS[i] == ')'&& !lastIsCloseParenthese)//如果他上一個不是')'或還沒遇到)'，並且自己為')' 
			lastIsCloseParenthese = true;
		else if( isDigit(infixS[i]) && lastIsCloseParenthese ){//如果他上一個是運算子，並且自己是數字
			check = false;
			lastIsCloseParenthese = false;
			cout << "Error 3: there is one extra operand.";
		}	//else if
		else if(isOpator(infixS[i]) && lastIsCloseParenthese) // 遇到運算子 
			lastIsCloseParenthese = false;
			
		
	} // for()
	
	return check;
} // checkExtraOperator()


bool checkhasInfixInTheParentheses(string infixS){ //看括號裡面有沒有值 
 	
 	bool check = true;
 	bool hasDigitIn = true;//預設有值 
 	int hasAUnDealOpator = 0;//有沒處理完的運算元 
 	bool nowOpen = false;	//括號 還沒刮起來 
 	int openNum = 0; // '('這個括弧的數量 
 	for( int i = 0; i< infixS.size()  ; i ++ ){
	
		if( infixS[i] == '(') {	//還沒括好 
			hasDigitIn = false;	//還沒遇到數值 
			nowOpen = true;	 
			openNum ++;
		}
		else if( infixS[i] == ')' &&  openNum == 1){//括起來了 
			nowOpen = false;
			openNum --;
		
		}	//else if
		else if(nowOpen){
			if( isDigit(infixS[i]) && !hasDigitIn && !hasAUnDealOpator) //如果現在只看到一個數字前面沒任何運算子 
				hasDigitIn = true;
			else if(isOpator(infixS[i])&& !hasDigitIn) {// 直接是運算子 
				check = false;
				cout << "Error 3: it is not infix in the parentheses.";
			}
			else if(isOpator(infixS[i])&& hasDigitIn){ //數字後面加運算子 
				hasAUnDealOpator ++;//有還沒處理的運算子 
				hasDigitIn = false;//所以裡面沒數值 
			}  // else if()
			else if( isDigit(infixS[i]) && !hasDigitIn && hasAUnDealOpator!=0){ //遇到數字並且前面有一運算子 
				hasDigitIn = true;//有數值了 
				hasAUnDealOpator --;
			} // else if()
			else if(infixS[i] == ')'){	//如果在這遇到代表前面有一個以上的'(' 
				
				if( !hasDigitIn )	//如果小括裡本來就沒有數值 
					check = false;
				else 
					hasDigitIn = true;	// 重設 
					
				openNum --;
			}	// else if()
				
				
		} // else if()
		
		
			
		
	} // for()
	
 		if( !nowOpen && hasAUnDealOpator!=0 )  // 括好了 ,並且還有沒處理完的運算子 
			check = false;
		else if( !nowOpen && !hasDigitIn ) //括好了 ，但裡面沒數值 
			check = false;	
	
		if ( !check)
 			cout << "Error 3: it is not infix in the parentheses.";
 	return check;
 	
 } // check hasInfixInTheParentheses()



bool checkError3(string infixS){ // 總和錯誤3 
	
	if( checkExtraOperator( infixS )){
		if(checkhasInfixInTheParentheses(infixS))
			if(checkExtraOperand( infixS ))
				return true;
		}
	return false;
	
} // checkError3



class expStack{//推疊 
	typedef struct sN{  
		char inner; // 內容物 
		struct sN *next;//下一個 
	} stackNode;
	stackNode *topPtr;//頂 
	
	public:
		expStack():topPtr(NULL){
		}
		
		void clear(){//清空 
			topPtr = NULL;
		}
		bool isEmpty() const{//是否為空 
			return topPtr == NULL;
		}
		
		void push( const char inValue ){//放東西 
			if( isEmpty()) {//如果是空的 ，就放在最頂 
			
				topPtr = new stackNode;
				topPtr -> inner = inValue;
				topPtr -> next = NULL;
			} // if()
			else {//如果不是多設一個接頂，在把它換成頂 
				
				stackNode *temp = new stackNode;
				temp -> inner = inValue;
				temp -> next = NULL;
				temp -> next = topPtr;
				topPtr = temp;
			} // else
		} // push
		
		char getTopValue( )	{ // 回傳頂的內容 
			return topPtr ->inner;
		} // getTopValue( )
		
		bool pop( char& outValue){ //拿頂出來 
			if( !isEmpty()){
				stackNode *tempPtr;	//為刪除頂 
				tempPtr = topPtr;
				outValue = topPtr ->inner;
				topPtr = topPtr -> next;
				delete tempPtr;
			} // if()
			else //如果是空回傳否 
				return false;
			
			return true;
		}	// pop()
		
		void print(){
		stackNode *walk; //為了不改到頭 
		walk = topPtr;
		while( walk != NULL){
			cout << walk -> inner;
			walk = walk -> next;
		}// while()
			
		} // print
};

class linkList{ // 連結 
	
struct OpatorOrDigit{
	char inner;// 內容物 
	OpatorOrDigit *next;//下一個 
};
	OpatorOrDigit *head;//頭 
	OpatorOrDigit *tail;//尾 
public:
	char getTail(){ //拿尾巴的值 
		if(isEmpty()) // 如果是空回傳錯誤訊號 
			return 'e';
		else 
			return tail -> inner;	
	}// getTail()
	
    void clear(){//頭尾清空 
		head = NULL;
		tail = NULL;
	}  
	
	bool isEmpty() const{//是否為空 
		return head == NULL;
	}//isEmpty()
	
	void print(){// 印出來 
		OpatorOrDigit *walk; //為了不改到頭 
		walk = head;
		while( walk != NULL){
			cout << walk -> inner;
			walk = walk -> next;
		}// while()
			
	} // print()
	
	void putIn(char inValue){//放進去 
		if( head == NULL){//如果頭是空的，就放頭，並且頭尾指同一個 
			head = new OpatorOrDigit;
			head -> next = NULL;
			head -> inner = inValue;
			tail = head;
		} //if()
		else {//放尾，讓尾變長 
			tail -> next = new OpatorOrDigit;
			tail -> next -> next =NULL;
			tail -> next -> inner = inValue;
			tail = tail -> next; 
		} // else
		
	}//putIn()
	

	
	
};

int priority( char checkOpator){//運算子優先權 
	switch( checkOpator ){
		case '+': case '-': return 1 ;
		case '*': case '/':case '%': return 2 ;
		default:			return 0;
	}
	
}



int main(int argc, char** argv) {
	int command = 0;
	
	do 
	{
		string infixS;
		cout << endl << "*Arithmetic Expression Evaluator*";
		cout << endl << "*0.QUIT                         *"; 
		cout << endl << "*1.infix2Postfix Transformation *";
		cout << endl << "*2.prefix2Postfix Transformation*";
		cout << endl << "*********************************";
		cout << endl << "input a choice(0,1,2):";
		cin >> command;	
		cin.ignore(MAX_LEN,'\n');
		expStack stack ;
		stack.clear();//清空 
		expStack stackA ;
		stackA.clear();//清空 
		linkList link;
		link.clear();//清空 
		switch( command )
		{
			case 0:break;
			case 1: cout << endl << "input an infix expression:";
					getline(cin, infixS);
					if( checkHasIllegalChar(  infixS ) && checkHasUnnecessaryParenthese( infixS )&&   checkError3( infixS )){//檢查是否合乎規則 
						cout << "It is a legitimate infix expression."<< endl;
						for( int i = 0; i < infixS.size(); i ++ ){
							if( isDigit(infixS[i])){//如果是數字 
								if(link.isEmpty())//並且為第一個，直接放 
									link.putIn(infixS[i]);
								else if( link.getTail() != ','&& !isDigit( link.getTail())){//如果不是，且尾巴也不是數字，先放'，'再放 
									link.putIn(',');
									link.putIn(infixS[i]);
								}
								else //前面是數字 ，幹看這裡 
									link.putIn(infixS[i]);
							} //if()
							else if( isOpator(infixS[i])){//如果是運算子 
								link.putIn(',');
								if(stack.isEmpty())//看堆的東西有沒有得比 ，沒有就堆 
									stack.push(infixS[i]);
								else if(priority(stack.getTopValue())>= priority(infixS[i])){//如果有就比 ，比堆的小就把堆的拿出來，然後堆自己 
									char temp;
									if(stack.pop(temp) )
										link.putIn(temp);
									stack.push(infixS[i]);
								} // else if()
								else {//比堆的大就堆 
									stack.push(infixS[i]);
								} //else
								
							} // else if()
							else if( isParenthese(infixS[i])){// 遇到括號 
								if( infixS[i] == '(')//左括號就堆 
									stack.push(infixS[i]);
								else { // 右括號 
									char temp2;
									while( stack.getTopValue() != '('){//拿到左括號為止 
										
										link.putIn(',');
										if(stack.pop(temp2))
											link.putIn(temp2);
									}// while()
									stack.pop(temp2); //把左括號拿出來 
									
								} //else
								
							} // else if()
							
						} // for()
						while( !stack.isEmpty()){ // 把堆的東西一個一個拿出來放後面 
							char temp1;
							link.putIn(',');
							if(stack.pop(temp1))
								link.putIn(temp1);
						} // while()
						link.print();// 印出來 
			
					} // if()
					break;
			case 2: cout << endl << "input an infix expression:";
					getline(cin, infixS);
					if( checkHasIllegalChar(  infixS ) && checkHasUnnecessaryParenthese( infixS )&&   checkError3( infixS )){//檢查是否合乎規則 
						cout << "It is a legitimate infix expression."<< endl;
						for( int i = infixS.size() -1; i >=0; i -- ){
														if( isDigit(infixS[i])){//如果是數字 
								if(link.isEmpty())//並且為第一個，直接放 
									stackA.push(infixS[i]);
								else if( link.getTail() != ','&& !isDigit( link.getTail())){//如果不是，且尾巴也不是數字，先放'，'再放 
									stackA.push(',');
									stackA.push(infixS[i]);
								}
								else //前面是數字 
									stackA.push(infixS[i]);
							} //if()
							else if( isOpator(infixS[i])){//如果是運算子 
								stackA.push(',');
								if(stack.isEmpty())//看堆的東西有沒有得比 ，沒有就堆 
									stack.push(infixS[i]);
								else if(priority(stack.getTopValue()) > priority(infixS[i])){//如果有就比 ，比堆的小就把堆的拿出來，然後堆自己 
									char temp;
									if(stack.pop(temp) ){ 
										stackA.push(temp);
										stackA.push(',');
										}//if() 
									stack.push(infixS[i]);
								} // else if()
								else {//比堆的大就堆 
									stack.push(infixS[i]);
								} //else
								
							} // else if()
							else if( isParenthese(infixS[i])){// 遇到括號 
								if( infixS[i] == ')')//右括號就堆 
									stack.push(infixS[i]);
								else { // 左括號 
									char temp2;
									while( stack.getTopValue() != ')'){//拿到右括號為止 
										
										stackA.push(',');
										if(stack.pop(temp2))
											stackA.push(temp2);
									}// while()
									stack.pop(temp2); //把左括號拿出來 
									
								} //else
								
							} // else if()
							
						} // for()
						while( !stack.isEmpty()){ // 把堆的東西一個一個拿出來放後面 
							char temp1;
							stackA.push(',');
							if(stack.pop(temp1))
								stackA.push(temp1);
						} // while()
						stackA.print();// 印出來 
						
					} //if()
						
					break;
			
			default: cout << endl << "Command does not exist" <<endl;
			
			
			
		} // switch()
	
	} while(command != 0); 
	
	
	
	system("pause");
	return 0;



	

} // main()

	      
	      
