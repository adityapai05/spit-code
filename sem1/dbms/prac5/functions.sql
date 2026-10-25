USE classicmodels;

-- Drop existing functions before recreating them
DROP FUNCTION IF EXISTS calculateCube;
DROP FUNCTION IF EXISTS findCityFromOfficeCode;
DROP FUNCTION IF EXISTS findHighestMSRP;
DROP FUNCTION IF EXISTS findHighestCreditLimit;


-- 1. Function to find the cube of a number

DELIMITER //

CREATE FUNCTION calculateCube(num INT)
RETURNS INT
DETERMINISTIC
BEGIN
    DECLARE num_cube INT;

    SET num_cube = num * num * num;

    RETURN num_cube;
END //

DELIMITER ;


-- Execution
SELECT calculateCube(5) AS "Cube";


-- 2. Function to return the city for a given officeCode

DELIMITER //

CREATE FUNCTION findCityFromOfficeCode(
    officeCodeVar VARCHAR(10)
)
RETURNS VARCHAR(50)
DETERMINISTIC
BEGIN
    DECLARE cityVar VARCHAR(50);

    SELECT city
    INTO cityVar
    FROM offices
    WHERE officeCode = officeCodeVar;

    RETURN cityVar;
END //

DELIMITER ;


-- Execution
SELECT findCityFromOfficeCode('1') AS City;


-- 3. Function to find the highest MSRP for each product line
-- using a window function

DELIMITER //

CREATE FUNCTION findHighestMSRP(
    productLineVar VARCHAR(50)
)
RETURNS DECIMAL(10,2)
NOT DETERMINISTIC
READS SQL DATA
BEGIN
    DECLARE highestMSRP DECIMAL(10,2);

    SELECT MAX(MSRP)
    INTO highestMSRP
    FROM (
        SELECT
            productLine,
            MSRP,
            MAX(MSRP) OVER (
                PARTITION BY productLine
            ) AS maxMSRP
        FROM products
    ) AS productData
    WHERE productLine = productLineVar;

    RETURN highestMSRP;
END //

DELIMITER ;


-- Execution
SELECT DISTINCT
    productLine,
    findHighestMSRP(productLine) AS Highest_MSRP
FROM products
ORDER BY productLine;


-- 4. Function to return the customer with the highest credit limit

DELIMITER //

CREATE FUNCTION findHighestCreditLimit()
RETURNS VARCHAR(50)
NOT DETERMINISTIC
READS SQL DATA
BEGIN
    DECLARE custName VARCHAR(50);

    SELECT customerName
    INTO custName
    FROM customers
    WHERE creditLimit = (
        SELECT MAX(creditLimit)
        FROM customers
    )
    LIMIT 1;

    RETURN custName;
END //

DELIMITER ;


-- Execution
SELECT findHighestCreditLimit() AS Customer_Name;