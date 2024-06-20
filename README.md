## Problem Statement:

A multi-user Electricity bill generating system that automates the electricity bill of
customers.

## Detail Description of the classes:

This is a multi-user system that automates the Electricity Bill of customers. The
system is controlled and used by three people divided as three modules, Admin,
Employee and User. All three have to register to the system in order to use it.
They have to login using correct credentials and access their account.

Admin will control the entire system.He recruits the employees, suspends the
employees,checks the bill payment status of his users and resets the account
after successful payment of the bill.

Employee selects within the existing user list and calculates their electricity
usage and generates bill. This bill is reflected in the user account for payment.
Employee can also view general details of his users.

There are two types of users, Domestic and Commercial. The charges for per
unit consumption of electricity is different for both kinds of users and the bill is
generated accordingly by the employee. User can view the bill details and
proceed to make payments online using credit card. The system will look after
the users bank balance details and processes the payment only if the balance is
sufficient. The amount gets deducted from user account and Admin will look
through it and updates the user's bill status.

### Assumptions:
Admin should be present from the beginning in the system. The
employers should be present to facilitate users to perform their tasks. Bill is
visible to the user only after the employee generates it. Admin and users’ bank
accounts should be linked to the system in order to make payments.