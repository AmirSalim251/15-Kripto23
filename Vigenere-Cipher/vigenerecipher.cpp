/*
Nama : Amir Salim
NPM : 140810210015
Kelas :  A
Deskripsi program : Program Viginere Cipher

*/
#include<iostream>

std::string encrypt(std::string ptext,std::string key){
    std::string hasil = "";
    int in = 0;
    
    for(int i=0;i<ptext.length();i++){    
        hasil += char(int(((ptext[i]-65) + (key[in]-65)) % 26) + 65);
    
   
        if(in<key.length()-1){
            in++;
        }
        else{
            in=0;
        }
    }

    return hasil;

}

std::string decrypt(std::string ctext,std::string key){
    std::string hasil = "";
    int in = 0;
    
    for(int i=0;i<ctext.length();i++){    
        int cek = int(((ctext[i]-65) - (key[in]-65)) % 26);
        if(cek<0){
            cek = 26 + cek;
        }
        hasil += char(cek + 65);
    
   
        if(in<key.length()-1){
            in++;
        }
        else{
            in=0;
        }
    }

    return hasil;

}

int main(int argc, char const *argv[])
{
    std::string ptext,key,enc,dec;
    std::cout<<"=== VIGINERE CIPHER ===\n";
    std::cout<<"Plain Text : ";
    std::cin>>ptext;
    std::cout<<"Key : ";
    std::cin>>key;

    enc = encrypt(ptext,key);
    dec = decrypt(enc,key);

    std::cout<<"\n=== HASIL ===\n";
    std::cout<<"Enkripsi : "<<enc<<"\n";
    std::cout<<"Dekripsi : "<<dec<<"\n";



    return 0;
}
