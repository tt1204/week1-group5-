// 10727207�i�@_10727240����f 
#include <iostream>
#include <math.h>
# include <stdlib.h>
# include <stdio.h> 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std ;

bool find1 = false;
unsigned long long int fibnum = 0,f0 = 1, nfb = 1,temp = 0;
unsigned long long int recursionsqrtint = 0,factorMax = 0, recursiontime = 0;
unsigned long long int fibTogether[92] = { 1,1 };
int maxj = 0;
void RemindOfBegin() ;
unsigned long long int UseSqrtToFindFactor( unsigned long long int &sqrtint );
unsigned long long int UseRecursionToFindFib( int current ) ;
unsigned long long int UseLoopToFindFib( int current ) ;
unsigned long long int UseLoopToFindFactor( unsigned long long int sqrtintloop, unsigned long long int &looptime ) ;

int main(int argc, char** argv) {

	int usercmd = 0;
    RemindOfBegin();
	
	while ( cin >> usercmd ) { // ��J�@��ƴN�|�] 
	  
	  if ( usercmd == 1)//��J���OQuit 
	    break;
	  else if( usercmd == 2 ) {//�ΰj��] 
	  
        printf( "Input a number: " ) ;
        fibnum = 0,f0 = 1, nfb = 1,temp = 0;
	    unsigned long long int sqrtintloop = 0,  looptime = 0, causemax = 0;
        bool find = false;
        int max = 0;
        scanf( "%llu", &fibnum );//��J�@���j��92���� 
        for ( int i = 1; i <= fibnum && i <= 92; i ++ ) {
          
          max ++;//���outloop 
          UseLoopToFindFib( i );
		  sqrtintloop = sqrt( nfb )  ;
		   	
		  	//����o�Ӽƪ������ 
        // �ݦ��S����n�㰣�A�p�G���N���
          sqrtintloop = UseLoopToFindFactor( sqrtintloop, looptime );
          causemax = nfb / sqrtintloop;
          printf ( "[%2d] %llu = %llu * %llu \t(Inner loop: %2llu times)\n", 
							 max, nfb, sqrtintloop, causemax, looptime ) ;
				
		  
          
          looptime = 0;
		  find = false;

        } // ��O��ƦC 
        if ( fibnum > 92 )
          cout << "outofrange" ;
        else
          cout << "<Outer loop:    " << max << " times>" << endl;
      }// else if()
      else if ( usercmd == 3 ){
        printf ( "Input a number: " ) ;

        
  
        maxj = 0;
        scanf( "%llu", &fibnum );
        for ( int j = 1; j <= fibnum; j++){
          maxj ++;
		  
          nfb = UseRecursionToFindFib( j );
          find1 = false;
		  recursionsqrtint = sqrt( nfb )  ;	
          while( !find1 ) {
		    recursionsqrtint = UseSqrtToFindFactor( recursionsqrtint );
            
          }// while()
          factorMax = nfb / recursionsqrtint;
          printf ( "[%2d] %llu = %llu * %llu \t(Inner recursion: %2llu times)\n", 
					maxj, nfb, recursionsqrtint, factorMax, recursiontime  ) ;
		  
          recursiontime =0;

  
          

 		} //for() 
        if ( fibnum > 92 )
          printf( "outofrange\n" );
        else
          printf("<Outer recursion:    %llu times>\n", maxj ); 
        
	  }// else if()
      else
	    printf( "error command,please try again\n" ); 
	    
	    
    cout << endl ; 
    RemindOfBegin();
    } // while()


	return 0;

}
void RemindOfBegin() {
	
    printf ( "\n** Fibonacci Series Generator **\n") ;
	printf ( "* 1. Quit                      *\n") ;
	printf ( "* 2. Iterative generation      *\n") ;
	printf ( "* 3. Recursive generation      *\n") ;
	printf ( "********************************\n") ;
	printf ( "Input a command( 1, 2, 3): " ) ;
	
} // RemindOfBegin()
unsigned long long int UseSqrtToFindFactor( unsigned long long int &sqrtint ) {+
    recursiontime ++;
    if ( recursiontime % 30000 == 0 ){
	

 
      return sqrtint ;
    } //else()
    else {
	
      if ( nfb % sqrtint == 0 ) { 
  	    
	    
        recursiontime =  recursiontime -  recursiontime / 30000;
	    find1 = true;
        return sqrtint ;
      } //if()
      else {

        sqrtint -- ;
        return UseSqrtToFindFactor( sqrtint );
    
      } // else
    } // else()
} // UseSqrtToFindFactor()

unsigned long long int UseRecursionToFindFib( int current ) { 
   if ( current == 1 ) 
	  return fibTogether[1];//�Ĥ@�����@ 
    else {
    	fibTogether[current ] = fibTogether[current -1 ] + fibTogether[current - 2 ];
      	return fibTogether[current ];
    } // else 
} // UseRecursionToFindFib

unsigned long long int UseLoopToFindFib( int current ) {
    if ( current == 1 ) 
	  ;//�Ĥ@�����@ 
    else {
      	temp = nfb; 
      	nfb = nfb + f0;//�e�ⶵ�ۥ[ 
        f0 = temp;
	
	} // �@�ӼƤ@�Ӽƨ� 
} // UseRecursionToFindFib

unsigned long long int UseLoopToFindFactor( unsigned long long int sqrtintloop, unsigned long long int &looptime ) {
	bool find = false;
    while ( !find ) {
		if ( nfb % sqrtintloop == 0 ) {//�p�G��n�㰣�N���F 
			find = true;//���F�]�X�j�� 
		} // if()
		else {
			sqrtintloop --;//���U�@�Ӷ] 
		}
		looptime ++;
	}
    return sqrtintloop;
} // UseSqrtToFindFactor()
	      
