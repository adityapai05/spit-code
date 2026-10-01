-- 1) List all data from deposit table.

SELECT *
FROM deposit_40;


-- 2) List all data from borrow table.

SELECT *
FROM borrow_40;


-- 3) List names of customers living in Nagpur City.

SELECT cname
FROM customer_40
WHERE city = 'nagpur';


-- 4) List names of borrowers having loan number 206.

SELECT cname
FROM borrow_40
WHERE loan_no = 206;


-- 5) List names of depositors having amount greater than 4000.

SELECT cname
FROM deposit_40
WHERE amount > 4000;


-- 6) List names of customers who opened account after date 1/12/95.

SELECT cname
FROM deposit_40
WHERE adate > '1995-12-01';


-- 7) List name of the city where the Karol Bagh branch is located.

SELECT city
FROM branch_40
WHERE bname = 'karolbagh';


-- 8) List total loan.

SELECT SUM(amount) as 'Total Loan'
FROM borrow_40;


-- 9) List total number of customer cities.

SELECT COUNT(DISTINCT city) as 'Total Customer Cities'
FROM customer_40;


-- 10) Count total number of customers.

SELECT COUNT(*) as 'Total Customers'
FROM customer_40;


-- 11) List maximum loan from VRCE branch.

SELECT MAX(amount) as 'Maximum Loan from VRCE Branch'
FROM borrow_40
WHERE bname = 'vrce';


-- 12) Add 10% interest to all depositors.

UPDATE deposit_40
SET amount = amount + (amount * 10 / 100);


-- 13) Add 10% interest to all depositors having VRCE branch.

UPDATE deposit_40
SET amount = amount + (amount * 10 / 100)
WHERE bname = 'vrce';


-- 14) Delete depositors if the branch is Virar and the depositor name is Shivani.

DELETE FROM deposit_40
WHERE bname = 'virar'
  AND cname = 'shivani';


-- 15) Delete customers from Mumbai City.

DELETE FROM customer_40
WHERE city = 'mumbai';


-- 16) Delete depositor having deposit less than 5000.

DELETE FROM deposit_40
WHERE amount < 5000;