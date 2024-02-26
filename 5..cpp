#include <stdio.h>
#include <ctype.h>

int modInverse(int a,int m) {
    int m0=m,t,q;
    int x0=0,x1=1;

    if (m==1)
        return 0;

    while (a>1) 
	{
        q=a/m;
        t=m;

        m=a%m,a=t;
        t=x0;

        x0=x1-q*x0;
        x1=t;
    }

    if (x1<0)
        x1+=m0;

    return x1;
}

char encrypt(int a,int b,char plain) 
{
    if (isalpha(plain)) 
	{
        char result;

        if (islower(plain)) 
		{
            result=(a*(plain-'a')+b)%26+'a';
        } else 
		{
            result=(a*(plain-'A')+b)%26+'A';
        }

        return result;
    }

    return plain;
}

char decrypt(int a,int b,char cipher) 
{
    if (isalpha(cipher)) 
{
        int aInverse=modInverse(a,26);
        char result;

        if (islower(cipher)) 
		{
            result=(aInverse*(cipher-'a'-b+26))%26+'a';
        } else 
		{
            result=(aInverse*(cipher-'A'-b+26))%26+'A';
        }

        return result;
    }

    return cipher;
}

int main() 
{
    char plaintext[100],encryptedText[100],decryptedText[100];
    int a,b;

    printf("Enter the plaintext:");
    fgets(plaintext,sizeof(plaintext),stdin);

    printf("Enter the values of 'a' and 'b'(space-separated):");
    scanf("%d %d",&a,&b);

    for(int i=0;plaintext[i]!='\0';i++) 
	{
        encryptedText[i]=encrypt(a,b,plaintext[i]);
    }

    encryptedText[sizeof(encryptedText)-1]='\0';

    for(int i=0;encryptedText[i]!='\0';i++)
	{
        decryptedText[i]=decrypt(a,b,encryptedText[i]);
    }

    decryptedText[sizeof(decryptedText)-1]='\0';

    printf("\nEncrypted Text:%s",encryptedText);
    printf("\nDecrypted Text:%s\n",decryptedText);
}