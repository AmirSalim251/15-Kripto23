/*
Nama : Amir Salim
NPM : 140810210015
Kelas :  A
Deskripsi program : Program Hill cipher
*/
#include<iostream>
#include<fstream>
#include<math.h>

typedef int Matrix[100][100];

// Fungsi untuk input matriks
void inputMatrix(Matrix m,int p,int l){
    for(int i=0;i<p;i++){
        std::cout<<"Baris ke - "<<i+1<<"\n";
        for(int j=0;j<l;j++){
            std::cout<<"\tKolom ke - "<<j+1<<":";
            std::cin>>m[i][j];
        
        }
        std::cout<<"\n";
    }

}

// Fungsi untuk print matriks
void printMatrix(Matrix m,int p,int l){
     for(int i=0;i<p;i++){
        std::cout<<"[ ";
        for(int j=0;j<l;j++){
            std::cout<<m[i][j]<<" ";    
        }
        std::cout<<"]\n";
    }

}

// Fungsi untuk print array(matriks nx1)
void printArray(int arr[],int p){
    for(int i=0;i<p;i++){
        std::cout<<"[" <<arr[i]<< "]"<<"\n";
    }
}

//Fungsi untuk proses perkalian matriks persegi
void mulMatPersegi(Matrix a,Matrix b,Matrix c,int d)
{
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            c[i][j] = 0;
            for (int k = 0; k < d; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
  
        } 
    }
}


// Fungsi untuk perkalian array(matriks nx1) dengan matriks nxn
void mulMatArr(Matrix a,int b[],int c[],int pa,int la){
    
        for (int i = 0; i < pa; i++) {
        c[i]=0;    
            for (int k = 0; k < pa; k++) {
                c[i] += a[i][k] * b[k];
            }
  
         
     }

    
}


// Fungsi untuk proses enkripsi hill cypher
std::string encrypt(std::string ptext,Matrix key,int p,int l){
    // variabel array untuk menempatkan string plaintext pada suatu matriks
    int b[100];

    // variabel untuk menyimpan hasil perkalian matriks key dengan matriks plaintext
    int c[100];

    // variabel untuk membentuk total stop sebagai banyak loop pembentukan matriks dari plain text dilakukan
    int stop;

    // String yang menyimpan hasil enkripsi
    std::string enc = "";
    // index untuk traversal string plaintext
    int si =0;

    // logika untuk menentukan jumlah stop (ganjil/genap)
    if(ptext.length()%p == 0)
        stop = ptext.length()/p;
    else
        stop = ptext.length()/p+1;
    
    //traversal
    for(int i=0;i<stop;i++){ 
        int j;
        for(int j=0;j<l;j++){
           // menempatkan tiap char string di suatu array
            b[j] = (int)(ptext[si]-'A');
            
            
            si++;
            
        }
        // mengalikan matriks key dengan b dan menempatkan di matriks c
        mulMatArr(key,b,c,p,l);       
        
        // membentuk string enkripsi berdasarkan matriks c
        for(int j=0;j<p;j++){
            
            enc= enc + (char)((c[j]%26)+'A');
            
        }
    }

    return enc;

}

// Fungsi untuk mencari kofaktor
void getCofactor(Matrix A, Matrix temp, int p, int q,
                 int n)
{
    int i = 0, j = 0;   
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
           
            if (row != p && col != q) {
                temp[i][j++] = A[row][col];
 
                
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
// Fungsi untuk mencari determinan
long int determinant(Matrix A, int n)
{
    int D = 0; 
    
    if(n==2){
        D = (A[0][0] * A[1][1]) - (A[0][1]*A[1][0]);
    }
   else{
    if (n == 1)
        return A[0][0];
 
    Matrix temp; 
 
    int sign = 1; 
 
    
    for (int f = 0; f < n; f++) {
        
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
 
      
        sign = -sign;
    }

    if(D<0){
        D = D * -1;
    }
   }
 
    return D;
}
 
// Fungsi untuk mencari adjoint
void adjoint(Matrix A, Matrix adj,int N)
{
    if (N == 1) {
        adj[0][0] = 1;
        return;
    }

    int sign = 1;
    Matrix temp;
 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            
            getCofactor(A, temp, i, j, N);
 
           
            sign = ((i + j) % 2 == 0) ? 1 : -1;
 
            
            adj[j][i] = (sign) * (determinant(temp, N - 1));
        }
    }
}
// Fungsi untuk melakukan operasi aritmatika op tiap elemen matriks dengan bilangan a. 
void MatrixOperation(Matrix m,int a,int p,int l,char op){
    for(int i=0;i<p;i++){
        for(int j=0;j<l;j++){
            switch (op)
            {
            case '+':
                m[i][j] = m[i][j] + a;
                break;
            case '*':
                m[i][j] = m[i][j] * a;
                break;
            case '%':
                if(m[i][j] < 0){
                 m[i][j] = (m[i][j] % a) + 26;

                }

                else{
                m[i][j] = m[i][j] % a;
                }
                break;
            
            default:
                break;
            }
        }

    }

}

// Fungsi untuk mendekripsi hill cypher
std::string decrypt(std::string ctext,Matrix key,int p,int l){
    // String untuk hasil dekripsi
    std::string dec = "";

    // src dibawah mencari invers Matrix key
    // variabel d yang menyimpan determinan dari kunci dan di mod 26
    long int d = determinant(key,p) % 26;
    
    // Apabila determinan negatif, maka ditambah 6(sesuai dengan ilmu matematika diskrit)
    if(d<0){
        d = d+26;
    }

    // Index i untuk mencari nilai x pada operasi (d * x) % 26 = 1
    int i = 1;

    // variabel b dan c dibawah memiliki fungsi sama di proseudur encrypt
    int b[100];
    int c[100];
    int si =0;

    // variabel matrix m untuk mencari adjoin
    Matrix m;

    // proses untuk mencari nilai x pada operasi (d * x) % 26 = 1
    adjoint(key,m,p);
    while((d*i)%26!=1){
        
        i++;
    }
    // melakukan operasi perkalian i dengan semua elemen di matriks
    MatrixOperation(m,i,p,l,'*');

    // melakukan operasi mod 26 dengan semua elemen di matriks
    MatrixOperation(m,26,p,l,'%');
    // akhir dari pencarian invers matrix key, disimpan pada variabel m

    
    // proses dibawah sama dengan function encrypt untuk melakukan perkalian dan pembentukan matriks dari plain text
    int stop;
     if(ctext.length()%p == 0)
        stop = ctext.length()/p;
    else
        stop = ctext.length()/p+1;
      for(int i=0;i<stop;i++){ 
        for(int j=0;j<l;j++){
            b[j] = (int)(ctext[si]-'A');
            si++;
            
        }
        mulMatArr(m,b,c,p,l);
       
        
        for(int j=0;j<p;j++){
            dec= dec + (char)((c[j]%26)+'A');
            
            
        }
    }

    return dec;
}

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
// fungsi untuk mencari kunci hill matriks jika diketahui cipher dan plain text saja
void getKeyMatrix(std::string ptext,std::string ctext,Matrix keyResult,int p,int l){
   Matrix cm,pm,pmi;
   int si = 0;

   // Menjadikan string tiap text menjadi bagian dari matrix
   for(int i=0;i<l;i++){
    for(int j=0;j<p;j++){
        cm[j][i] =(int)(ctext[si]-'A'); 
        pm[j][i] =(int)(ptext[si]-'A'); 
        si++;
    }
   }

    int d;
    si = 0;
    while(si<ptext.length()-1 && gcd(d,26)!=1){
    // Mencari invers matriks plaintext
    int temp = si;
        for(int i=0;i<l;i++){
            for(int j=0;j<p;j++){
                cm[j][i] =(int)(ctext[si]-'A'); 
                pm[j][i] =(int)(ptext[si]-'A'); 
                si++;
            }
        }
    printMatrix(pm,p,l);
    si = temp;
    si+=2;
    d = determinant(pm,p)%26;
        if(d<0){
        d = d+26;
        }
    std::cout<<"GCD"<<gcd(d,26)<<"\n";


   
    }    
  printMatrix(pm,p,l);
    int i = 1;

    adjoint(pm,pmi,p);
    
    while((d*i)%26!=1 ){
        
        i++;
        
    }
    MatrixOperation(pmi,i,p,l,'*');
    MatrixOperation(pmi,26,p,l,'%');


    //Proses perkalian invers matriks plaintext dengan matriks ciphertext
    mulMatPersegi(cm,pmi,keyResult,p);
    MatrixOperation(keyResult,26,p,l,'%');


}

int main(){
    std::string ptext;
    int p  ,l;

    std::cout<<"=== PLAIN TEXT ===\n";
    std::cout<<"Plain text : ";
    std::cin>>ptext;

    std::cout<<"=== KEY === \n";
    std::cout<<"Panjang Matriks : ";
    std::cin>>p;
    std::cout<<"Lebar Matriks : ";
    std::cin>>l;
    Matrix key,unk;


    std::cout<<"=== INPUT MATRIX ===\n";
    inputMatrix(key,p,l);



    if(p!=l || determinant(key,p)==0){
        std::cout<<"Matriks : \n";
        printMatrix(key,p,l);
        std::cout<<"Tidak dapat digunakan sebagai kunci karena : ";

        if(p!=l){
            std::cout<<"bukan matriks persegi ";
        }
        if(determinant(key,p)==0){
            std::cout<<"tidak memiliki invers ";

        }
        std::cout<<"\n";
    }

    std::string enc = encrypt(ptext,key,p,l);
    std::string dec = decrypt(enc,key,p,l);

    std::cout<<"Hasil Enkripsi = "<<enc<<"\n";
    std::cout<<"Hasil Dekripsi = "<<dec<<"\n";
   

    



}