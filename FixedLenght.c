
//Title of this code
//Compiler Version 18.00.21005.1 for x86
//Author Claudiu Ciutacu (2015)


#include <iostream>
#include <stdarg.h>
#include <string.h>

#define STR_TEST \
"40DUM10 DU010             41          42XX00             1                                                          105         17  15dummy signal dummy ENTRY DUMMY ENTRY DUMMY ENTRY\n"\
"40DUM20 DU010             41          42XX00             1                                                          105         17  15dummy signam dummy ENTRY DUMMY ENTRY DUMMZ ENTRY\n"\
"40DUM30 DU010             41          42XX00             1                                                          105         17  15dummy signan dummy ENTRY DUMMY ENTRY DUMM0 ENTRY\n"\

int GetL(char** pszOut, char* szIn, ...);
int GetL(char** pszOut, const char* szIn, unsigned int* nPos, unsigned int nCols);
int GetT(char*** ppszOut, const char* szInpBuf, unsigned int* nPos, unsigned int nRows, unsigned int nCols);


class clsFixedLenght
{
    public:
        clsFixedLenght();
        ~clsFixedLenght();
    
};


int main()
{
    char* szBuf = new char[23*190];
    char* szTmp = szBuf;
    memcpy(szBuf, STR_TEST, strlen(STR_TEST));
    // std::cout<<szBuf<<std::endl;
    // std::cout<<"//////////////////////////////////////////////////////////////////////////////"<<std::endl;
    unsigned int nPos[] = {21, 29, 41, 46, 59, 85, 97, 104, 110, 120, 131, 135, 154, 189, 0};
    int nRows = 3;
    int nCols = sizeof(nPos)/sizeof(int);
    // std::cout<<"nCols = "<<nCols<<std::endl;     
    char*** ppszOut = new char**[nRows];
    for(unsigned int i = 0; i<nRows; i++)
    {
        ppszOut[i] = new char*[nCols-1];
        for(unsigned int j = 0; j<nCols-1; j++)
        {
            ppszOut[i][j] = new char[nPos[j]-(j>0)*nPos[j-(j>0)]+1];
        }
    }
    GetT(ppszOut, szBuf, nPos, nRows, nCols);
    char* szNew = strchr(szTmp+1, '\n')+1;
    for(unsigned int i = 0; i<nRows; i++)
    {
        std::cout<<"##DEBUG3111##"<<std::endl;
        char* szInp = new char[nPos[nCols-2]];      
        
        // std::cout<<"Columns: "<<nPos[nCols-2]<<std::endl;
        // std::cout<<szNew<<std::endl;
        std::cout<<"##DE_LEN = "<<szNew-szTmp<<std::endl;
        memcpy(szInp, szTmp, szNew-szTmp-1);
        std::cout<<"##DEBUG3121##"<<std::endl;
        // std::cout<<szInp<<std::endl;
        char** pszOut = new char*[nCols-1]; // nCols columns maximum...
        for(unsigned int j = 0; j<nCols-1; j++)
        {
            if(nPos[j]>=nPos[j-(j>0)])
            {
                pszOut[j] = new char[nPos[j]-(j>0)*nPos[j-(j>0)]+1]; // reserve size according to the field size...                
            }
        }
        
        GetL(pszOut, szInp, nPos, nCols);
        for(unsigned int j=0; j<nCols-1; j++)
        {
            if(nPos[j]>=nPos[j-(j>0)])
            {
                std::cout<<i<<"\t"<<nPos[j]<<"\t"<<nPos[j]-(j>0)*nPos[j-(j>0)]<<"\t|"<<pszOut[j]<<"|"<<std::endl;                
            }
        }
        
        for(unsigned int j = 0; j<nCols-1; j++)
        {
            // std::cout<<"here!!!!!!! "<<j<<"\t"<<nPos[j]<<std::endl;
            if(nPos[j]>=nPos[j-(j>0)])
            {
                delete[] pszOut[j];
            }
        }
        delete[] pszOut;
        delete[] szInp;
        szTmp = szNew;
        szNew = strchr(szTmp+1, '\n')+1;
    }
    std::cout<<"/////////////////////////////////////////"<<std::endl;
    for(unsigned int i = 0; i<nRows; i++)
    {
        for(unsigned int j = 0; j<nCols-1; j++)
        {
            std::cout<<"|"<<ppszOut[i][j]<<"|";
        }
        std::cout<<std::endl;
    }
    std::cout<<"/////////////////////////////////////////"<<std::endl;
    delete[] ppszOut;
    std::cout<<"##DEBUG3889##"<<std::endl;
    delete[] szBuf;
    std::cout<<"##DEBUG3323##"<<std::endl;
    std::cout << "Hello, world!\n";
    return 0;
}


int GetT(char*** ppszOut, const char* szInpBuf, unsigned int* nPos, unsigned int nRows, unsigned int nCols)
{
    char* szBuf = new char[strlen(szInpBuf)]; 
    memcpy(szBuf, szInpBuf, strlen(szInpBuf)); 
    char* szTmp = szBuf;
    char* szNew = strchr(szTmp+1, '\n')+1;

    for(unsigned int i = 0; i<nRows; i++)
    {
        // std::cout<<"##DEBUG3111##"<<std::endl;
        char* szInp = new char[nPos[nCols-2]];      
        
        // std::cout<<"Columns: "<<nPos[nCols-2]<<std::endl;
        // std::cout<<szNew<<std::endl;
        // std::cout<<"##DE_LEN = "<<szNew-szTmp<<std::endl;
        memcpy(szInp, szTmp, szNew-szTmp-1);
        std::cout<<"##DEBUG3121##"<<std::endl;
        // std::cout<<szInp<<std::endl;
        char** pszOut = new char*[nCols-1]; // nCols columns maximum...
        for(unsigned int j = 0; j<nCols-1; j++)
        {
            if(nPos[j]>=nPos[j-(j>0)])
            {
                pszOut[j] = new char[nPos[j]-(j>0)*nPos[j-(j>0)]+1]; // reserve size according to the field size...                
            }
        }
        
        GetL(pszOut, szInp, nPos, nCols);
        GetL(ppszOut[i], szInp, nPos, nCols);
        // ppszOut[i] = pszOut; // load the input table of char*-strings
        for(unsigned int j=0; j<nCols-1; j++)
        {
            if(nPos[j]>=nPos[j-(j>0)])
            {
                std::cout<<i<<"\t"<<nPos[j]<<"\t"<<nPos[j]-(j>0)*nPos[j-(j>0)]<<"\t|"<<pszOut[j]<<"|"<<std::endl;                
            }
        }
        for(unsigned int j = 0; j<nCols-1; j++)
        {
            // std::cout<<"here!!!!!!! "<<j<<"\t"<<nPos[j]<<std::endl;
            if(nPos[j]>=nPos[j-(j>0)])
            {
                delete[] pszOut[j];
            }
        }
        delete[] pszOut;
        delete[] szInp;
        szTmp = szNew;
        szNew = strchr(szTmp+1, '\n')+1;
    }
    std::cout<<"##DEBUG2122##"<<std::endl;
    delete[] szBuf;
    std::cout<<"##DEBUG2722##"<<std::endl;
    return 0;
}



int GetL(char** pszOut, char* szIn, ...)
{
    int i = 0; // counts variable arguments
    int poo = 0; // position of the previous field 
    int pos = 32767; // catches the arguments, then pos-poo is the lenght of a field
    char* szTmp = new char[100];
    
    va_list ap;
    va_start(ap, 0);
    while(pos)
    {
        pos = va_arg(ap, int);
        pos--;
        if(poo>pos) break;
        memcpy(pszOut[i], szIn+poo, pos-poo);
        // std::cout<<pos<<"\t"<<pos-poo<<"\t"<<pszOut[i]<<std::endl;
        poo = pos;
        i++;
    };
    va_end(ap);
    delete[] szTmp;
    return i;
}


int GetL(char** pszOut, const char* szIn, unsigned int* nPos, unsigned int nCols)
{
    int poo = 0; // position of the previous field 
    int pos = 1000; // catches the arguments, then pos-poo is the lenght of a field
    
    // std::cout<<"szIn = \""<<szIn<<"\""<<std::endl;
    for(int i=0; i<nCols-1; i++)
    {
        pos = nPos[i]-1;
        // std::cout<<"X\t"<<pos<<"\t"<<pos-poo<<"\t";
        memcpy(pszOut[i], szIn+poo, pos-poo);      
        // std::cout<<pszOut[i];
        poo = pos;
        // std::cout<<std::endl;
    }
    return 0;
}

int MyTrim(char* szInp)
{
    
    return 0;
}

