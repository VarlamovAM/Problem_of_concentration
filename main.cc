#include <iostream>
#include <fstream>
#include <iomanip>



int const Size = 11;
int const Polynom_power = Size - 1;



struct Acid_data{
    double rho[100];
    double concentration[100];

};


struct Solution_data{
    double Start_solution_V;
    double Start_solution_C;
    double Final_solution_V;
    double Final_solution_C;
    double Buffer_solution_V;
    double Buffer_solution_C;
    bool Incorrect_input = true;
};


void Print_Matrix(double* A, double* B){

    int i = 0;
    int j = 0;

    for(i >= 0; i < Size; i++){
        for (j >= 0; j < Size; j++){
              std::cout << "\t" << std::setprecision(3) << *(A + i * Size + j );
        }
        std::cout << "      " << *(B + i);
        j = 0;
        std::cout << "\n";
    }

    i = 0;
    j = 0;

    return;
}


void Matrix_string_convertation(double* A, double* B, int pos_base_string, int pos_chaning_string){

    while(true){
        if (*(A + (pos_chaning_string - 1)  * Size + (pos_base_string - 1)) == 0){
            std::cout << "Warning: some diagonal elements equal to 0!" << "\n";
            break;
        } else {
            double tmp = *(A + (pos_chaning_string - 1)  * Size + (pos_base_string - 1));
            int k = 0;

            *(B + (pos_chaning_string - 1)) = (*(B + (pos_chaning_string - 1)))/(tmp);

            for(k >= (pos_base_string - 1); k <Size; k++){
                *(A + (pos_chaning_string - 1)  * Size + k) = (*(A + (pos_chaning_string - 1)  * Size + k))/(tmp);
            }
            k = 0;
        }
        break;
    }
    return;
}


void Matrix_convertation(double* A, double* B){

    int pos_base_string = 1;
    int pos_change_string = 1;

    for (pos_base_string >= 1; pos_base_string <= Size; pos_base_string++){
        for (pos_change_string >= pos_base_string; pos_change_string <=Size; pos_change_string++){
            Matrix_string_convertation(A, B, pos_base_string, pos_change_string);
        }
        pos_change_string = pos_base_string + 1;
        for (pos_change_string > pos_base_string; pos_change_string <= Size; pos_change_string++){
            int k = pos_base_string - 1;
            for (k >= pos_base_string; k < Size; k++){
                *(A + (pos_change_string - 1)  * Size + k) = *(A + (pos_change_string - 1)  * Size + k) - *(A + (pos_base_string - 1)  * Size + k);
            }
            *(B + (pos_change_string - 1)) = *(B + (pos_change_string - 1)) - *(B + (pos_base_string - 1));
            k = pos_base_string;
        }
        pos_change_string = pos_base_string + 1;
    }

    return;
}


double Power(double x, int pow){

    double results = 1;
    int i = 1;

    while (i <= pow){
        results = results * x;
        i++;
    }
    i = 1;


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

    std::ifstream in("C:\Sulfur_acid.txt");
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

    in.close();

    return Sulfur_acid_data;
};


void Matrix_maker(double* A, double* B, struct Acid_data Sulfur_acid_data){


    int i = 0;
    int j = 0;

    for (i >= 0; i < Size; i++){
        for (j >= 0; j < Size; j++){
            double *c = new double[80];
            int k = 0;
            for (k >= 0; k < 80; k++){
                *(c + k) = Power((Sulfur_acid_data.concentration[k]/Sulfur_acid_data.rho[k]), i + j);
            }
            *(A + i * Size + j) = Summ(c, 80);
            delete [] c;
        }
        int k = 0;
        double* d = new double[80];
        for (k >= 0; k < 80; k++){
            *(d + k) = Power((Sulfur_acid_data.concentration[k]/Sulfur_acid_data.rho[k]), i) * Sulfur_acid_data.concentration[k];
        }
        *(B + i) = Summ(d, 80);
        delete [] d;
        j = 0;
    }

    return;
}


double Get_elements(double* A, double* B, int k, bool* F){

    if ((k == Polynom_power) ||
        (*(F + k))){
        *(B + k) = *(B + k);
    } else {
        int n = Polynom_power;
        int p = 0;
        while((n > k)            &&
            (n <= Polynom_power)){
                *(B + k) = *(B + k) - *(A + (k) * Size + n) * Get_elements(A, B, n, F);
                n--;
            }
        n = Polynom_power;
    }
    *(F + k) = true;

    return *(B + k);
}


struct Solution_data Get_Solution_from_input(){
    struct Solution_data Solution;

    while (Solution.Incorrect_input){
        std::cout << "Enter start solution Value and concentration: " << "\n";
        std::cout << "V = ";
        std::cin >> Solution.Start_solution_V;
        std::cout << "\n" << "C = ";
        std::cin >> Solution.Start_solution_C;
        std::cout << "Enter final solution Value and concentration: " << "\n";
        std::cout << "V = ";
        std::cin >> Solution.Final_solution_V;
        std::cout << "\n" << "C = ";
        std::cin >> Solution.Final_solution_C;
        Solution.Incorrect_input = false;
    }

    return Solution;
};


int main(){
	/* Main function of project. in this function we will count parametrs
	 * of solution from inputs data from user.
	 * In input we will get starts solution param. and final solution param.
	 * In output we will write param. of buffer solution*/

    double A[Size][Size];
    double B[Size];
    bool F[Size];


    int i = 0;
    int j = 0;


    for (i >= 0; i < Size; i++){
        *(F + i) = false;
    }


    struct Acid_data Sulfur_acid_data = Get_data();


    for (i >= 0; i < 16; i++){
        if (*(&A[0][0] + i) == -0.){
            *(&A[0][0] + i) = 0;
        } else {
            continue;
        }
    }
    i = 0;


    Matrix_maker(&(A[0][0]), B, Sulfur_acid_data);
    Matrix_convertation(&A[0][0], B);


    double y = Get_elements(&A[0][0], B, i, F);
    std::cout << "\n";

    for (i >= 0; i < Size; i++){
        std::cout  << "\t" << "B[" << i << "] " << B[i];
    }



	return 0;
}
