#include <stdio.h> 

typedef struct {
  Neuron* from; 
  Neuron* to; 
  double weight; 
}Connection; 

typedef struct{
  double bias ; 
}Neuron;

typdef Connection* Layer; 

typedef struct{
  int* dimensions; 
}Network; 

void backPropagate(){
  // calculate the error 
  //  change in weight = lr * error term * output
  //    error term : 
  //      if in last layer : error rate = output(1-output)(target - output)
  //      if in hidden layer : error rate = output (1-output)  (weight * (next error rate))
}

void forwardPropagate(){
  // take input and feed through network
  //    for every layer : 
  //      multiply by layer 
  //      input to nonlinearity
}

Network createNetwork(int* dimensions){
  // create neurons 
  for (int i = 0; i < sizeof(*dimensions) ; i++){
    for (int j = 0; j < dimensions[i] ; j++){

    }
  }

  // create connections 
  
  //create layers  
  
}


int int main(int argc, char *argv[]){
  // Get epochs from user 
  int epochs = argv[1];

  // Get dimensions from user 
  int dimensions[argc-2]; 
  for (int i = 0; i < argc ; i++){
    dimensions[i] = *argv[i+1]; 
  }

  // create a network
  Network* net = createNetwork(dimensions); 

  for (int i = 0 ; i < epochs ; i++){
    // forward propagate
    output = forwardPropagate(); 

    // back propagate
    backPropagate(output); 
  }
}
