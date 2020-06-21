#include <iostream>
#include <fstream>



int const Size = 100;


struct Acid_data{
    double rho[100];
    double concentration[100];

};


void Print_Matrix(float* A){

    int i = 0;
    int j = 0;

    for(i >= 0; i < Size; i++){
        for (j >= 0; j < Size; j++){
              std::cout << "\t" << *(A + i * Size + j );
        }
        j = 0;
        std::cout << "\n";
    }

    i = 0;
    j = 0;

    return;
}


void Matrix_string_convertation(float* A, int pos_base_string, int pos_chaning_string){


    while(true){
        float delta;

        if (*(A + Size * (pos_chaning_string - 1) + pos_base_string - 1) == 0){
            break;
        } else {
            delta = (*(A + Size * (pos_chaning_string - 1) + pos_base_string - 1))/(*(A + Size * (pos_base_string - 1) + pos_base_string - 1));

            int k = 0;
            int first_pos = pos_base_string - 1;

                for (k >=first_pos; k < Size; k++){
                    *(A + Size * (pos_chaning_string - 1) + k) = *(A + Size * (pos_chaning_string - 1) + k) - *(A + Size * (pos_base_string - 1) + k) * delta;
                }
            k = first_pos;
        }
    }

    return;
}


void Matrix_convertation(float* A, int i, int j){


    int base_string = 1;
    int changed_string = 2;

    for (base_string >= 1; base_string < Size; base_string ++){
        for (changed_string > base_string; changed_string <= Size; changed_string++){
            Matrix_string_convertation(A, base_string, changed_string);
        }
        changed_string = base_string + 2;
    }






    return;
}


double Power(double x, int pow){

    double results = x;
    int i = 2;

    while (i <= pow){
        results = results * x;
        i++;
    }
    i = 2;


    return results;
}


double Summ(double* A, int number_of_terms){

    double results = 0;
    int i = 0;


    while(i <= number_of_terms){
        results += *(A + i);
        i++;
    }

    return results;
}


struct Acid_data Get_data(){

    struct Acid_data Sulfur_acid_data;


    int N = 0;
    int h = 0;

    std::string line;

    std::ifstream in("C:\Sulfur_acid.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        in >> N;


        for ( h >= 0; h < N; h++){
            double a = 0.;
            double b = 0.;
            in  >> a >> b;
            Sulfur_acid_data.rho[h] = a;
            Sulfur_acid_data.concentration[h] = b;

        }

        h = 0;

    }

    in.close();     // закрываем файл


    return Sulfur_acid_data;
};


void Matrix_maker(double* A, struct Acid_data Sulfur_acid_data){

    std::cout <<"Test"<<"\n";

    return;
}


int main(){
	/* Main function of project. in this function we will count parametrs
	 * of solution from inputs data from user.
	 * In input we will get starts solution param. and final solution param.
	 * In output we will write param. of buffer solution*/

    double A[Size][Size];

    struct Acid_data Sulfur_acid_data = Get_data();

    Matrix_maker(&(A[0][0]), Sulfur_acid_data);
    std::cout << Sulfur_acid_data.concentration[80];


	return 0;
}
