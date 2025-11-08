# System Software mini project
A multithreaded client–server bank management system with a TUI client built using ncurses and secure password handling via libbcrypt.

### Setup:
```bash
./install_packages.sh    # install dependencies  
./run_server.sh          # start the server  
./run_client.sh          # start the client  
```

## Features
the following user phases are supported:  
- Admin
    - Create, view, modify, and delete users
- Manager
    - Activate/deactivate customer accounts
    - Assign loan applications to employees
    - Review customer feedback
- Employee
    - Add or update customer info (update currently unstable)
    - Review assigned loans
    - View customer transactions
- Customer
    - View balance and transaction history
    - Deposit, withdraw, and transfer money
    - Apply for loans and view applications
    - Submit feedback

All users can change their password as well.


## Architecture & Flow
- the models store the structure of data used throughout the project
- the controllers directly interact with the database files, using locking to ensure the files are not modified unexpectedly
- the server births a new thread for each incoming connection
- the client must login using credentials which are verified by the worker thread using functions provided by 
the [user controller](https://github.com/ImSonu2030/System-Software/blob/main/controller/user.h)
- if the same user logs in from a different terminal, the previous thread with for that user account is cancelled
- once authenticated, the server responds with the role of the user
- the client shows the menu corresponding to the role of the logged-in user
- subsequent requests are serviced as they arrive and the response is sent by the worker thread through the socket
- for special kinds of request where the size of the response is not pre-known, the data is buffered into the socket 
the number of objects to be read from the socket is sent in the response under the `bufcount` variable
- the types of requests and their required data can be seen in [request.h](https://github.com/ImSonu2030/System-Software/blob/main/model/request.h)
- unions are used in the Request and Response structs to store the required data before being sent

### Known issues
- updating customer info from employee phase causes crash

### class diagram
![class_diagram.png](https://github.com/ImSonu2030/System-Software/blob/main/class_diagram.png)
