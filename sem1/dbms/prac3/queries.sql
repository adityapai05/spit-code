-- 1. List names of depositors having same branch as the branch of SUNIL.
SELECT cname
FROM deposit_40
WHERE bname = (
    SELECT bname
    FROM deposit_40
    WHERE cname = 'sunil'
)
AND cname != 'sunil';


-- 2. List LoanNo and LoanAmount of borrowers having the same branch as the depositor SUNIL.
SELECT loan_no, amount
FROM borrow_40
WHERE bname = (
    SELECT bname
    FROM deposit_40
    WHERE cname = 'sunil'
)
AND cname != 'sunil';


-- 3. List all depositors living in NAGPUR.
SELECT cname
FROM deposit_40
WHERE cname IN (
    SELECT cname
    FROM customer_40
    WHERE city = 'nagpur'
);


-- 4. List all depositors having deposit in all the branches where SUNIL is having account.
SELECT cname
FROM deposit_40
WHERE bname IN (
    SELECT bname
    FROM deposit_40
    WHERE cname = 'sunil'
)
OR bname IN (
    SELECT bname
    FROM borrow_40
    WHERE cname = 'sunil'
);


-- 5. List names of customers having maximum deposit.
SELECT cname
FROM deposit_40
WHERE amount IN (
    SELECT MAX(amount)
    FROM deposit_40
);


-- 6. List names of customers having maximum deposit among customers living in Nagpur.
SELECT cname
FROM deposit_40
WHERE amount = (
    SELECT MAX(amount)
    FROM deposit_40
    WHERE cname IN (
        SELECT cname
        FROM customer_40
        WHERE city = 'nagpur'
    )
);


-- 7. List the names of branches having highest number of depositors.
SELECT bname
FROM deposit_40
GROUP BY bname
HAVING COUNT(cname) >= ALL (
    SELECT COUNT(cname)
    FROM deposit_40
    GROUP BY bname
);


-- 8. List the highest deposit of the city where branch of Sunil is located.
SELECT MAX(amount)
FROM deposit_40
WHERE bname IN (
    SELECT bname
    FROM branch_40
    WHERE city = (
        SELECT city
        FROM branch_40
        WHERE bname = (
            SELECT bname
            FROM deposit_40
            WHERE cname = 'sunil'
        )
    )
);


-- 9. List the names of customers having more deposit than the average deposit in their respective branches.
SELECT d.cname
FROM deposit_40 d
WHERE d.amount > (
    SELECT AVG(d2.amount)
    FROM deposit_40 d2
    WHERE d2.bname = d.bname
);


-- 10. List the names of branches where number of depositors is less than 2.
SELECT bname
FROM deposit_40
GROUP BY bname
HAVING COUNT(cname) < 2;


-- 11. Count the number of customers living in the city where branch is located.
SELECT COUNT(cname)
FROM customer_40
WHERE city IN (
    SELECT city
    FROM branch_40
);


-- 12. Change the living city of the VRCE branch borrowers to Nagpur.
UPDATE customer_40
SET city = 'nagpur'
WHERE cname IN (
    SELECT cname
    FROM borrow_40
    WHERE bname = 'vrce'
);


-- 13. Update deposit of Anil. Give him maximum deposit from depositors living in city Nagpur.
UPDATE deposit_40
SET amount = (
    SELECT MAX(amount)
    FROM deposit_40
    WHERE bname IN (
        SELECT bname
        FROM branch_40
        WHERE city = 'nagpur'
    )
)
WHERE cname = 'anil';


-- 14. Transfer Rs. 100 from account Anil to account Sunil if both are having the same branch.
UPDATE deposit_40
SET amount = amount - 100
WHERE cname = 'anil'
AND bname = (
    SELECT bname
    FROM deposit_40
    WHERE cname = 'sunil'
);

UPDATE deposit_40
SET amount = amount + 100
WHERE cname = 'sunil'
AND bname = (
    SELECT bname
    FROM deposit_40
    WHERE cname = 'anil'
);


-- 15. Add Rs. 100 to the account of all those depositors who are having the highest deposit amount in their respective branches.
UPDATE deposit_40
SET amount = amount + 100
WHERE amount IN (
    SELECT MAX(amount)
    FROM deposit_40
    GROUP BY bname
);


-- 16. Delete branches having deposit from Nagpur.
DELETE FROM branch_40
WHERE city = 'nagpur'
AND bname IN (
    SELECT bname
    FROM deposit_40
);


-- 17. Delete deposit of Anil and Sunil if both are living in the same city.
DELETE FROM deposit_40
WHERE cname IN ('anil', 'sunil')
AND (
    SELECT city
    FROM customer_40
    WHERE cname = 'anil'
) = (
    SELECT city
    FROM customer_40
    WHERE cname = 'sunil'
);


-- 18. Delete borrowers of branches having minimum number of customers.
DELETE FROM borrow_40
WHERE bname IN (
    SELECT bname
    FROM (
        SELECT bname
        FROM borrow_40
        GROUP BY bname
        HAVING COUNT(cname) <= ALL (
            SELECT COUNT(cname)
            FROM borrow_40
            GROUP BY bname
        )
    ) AS temp
);


-- 19. List names of customers who are depositors as well as borrowers.
SELECT cname
FROM customer_40
WHERE cname IN (
    SELECT cname
    FROM deposit_40
)
AND cname IN (
    SELECT cname
    FROM borrow_40
);


-- 20. List all the customers who are depositors but not borrowers.
SELECT cname
FROM customer_40
WHERE cname IN (
    SELECT cname
    FROM deposit_40
)
AND cname NOT IN (
    SELECT cname
    FROM borrow_40
);


-- 21. List the depositors having the same living city as Sunil and the same branch city as Anil.
SELECT d.cname
FROM deposit_40 d
WHERE d.cname IN (
    SELECT cname
    FROM customer_40
    WHERE city = (
        SELECT city
        FROM customer_40
        WHERE cname = 'sunil'
    )
)
AND d.bname IN (
    SELECT bname
    FROM branch_40
    WHERE city = (
        SELECT city
        FROM branch_40
        WHERE bname = (
            SELECT bname
            FROM deposit_40
            WHERE cname = 'anil'
        )
    )
);


-- 22. List the depositors having amount less than 5000 and living in the city as Shivani.
SELECT cname
FROM deposit_40
WHERE amount < 5000
AND cname IN (
    SELECT cname
    FROM customer_40
    WHERE city = (
        SELECT city
        FROM customer_40
        WHERE cname = 'shivani'
    )
);


-- 23. List the customers who are borrowers or depositors and having living city Mumbai and branch city same as that of Sandip.
SELECT cname
FROM customer_40
WHERE city = 'mumbai'
AND cname IN (
    SELECT cname
    FROM deposit_40
    WHERE bname IN (
        SELECT bname
        FROM branch_40
        WHERE city = (
            SELECT city
            FROM branch_40
            WHERE bname IN (
                SELECT bname
                FROM deposit_40
                WHERE cname = 'sandip'
            )
        )
    )
    UNION
    SELECT cname
    FROM borrow_40
    WHERE bname IN (
        SELECT bname
        FROM branch_40
        WHERE city = (
            SELECT city
            FROM branch_40
            WHERE bname IN (
                SELECT bname
                FROM deposit_40
                WHERE cname = 'sandip'
            )
        )
    )
);


-- 24. List the branch name and branch wise deposit.
SELECT bname, SUM(amount) AS total_deposit
FROM deposit_40
GROUP BY bname;


-- 25. Add 100 to the amount of all depositors having deposit higher than the average deposit of their branch.
UPDATE deposit_40 d
SET amount = amount + 100
WHERE amount > (
    SELECT AVG(d2.amount)
    FROM deposit_40 d2
    WHERE d2.bname = d.bname
);


-- 26. List names of depositors who have third highest amount.
SELECT cname
FROM deposit_40
WHERE amount = (
    SELECT MAX(amount)
    FROM deposit_40
    WHERE amount < (
        SELECT MAX(amount)
        FROM deposit_40
        WHERE amount < (
            SELECT MAX(amount)
            FROM deposit_40
        )
    )
);


-- 27. List details of depositors according to ascending order of customer names.
SELECT *
FROM deposit_40
ORDER BY cname ASC;