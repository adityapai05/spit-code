-- 1. List names of depositors having same branch as the branch ofSUNIL.
SELECT d.cname
FROM deposit_40 d, deposit_40 s
WHERE
    d.bname = s.bname
    AND s.cname = 'sunil';

-- 2. List LoanNo and LoanAmount of borrowers having the samebranch as the of depositor SUNIL.
SELECT b.loan_no, b.amount
FROM borrow_40 b, deposit_40 d
WHERE
    b.bname = d.bname
    AND d.cname = 'sunil';

-- 3. List all depositors living in NAGPUR.
SELECT d.cname
FROM deposit_40 d, customer_40 c
WHERE
    d.cname = c.cname
    AND c.city = 'nagpur';

-- 4. List all depositors having deposit in all the branches whereSUNIL is having account.
SELECT d.cname
FROM deposit_40 d, deposit_40 s
WHERE
    d.bname = s.bname
    AND s.cname = 'sunil'
GROUP BY
    d.cname
HAVING
    COUNT(DISTINCT d.bname) = (
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
SELECT d.cname
FROM deposit_40 d, customer_40 c
WHERE
    d.cname = c.cname
    AND c.city = 'nagpur'
    AND d.amount = (
        SELECT MAX(d2.amount)
        FROM deposit_40 d2, customer_40 c2
        WHERE
            d2.cname = c2.cname
            AND c2.city = 'nagpur'
    );

-- 7. List the names of branches having highest number ofdepositors.
SELECT b.bname
FROM branch_40 b
    LEFT JOIN deposit_40 d ON b.bname = d.bname
GROUP BY
    b.bname
HAVING
    COUNT(d.cname) = (
        SELECT MAX(total)
        FROM (
                SELECT COUNT(d2.cname) AS total
                FROM branch_40 b2
                    LEFT JOIN deposit_40 d2 ON b2.bname = d2.bname
                GROUP BY
                    b2.bname
            ) x
    );

-- 8. List the highest deposit of the city where branch of Sunil islocated.
SELECT MAX(d.amount) AS highest_deposit
FROM deposit_40 d, branch_40 b
WHERE
    d.bname = b.bname
    AND b.city IN (
        SELECT b2.city
        FROM deposit_40 s, branch_40 b2
        WHERE
            s.bname = b2.bname
            AND s.cname = 'sunil'
    );

-- 9. List the names of customers having more deposit than theaverage deposit in their respective branches.
SELECT d.cname
FROM deposit_40 d
WHERE
    d.amount > (
        SELECT AVG(d2.amount)
        FROM deposit_40 d2
        WHERE
            d2.bname = d.bname
    );

-- 10. List the names of branches where number of depositors lessthan 2.
SELECT b.bname
FROM branch_40 b
    LEFT JOIN deposit_40 d ON b.bname = d.bname
GROUP BY
    b.bname
HAVING
    COUNT(d.cname) < 2;

-- 11. Count the number of customers living in the city where branchis located.
SELECT COUNT(DISTINCT c.cname) AS total_customers
FROM customer_40 c, branch_40 b
WHERE
    c.city = b.city;

-- 12. Change the living city of the VRCE branch borrowers toNagpur.
UPDATE customer_40 c
JOIN borrow_40 b ON c.cname = b.cname
SET
    c.city = 'nagpur'
WHERE
    b.bname = 'vrce';

-- 13. Update deposit of Anil. Give him maximum deposit fromdepositors living in city Nagpur.
UPDATE deposit_40 d
JOIN customer_40 c ON d.cname = c.cname
SET
    d.amount = (
        SELECT MAX(d2.amount)
        FROM deposit_40 d2, customer_40 c2
        WHERE
            d2.cname = c2.cname
            AND c2.city = 'nagpur'
    )
WHERE
    d.cname = 'anil';

-- 14. Transfer Rs. 100 from account Anil to account Sunil if both arehaving the same branch.
UPDATE deposit_40 a
JOIN deposit_40 s ON a.bname = s.bname
SET
    a.amount = a.amount - 100
WHERE
    a.cname = 'anil'
    AND s.cname = 'sunil'
    AND a.amount >= 100;

UPDATE deposit_40 a
JOIN deposit_40 s ON a.bname = s.bname
SET
    s.amount = s.amount + 100
WHERE
    a.cname = 'anil'
    AND s.cname = 'sunil'
    AND a.amount >= 0;

-- 15. Add Rs. 100 to the account of all those depositors who arehaving the highest deposit amount in their respective branches.
UPDATE deposit_40 d
JOIN deposit_40 d2 ON d.bname = d2.bname
SET
    d.amount = d.amount + 100
WHERE
    d.amount = (
        SELECT MAX(amount)
        FROM deposit_40
        WHERE
            bname = d.bname
    );

-- 16. Delete branches having deposit from Nagpur.
DELETE b
FROM branch_40 b
    JOIN deposit_40 d ON b.bname = d.bname
WHERE
    b.city = 'nagpur';

-- 17. Delete deposit of Anil and Sunil if both are living in the samecity.
DELETE d
FROM
    deposit_40 d,
    customer_40 a,
    customer_40 s
WHERE
    d.cname IN ('anil', 'sunil')
    AND a.cname = 'anil'
    AND s.cname = 'sunil'
    AND a.city = s.city;

-- 18. Delete borrower of branches having minimum number ofcustomers.
DELETE b
FROM borrow_40 b
    JOIN branch_40 br ON b.bname = br.bname
WHERE (
        SELECT COUNT(*)
        FROM customer_40 c
        WHERE
            c.city = br.city
    ) = (
        SELECT MIN(total)
        FROM (
                SELECT COUNT(*) AS total
                FROM branch_40 br2, customer_40 c2
                WHERE
                    br2.city = c2.city
                GROUP BY
                    br2.city
            ) x
    );

-- 19. List names of customers who are depositors as well asborrowers.
SELECT d.cname
FROM deposit_40 d, borrow_40 b
WHERE
    d.cname = b.cname;

-- 20. List all the customers who are depositors but not borrowers.
SELECT DISTINCT
    d.cname
FROM deposit_40 d
    LEFT JOIN borrow_40 b ON d.cname = b.cname
WHERE
    b.cname IS NULL;

-- 21. List the depositors having the same living city as Sunil and thesame branch city as Anil.
SELECT d.cname
FROM
    deposit_40 d,
    customer_40 c,
    customer_40 s,
    branch_40 db,
    deposit_40 ad,
    branch_40 ab
WHERE
    d.cname = c.cname
    AND s.cname = 'sunil'
    AND c.city = s.city
    AND d.bname = db.bname
    AND ad.cname = 'anil'
    AND ad.bname = ab.bname
    AND db.city = ab.city;

-- 22. List the depositors having amount less than 5000 and living inthe city as Shivani.
SELECT d.cname
FROM
    deposit_40 d,
    customer_40 c,
    customer_40 s
WHERE
    d.cname = c.cname
    AND s.cname = 'shivani'
    AND c.city = s.city
    AND d.amount < 5000;

-- 23. List the customers who are borrowers or depositors and havingliving city Mumbai andthebranch city same as that of Sandip.
SELECT c.cname
FROM
    customer_40 c,
    borrow_40 br,
    branch_40 b
WHERE
    c.cname = br.cname
    AND br.bname = b.bname
    AND c.city = 'mumbai'
    AND b.city IN (
        SELECT sb.city
        FROM deposit_40 sd, branch_40 sb
        WHERE
            sd.bname = sb.bname
            AND sd.cname = 'sandip'
    )
UNION
SELECT c.cname
FROM
    customer_40 c,
    deposit_40 d,
    branch_40 b
WHERE
    c.cname = d.cname
    AND d.bname = b.bname
    AND c.city = 'mumbai'
    AND b.city IN (
        SELECT sb.city
        FROM deposit_40 sd, branch_40 sb
        WHERE
            sd.bname = sb.bname
            AND sd.cname = 'sandip'
    );

-- 24. List the branch name and branch wise deposit.
SELECT b.bname, SUM(d.amount) AS total_deposit
FROM branch_40 b, deposit_40 d
WHERE
    b.bname = d.bname
GROUP BY
    b.bname;

-- 25. Add 100 to the amount of all depositors having deposit higherthan the average deposit of their branch.
UPDATE deposit_40 d
JOIN deposit_40 d2 ON d.bname = d2.bname
SET
    d.amount = d.amount + 100
WHERE
    d.amount > (
        SELECT AVG(amount)
        FROM deposit_40
        WHERE
            bname = d.bname
    );

-- 26. List names of depositors who has third highest amount.
SELECT d.cname
FROM deposit_40 d
WHERE
    d.amount = (
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