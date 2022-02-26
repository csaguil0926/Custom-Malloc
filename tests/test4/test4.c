#include <stdio.h>
#include <stdlib.h>

//same as test 1 but expect seg fault error because trying to access something you already freed

int main(){
    
    printf("Enter number of items:"); 

    int n;
    scanf("%d", &n); 

    printf("Number of elements: %d\n", n);
    
    int* array = (int*)malloc(n*sizeof(int)); 
    
    for (int i = 0; i<n; i++){
        array[i]=i+1;
    }

    free(array);

    printf("Array: {");
    for (int i = 0; i<n; i++){
        
        if(i==n-1){
           printf("%d", array[i]);
        }else{
           printf("%d, ", array[i]);
        }
    }
    printf("}\n");
    
    return 0;

}