#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define EULER_NUMBER_F 2.7182818284

typedef struct{
  float outputValue; 
}Neuron;

typedef struct {
  Neuron* from; 
  Neuron* to; 
  float weight; 
}Connection; 

typedef Connection* Layer; 

typedef struct{
  int* dimensions;
  Layer* layers; 
}Network; 

float nonlinearity(float n) {
    return (1 / (1 + powf(EULER_NUMBER_F, -n )));
}

void backPropagate(Network* net, float lr, float* output, float expected){
  // calculate the error 
  //  change in weight = lr * error term * output
  //    error term : 
  //      if in last layer : error term = output(1-output)(target - output)
  //      if in hidden layer : error term = output (1-output)  (weight * (next error rate))

  Network thisNet = *net; 
  for (int i = sizeof(thisNet.layers); i > 0; i--){ // itterate through layers
    float next_error; 
    for (int j = 0 ; j < sizeof(thisNet.layers[i]); j++){
      Connection connection = *(thisNet.layers[i]); 
      if (i == sizeof(thisNet.layers)){
        float error_term =  output[j] * (1-output[j]) * (expected-output[j]); 
        next_error = error_term;  
        connection.weight = connection.weight - (lr * error_term * output[j]); 
      }else {
        float error_term = output[j] * (1-output[j]) * (connection.weight * next_error); 
        next_error = error_term;
        connection.weight = connection.weight - (lr * error_term * output[j]); 

      }
    }
  }

}

// multiplies layer by value
float mat_mul(float value, Layer* layer){
  for(int i = 0; i < sizeof(layer); i++){
    Connection connection = *layer[i]; 
    float weight = connection.weight; 
    value = value * weight; 
  }
  return value; 
}

/*
 *  Net -> 
 *        layers ['', '', '', '']
 *                |
 *                |
 *                v
 *    connections ['', -> connection.to =  neuron
 *                 '',
 *                 '']
 *
 * */
float* forwardPropagate(Network* net){
  // take input and feed through network
  //    for every layer : 
  //      multiply by layer 
  //      input to nonlinearity
  float* output = malloc(sizeof(float) * net->dimensions[sizeof(net->dimensions)-1]); 
  for (int i = 0 ; i < sizeof(net->dimensions); i++){ // iterate through layers
    for (int j = 1; j < net->dimensions[j] - 1; j++) {  // every layer needs to be multiplied with every neurons outputValue 
      Layer* layers = net->layers; 
      Connection* layer = layers[i];
     // Connection neuronFulConnection = layer[(net->dimensions[j-1]) * j]; // the layer index should be multiplied by the layer height to keep unique neurons
      
      Connection* neuronFulConnection = &layer[j]; // the layer index should be multiplied by the layer height to keep unique neurons
      Neuron thisNeuron = *neuronFulConnection->from ;
      float outValue = thisNeuron.outputValue; 
      // get weight for layer 
      Neuron nextNeuron = *neuronFulConnection->to; 
      nextNeuron.outputValue = nonlinearity(mat_mul(outValue, &layer)); 
      
      if (i == sizeof(net->dimensions)) {
        output[j] = nextNeuron.outputValue; 
      }
    }
  } 
  return output; 
}

int getNumberOfConnection(int* dimensions){
  int total = 0; 
  for (int i = 0 ; i < sizeof(dimensions)-1; i++){
    total += dimensions[i] * dimensions[i+1]; 
  }
  return total; 
}

Network* createNetwork(int* dimensions, int input1, int input2){
  
  Network net;
  net.dimensions = dimensions;
  printf("dim = %d\n", sizeof(dimensions)/sizeof(int));
  int numberOfNeurons = 0; 
  for (int i = 0; i < sizeof(dimensions) ; i++){
    numberOfNeurons += dimensions[i]; 
  }

  // create neurons 
  Neuron* neurons[numberOfNeurons]; 
  Neuron neuron; 
  for (int i = 0; i < sizeof(*dimensions) ; i++){
    for (int j = 0; j < dimensions[i] ; j++){
      if (i == 0){
        if (j == 0){
          neuron.outputValue = input1;   
        }else if (j==1) {
          neuron.outputValue =  input2; 
        }
      }
      neurons[i+j] = &neuron; 
    }
  }

  // create connections 
  Connection* connections[getNumberOfConnection(dimensions)]; 
  for (int i = 0; i < sizeof(*dimensions)-1 ; i++){
    for (int j = 0; j < dimensions[i]; j++){
      Connection con = {
        .from = neurons[i], 
        .to = neurons[i+dimensions[i]],
        .weight = rand(),
      };
      connections[i+j] = &con; 
    }
  }

  //create layers   
  Layer* layers[sizeof(*dimensions)-1]; 
  for(int i = 0 ; i < sizeof(*dimensions) - 1; i++){
    int startidx = dimensions[i]; 
    int length = dimensions[i+1]; 
    Layer layer = malloc(sizeof(Layer));

    for (int j = 0 ; j < length; j++){  // get permutations of length dimension + 1 
      layer[j] = *connections[startidx+j]; 
    }
  }

  net.layers = layers; 

  return &net; 
}


int main(int argc, char *argv[]){
  // Get epochs from user 
  int epochs = atoi(argv[1]);
  printf("epochs = %d\n", epochs);
  float lr = atof(argv[2]);
  printf("lr = %d\n", lr);
  int input1 = atoi(argv[3]); 
  printf("input1 = %d\n", input1);
  int input2 = atoi(argv[4]); 
  printf("input2 = %d\n", input2);
  
  // Get dimensions from user 
  int* dimensions = malloc(sizeof(int) * (argc-4));; 
  for (int i = 0; i < argc-1 ; i++){
    dimensions[i] = *argv[i+1]; 
  }

  float expected = 1.0; 
  // create a network
  Network* net = createNetwork(dimensions, input1, input2); 
  printf("here\n");
  float* output; // pointer to array of outputs 
  for (int i = 0 ; i < epochs ; i++){
    // forward propagate
    output = forwardPropagate(net); 

    // back propagate
    backPropagate(net, lr, output, expected); 
  }

  output =  forwardPropagate(net); 

  printf("%d \n" , output);
}
