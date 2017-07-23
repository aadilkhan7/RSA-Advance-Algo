/*
	Date: 09/16/16
	Advanced Algorithm
	Assignment-1: RSA Algorithm implementation using Bearcatii values.
	Group-1
		AMAN SHRIVASTAVA
		AADIL KHAN
		KARANSINGH PATIL
		NANDIKA SHENDRE
*/

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#define ll long long
using namespace std;
//Class for Data Entry
class DataEntry
{

public:	
char letter[27];
int code[27];

//Function to insert Bearcatii in Array
void fillCode()
{
	for(int i=0;i<27;i++)
	{
		code[i]= i;
	}
}

//Function to insert characters in Array
void fillLetters()
{
	int c=65;
	letter[0]=' ';
	for(int i=1;i<27;i++)
	{
		letter[i]=c;
		c++;
	}
}

//Function to match characters with index
int findBaseNumber(char c)
{
	int i=0,val;
	do 
	{
		if(letter[i]==c)
		{
			val=code[i];
			exit;
		}
		++i;
	}
	while(i<27);
	return val;		
}
};


//Function to take Power Modulus
ll powerD(ll base, ll exponent, int modulus)
{
    ll result = 1;
    //Iterating over Power
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

//CHECK WHETHER PRIME OR NOT
bool isPrime(int n)
{

	bool p=false;
	for(int i=2;i<sqrt(n);i++)
	{
		if(n%i==0)
		{
			return false;			
		}
	}
	p=true;	
	return p;
}

//PRIME NUMBER GENERATION
int generatePrime()
{
	time_t t;	
	srand((unsigned) time(&t));
	int v;
	while(1)
	{
		v=rand();
		if(isPrime(v))
		{
			return v;		
		}
	}
}



// Extended Euclidean Algorithm for GCD
int gcd(int num1, int num2, int *x, int *y)
{
    // Base Case
    if (num1 == 0)
    {
        *x = 0, *y = 1;
        return num2;
    }
 
    int x1, y1; // To store results of recursive call
    int gc = gcd(num2%num1, num1, &x1, &y1);
    *x = y1 - (num2/num1) * x1;
    *y = x1;
 
    return gc;
}

// Private key(d) generation. Using congruence relation.
int multiplicativeInverseModulus(int num1, int num2)
{
    int x, y;
    int g = gcd(num1, num2, &x, &y);
    if (g != 1)
        cout << "Inverse doesn't exist";
    else
    {
        int res = (x%num2 + num2) % num2;
        return res;
    }
}
 
// Public key(e) check
int publickeyCal(long int toition)
{
	int e,x,y,k=0;
	while(1)  
	{
		if(k==0)
			cout<<"\nPlease enter 'e': ";
		else
			cout<<"\nPlease Re-enter 'e': ";
		cin>>e;
		int gc = gcd(toition,e,&x,&y);
		if(gc==1)
		{
			break;
		}
		k++;
			
	}
	return e;
}

//Function for Decrypting Ciphered Text
int decryption(long int cipheredMessage, long int privateKey, long int n)
{
	long long int decryptedMessage= powerD(cipheredMessage, privateKey, n);
	return decryptedMessage;
}

//Function to convert number to Characters
void convertToText(ll int decryptedMessage, long int base, char letter[], char ans[], int size)
{
	int dM= decryptedMessage;
	int q,r,i=size,j=0;
	
	q=dM/base;
	r=dM%base;
	while(i>0)
	{
		if(r==0)
			r=-32;
		ans[j]=char(r+64);
		r=q%base;
		q=q/base;		
		i--;j++;
	}
}


int main()
{
	DataEntry de;
	
	de.fillCode();
	de.fillLetters();
	string userMessage;
	int em=0;
	
	cout<<"Enter the Message: ";
	std::getline(std::cin,userMessage);
	
	int n[userMessage.size()];
	int l=userMessage.size();
	
	
	
	for(int i=0;i<l;i++)	
	{
		n[i]=de.findBaseNumber(userMessage[i]);
	}
	
	//generating Integer message
	for(int i=0;i<l;i++)	
	{
		//Converting integer User Message into Bearcatii number
		em+= n[l-i-1]*(pow(27,i));
				
	}
	
	//First Random Prime Number
	long int p=generatePrime();
	//Second Random Prime Number
	long int q;
	while (1)
	{
		q=generatePrime();
		if (p!=q)
		break;
	}
	long int N=p*q;
	
	long int toition = (p-1)*(q-1);
	
	long int publickey=publickeyCal(toition);
	
	long int privateKey= multiplicativeInverseModulus(publickey, toition);
	
	//Encryption of User Message
	ll int cipheredMessage=powerD(em,publickey,N);
	//	cout<<"Ciphered Message or PowerMod is--> "<<cipheredMessage<<endl;
		
	if(privateKey!=-1)
	{
		ll int decryptedMessage = decryption(cipheredMessage,privateKey, N);
		cout<<"Prime Num1: "<<p<<"\n";
		cout<<"Prime Num2: "<<q<<"\n";
		cout<<"N: "<<N<<"\n";
		cout<<"Totient: "<<toition<<"\n";
		cout<<"Public key: "<<publickey<<"\n";
		cout<<"Private Key: "<<privateKey<<"\n";
		
		char ans[userMessage.size()];
		convertToText(cipheredMessage,27,de.letter,ans,userMessage.size());
		cout<<"\nCiphered Text: ";
		for(int i=userMessage.size()-1;i>=0;i--)
		{
			cout<<ans[i];
		}
		convertToText(decryptedMessage,27,de.letter,ans,userMessage.size());
		cout<<"\nDeciphered Text: ";
		for(int i=userMessage.size()-1;i>=0;i--)
		{
			cout<<ans[i];
		}	
	}
}
/*
	Note: This code might give garbled values for longer string(User Message) due to storage contraints which occurs due to overflow.
*/
