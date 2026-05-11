#include <stdio.h> 

typedef enum {
  STANDARD_DOT_PRODUCT, 
  NON_EUCLIDEAN_DOT_PRODUCT, 
}InnerProducts ; 

typedef enum {
  RELU, 
  SIGMOID,
}Activations; 

typedef struct {
	char* name ;  
	int* dimension;
  int layers; 
  Activations activation; 
}Network; 

typedef struct {
  int bias; 
  int* connections;
  Activations activation; 
}Neuron;

typedef struct {
  InnerProducts innerProduct; 
  float weight;  
  int* from;
  int* to;
}Connection;

typedef struct {
  float guess;
  float error;  
}Results;

typedef struct {
  int* input;  
}Input;

int multiply(int weight, int input){
  return weight * intput ; 
}

int activate(int in){
  if (in > 0.5){
    return 1; 
  }else {
    return 0; 
  }
}

void feedForward(Network *net , Input *in){
  if (sizeof(*in.input) < *net.dimension[0]){
    exit(EXIT_FAILUR); 
  }
  
  for (int i = 0 ; i < layers ; i++){
    for (int j = 0 ; j < net.dimensions[i] ; j++){
        if (i = 0){
          weight = *net.
          multiplied = multiply(weight, in); 
          out = activate(multiplied); 
        }


    }
  }


}

// delta = target - output
// gradient = delta * outputTransferFunciton derivative
void calcOutputGrad(){}

// sum through the weights in next layer multiplied by their gradient 
void calcDOW(Layer nextLayer){}

// dow = 
// gradient = delta * outputTransferFunciton
void calcHiddenGrad(){}

void backprop(){
  // calculate output gradients
  
  // calculate the hidden layer gradients 
  
  // update neuron weights 
}

void getResults(){

}

void createNetwork(Network *net){
  // For each layer in the neural network add neurons
  for (int i = 0; i < net.layers; i++){
    for (int j = 0 ; j < net.dimension[i]; j++){
      // create neuron 
      Neuron* ner =  malloc(sizeof(Neuron));
      
      ner->bias = rand ; 
      ner->activation = net.activation; 
     // create connections
      Connection connections[net.dimensions[j+1]] ; 
      if (i < net.layers-1){ // dont create any connection for the last layer 
          for (int k = 0; k < net.dimension[j+1]; k++){ 
            connections[k].innerProduct = innerProducts.STANDARD_DOT_PRODUCT, 
            connections[k].weight = rand, 
            connections[k].from = &ner, 
            connections[k].to = &ner + net.dimensions[j+1],  // to neuron should be that far away
          }  
        }
      }
      ner->connections = connections ;  // update connection
    }
  }
}

int main(void){

	// enter neural network dimensions 
  int dimensions[] = {2, 3, 4, 5}; 
  
	// create a neural network using dimensions 
	Network net = {
		.name = "first net", 
    .dimension = dimensions, 
    .layers = 4
	};

  // 10 epochs 
  for (int i = 0 ; i < 10 ; i++){
    int results = net.feedForward(); 
    net.backprop(results); 
  }


  int results [] = net.getResults(); 
  printf("%s\n");

}
