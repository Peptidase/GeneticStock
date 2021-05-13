# GeneticStock
A stock trading bot that will simulate 52 weeks worth of generational learning to create a good portfolio /selection of equity.


## Fitness:
The fittness of this function is measured via the max returns,
This can be changed to utilize different metrics that take into account risk such as the Sharpe Ratio etc.

## Data
This uses the S&P500 set of stocks as specific "genes". The performance of the genes over the course of a week/year are able to show how well they perform. We can also backtest the portfolio's success against the next year to "test" the performance.

## Libraries
This utilizes the custom written library for fetching yahoo Finance Data.
