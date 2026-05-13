#include <stdio.h> 
#include <stdlib.h>
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

float nonlinearity(float input){
  if (input < 0.5){
    return 1.0; 
  }else {
    return -1.0; 
  }
}

void backPropagate(Network* net, float lr, float output, float expected){
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
        float error_term =  output * (1-output) * (expected-output); 
        next_error = error_term;  
        connection.weight = connection.weight - (lr * error_term * output); 
      }else {
        float error_term = output * (1-output) * (connection.weight * next_error); 
        next_error = error_term;
        connection.weight = connection.weight - (lr * error_term * output); 

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



void forwardPropagate(Network* net){
  // take input and feed through network
  //    for every layer : 
  //      multiply by layer 
  //      input to nonlinearity
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
    }
  } 
}

int getNumberOfConnection(int* dimensions){
  int total = 0; 
  for (int i = 0 ; i < sizeof(dimensions)-1; i++){
    total += dimensions[i] * dimensions[i+1]; 
  }
  return total; 
}

Network* createNetwork(int* dimensions){
  
  Network net;
  net.dimensions = dimensions;

  int numberOfNeurons = 0; 
  for (int i = 0; i < sizeof(dimensions) ; i++){
    numberOfNeurons += dimensions[i]; 
  }

  // create neurons 
  Neuron* neurons[numberOfNeurons]; 
  for (int i = 0; i < sizeof(*dimensions) ; i++){
    for (int j = 0; j < dimensions[i] ; j++){
      if (i == 0){
        if (j == 0){
          Neuron neuron = {
            .outValue = input1  
          }
        }else if (j==1) {
          Neuron neuron = {
            .outValue =  input2
          }
        }
      }else {
        Neuron neuron; 
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
  int input1 = atoi(argv[2]); 
  int input2 = atoi(argv[3]); 

  // Get dimensions from user 
  int dimensions[argc-4]; 
  for (int i = 0; i < argc ; i++){
    dimensions[i] = *argv[i+1]; 
  }

  // create a network
  Network* net = createNetwork(dimensions, input1, input2); 
  
  float output; 
  for (int i = 0 ; i < epochs ; i++){
    // forward propagate
    output = forwardPropagate(net, input); 

    // back propagate
    backPropagate(output); 
  }

  output =  forwardPropagate(net, input); 

  printf("%d \n" , output);
}
