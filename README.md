# Coffee Shop Simulation

In Coffee Shop Simulation, two different models are used to compare overall efficiency and customer satisfaction. Each model has N cashiers and N/3 baristas. 
For the first model,  there is one queue for cashiers and one queue for baristas. For the second model, there is one queue for cashiers, and N/3 queues for baristas. Orders from the first three cashiers are directed to the initial barista, while the following trio of cashiers send their orders to the second barista, continuing this pattern.
In the cashier queue, orders are processed on a first-come-first-served basis, while in the barista queue, priority is given to serving the most expensive coffee first. This structure applies consistently to both models.
Through simulation of these models, we obtain the following statistics:
1. Overall system running time
2. Utilization rates for both cashiers and baristas
3. Turnaround times for individual orders
4. Maximum queue lengths for each station
