-- 1. List names of depositors having same branch as the branch of SUNIL.

SELECT d1.cname
FROM deposit_40 d1
    JOIN deposit_40 d2 ON d1.bname = d2.bname
WHERE
    d2.cname = 'sunil'
    AND d1.cname != 'sunil';

-- 2. List LoanNo and LoanAmount of borrowers having the same branch as the depositor SUNIL.

SELECT b.loan_no, b.amount
FROM borrow_40 b
    JOIN deposit_40 d ON b.bname = d.bname
WHERE
    d.cname = 'sunil';

-- 3. List all depositors living in NAGPUR.

SELECT d.cname
FROM deposit_40 d
    JOIN customer_40 c ON d.cname = c.cname
WHERE
    c.city = 'nagpur';

-- 4. List all depositors having deposit in all the branches where SUNIL is having account.

SELECT DISTINCT
    d1.cname
FROM deposit_40 d1
    JOIN deposit_40 d2 ON d1.bname = d2.bname
WHERE
    d2.cname = 'sunil'
    AND d1.cname != 'sunil';

-- 5. List names of customers having maximum deposit.

SELECT d.cname
FROM deposit_40 d
    JOIN (
        SELECT MAX(amount) AS max_amount
        FROM deposit_40
    ) m ON d.amount = m.max_amount;

-- 6. List names of customers having maximum deposit among customers living in Nagpur.

SELECT d.cname
FROM
    deposit_40 d
    JOIN customer_40 c ON d.cname = c.cname
    JOIN (
        SELECT MAX(d2.amount) AS max_amount
        FROM deposit_40 d2
            JOIN customer_40 c2 ON d2.cname = c2.cname
        WHERE
            c2.city = 'nagpur'
    ) m ON d.amount = m.max_amount
WHERE
    c.city = 'nagpur';

-- 7. List the names of branches having highest number of depositors.

SELECT d1.bname
FROM deposit_40 d1
    LEFT JOIN deposit_40 d2 ON d1.bname = d2.bname
GROUP BY
    d1.bname
HAVING
    COUNT(d2.cname) >= ALL (
        SELECT COUNT(cname)
        FROM deposit_40
        GROUP BY
            bname
    );

-- 8. List the highest deposit of the city where branch of Sunil is located.

SELECT MAX(d.amount)
FROM
    deposit_40 d
    JOIN branch_40 b ON d.bname = b.bname
    JOIN branch_40 sb ON b.city = sb.city
    JOIN deposit_40 s ON sb.bname = s.bname
WHERE
    s.cname = 'sunil';

-- 9. List the names of customers having more deposit than the average deposit in their respective branches.

SELECT d.cname
FROM deposit_40 d
    JOIN (
        SELECT bname, AVG(amount) AS avg_amount
        FROM deposit_40
        GROUP BY
            bname
    ) a ON d.bname = a.bname
WHERE
    d.amount > a.avg_amount;

-- 10. List the names of branches where number of depositors is less than 2.

SELECT b.bname
FROM branch_40 b
    LEFT JOIN deposit_40 d ON b.bname = d.bname
GROUP BY
    b.bname
HAVING
    COUNT(d.cname) < 2;

-- 11. Count the number of customers living in the city where branch is located.

SELECT COUNT(DISTINCT c.cname)
FROM customer_40 c
    JOIN branch_40 b ON c.city = b.city;

-- 12. Change the living city of the VRCE branch borrowers to Nagpur.

UPDATE customer_40 c
JOIN borrow_40 b ON c.cname = b.cname
SET
    c.city = 'nagpur'
WHERE
    b.bname = 'vrce';

-- 13. Update deposit of Anil. Give him maximum deposit from depositors living in city Nagpur.

UPDATE deposit_40 d
JOIN (
    SELECT MAX(d2.amount) AS max_amount
    FROM deposit_40 d2
        JOIN customer_40 c ON d2.cname = c.cname
    WHERE
        c.city = 'nagpur'
) m ON 1 = 1
SET
    d.amount = m.max_amount
WHERE
    d.cname = 'anil';

-- 14. Transfer Rs. 100 from account Anil to account Sunil if both are having the same branch.

UPDATE deposit_40 a
JOIN deposit_40 s ON a.bname = s.bname
SET
    a.amount = a.amount - 100,
    s.amount = s.amount + 100
WHERE
    a.cname = 'anil'
    AND s.cname = 'sunil';

-- 15. Add Rs. 100 to the account of all those depositors who are having the highest deposit amount in their respective branches.

UPDATE deposit_40 d
LEFT JOIN deposit_40 d2 ON d.bname = d2.bname
AND d2.amount > d.amount
SET
    d.amount = d.amount + 100
WHERE
    d2.actno IS NULL;

-- 16. Delete branches having deposit from Nagpur.

DELETE b
FROM branch_40 b
    JOIN deposit_40 d ON b.bname = d.bname
WHERE
    b.city = 'nagpur';

-- 17. Delete deposit of Anil and Sunil if both are living in the same city.

DELETE d
FROM
    deposit_40 d
    JOIN customer_40 a ON a.cname = 'anil'
    JOIN customer_40 s ON s.cname = 'sunil'
WHERE
    d.cname IN ('anil', 'sunil')
    AND a.city = s.city;

-- 18. Delete borrowers of branches having minimum number of customers.

DELETE b
FROM borrow_40 b
    JOIN (
        SELECT b1.bname
        FROM borrow_40 b1
            LEFT JOIN borrow_40 b2 ON b1.bname = b2.bname
        GROUP BY
            b1.bname
        HAVING
            COUNT(b2.cname) <= ALL (
                SELECT COUNT(cname)
                FROM borrow_40
                GROUP BY
                    bname
            )
    ) m ON b.bname = m.bname;

-- 19. List names of customers who are depositors as well as borrowers.

SELECT DISTINCT
    c.cname
FROM
    customer_40 c
    JOIN deposit_40 d ON c.cname = d.cname
    JOIN borrow_40 b ON c.cname = b.cname;

-- 20. List all the customers who are depositors but not borrowers.

SELECT DISTINCT
    c.cname
FROM
    customer_40 c
    JOIN deposit_40 d ON c.cname = d.cname
    LEFT JOIN borrow_40 b ON c.cname = b.cname
WHERE
    b.cname IS NULL;

-- 21. List the depositors having the same living city as Sunil and the same branch city as Anil.

SELECT DISTINCT
    d.cname
FROM
    deposit_40 d
    JOIN customer_40 c ON d.cname = c.cname
    JOIN customer_40 s ON c.city = s.city
    JOIN branch_40 b ON d.bname = b.bname
    JOIN deposit_40 a ON a.cname = 'anil'
    JOIN branch_40 ab ON a.bname = ab.bname
WHERE
    s.cname = 'sunil'
    AND b.city = ab.city;

-- 22. List the depositors having amount less than 5000 and living in the city as Shivani.

SELECT DISTINCT
    d.cname
FROM
    deposit_40 d
    JOIN customer_40 c ON d.cname = c.cname
    JOIN customer_40 s ON c.city = s.city
WHERE
    d.amount < 5000
    AND s.cname = 'shivani';

-- 23. List the customers who are borrowers or depositors and having living city Mumbai and branch city same as that of Sandip.

SELECT DISTINCT
    c.cname
FROM
    customer_40 c
    JOIN deposit_40 d ON c.cname = d.cname
    JOIN branch_40 b ON d.bname = b.bname
    JOIN deposit_40 s ON s.cname = 'sandip'
    JOIN branch_40 sb ON s.bname = sb.bname
WHERE
    c.city = 'mumbai'
    AND b.city = sb.city
UNION
SELECT DISTINCT
    c.cname
FROM
    customer_40 c
    JOIN borrow_40 br ON c.cname = br.cname
    JOIN branch_40 b ON br.bname = b.bname
    JOIN deposit_40 s ON s.cname = 'sandip'
    JOIN branch_40 sb ON s.bname = sb.bname
WHERE
    c.city = 'mumbai'
    AND b.city = sb.city;

-- 24. List the branch name and branch wise deposit.

SELECT b.bname, SUM(d.amount) AS total_deposit
FROM branch_40 b
    LEFT JOIN deposit_40 d ON b.bname = d.bname
GROUP BY
    b.bname;

-- 25. Add 100 to the amount of all depositors having deposit higher than the average deposit of their branch.

UPDATE deposit_40 d
JOIN (
    SELECT bname, AVG(amount) AS avg_amount
    FROM deposit_40
    GROUP BY
        bname
) a ON d.bname = a.bname
SET
    d.amount = d.amount + 100
WHERE
    d.amount > a.avg_amount;

-- 26. List names of depositors who have third highest amount.

SELECT d1.cname
FROM deposit_40 d1
    LEFT JOIN deposit_40 d2 ON d2.amount > d1.amount
GROUP BY
    d1.actno,
    d1.cname,
    d1.amount
HAVING
    COUNT(DISTINCT d2.amount) = 2;

-- 27. List details of depositors according to ascending order of customer names.

SELECT d.*
FROM deposit_40 d
    JOIN customer_40 c ON d.cname = c.cname
ORDER BY c.cname ASC;