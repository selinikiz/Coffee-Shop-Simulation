# Coffee Shop Simulation

In Coffee Shop Simulation, two different models are used to compare overall efficiency and customer satisfaction. Each model has N cashiers and N/3 baristas. 

For the first model, there is one queue for cashiers and one queue for baristas. 

<img width="821" alt="model1" src="https://github.com/selinikiz/Coffee-Shop-Simulation/assets/134490814/62584328-b0c5-450d-b9f1-17b72c91ed16">

For the second model, there is one queue for cashiers, and N/3 queues for baristas. Orders from the first three cashiers are directed to the initial barista, while the following trio of cashiers send their orders to the second barista, continuing this pattern. 

<img width="708" alt="model2" src="https://github.com/selinikiz/Coffee-Shop-Simulation/assets/134490814/2168ae5a-6c6d-4406-b046-b9cc068a8dbc">


In the cashier queue, orders are processed on a first-come-first-served basis, while in the barista queue, priority is given to serving the most expensive coffee first. This structure applies consistently to both models. 

Through simulation of these models, we obtain the following statistics:

1. Overall system running time
2. Utilization rates for both cashiers and baristas
3. Turnaround times for individual orders
4. Maximum queue lengths for each station

## Input/Output File Format

The input file follows this format:

1. The first line indicates the number of cashiers (N).
2. The second line indicates the total number of orders (X).
3. Subsequent X lines contain order information, with each line comprising four variables separated by spaces:
  - Arrival Time: Time when the customer enters the coffee shop (in seconds)
  - Order Time: Time required to place the coffee order (in seconds)
  - Brew Time: Time required to prepare the coffee (in seconds)
  - Price of Order: Cost of the coffee.

The output file follows this format:

1. The first line denotes the total running time of the coffee shop (in seconds).
2. The subsequent line indicates the maximum length of the cashier queue.
3. If the coffee shop has one barista queue, the next line represents the maximum length of this queue. If the coffee shop has N/3 barista queues, the next N/3 lines detail the maximum lengths of each barista queue.
4. The following N lines present the utilization of the cashiers.
5. The subsequent N/3 lines present the utilization of the baristas.
6. Finally, the next X lines display the turnaround times of orders.

## Execution

```
make
./CoffeeShopSimulation input.txt output.txt
```





