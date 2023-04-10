#include <iostream>
#include <vector> 
#include <cassert>
#include <fstream>
#include <string>


namespace cwt
{

    double randon_weight() 
    { 
        return rand() / double(RAND_MAX); 
    }
    double transfer_function(const double x)
    {
        // tanh = ouput range [-1.0 .. 1.0]
        // this represents hyperbolic function
        return tanh(x);
    }
    double transfer_function_derivative(const double x)
    {
        // tanh derivative approximation: 1-x^2
        return  1.0 - x*x;
    }


    struct connection
    {
        double weight;
        double delta;
    };

    class neuron 
    { 
        using layer = std::vector<neuron>;

        public: 
            neuron(const std::size_t outputs_count, const std::size_t index) : m_index(index) 
            {
                for (std::size_t i = 0 ; i < outputs_count ; ++i)
                {
                    m_output_weights.push_back(connection{});
                    m_output_weights.back().weight = randon_weight();
                }
            }
            void feed_forward(const layer& prev_layer)
            {
                double sum = 0.0;
                // sum the prev layers outputs (which are inptus)
                // inclucde the bias node from the prev layer
                for (const auto& v : prev_layer) {
                    sum += v.output_value() * v.m_output_weights[m_index].weight;
                }
                m_output_value = transfer_function(sum);
            }
            double sum_dow(const layer& next_layer) const
            {
                double sum = 0.0;
                // sum our contributions of the errors at the nodes we feed
                for (std::size_t n = 0 ; n < next_layer.size() - 1 ; ++n) {
                    sum += m_output_weights[n].weight * next_layer[n].m_gradient;
                }
                return sum;
            }
            void calculate_hidden_gradients(const layer& next_layer)
            {
                double dow = sum_dow(next_layer);
                m_gradient = dow * transfer_function_derivative(m_output_value);
            }
            void calculate_output_gradients(const double target_value)
            {
                double delta = target_value - m_output_value;
                m_gradient = delta * transfer_function_derivative(m_output_value);
            }
            // this modifies the previous layer!!!
            void update_input_weights(layer& prev_layer)
            {
                // updates the weights in the connection container of the prev layer
                for (auto& prev : prev_layer)
                {
                    // this represents the connection from the prev layers neuron to this neuron
                    double old_delta = prev.m_output_weights[m_index].delta;
                    double new_delta = 
                        // indvidual input, magnified by the gradient and train rate:
                        m_eta // eta represetns the training rate
                        * prev.output_value() // Watchout -> this refers to the prev. layers neuron!!!!
                        * m_gradient
                        // also add momentum alpha 
                        + m_alpha 
                        * old_delta;
                    // eta overall net learning: 0.0 = slow learner, 0.2 = medium learner, 1.0 = reckless learner
                    // alpha momentum: 0.0 = no momentum, 0.5 = moderate momentum

                    prev.m_output_weights[m_index].delta = new_delta;
                    prev.m_output_weights[m_index].weight += new_delta;
                }
            }
            double output_value() const { return m_output_value; }
            void set_output_value(const double value) { m_output_value = value; }
        private:
            std::size_t m_index;
            double m_output_value;
            double m_gradient;
            std::vector<connection> m_output_weights;
            double m_eta{0.15}; // [0.0..1.0]
            double m_alpha{0.5}; // [0.0..1.0]
    };

    class neural_net
    {
        public: 
            neural_net(const std::vector<unsigned int>& topology)
            {
                std::size_t layers_count = topology.size();
                for (std::size_t layer_num = 0 ; layer_num < layers_count ; ++layer_num)
                {
                    std::cout << "adding a layer with " << topology[layer_num] << " neurons " << std::endl;
                    m_layers.push_back(layer());
                    std::size_t outputs_count = layer_num == layers_count - 1 ? 0 : topology[layer_num+1];
                    // -------------------------------------vvvvv lessorequal adds the bias
                    for (std::size_t neuron_num = 0 ; neuron_num <= topology[layer_num] ; ++neuron_num)
                    {
                        // add neurons to the last added one from first line in this constructor
                        m_layers.back().push_back(neuron(outputs_count, neuron_num));
                        std::cout << "added neuron to layer " << layer_num << std::endl;
                    }

                    // force the bias to 1.0
                    m_layers.back().back().set_output_value(1.0);
                }
            }
            void feed_forward(const std::vector<double>& input)
            {
                assert(input.size() == m_layers[0].size()-1);

                // assign the input values of layers[0]
                for (std::size_t i = 0 ; i < input.size() ; ++i)
                {
                    m_layers[0][i].set_output_value(input[i]);
                }

                for (std::size_t layer_num = 1 ; layer_num < m_layers.size() ; ++layer_num) {
                    layer& prev_layer = m_layers[layer_num-1];
                    // -------------------------------------------------------------------vvvvvvvv minus 1
                    for (std::size_t neuron_num = 0 ; neuron_num < m_layers[layer_num].size()-1 ; ++neuron_num) {
                        // feeds the value from the neuron input to output and does the actual math here 
                        m_layers[layer_num][neuron_num].feed_forward(prev_layer);
                    }
                }
            }
            void back_prop(const std::vector<double>& target_values)
            {
                // back propagation steps to train the neural network: 
                // 1. calculate overall net errror (root mean square error of output neurons errors)
                layer& output_layer = m_layers.back();
                std::size_t error = 0.0;

                for (std::size_t n = 0 ; n < output_layer.size()-1 ; ++n) {
                    // sum up the error
                    double delta = target_values[n] - output_layer[n].output_value();
                    error += delta*delta;
                }
                error /= output_layer.size()-1; // get averager error squared
                error = sqrt(error); // this is the actual rms

                m_recent_average_error = 
                    (m_recent_average_error * m_smooth_factor + error)
                    / (m_smooth_factor + 1.0);
                
                // 2. calculate output layer gradients
                for (std::size_t n = 0 ; n < output_layer.size() - 1 ; ++n ) {
                    output_layer[n].calculate_output_gradients(target_values[n]);
                }

                // 3. calculate gradients on hidden layers
                // minus 2 represents the first hidden layer 
                // size is greater than the vector, minus 1 is the output values of the net
                for (std::size_t layer_num = m_layers.size() - 2 ; layer_num > 0 ; --layer_num)
                {
                    layer& hidden_layer = m_layers[layer_num];
                    layer& next_layer = m_layers[layer_num+1];
                    for (std::size_t n  = 0; n < hidden_layer.size() ; ++n){
                        hidden_layer[n].calculate_hidden_gradients(next_layer);
                    }
                }

                // for all layers from outputs to first hidden layer
                // update connection weights
                for (std::size_t layer_num = m_layers.size() - 1 ; layer_num > 0 ; --layer_num)
                {
                    layer& current_layer = m_layers[layer_num];
                    layer& prev_layer = m_layers[layer_num-1];
                    for (std::size_t n = 0 ; n < current_layer.size() - 1 ; ++n){
                        current_layer[n].update_input_weights(prev_layer);
                    }
                }
            }
            std::vector<double> get_result() const
            {
                std::vector<double> result_values;
                for (std::size_t n = 0 ; n < m_layers.back().size() - 1 ; ++n)
                {
                    result_values.push_back(m_layers.back()[n].output_value());
                }
                return result_values;
            }
            double recent_average_error() const { return m_recent_average_error; }
        private:
            using layer = std::vector<neuron>;
            std::vector<layer> m_layers;
            double m_recent_average_error{0.0};
            double m_smooth_factor{100.0};
    };

} // namespace cwt