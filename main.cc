#include <iostream>



int const Size = 100;



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

int main(){
	/* Main function of project. in this function we will count parametrs
	 * of solution from inputs data from user.
	 * In input we will get starts solution param. and final solution param.
	 * In output we will write param. of buffer solution*/

    float A[Size][Size];

    int i = 0;
    int j = 0;

    for(i >= 0; i < Size; i++){
        for (j >= 0; j < Size; j++){
            A[i][j] = Size * i + j + 1;
        }
        j = 0;
    }


    i = 0;
    j = 0;

    Matrix_convertation(&A[0][0], i, j);
    std::cout << "final";



	return 0;
}
