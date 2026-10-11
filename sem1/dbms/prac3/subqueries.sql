-- 1. List names of depositors having same branch as the branch ofSUNIL.
SELECT cname
FROM deposit_40
WHERE
    bname IN (
        SELECT bname
        FROM deposit_40
        WHERE
            cname = 'sunil'
    );

-- 2. List LoanNo and LoanAmount of borrowers having the samebranch as the of depositor SUNIL.
SELECT loan_no, amount
FROM borrow_40
WHERE
    bname IN (
        SELECT bname
        FROM deposit_40
        WHERE
            cname = 'sunil'
    );

-- 3. List all depositors living in NAGPUR.
SELECT cname
FROM deposit_40
WHERE
    cname IN (
        SELECT cname
        FROM customer_40
        WHERE
            city = 'nagpur'
    );

-- 4. List all depositors having deposit in all the branches whereSUNIL is having account.
SELECT d.cname
FROM deposit_40 d
WHERE (
        SELECT COUNT(DISTINCT bname)
        FROM deposit_40
        WHERE
            cname = d.cname
            AND bname IN (
                SELECT bname
                FROM deposit_40
                WHERE
                    cname = 'sunil'
            )
    ) = (
        SELECT COUNT(DISTINCT bname)
        FROM deposit_40
        WHERE
            cname = 'sunil'
    );

-- 5. List names of customers having maximum deposit.
SELECT cname
FROM deposit_40
WHERE
    amount = (
        SELECT MAX(amount)
        FROM deposit_40
    );

-- 6. List names of customers having maximum deposit in thecustomers living in Nagpur.
SELECT cname
FROM deposit_40
WHERE
    cname IN (
        SELECT cname
        FROM customer_40
        WHERE
            city = 'nagpur'
    )
    AND amount = (
        SELECT MAX(amount)
        FROM deposit_40
        WHERE
            cname IN (
                SELECT cname
                FROM customer_40
                WHERE
                    city = 'nagpur'
            )
    );

-- 7. List the names of branches having highest number ofdepositors.
SELECT bname
FROM deposit_40
GROUP BY
    bname
HAVING
    COUNT(cname) >= ALL (
        SELECT total
        FROM (
                SELECT COUNT(cname) AS total
                FROM deposit_40
                GROUP BY
                    bname
            ) x
    );

-- 8. List the highest deposit of the city where branch of Sunil islocated.
SELECT MAX(amount) AS highest_deposit
FROM deposit_40
WHERE
    bname IN (
        SELECT bname
        FROM branch_40
        WHERE
            city IN (
                SELECT city
                FROM branch_40
                WHERE
                    bname IN (
                        SELECT bname
                        FROM deposit_40
                        WHERE
                            cname = 'sunil'
                    )
            )
    );

-- 9. List the names of customers having more deposit than theaverage deposit in their respective branches.
SELECT cname
FROM deposit_40 d
WHERE
    amount > (
        SELECT AVG(amount)
        FROM deposit_40
        WHERE
            bname = d.bname
    );

-- 10. List the names of branches where number of depositors lessthan 2.
SELECT bname
FROM branch_40
WHERE (
        SELECT COUNT(*)
        FROM deposit_40
        WHERE
            deposit_40.bname = branch_40.bname
    ) < 2;

-- 11. Count the number of customers living in the city where branchis located.
SELECT COUNT(*)
FROM customer_40
WHERE
    city IN (
        SELECT city
        FROM branch_40
    );

-- 12. Change the living city of the VRCE branch borrowers toNagpur.
UPDATE customer_40
SET
    city = 'nagpur'
WHERE
    cname IN (
        SELECT cname
        FROM borrow_40
        WHERE
            bname = 'vrce'
    );

-- 13. Update deposit of Anil. Give him maximum deposit fromdepositors living in city Nagpur.
UPDATE deposit_40
SET
    amount = (
        SELECT MAX(amount)
        FROM (
                SELECT d.amount
                FROM deposit_40 d
                WHERE
                    d.cname IN (
                        SELECT cname
                        FROM customer_40
                        WHERE
                            city = 'nagpur'
                    )
            ) x
    )
WHERE
    cname = 'anil';

-- 14. Transfer Rs. 100 from account Anil to account Sunil if both arehaving the same branch.
UPDATE deposit_40
SET
    amount = amount - 100
WHERE
    cname = 'anil'
    AND amount >= 100
    AND bname IN (
        SELECT bname
        FROM deposit_40
        WHERE
            cname = 'sunil'
    );

UPDATE deposit_40
SET
    amount = amount + 100
WHERE
    cname = 'sunil'
    AND bname IN (
        SELECT bname
        FROM deposit_40
        WHERE
            cname = 'anil'
    );

-- 15. Add Rs. 100 to the account of all those depositors who arehaving the highest deposit amount in their respective branches.
UPDATE deposit_40
SET
    amount = amount + 100
WHERE (bname, amount) IN (
        SELECT bname, highest
        FROM (
                SELECT bname, MAX(amount) AS highest
                FROM deposit_40
                GROUP BY
                    bname
            ) x
    );

-- 16. Delete branches having deposit from Nagpur.
DELETE FROM branch_40
WHERE
    city = 'nagpur'
    AND bname IN (
        SELECT bname
        FROM deposit_40
    );

-- 17. Delete deposit of Anil and Sunil if both are living in the samecity.
DELETE FROM deposit_40
WHERE
    cname IN ('anil', 'sunil')
    AND (
        SELECT city
        FROM customer_40
        WHERE
            cname = 'anil'
    ) = (
        SELECT city
        FROM customer_40
        WHERE
            cname = 'sunil'
    );

-- 18. Delete borrower of branches having minimum number ofcustomers.
DELETE FROM borrow_40
WHERE
    bname IN (
        SELECT bname
        FROM branch_40
        WHERE
            city IN (
                SELECT city
                FROM customer_40
                GROUP BY
                    city
                HAVING
                    COUNT(*) = (
                        SELECT MIN(total)
                        FROM (
                                SELECT COUNT(*) AS total
                                FROM customer_40
                                GROUP BY
                                    city
                            ) x
                    )
            )
    );

-- 19. List names of customers who are depositors as well asborrowers.
SELECT cname
FROM deposit_40
WHERE
    cname IN (
        SELECT cname
        FROM borrow_40
    );

-- 20. List all the customers who are depositors but not borrowers.
SELECT cname
FROM deposit_40
WHERE
    cname NOT IN(
        SELECT cname
        FROM borrow_40
    );

-- 21. List the depositors having the same living city as Sunil and thesame branch city as Anil.
SELECT cname
FROM deposit_40
WHERE
    cname IN (
        SELECT cname
        FROM customer_40
        WHERE
            city = (
                SELECT city
                FROM customer_40
                WHERE
                    cname = 'sunil'
            )
    )
    AND bname IN (
        SELECT bname
        FROM branch_40
        WHERE
            city IN (
                SELECT city
                FROM branch_40
                WHERE
                    bname IN (
                        SELECT bname
                        FROM deposit_40
                        WHERE
                            cname = 'anil'
                    )
            )
    );

-- 22. List the depositors having amount less than 5000 and living inthe city as Shivani.
SELECT cname
FROM deposit_40
WHERE
    amount < 5000
    AND cname IN (
        SELECT cname
        FROM customer_40
        WHERE
            city = (
                SELECT city
                FROM customer_40
                WHERE
                    cname = 'shivani'
            )
    );

-- 23. List the customers who are borrowers or depositors and havingliving city Mumbai andthebranch city same as that of Sandip.
SELECT cname
FROM customer_40
WHERE
    city = 'mumbai'
    AND cname IN (
        SELECT cname
        FROM borrow_40
        WHERE
            bname IN (
                SELECT bname
                FROM branch_40
                WHERE
                    city IN (
                        SELECT city
                        FROM branch_40
                        WHERE
                            bname IN (
                                SELECT bname
                                FROM deposit_40
                                WHERE
                                    cname = 'sandip'
                            )
                    )
            )
    )
    OR city = 'mumbai'
    AND cname IN (
        SELECT cname
        FROM deposit_40
        WHERE
            bname IN (
                SELECT bname
                FROM branch_40
                WHERE
                    city IN (
                        SELECT city
                        FROM branch_40
                        WHERE
                            bname IN (
                                SELECT bname
                                FROM deposit_40
                                WHERE
                                    cname = 'sandip'
                            )
                    )
            )
    );

-- 24. List the branch name and branch wise deposit.
SELECT bname, SUM(amount) AS total_deposit
FROM deposit_40
GROUP BY
    bname;

-- 25. Add 100 to the amount of all depositors having deposit higherthan the average deposit of their branch.
UPDATE deposit_40 d
SET
    amount = amount + 100
WHERE
    amount > (
        SELECT AVG(amount)
        FROM (
                SELECT bname, amount
                FROM deposit_40
            ) x
        WHERE
            x.bname = d.bname
    );

-- 26. List names of depositors who has third highest amount.
SELECT cname
FROM deposit_40
WHERE
    amount = (
        SELECT DISTINCT
            amount
        FROM deposit_40
        ORDER BY amount DESC
        LIMIT 1
        OFFSET
            2
    );

-- 27. List details of depositors according to ascending order ofcustomer names.
SELECT * FROM deposit_40 ORDER BY cname ASC;